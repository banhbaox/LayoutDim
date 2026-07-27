#include "StdAfx.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>

#include "ck_sdk.h"
#include "ck_attr.h"
#include "Funcs.h"

static const std::wstring kTubeGeoLevelNum = L"2.1";
static const double kDimOffset   = 25.0;
static const double kEndpointTol = 0.001;

static double Dist3D(const CKSCoord& a, const CKSCoord& b)
    {
    double dx = a.m_dX - b.m_dX, dy = a.m_dY - b.m_dY, dz = a.m_dZ - b.m_dZ;
    return sqrt(dx*dx + dy*dy + dz*dz);
    }

static bool IsOnTubeGeoLevel(CKPart& part, CKSEntity& ent)
    {
    CKSLevel level;
    if(part.GetEntityLevel(ent, level) != CK_NOERROR || !level.IsValid()) return false;
    std::wstring num;
    if(part.GetLevelInfo(level, NULL, &num, NULL, NULL, NULL) != CK_NOERROR) return false;
    return num == kTubeGeoLevelNum;
    }

// GetLine/GetArc with &drawInst return layout sheet-space coords.
// nDispView = 0 keeps the dim on the layout sheet (sheet-space); using the actual
// display view number tells KC to place the dim in 3D model space, which mismatches
// the sheet-space coords from GetLine(&drawInst) and puts the dim far off-screen.
//
// Round 1 (see git history) hand-computed dAxisAngle=atan2(dy,dx) alone against the
// generic active CPlane matrix - still produced horizontal-only dimensions. Round 2
// switched pMatrix to the instance's own view orientation (GetInstAttributes'
// pViewMat) but replaced dAxisAngle with a flat 0.0, relying on SetAligned(true) to
// derive the angle - line 1 (whose direction IS this view's own X axis, see
// BuildBendViewMatrix in TubeMakerFuncs.cpp) came out aligned by coincidence, with
// the right rotation but wrong origin; line 2 (a genuinely different direction) came
// out at line 1's angle instead of its own - dAxisAngle=0 always means "align with
// the matrix's own x-axis", not "derive per-line" as assumed.
//
// Round 3: dAxisAngle needs to be computed per-line after all, exactly like Round 1,
// but now measured against the CORRECT matrix (viewMat) instead of the generic
// CPlane - that specific combination was never tried. Also stripped viewMat's
// translation via TranslateTo(0,0,0), reasoning it was irrelevant to a pure
// rotation reference - this "fixed" the origin but only by accident, per Round 4.
//
// Round 4 (confirmed by the user manually toggling live in KeyCreator): the
// dimension's "Display Text in Detail Plane" checkbox (m_Format's CPlaneText,
// checked/true by default, never touched until now) makes KC compute TEXT
// orientation from the ACTIVE CPlane - a different, mismatched plane from
// viewMat - hence backwards text, independent of everything else being correct.
// Unchecking it in the UI fixed the text, but then broke the extension lines
// ("drawn to some invisible entity far away") - because with CPlaneText off, KC
// uses pMatrix's full transform (rotation AND translation) for placement, and
// Round 3's zeroed translation anchors that to world origin, nowhere near the
// actual part. So: SetCPlaneText(false) so text and geometry both consistently
// use viewMat instead of two different, mismatched planes.
//
// Round 5 tried making viewMat the session's real active CPlane (not just a
// per-call pMatrix argument) - origin bug persisted unchanged. Three different
// treatments of "the matrix/plane" (zeroed pMatrix translation, real pMatrix
// translation, session active CPlane) have now all failed to move the
// extension-line origin, while angle/value/text are all independently
// confirmed correct. Round 6 dropped pMatrix to NULL entirely - this DID fix
// the origin (extension lines correctly attach to the actual lines now), but
// regressed the angle back to horizontal-only. Per SDK.RTF, dAxisAngle is "the
// angle from the dimension matrix x-axis to the CPlane x-axis" - when
// pMatrix=NULL, "the dimension matrix" defaults to the current CPlane itself,
// so dAxisAngle ends up measuring a plane against itself: always a no-op,
// regardless of the value passed in. That explains the whole trade-off: a
// custom matrix gives dAxisAngle a real second reference (correct angle, wrong
// origin); no matrix collapses it to nothing (correct origin, wrong angle).
//
// Round 7: restore pMatrix=viewMat, but switch pFirstLoc/pSecondLoc from
// EndEntLoc (entity+drawInst-wrapped) to plain coordinate CKS::Location - every
// prior round using a custom matrix also used EndEntLoc, so the two were never
// tested apart. Hypothesis: EndEntLoc's own entity/instance-relative mapping
// plus a second, independent pMatrix transform double-applies, landing the
// origin far away regardless of the matrix's translation value. A bare
// coordinate Location only goes through pMatrix once. Losing entity
// associativity is fine here - this is a one-time placement, not a live-
// tracked reference back to the line.
static void DimLine(CKPart& part, CKSEntity& ent, CKSDrawInst& drawInst,
                    const CKSMatrix& viewMat, CKSDimensionOptions& opts)
    {
    CKSCoord ptStart, ptEnd;
    if(part.GetLine(ent, &drawInst, ptStart, ptEnd) != CK_NOERROR) return;

    double dx = ptEnd.m_dX - ptStart.m_dX;
    double dy = ptEnd.m_dY - ptStart.m_dY;
    double projLen = sqrt(dx*dx + dy*dy);
    if(projLen < 1e-10) return;

    double dAxisAngle = atan2(dy, dx) * 180.0 / M_PI;

    CKSCoord textPt(
        (ptStart.m_dX + ptEnd.m_dX) * 0.5 + (-dy / projLen) * kDimOffset,
        (ptStart.m_dY + ptEnd.m_dY) * 0.5 + ( dx / projLen) * kDimOffset,
        (ptStart.m_dZ + ptEnd.m_dZ) * 0.5);

    CKSRefLine refLine;
    refLine.m_ptStart = ptStart;
    refLine.m_ptEnd   = ptEnd;

    CKS::LocationPtr locFirst  = new CKS::Location(ptStart);
    CKS::LocationPtr locSecond = new CKS::Location(ptEnd);
    CKS::LocationPtr textLoc   = new CKS::Location(textPt);
    part.AddLinearDim(dAxisAngle, &refLine, locFirst, locSecond,
                      textLoc, &opts, 0, NULL, &viewMat);
    }

