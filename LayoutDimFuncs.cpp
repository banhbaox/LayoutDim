#include "StdAfx.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>

#include "ck_sdk.h"
#include "ck_attr.h"
#include "Funcs.h"

// Fallback level number string for TubeGeo entities
static const std::wstring kTubeGeoLevelNum = L"2.1";

// Text offset distance from the entity
static const double kDimOffset = 25.0;

// Parse a TubeMaker bend view name of the form "BendN:leftLineId,arcId,rightLineId".
// Returns true and fills the three IDs on success.
static bool ParseBendViewName(const std::wstring& name,
                              ULONG& leftId, ULONG& arcId, ULONG& rightId)
    {
    size_t colon = name.find(L':');
    if(colon == std::wstring::npos)
        return false;

    std::wstring ids = name.substr(colon + 1);
    size_t c1 = ids.find(L',');
    if(c1 == std::wstring::npos)
        return false;
    size_t c2 = ids.find(L',', c1 + 1);
    if(c2 == std::wstring::npos)
        return false;

    wchar_t* end = nullptr;
    leftId = wcstoul(ids.substr(0, c1).c_str(),       nullptr, 10);
    arcId  = wcstoul(ids.substr(c1 + 1, c2 - c1 - 1).c_str(), nullptr, 10);
    rightId = wcstoul(ids.substr(c2 + 1).c_str(),      nullptr, 10);

    return leftId != 0 && arcId != 0 && rightId != 0;
    }

// CKS::Location and derived classes have protected destructors — they must live
// on the heap and be held via LocationPtr (GAtom reference counting).
static void DimLine(CKPart& part, CKSEntity& ent, CKSDrawInst& drawInst,
                    int nDispView, const CKSMatrix& matCPlane,
                    CKSDimensionOptions& opts)
    {
    CKSCoord ptStart, ptEnd;
    if(part.GetLine(ent, &drawInst, ptStart, ptEnd) != CK_NOERROR)
        return;

    double dx = ptEnd.m_dX - ptStart.m_dX;
    double dy = ptEnd.m_dY - ptStart.m_dY;
    double projLen = sqrt(dx * dx + dy * dy);
    if(projLen < 1e-10)
        return;

    // Axis angle aligns the dimension with the segment → measures true length
    double dAxisAngle = atan2(dy, dx) * 180.0 / M_PI;

    // Text offset perpendicular to the segment
    CKSCoord textPt(
        (ptStart.m_dX + ptEnd.m_dX) * 0.5 + (-dy / projLen) * kDimOffset,
        (ptStart.m_dY + ptEnd.m_dY) * 0.5 + ( dx / projLen) * kDimOffset,
        (ptStart.m_dZ + ptEnd.m_dZ) * 0.5);

    CKS::LocationPtr locFirst  = new CKS::EndEntLoc(ptStart, ent, drawInst, true,  1);
    CKS::LocationPtr locSecond = new CKS::EndEntLoc(ptEnd,   ent, drawInst, false, 1);
    CKS::LocationPtr textLoc   = new CKS::Location(textPt);

    part.AddLinearDim(dAxisAngle, NULL, locFirst, locSecond,
                      textLoc, &opts, nDispView, NULL, &matCPlane);
    }

static void DimArc(CKPart& part, CKSEntity& ent, CKSDrawInst& drawInst,
                   int nDispView, CKSDimensionOptions& opts)
    {
    double dRad, dStartAng, dDeltaAng;
    CKEntityAttrib arcAttrib;
    CKSMatrix arcMatrix;
    if(part.GetArc(ent, &drawInst, &dRad, &dStartAng, &dDeltaAng,
                   &arcAttrib, &arcMatrix) != CK_NOERROR)
        return;

    double vals[4][4];
    arcMatrix.GetValues(vals);
    CKSCoord center(vals[3][0], vals[3][1], vals[3][2]);

    CKSRefArc refArc;
    refArc.m_dRadius     = dRad;
    refArc.m_dStartAngle = dStartAng;
    refArc.m_dEndAngle   = dStartAng + dDeltaAng;
    refArc.m_ptCenter    = center;

    double midAngRad = (dStartAng + dDeltaAng * 0.5) * M_PI / 180.0;
    CKSCoord textPt(
        center.m_dX + cos(midAngRad) * dRad * 1.5,
        center.m_dY + sin(midAngRad) * dRad * 1.5,
        center.m_dZ);
    CKS::LocationPtr textLoc = new CKS::Location(textPt);

    part.AddCircularDim(refArc, &ent, textLoc, nDispView, &opts,
                        NULL, NULL, &drawInst);
    }

