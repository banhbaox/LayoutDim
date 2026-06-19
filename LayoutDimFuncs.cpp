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

// GetLine/GetArc with &drawInst return layout sheet-space coords, which is what
// CKS::Location coords (m_ptCoord) and CKSRefLine expect when pMatrix = global CPlane.
// Pass pRefLine so KC derives the aligned angle from the refLine direction rather than
// defaulting to 0 deg (horizontal) when pRefLine is NULL.
static void DimLine(CKPart& part, CKSEntity& ent, CKSDrawInst& drawInst,
                    int nDispView, const CKSMatrix& cplaneMat, CKSDimensionOptions& opts)
    {
    CKSCoord ptStart, ptEnd;
    if(part.GetLine(ent, &drawInst, ptStart, ptEnd) != CK_NOERROR) return;

    double dx = ptEnd.m_dX - ptStart.m_dX;
    double dy = ptEnd.m_dY - ptStart.m_dY;
    double projLen = sqrt(dx*dx + dy*dy);
    if(projLen < 1e-10) return;

    // pRefLine tells AddLinearDim to align the dim parallel to this line direction
    CKSRefLine refLine;
    refLine.m_ptStart = ptStart;
    refLine.m_ptEnd   = ptEnd;

    CKSCoord textPt(
        (ptStart.m_dX + ptEnd.m_dX) * 0.5 + (-dy / projLen) * kDimOffset,
        (ptStart.m_dY + ptEnd.m_dY) * 0.5 + ( dx / projLen) * kDimOffset,
        (ptStart.m_dZ + ptEnd.m_dZ) * 0.5);

    CKS::LocationPtr locFirst  = new CKS::EndEntLoc(ptStart, ent, drawInst, true,  1);
    CKS::LocationPtr locSecond = new CKS::EndEntLoc(ptEnd,   ent, drawInst, false, 1);
    CKS::LocationPtr textLoc   = new CKS::Location(textPt);
    part.AddLinearDim(0.0, &refLine, locFirst, locSecond,
                      textLoc, &opts, nDispView, NULL, &cplaneMat);
    }

static void DimArc(CKPart& part, CKSEntity& ent, CKSDrawInst& drawInst,
                   int nDispView, const CKSMatrix& cplaneMat, CKSDimensionOptions& opts)
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
    part.AddCircularDim(refArc, &ent, textLoc, nDispView, &opts, NULL, NULL, &drawInst);
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

    // Find the TubeMaker display view that owns this arc.
    // TubeMaker encodes entity IDs in the view name: "Bend#:leftLineId,arcId,rightLineId"
    ULONG arcId = part.GetID(selEntity);
    int nDispView = -1;
    for(int n = 1; n <= 500; ++n)
        {
        std::wstring vname;
        if(part.GetDispViewName(n, vname) != CK_NOERROR) break;
        size_t col = vname.find(L':'); if(col == std::wstring::npos) continue;
        std::wstring ids = vname.substr(col+1);
        size_t c1 = ids.find(L','); if(c1 == std::wstring::npos) continue;
        size_t c2 = ids.find(L',', c1+1); if(c2 == std::wstring::npos) continue;
        ULONG vid = (ULONG)wcstoul(ids.substr(c1+1, c2-c1-1).c_str(), nullptr, 10);
        if(vid == arcId) { nDispView = n; break; }
        }
    if(nDispView < 0)
        { AfxMessageBox(L"Arc not found in a TubeMaker bend view. Run TubeMaker first."); return CKNoError; }

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
    CKSDimensionOptions linOpts; part.GetActiveAttrib(linOpts, CKMaskLinearDim);
    CKSDimensionOptions circOpts; part.GetActiveAttrib(circOpts, CKMaskCircularDim);
    circOpts.m_Lines.SetDisplayStyle(UCHAR(CK_RadialCircular));

    if(lineAtT1.IsValid()) DimLine(part, lineAtT1, drawInst, nDispView, cplaneMat, linOpts);
    DimArc(part, selEntity, drawInst, nDispView, cplaneMat, circOpts);
    if(lineAtT2.IsValid()) DimLine(part, lineAtT2, drawInst, nDispView, cplaneMat, linOpts);

    part.NoteState();
    return CKNoError;
    }