static void DimArc(CKPart& part, CKSEntity& ent, CKSDrawInst& drawInst,
                   const CKSMatrix& cplaneMat, CKSDimensionOptions& opts)
    {
    double dRad, dStartAng, dDeltaAng; CKEntityAttrib arcAttrib; CKSMatrix arcMatrix;
    if(part.GetArc(ent, &drawInst, &dRad, &dStartAng, &dDeltaAng,
                   &arcAttrib, &arcMatrix) != CK_NOERROR)
        return;

    double vals[4][4]; arcMatrix.GetValues(vals);
    CKSCoord center(vals[3][0], vals[3][1], vals[3][2]);

    CKSRefArc refArc;
    refArc.m_dRadius     = dRad;
    refArc.m_dStartAngle = dStartAng;
    refArc.m_dEndAngle   = dStartAng + dDeltaAng;
    refArc.m_ptCenter    = center;

    // Text at mid-arc, offset outward (all in sheet-space coords from GetArc(&drawInst))
    double midAng = dStartAng + dDeltaAng * 0.5;
    CKSCoord textPt(
        center.m_dX + cos(midAng) * dRad * 1.5,
        center.m_dY + sin(midAng) * dRad * 1.5,
        center.m_dZ);
    CKS::LocationPtr textLoc = new CKS::Location(textPt);
    part.AddCircularDim(refArc, &ent, textLoc, 0, &opts, NULL, NULL, &drawInst);
    }