// Fallback: dimension all level-2.1 lines and arcs visible in the instance.
// Used when the view name doesn't carry encoded entity IDs (old TubeMaker format).
static int DimByLevel(CKPart& part, CKSEntityArray& geom, CKSDrawInst& drawInst,
                      int nDispView, const CKSMatrix& matCPlane,
                      CKSDimensionOptions& linOpts, CKSDimensionOptions& circOpts)
    {
    int count = 0;
    for(size_t i = 0; i < geom.size(); ++i)
        {
        CKSEntity ent = geom[i];
        if(!ent.IsValid())
            continue;

        CKSLevel level;
        if(part.GetEntityLevel(ent, level) != CK_NOERROR || !level.IsValid())
            continue;
        std::wstring levelNum;
        if(part.GetLevelInfo(level, NULL, &levelNum, NULL, NULL, NULL) != CK_NOERROR)
            continue;
        if(levelNum != kTubeGeoLevelNum)
            continue;

        CKMaskTypes entType;
        if(part.GetEntityType(ent, entType) != CK_NOERROR)
            continue;

        if(entType == CKMaskLine)
            { DimLine(part, ent, drawInst, nDispView, matCPlane, linOpts); ++count; }
        else if(entType == CKMaskArc)
            { DimArc(part, ent, drawInst, nDispView, circOpts); ++count; }
        }
    return count;
    }

int DimLayout()
    {
    CKPart part = CKGetActivePart();
    if(!part.IsValid())
        return CKError;

    if(TRUE != part.InLayoutMode())
        {
        AfxMessageBox(L"Switch to Layout mode before running DimLayout.");
        return CKNoError;
        }

    CKSEntity selEntity;
    CKSDrawInst drawInst;
    switch(part.GetEnt(L"Select bend drawing instance to dimension:",
                       selEntity, drawInst, CKS::SelectInst))
        {
        case CKNoError: break;
        default:        return CKNoError;
        }

    if(!drawInst.IsValid())
        return CKNoError;

    // Retrieve the display view name from the instance attributes.
    // TubeMaker encodes the three relevant entity IDs: "BendN:leftId,arcId,rightId"
    CKSCoord ckscBase;
    double dScale = 0, dRot = 0, dW = 0, dH = 0;
    bool bFrozen = false, bBorder = false;
    CKS::Rendering ucRender = CKS::RenderWireFrame;
    std::wstring viewName;
    part.GetInstAttributes(drawInst, ckscBase, dScale, dRot, dW, dH,
                           bFrozen, bBorder, ucRender, NULL, NULL, NULL,
                           NULL, NULL, NULL, &viewName);

    int nDispView = (int)part.GetID(drawInst);

    CKSMatrix matCPlane;
    part.GetActiveCPlaneMatrix(matCPlane);

    CKSDimensionOptions linOpts;
    part.GetActiveAttrib(linOpts, CKMaskLinearDim);

    CKSDimensionOptions circOpts;
    part.GetActiveAttrib(circOpts, CKMaskCircularDim);
    circOpts.m_Lines.SetDisplayStyle(UCHAR(CK_RadialCircular));

    int dimsCreated = 0;

    ULONG leftId = 0, arcId = 0, rightId = 0;
    if(ParseBendViewName(viewName, leftId, arcId, rightId))
        {
        // New TubeMaker format: dimension only the three specific entities
        CKSEntity leftLine  = part.GetEntity(leftId);
        CKSEntity arcEnt    = part.GetEntity(arcId);
        CKSEntity rightLine = part.GetEntity(rightId);

        if(leftLine.IsValid())
            { DimLine(part, leftLine,  drawInst, nDispView, matCPlane, linOpts); ++dimsCreated; }
        if(arcEnt.IsValid())
            { DimArc(part,  arcEnt,    drawInst, nDispView, circOpts); ++dimsCreated; }
        if(rightLine.IsValid())
            { DimLine(part, rightLine, drawInst, nDispView, matCPlane, linOpts); ++dimsCreated; }
        }
    else
        {
        // Fallback: view name has no encoded IDs — dimension all level-2.1 entities
        CKSEntityArray geom;
        if(part.GetInstanceGeometry(drawInst, geom) != CK_NOERROR)
            {
            AfxMessageBox(L"GetInstanceGeometry failed.");
            return CKError;
            }
        dimsCreated = DimByLevel(part, geom, drawInst, nDispView, matCPlane, linOpts, circOpts);
        }

    if(dimsCreated == 0)
        {
        AfxMessageBox(L"No entities to dimension were found in the selected instance.");
        return CKNoError;
        }

    part.NoteState();
    return CKNoError;
    }
