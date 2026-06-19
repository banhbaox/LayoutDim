#include "StdAfx.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>

#include "ck_sdk.h"
#include "ck_attr.h"
#include "Funcs.h"

// Level number string for TubeGeo entities (matches TubeMaker level 2.1)
static const std::wstring kTubeGeoLevelNum = L"2.1";

// Fixed offset used to place dimension text away from the entity
static const double kDimOffset = 25.0;

static bool GetEntityLevelNumber(CKPart& part, CKSEntity& ent, std::wstring& outNum)
    {
    CKSLevel level;
    if(part.GetEntityLevel(ent, level) != CK_NOERROR || !level.IsValid())
        return false;
    if(part.GetLevelInfo(level, NULL, &outNum, NULL, NULL, NULL) != CK_NOERROR)
        return false;
    return true;
    }

static void DimLine(CKPart& part, CKSEntity& ent, CKSDrawInst& drawInst,
                    int nDispView, const CKSMatrix& matCPlane,
                    CKSDimensionOptions& opts)
    {
    CKSCoord ptStart, ptEnd;
    if(part.GetLine(ent, &drawInst, ptStart, ptEnd) != CK_NOERROR)
        return;

    // Direction of the segment in XY (view) plane
    double dx = ptEnd.m_dX - ptStart.m_dX;
    double dy = ptEnd.m_dY - ptStart.m_dY;
    double projLen = sqrt(dx * dx + dy * dy);
    if(projLen < 1e-10)
        return;

    // Axis angle aligns the dimension with the segment so true length is shown
    double dAxisAngle = atan2(dy, dx) * 180.0 / M_PI;

    // Text position: midpoint offset perpendicular to the segment
    double perpX = -dy / projLen * kDimOffset;
    double perpY =  dx / projLen * kDimOffset;
    CKSCoord textPt(
        (ptStart.m_dX + ptEnd.m_dX) * 0.5 + perpX,
        (ptStart.m_dY + ptEnd.m_dY) * 0.5 + perpY,
        (ptStart.m_dZ + ptEnd.m_dZ) * 0.5);

    CKS::EndEntLoc locFirst (ptStart, ent, drawInst, true,  1);
    CKS::EndEntLoc locSecond(ptEnd,   ent, drawInst, false, 1);
    CKS::Location  textLoc(textPt);

    part.AddLinearDim(dAxisAngle, NULL, &locFirst, &locSecond,
                      &textLoc, &opts, nDispView, NULL, &matCPlane);
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

    // Arc center is the translation column of the matrix
    double vals[4][4];
    arcMatrix.GetValues(vals);
    CKSCoord center(vals[3][0], vals[3][1], vals[3][2]);

    CKSRefArc refArc;
    refArc.m_dRadius     = dRad;
    refArc.m_dStartAngle = dStartAng;
    refArc.m_dEndAngle   = dStartAng + dDeltaAng;
    refArc.m_ptCenter    = center;

    // Text position at the arc midpoint angle, 1.5× radius from center
    double midAngRad = (dStartAng + dDeltaAng * 0.5) * M_PI / 180.0;
    CKSCoord textPt(
        center.m_dX + cos(midAngRad) * dRad * 1.5,
        center.m_dY + sin(midAngRad) * dRad * 1.5,
        center.m_dZ);
    CKS::Location textLoc(textPt);

    part.AddCircularDim(refArc, &ent, &textLoc, nDispView, &opts,
                        NULL, NULL, &drawInst);
    }

int DimLayout()
    {
    CKPart part = CKGetActivePart();
    if(!part.IsValid())
        return CKError;

    // This function only makes sense in Layout mode
    if(TRUE != part.InLayoutMode())
        {
        AfxMessageBox(L"Switch to Layout mode before running DimLayout.");
        return CKNoError;
        }

    // Select the drawing instance (bend view) to dimension
    CKSEntity selEntity;
    CKSDrawInst drawInst;
    switch(part.GetEnt(L"Select bend drawing instance to dimension:",
                       selEntity, drawInst, CKS::SelectInst))
        {
        case CKNoError:
            break;
        default:
            return CKNoError;
        }

    if(!drawInst.IsValid())
        return CKNoError;

    // Get all entities projected into this instance
    CKSEntityArray geom;
    if(part.GetInstanceGeometry(drawInst, geom) != CK_NOERROR)
        {
        AfxMessageBox(L"GetInstanceGeometry failed.");
        return CKError;
        }

    // The display view ID drives dimension association to the view
    int nDispView = (int)part.GetID(drawInst);

    // Active construction plane for dimension orientation
    CKSMatrix matCPlane;
    part.GetActiveCPlaneMatrix(matCPlane);

    // Dimension options (read from part's current settings)
    CKSDimensionOptions linOpts;
    part.GetActiveAttrib(linOpts, CKMaskLinearDim);

    CKSDimensionOptions circOpts;
    part.GetActiveAttrib(circOpts, CKMaskCircularDim);
    circOpts.m_Lines.SetDisplayStyle(UCHAR(CK_RadialCircular));

    int dimsCreated = 0;

    for(size_t i = 0; i < geom.size(); ++i)
        {
        CKSEntity ent = geom[i];
        if(!ent.IsValid())
            continue;

        // Only dimension TubeGeo entities (level 2.1)
        std::wstring levelNum;
        if(!GetEntityLevelNumber(part, ent, levelNum))
            continue;
        if(levelNum != kTubeGeoLevelNum)
            continue;

        CKMaskTypes entType;
        if(part.GetEntityType(ent, entType) != CK_NOERROR)
            continue;

        if(entType == CKMaskLine)
            {
            DimLine(part, ent, drawInst, nDispView, matCPlane, linOpts);
            ++dimsCreated;
            }
        else if(entType == CKMaskArc)
            {
            DimArc(part, ent, drawInst, nDispView, circOpts);
            ++dimsCreated;
            }
        }

    if(dimsCreated == 0)
        {
        AfxMessageBox(L"No level-2.1 lines or arcs found in the selected instance.");
        return CKNoError;
        }

    part.NoteState();
    return CKNoError;
    }