// The angle between the two lines flanking a bend - the Detail/Angular/Two
// Lines (Ctrl+W) equivalent. Manufacturing convention (per user): always the
// value <= 180 degrees - bInnerAngle=false previously gave 351 degrees, i.e.
// exactly 360 minus the ~9 degree angle that bInnerAngle=true would have given
// directly. Since one of the two always sits <=180 and the other >=180 by
// construction, always requesting the inner one satisfies the rule with no
// extra per-bend logic needed.
//
// Round 1 used AddAngularDim's "Two Lines" overload (raw CKSEntity, no
// CKSDrawInst at all) with sheet-space textLoc/ckscAnglePick - measured "off in
// the distance", not touching the lines. That overload has no way to say which
// placed instance the raw model-space CKSEntity should be interpreted through,
// so it almost certainly resolves in Model/world space - sheet-space numbers
// fed into a world-space call would legitimately land nowhere near the bend.
//
// Round 2: switch to the OTHER AddAngularDim overload that takes CKSRefLine
// (not raw CKSEntity) + an explicit CKSDrawInst *pInst - the same shape of
// fields GetAngularDim/ModAngularDim round-trip for an EXISTING angular dim
// (see DimensionCreateFuncs1.cpp's ModAngularDim sample), so this is very
// likely what Ctrl+W's Two-Lines tool actually calls under the hood.
//
// Round 4: same CPlaneText fix as DimLine (see its comment) - SetCPlaneText(false)
// on angOpts (set in DimLayout).
//
// Round 6 dropped pMatrix to NULL, matching DimLine's change at the time.
//
// Round 7: restore pMatrix=viewMat, matching DimLine's latest change - this
// function never used EndEntLoc (refLine1/refLine2 are already bare CKSRefLine
// values, not entity-wrapped), so the "double transform" fix that motivated
// Round 7 in DimLine doesn't directly apply here, but keeping both dimension
// types on the same matrix strategy avoids testing them apart.
//
// UNVERIFIED, flag for Kubotek if still wrong: aLocations (CKS::LocationArray)
// has no create-from-scratch sample anywhere in the SDK - every existing use
// only reads it back from GetAngularDim on a dim made interactively. Passing
// it empty here as a best guess; if the dimension still misplaces, this exact
// parameter's required contents is the concrete question to ask.
static void DimAngle(CKPart& part, CKSEntity& line1, CKSEntity& line2,
                     CKSEntity& arc, CKSDrawInst& drawInst,
                     const CKSMatrix& viewMat, CKSDimensionOptions& opts)
    {
    CKSCoord l1s, l1e, l2s, l2e;
    if(part.GetLine(line1, &drawInst, l1s, l1e) != CK_NOERROR) return;
    if(part.GetLine(line2, &drawInst, l2s, l2e) != CK_NOERROR) return;

    // Fetch the arc's own sheet-space center (same coordinate space GetLine
    // above returns) rather than reusing the model-space center DimLayout
    // already computed for tangent-point matching - mixing the two spaces
    // would put textPt/ckscAnglePick nowhere near the actual bend on screen.
    double dRad, dStartAng, dDeltaAng; CKEntityAttrib arcAttrib; CKSMatrix arcMatrix;
    if(part.GetArc(arc, &drawInst, &dRad, &dStartAng, &dDeltaAng,
                   &arcAttrib, &arcMatrix) != CK_NOERROR)
        return;
    double vals[4][4]; arcMatrix.GetValues(vals);
    CKSCoord bendCenter(vals[3][0], vals[3][1], vals[3][2]);

    // Text at the bend center, offset outward along the average of both
    // lines' midpoint-to-center directions (roughly "away from the corner").
    CKSCoord mid1((l1s.m_dX + l1e.m_dX) * 0.5, (l1s.m_dY + l1e.m_dY) * 0.5, (l1s.m_dZ + l1e.m_dZ) * 0.5);
    CKSCoord mid2((l2s.m_dX + l2e.m_dX) * 0.5, (l2s.m_dY + l2e.m_dY) * 0.5, (l2s.m_dZ + l2e.m_dZ) * 0.5);
    CKSCoord textPt(
        bendCenter.m_dX - ((mid1.m_dX + mid2.m_dX) * 0.5 - bendCenter.m_dX) * 0.5,
        bendCenter.m_dY - ((mid1.m_dY + mid2.m_dY) * 0.5 - bendCenter.m_dY) * 0.5,
        bendCenter.m_dZ);

    CKSRefLine refLine1; refLine1.m_ptStart = l1s; refLine1.m_ptEnd = l1e;
    CKSRefLine refLine2; refLine2.m_ptStart = l2s; refLine2.m_ptEnd = l2e;

    CKS::LocationPtr textLoc = new CKS::Location(textPt);
    CKS::LocationArray emptyLocs;

    part.AddAngularDim(true /* always <= 180 degrees */, refLine1, refLine2,
                       emptyLocs, textLoc, &drawInst, &opts, &viewMat);
    }

