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
// generic active CPlane matrix - still produced horizontal-only dimensions. The SDK's
// own prose docs (SDK.RTF, never checked in that round) define dAxisAngle as "the
// angle from the DIMENSION MATRIX x-axis to the CPlane x-axis" and pMatrix as "the
// dimension's orientation with respect to the WORLD coordinate system" - i.e. pMatrix
// IS the dimension's own reference frame, and the generic active CPlane is very
// unlikely to match this specific bend's actual 3D view orientation. Round 2: fetch
// the placed instance's own view orientation via GetInstAttributes' pViewMat ("the
// matrix of the instance's display View" per SDK.RTF - distinct from that same call's
// own pMatrix output, which is a world-to-instance-local transform, the wrong
// direction). Pass viewMat as AddLinearDim's pMatrix, and dAxisAngle=0.0 - relying on
// m_Format.SetAligned(true) + pRefLine to derive the true angle from the geometry
// itself, rather than fighting the angle math by hand a third time.
static void DimLine(CKPart& part, CKSEntity& ent, CKSDrawInst& drawInst,
                    const CKSMatrix& viewMat, CKSDimensionOptions& opts)
    {
    CKSCoord ptStart, ptEnd;
    if(part.GetLine(ent, &drawInst, ptStart, ptEnd) != CK_NOERROR) return;

    double dx = ptEnd.m_dX - ptStart.m_dX;
    double dy = ptEnd.m_dY - ptStart.m_dY;
    double projLen = sqrt(dx*dx + dy*dy);
    if(projLen < 1e-10) return;

    CKSCoord textPt(
        (ptStart.m_dX + ptEnd.m_dX) * 0.5 + (-dy / projLen) * kDimOffset,
        (ptStart.m_dY + ptEnd.m_dY) * 0.5 + ( dx / projLen) * kDimOffset,
        (ptStart.m_dZ + ptEnd.m_dZ) * 0.5);

    CKSRefLine refLine;
    refLine.m_ptStart = ptStart;
    refLine.m_ptEnd   = ptEnd;

    CKS::LocationPtr locFirst  = new CKS::EndEntLoc(ptStart, ent, drawInst, true,  1);
    CKS::LocationPtr locSecond = new CKS::EndEntLoc(ptEnd,   ent, drawInst, false, 1);
    CKS::LocationPtr textLoc   = new CKS::Location(textPt);
    part.AddLinearDim(0.0, &refLine, locFirst, locSecond,
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

// The outside angle between the two lines flanking a bend - the Detail/Angular/
// Two Lines (Ctrl+W) equivalent. bInnerAngle=false selects the reflex/outside
// angle rather than the angle you'd get pointing both line directions away
// from the bend corner.
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

    part.AddAngularDim(false /* outside angle */, refLine1, refLine2,
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

    CKSMatrix cplaneMat; part.GetActiveCPlaneMatrix(cplaneMat);

    // The instance's own 3D display-view orientation (SDK.RTF: GetInstAttributes'
    // pViewMat = "the matrix of the instance's display View") - used for the
    // linear/angular dims below instead of the generic active CPlane, which has
    // no reason to match this specific bend's view direction. DimArc is left
    // using cplaneMat unchanged - the arc dimension already works correctly.
    CKSCoord ckscBase; double dScale, dRotation, dWidth, dHeight;
    bool bFrozen, bDrawBorder; CKS::Rendering ucRendering;
    CKSMatrix viewMat;
    part.GetInstAttributes(drawInst, ckscBase, dScale, dRotation, dWidth, dHeight,
                           bFrozen, bDrawBorder, ucRendering, &viewMat);

    CKSDimensionOptions linOpts; part.GetActiveAttrib(linOpts, CKMaskLinearDim);
    // Aligned = true length along the (possibly tilted) line, matching what
    // Ctrl+Q's Detail/Dimension tool produces - not a horizontal/vertical-only
    // measurement. ViewReadableText keeps the dimension text horizontal/
    // readable instead of rotated to the dimension's own angle. Neither flag
    // was ever set in earlier attempts at this (see git history).
    linOpts.m_Format.SetAligned(true);
    linOpts.m_Format.SetViewReadableText(true);

    CKSDimensionOptions circOpts; part.GetActiveAttrib(circOpts, CKMaskCircularDim);
    circOpts.m_Lines.SetDisplayStyle(UCHAR(CK_RadialCircular));
    circOpts.m_Format.SetViewReadableText(true);

    CKSDimensionOptions angOpts; part.GetActiveAttrib(angOpts, CKMaskAngularDim);
    angOpts.m_Format.SetViewReadableText(true);

    if(lineAtT1.IsValid()) DimLine(part, lineAtT1, drawInst, viewMat, linOpts);
    DimArc(part, selEntity, drawInst, cplaneMat, circOpts);
    if(lineAtT2.IsValid()) DimLine(part, lineAtT2, drawInst, viewMat, linOpts);
    if(lineAtT1.IsValid() && lineAtT2.IsValid())
        DimAngle(part, lineAtT1, lineAtT2, selEntity, drawInst, viewMat, angOpts);

    part.NoteState();
    return CKNoError;
    }
