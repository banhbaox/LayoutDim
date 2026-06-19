#include "StdAfx.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>

#include "ck_sdk.h"
#include "ck_attr.h"
#include "Funcs.h"

static const std::wstring kTubeGeoLevelNum = L"2.1";
static const double kDimOffset   = 25.0;  // text offset from entity
static const double kEndpointTol = 0.001; // tolerance for tangent-point matching (model units)

static double Dist3D(const CKSCoord& a, const CKSCoord& b)
    {
    double dx = a.m_dX - b.m_dX;
    double dy = a.m_dY - b.m_dY;
    double dz = a.m_dZ - b.m_dZ;
    return sqrt(dx*dx + dy*dy + dz*dz);
    }

static bool IsOnTubeGeoLevel(CKPart& part, CKSEntity& ent)
    {
    CKSLevel level;
    if(part.GetEntityLevel(ent, level) != CK_NOERROR || !level.IsValid())
        return false;
    std::wstring num;
    if(part.GetLevelInfo(level, NULL, &num, NULL, NULL, NULL) != CK_NOERROR)
        return false;
    return num == kTubeGeoLevelNum;
    }

// Location objects are GAtom-derived with protected dtors — must be heap-allocated.
static void DimLine(CKPart& part, CKSEntity& ent, CKSDrawInst& drawInst,
                    int nDispView, const CKSMatrix& matCPlane,
                    CKSDimensionOptions& opts)
    {
    CKSCoord ptStart, ptEnd;
    if(part.GetLine(ent, &drawInst, ptStart, ptEnd) != CK_NOERROR)
        return;

    double dx = ptEnd.m_dX - ptStart.m_dX;
    double dy = ptEnd.m_dY - ptStart.m_dY;
    double projLen = sqrt(dx*dx + dy*dy);
    if(projLen < 1e-10)
        return;

    double dAxisAngle = atan2(dy, dx) * 180.0 / M_PI;

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

    // Get all entities visible through this instance
    CKSEntityArray geom;
    if(part.GetInstanceGeometry(drawInst, geom) != CK_NOERROR)
        {
        AfxMessageBox(L"GetInstanceGeometry failed.");
        return CKError;
        }

    // Separate level-2.1 entities into lines and arcs
    std::vector<CKSEntity> lines, arcs;
    for(size_t i = 0; i < geom.size(); ++i)
        {
        CKSEntity ent = geom[i];
        if(!ent.IsValid() || !IsOnTubeGeoLevel(part, ent))
            continue;

        CKMaskTypes t;
        if(part.GetEntityType(ent, t) != CK_NOERROR)
            continue;

        if(t == CKMaskLine)      lines.push_back(ent);
        else if(t == CKMaskArc)  arcs.push_back(ent);
        }

    if(arcs.empty())
        {
        AfxMessageBox(L"No level-2.1 arcs found in this instance.");
        return CKNoError;
        }

    // Retrieve the 3D display view matrix from the drawing instance.
    // Its origin (column 3) is the bend corner point (ptB) used to build the view.
    CKSCoord ckscBase;
    double dScale = 0, dRot = 0, dW = 0, dH = 0;
    bool bFrozen = false, bBorder = false;
    CKS::Rendering ucRender = CKS::RenderWire;
    CKSMatrix viewMat;
    part.GetInstAttributes(drawInst, ckscBase, dScale, dRot, dW, dH,
                           bFrozen, bBorder, ucRender, &viewMat);

    double vm[4][4];
    viewMat.GetValues(vm);
    CKSCoord viewOrigin(vm[3][0], vm[3][1], vm[3][2]);

    // Find the arc whose center is closest to the view origin (= bend corner).
    // Each bend's arc center is uniquely close to its own corner in a valid tube.
    CKSEntity targetArc;
    double bestDist  = 1e30;
    double bestRad   = 0, bestStart = 0, bestDelta = 0;
    CKSMatrix bestArcMat;

    for(size_t i = 0; i < arcs.size(); ++i)
        {
        double rad, startAng, deltaAng;
        CKEntityAttrib attr;
        CKSMatrix aMat;
        if(part.GetArc(arcs[i], NULL, &rad, &startAng, &deltaAng, &attr, &aMat) != CK_NOERROR)
            continue;

        double av[4][4];
        aMat.GetValues(av);
        CKSCoord arcCenter(av[3][0], av[3][1], av[3][2]);

        double d = Dist3D(arcCenter, viewOrigin);
        if(d < bestDist)
            {
            bestDist    = d;
            targetArc   = arcs[i];
            bestRad     = rad;
            bestStart   = startAng;
            bestDelta   = deltaAng;
            bestArcMat  = aMat;
            }
        }

    if(!targetArc.IsValid())
        {
        AfxMessageBox(L"Could not identify the target arc for this view.");
        return CKNoError;
        }

    // Compute the arc's two tangent endpoints (T1 = start, T2 = end) in 3D world space.
    // The arc matrix encodes center (col 3) and local axes (cols 0,1).
    double av[4][4];
    bestArcMat.GetValues(av);
    CKSCoord center(av[3][0], av[3][1], av[3][2]);
    CKSCoord xAx(av[0][0], av[0][1], av[0][2]);
    CKSCoord yAx(av[1][0], av[1][1], av[1][2]);

    double startRad = bestStart * M_PI / 180.0;
    double endRad   = (bestStart + bestDelta) * M_PI / 180.0;

    CKSCoord T1(
        center.m_dX + bestRad * (cos(startRad) * xAx.m_dX + sin(startRad) * yAx.m_dX),
        center.m_dY + bestRad * (cos(startRad) * xAx.m_dY + sin(startRad) * yAx.m_dY),
        center.m_dZ + bestRad * (cos(startRad) * xAx.m_dZ + sin(startRad) * yAx.m_dZ));

    CKSCoord T2(
        center.m_dX + bestRad * (cos(endRad) * xAx.m_dX + sin(endRad) * yAx.m_dX),
        center.m_dY + bestRad * (cos(endRad) * xAx.m_dY + sin(endRad) * yAx.m_dY),
        center.m_dZ + bestRad * (cos(endRad) * xAx.m_dZ + sin(endRad) * yAx.m_dZ));

    // Find the two lines whose endpoints touch T1 or T2.
    // Each trimmed line's endpoint exactly meets an arc tangent point.
    CKSEntity lineAtT1, lineAtT2;
    for(size_t i = 0; i < lines.size(); ++i)
        {
        CKSCoord ls, le;
        if(part.GetLine(lines[i], NULL, ls, le) != CK_NOERROR)
            continue;

        if(!lineAtT1.IsValid() &&
           (Dist3D(ls, T1) < kEndpointTol || Dist3D(le, T1) < kEndpointTol))
            lineAtT1 = lines[i];

        if(!lineAtT2.IsValid() &&
           (Dist3D(ls, T2) < kEndpointTol || Dist3D(le, T2) < kEndpointTol))
            lineAtT2 = lines[i];
        }

    int nDispView  = (int)part.GetID(drawInst);
    CKSMatrix matCPlane;
    part.GetActiveCPlaneMatrix(matCPlane);

    CKSDimensionOptions linOpts;
    part.GetActiveAttrib(linOpts, CKMaskLinearDim);

    CKSDimensionOptions circOpts;
    part.GetActiveAttrib(circOpts, CKMaskCircularDim);
    circOpts.m_Lines.SetDisplayStyle(UCHAR(CK_RadialCircular));

    int dimsCreated = 0;

    if(lineAtT1.IsValid())
        { DimLine(part, lineAtT1, drawInst, nDispView, matCPlane, linOpts); ++dimsCreated; }

    DimArc(part, targetArc, drawInst, nDispView, circOpts);
    ++dimsCreated;

    if(lineAtT2.IsValid())
        { DimLine(part, lineAtT2, drawInst, nDispView, matCPlane, linOpts); ++dimsCreated; }

    part.NoteState();
    return CKNoError;
    }