int DimLayout()
    {
    CKPart part = CKGetActivePart();
    if(!part.IsValid()) return CKError;

    if(TRUE != part.InLayoutMode())
        { AfxMessageBox(L"Switch to Layout mode before running DimLayout."); return CKNoError; }

    CKSEntity selEntity; CKSDrawInst drawInst;
    switch(part.GetEnt(L"Click the bend arc to dimension (2 lines + arc will be added):",
                       selEntity, drawInst, 0))
        { case CKNoError: break; default: return CKNoError; }
    if(!selEntity.IsValid()) return CKNoError;

    CKMaskTypes entType;
    if(part.GetEntityType(selEntity, entType) != CK_NOERROR || entType != CKMaskArc)
        { AfxMessageBox(L"Please click directly on a bend arc (not a line or other entity)."); return CKNoError; }
    if(!IsOnTubeGeoLevel(part, selEntity))
        { AfxMessageBox(L"Selected arc is not on level 2.1 (TubeGeo)."); return CKNoError; }

    // Confirm TubeMaker has been run by checking for at least one "Bend" display view.
    bool hasBendViews = false;
    for(int n = 1; n <= 500; ++n)
        {
        std::wstring vname;
        if(part.GetDispViewName(n, vname) != CK_NOERROR) break;
        if(vname.size() >= 4 && vname.substr(0, 4) == L"Bend") { hasBendViews = true; break; }
        }
    if(!hasBendViews)
        { AfxMessageBox(L"No TubeMaker bend views found. Run TubeMaker first."); return CKNoError; }

    // Collect level-2.1 lines from the clicked drawing instance
    CKSEntityArray geom;
    if(part.GetInstanceGeometry(drawInst, geom) != CK_NOERROR)
        { AfxMessageBox(L"GetInstanceGeometry failed."); return CKError; }
    std::vector<CKSEntity> lines;
    for(size_t i = 0; i < geom.size(); ++i)
        {
        CKSEntity ent = geom[i]; if(!ent.IsValid() || !IsOnTubeGeoLevel(part, ent)) continue;
        CKMaskTypes t; if(part.GetEntityType(ent,t)==CK_NOERROR && t==CKMaskLine) lines.push_back(ent);
        }

    // Arc tangent endpoints in 3D world space (NULL = model coords) for line matching
    double dRad, dStartAng, dDeltaAng; CKEntityAttrib arcAttr; CKSMatrix arcMat;
    if(part.GetArc(selEntity, NULL, &dRad, &dStartAng, &dDeltaAng, &arcAttr, &arcMat) != CK_NOERROR)
        { AfxMessageBox(L"Failed to retrieve arc geometry."); return CKError; }
    double av[4][4]; arcMat.GetValues(av);
    CKSCoord center(av[3][0], av[3][1], av[3][2]);
    CKSCoord xAx(av[0][0], av[0][1], av[0][2]), yAx(av[1][0], av[1][1], av[1][2]);
    CKSCoord T1(
        center.m_dX + dRad*(cos(dStartAng)*xAx.m_dX + sin(dStartAng)*yAx.m_dX),
        center.m_dY + dRad*(cos(dStartAng)*xAx.m_dY + sin(dStartAng)*yAx.m_dY),
        center.m_dZ + dRad*(cos(dStartAng)*xAx.m_dZ + sin(dStartAng)*yAx.m_dZ));
    double endAng = dStartAng + dDeltaAng;
    CKSCoord T2(
        center.m_dX + dRad*(cos(endAng)*xAx.m_dX + sin(endAng)*yAx.m_dX),
        center.m_dY + dRad*(cos(endAng)*xAx.m_dY + sin(endAng)*yAx.m_dY),
        center.m_dZ + dRad*(cos(endAng)*xAx.m_dZ + sin(endAng)*yAx.m_dZ));

    CKSEntity lineAtT1, lineAtT2;
    for(size_t i = 0; i < lines.size(); ++i)
        {
        CKSCoord ls, le; if(part.GetLine(lines[i], NULL, ls, le) != CK_NOERROR) continue;
        if(!lineAtT1.IsValid() && (Dist3D(ls,T1)<kEndpointTol || Dist3D(le,T1)<kEndpointTol)) lineAtT1=lines[i];
        if(!lineAtT2.IsValid() && (Dist3D(ls,T2)<kEndpointTol || Dist3D(le,T2)<kEndpointTol)) lineAtT2=lines[i];
        }

    // DIAGNOSTIC (temporary): the 2nd linear dimension has come out identical to
    // the 1st across two otherwise-unrelated rounds of fixes to AddLinearDim's
    // parameters - suspicious enough to suspect lineAtT1/lineAtT2 might be
    // resolving to the SAME entity (a bug in the tangent-point matching above)
    // rather than another parameter-tuning miss. Report their IDs and sheet-space
    // geometry directly instead of guessing a 5th time.
    if(lineAtT1.IsValid() && lineAtT2.IsValid())
        {
        CKSCoord d1s, d1e, d2s, d2e;
        part.GetLine(lineAtT1, &drawInst, d1s, d1e);
        part.GetLine(lineAtT2, &drawInst, d2s, d2e);
        CString diag;
        diag.Format(
            L"lineAtT1 ID=%u  sheet pts: (%.4f,%.4f) -> (%.4f,%.4f)\n"
            L"lineAtT2 ID=%u  sheet pts: (%.4f,%.4f) -> (%.4f,%.4f)\n"
            L"Same entity? %s",
            part.GetID(lineAtT1), d1s.m_dX, d1s.m_dY, d1e.m_dX, d1e.m_dY,
            part.GetID(lineAtT2), d2s.m_dX, d2s.m_dY, d2e.m_dX, d2e.m_dY,
            (part.GetID(lineAtT1) == part.GetID(lineAtT2)) ? L"YES - bug in tangent matching" : L"No - different entities");
        AfxMessageBox(diag);
        }

    CKSMatrix cplaneMat; part.GetActiveCPlaneMatrix(cplaneMat);

    // The instance's own 3D display-view orientation (SDK.RTF: GetInstAttributes'
    // pViewMat = "the matrix of the instance's display View") - restored for
    // Round 7 (see DimLine's comment for the full history of why this was
    // dropped in Round 6 and is now back, paired with plain Location objects
    // instead of entity-wrapped ones).
    CKSCoord ckscBase; double dScale, dRotation, dWidth, dHeight;
    bool bFrozen, bDrawBorder; CKS::Rendering ucRendering;
    CKSMatrix viewMat;
    part.GetInstAttributes(drawInst, ckscBase, dScale, dRotation, dWidth, dHeight,
                           bFrozen, bDrawBorder, ucRendering, &viewMat);

    CKSDimensionOptions linOpts; part.GetActiveAttrib(linOpts, CKMaskLinearDim);
    // Aligned = true length along the (possibly tilted) line, matching what
    // Ctrl+Q's Detail/Dimension tool produces - not a horizontal/vertical-only
    // measurement. ViewReadableText keeps the dimension text horizontal/
    // readable instead of rotated to the dimension's own angle. CPlaneText=false
    // (confirmed live by toggling "Display Text in Detail Plane" off in KC) is
    // what actually fixes the backwards/mirrored text - true (the default) made
    // text follow the active CPlane instead of viewMat, a different plane from
    // everything else this dimension uses.
    linOpts.m_Format.SetAligned(true);
    linOpts.m_Format.SetViewReadableText(true);
    linOpts.m_Format.SetCPlaneText(false);

    CKSDimensionOptions circOpts; part.GetActiveAttrib(circOpts, CKMaskCircularDim);
    circOpts.m_Lines.SetDisplayStyle(UCHAR(CK_RadialCircular));
    circOpts.m_Format.SetViewReadableText(true);

    CKSDimensionOptions angOpts; part.GetActiveAttrib(angOpts, CKMaskAngularDim);
    angOpts.m_Format.SetViewReadableText(true);
    angOpts.m_Format.SetCPlaneText(false);

    DimArc(part, selEntity, drawInst, cplaneMat, circOpts);

    if(lineAtT1.IsValid()) DimLine(part, lineAtT1, drawInst, viewMat, linOpts);
    if(lineAtT2.IsValid()) DimLine(part, lineAtT2, drawInst, viewMat, linOpts);
    if(lineAtT1.IsValid() && lineAtT2.IsValid())
        DimAngle(part, lineAtT1, lineAtT2, selEntity, drawInst, viewMat, angOpts);

    part.NoteState();
    return CKNoError;
    }
