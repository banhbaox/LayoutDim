// Copyright Kubotek Corporation, 2000-2014
// All Rights Reserved
#ifndef CKSMATH_INCLUDED
#define CKSMATH_INCLUDED

#include "ck_export.h"

class CKSEntity;
class CKSDrawInst;
class CKSCoord;
class CKSMatrix;

// @doc EXTERNAL SDK

// @class CKSMath | Namespace for KeyCreator Math functions and constants
namespace CKSMath
    {

// Group Often used constants
    // @cmember PI
    SDK_FUNC const double PI;
    // @cmember PI * 0.25
    SDK_FUNC const double PI0_25;
    // @cmember PI * 0.5
    SDK_FUNC const double PI0_5;
    // @cmember PI * 1.0
    SDK_FUNC const double PI1_0;
    // @cmember PI * 1.5;
    SDK_FUNC const double PI1_5;
    // @cmember PI * 2.0;
    SDK_FUNC const double PI2_0;

    // @cmember The minimum length of an entity
    SDK_FUNC const double MinLength;
    // @cmember The maximum length of an entity
    SDK_FUNC const double MaxLength;

    // @cmember The minimum non-zero angle, in degrees
    SDK_FUNC const double MinAngleDeg;
    // @cmember The minimum non-zero angle, in radians
    SDK_FUNC const double MinAngleRad;

    // @cmember Conversion from Degrees to Radians
    SDK_FUNC const double DegToRad;
    // @cmember Conversion from Radians to Degrees
    SDK_FUNC const double RadToDeg;

    // @cmember Conversion from Gradians to Radians
    SDK_FUNC const double GradToRad;
    // @cmember Conversion from Radians to Gradians
    SDK_FUNC const double RadToGrad;

    // @cmember Normalize an angle to 0 to 2PI
    SDK_FUNC double Normalize(double dAngle);

    // @cmember Round angles within MinAngle of a quadrant to that
    // quadrant.
    SDK_FUNC void RoundAngle(double &dAngle);

    // @cmember Convert an angle from degrees to radians and
    // normalize it
    inline double ToRadians(double dDegrees)
        { return(Normalize(dDegrees * DegToRad)); }

    // @cmember Convert an angle from radians to degrees and
    // normalize it
    inline double ToDegrees(double dRadians)
        { return(Normalize(dRadians) * RadToDeg); }

    SDK_FUNC double RoundValue(double dValue, int nPrecision);

// @cmember Find a point a given distance along an entity
SDK_FUNC int Along(const CKSEntity &rEntity, const CKSDrawInst *pDrawInst,
                   bool bStart, double dLen, CKSCoord &rCoord, int &nSeg, 
                   double &dParam, bool bExtendCurve);

// @cmember Given three points, generate an arc that passes through those points.
//  It begins at the first point and ends at the third point.
SDK_FUNC int ArcThreePoints(const CKSCoord &ckcFirst,
                            const CKSCoord &ckcSecond,
                            const CKSCoord &ckcThird,
                            double &dRadius, double &dStartAngle,
                            double &dDeltaAngle, CKSMatrix &mat);

// @cmember Support function that builds a CKSMatrix appropriate for
// the given CKSEntity and CKSDrawInst pointer.
SDK_FUNC int BuildWorldMatrix(CKSEntity &rEnt,
                           CKSDrawInst *pDrawInst,
                           CKSMatrix &rMatrix);

// @cmember Convert cartesian coordinates to polar.
SDK_FUNC int CartToPolar(const CKSCoord &rOrigin, const CKSCoord &rCart,
                         CKSCoord &rPolar);

// @cmember Find the center of a circle passing through 3 points.
SDK_FUNC int CenterThreePoints(const CKSCoord &ckcPos1,
                               const CKSCoord &ckcPos2,
                               const CKSCoord &ckcPos3,
                               CKSCoord &ckcCenter);

// @cmember Compute a circle with a given radius that is tangent to or
// passes through two entities or points respectively.
SDK_FUNC int Circle2TanPtRadius(bool b3D, double dRadius,
                                const CKSEntity &pEnt1,
                                const CKSEntity &pEnt2,
                                int &nSeg1, double &dParam1, CKSCoord &rPoint1,
                                int &nSeg2, double &dParam2, CKSCoord &rPoint2,
                                CKSMatrix &ckmArc,
                                const CKSDrawInst *pDrawInst1 = NULL,
                                const CKSDrawInst *pDrawInst2 = NULL,
                                const CKSMatrix *pWorldMat = NULL);

// @cmember Given three points, generate an arc or circle that passes through
// those points.  If it is an arc, the arc begins at the first point and
// stops at the third point.
SDK_FUNC int CircleThreePoints(const CKSCoord &ckcFirst,
                               const CKSCoord &ckcSecond,
                               const CKSCoord &ckcThird,
                               double &dRadius, CKSMatrix &mat);

// @cmember Compute a circle that is tangent to or passes through three
// entities or points respectively.
SDK_FUNC int CircleThreeTanPt(bool b3D,
                              const CKSEntity &pEnt1, const CKSEntity &pEnt2,
                              const CKSEntity &pEnt3,
                              int &nSeg1, double &dParam1, CKSCoord &rPoint1,
                              int &nSeg2, double &dParam2, CKSCoord &rPoint2,
                              int &nSeg3, double &dParam3, CKSCoord &rPoint3,
                              CKSMatrix &rMatrix, double &dRadius,
                              const CKSDrawInst *pDrawInst1 = NULL,
                              const CKSDrawInst *pDrawInst2 = NULL,
                              const CKSDrawInst *pDrawInst3 = NULL,
                              const CKSMatrix *pWorldMat = NULL);

// @cmember Compare two floating-point values, within a default tolerance.
SDK_FUNC int CompareDoubles(double dValue1, double dValue2);

// @cmember Compare two floating-point values, within a specified tolerance.
SDK_FUNC int CompareDoubles(double dValue1, double dValue2, double dTolerance);

// @cmember Compare a floating-point value to zero, within a default tolerance.
SDK_FUNC int CompareToZero(double dValue);

// @cmember Compare a floating point value to zero, within a specified tolerance.
SDK_FUNC int CompareToZero(double dValue, double dTolerance);

// @cmember Compute the cross product of 2 vectors.
SDK_FUNC void Cross(double &rx, double &ry, double &rz,
                    double x1, double y1, double z1,
                    double x2, double y2, double z2);

// @cmember Compute the cross product of 2 vectors and return the result as a CKSCoord.
SDK_FUNC CKSCoord Cross(const CKSCoord &vec1, const CKSCoord &vec2);

// @cmember Computes the distance between two coordinates.
SDK_FUNC int Distance(const CKSCoord &rPoint1, const CKSCoord &rPoint2,
                      double &dDistance);

// @cmember Computes then returns the distance between two coordinates
SDK_FUNC double Distance(const CKSCoord &rPoint1, const CKSCoord &rPoint2,
                         const CKSMatrix *pProjMatrix = NULL);

// @cmember Compute the dot product of two vectors.
SDK_FUNC double DotProduct(double x1, double y1, double z1,
                           double x2, double y2, double z2);

// @cmember Compute the dot product of two vectors.
SDK_FUNC double DotProduct(const CKSCoord &vec1, const CKSCoord &vec2);

// @cmember Find the closest end point of the entity to a given point.
SDK_FUNC int EndEnt(const CKSEntity &rEntity, const CKSDrawInst *pDrawInst,
                    const CKSCoord &rCoord, const CKSMatrix &rProjMatrix,
                    CKSCoord &rEnd, int &nSeg, double &dParam,
                    const CKSMatrix *pWorldMatrix);

// @cmember Extracts the end points of an entity.
SDK_FUNC int EndPoints(const CKSEntity &rEntity, const CKSDrawInst *pDrawInst,
                       CKSCoord &rEnd1, CKSCoord &rEnd2,
                       const CKSMatrix *pWorldMatrix);

    // @cmember Compares two points to see if they're equal, within a given
    // tolerance.
    inline bool EqualPoints(const CKSCoord &c1, const CKSCoord &c2, double dTol)
        {
        return(0 == CompareToZero(Distance(c1, c2), dTol));
        }

    // @cmember Compares two points to see if they're equal, within a default
    // tolerance.
    inline bool EqualPoints(const CKSCoord &c1, const CKSCoord &c2)
        {
        return(0 == CompareToZero(Distance(c1, c2)));
        }

// @cmember Evaluate various mathematical attributes of the entity at the given
// segment and parameter values.
SDK_FUNC int Evaluate(const CKSEntity &rEntity, const CKSDrawInst *pDrawInst,
                      bool bFlatten, bool bExtendCurveStart,
                      bool bExtendCurveEnd, int nSeg, double dParam,
                      const CKSMatrix *pWorldMatrix, CKSCoord *pPosition,
                      CKSCoord *pFirstD = NULL, CKSCoord *pSecondD = NULL,
                      CKSCoord *pThirdD = NULL);

// @cmember Retrieve the number of segment, number and parameter value
// of the start segment, number and parameter value of the end segment.
SDK_FUNC int Info(const CKSEntity &rEntity, int &nSeg, int &nStartSeg,
                  double &dStartParam, int &nEndSeg, double &dEndParam,
                  bool &bClosed);

// @cmember Compute the intersection of two curves.
SDK_FUNC int Intersection(const CKSEntity &pFirst,
                          const CKSDrawInst *pDrawInst1,
                          const CKSEntity &pSecond,
                          const CKSDrawInst *pDrawInst2,
                          CKSCoord &rPoint, int &nFirstSeg,
                          double &dFirstParam, int &nSecondSeg,
                          double &dSecondParam, bool bExtendCurve = true,
                          const CKSMatrix *pMatrix = NULL);

// @cmember Compute the intersection of two infinite lines defined by two points
// on each line, called Start and End.
SDK_FUNC int Intersection(const CKSCoord &ckcFirstStart,
                          const CKSCoord &ckcFirstEnd,
                          const CKSCoord &ckcSecondStart,
                          const CKSCoord &ckcSecondEnd,
                          CKSCoord &rIntersection,
                          double *pFirstParam = NULL,
                          double *pSecondParam = NULL,
                          const CKSMatrix *pMatrix = NULL);

// @cmember Returns the length of a given entity.
SDK_FUNC int Length(const CKSEntity &rEntity, const CKSDrawInst *pDrawInst,
                    int nStartSeg, double dStartParam, int nEndSeg,
                    double dEndParam, double &dLength,
                    const CKSMatrix *pMatrix = NULL);

// @cmember Returns the length of a given entity.
SDK_FUNC int Length(const CKSEntity &rEntity, double &dLength);


// @cmember Compute a line either tangent or perpendicular to each of two
// entities.  Either entity may be omitted, in which case a provided fixed
// point is used.
SDK_FUNC int LineTanPerp(bool b3D, const CKSEntity &pEnt1,
                         const CKSEntity &pEnt2,
                         bool bTan1, int &nSeg1, double &dParam1,
                         CKSCoord &rPoint1,
                         bool bTan2, int &nSeg2, double &dParam2,
                         CKSCoord &rPoint2,
                         const CKSDrawInst *pDrawInst1 = NULL,
                         const CKSDrawInst *pDrawInst2 = NULL,
                         const CKSMatrix *pWorldMat = NULL);

// @cmember Find the mathematical mid point of an entity.
SDK_FUNC int Midpoint(const CKSEntity &rEntity, const CKSDrawInst *pDrawInst,
                      CKSCoord &rMid, int &nSeg, double &dParam);

// @cmember Compute the minimum distance between two curves.
SDK_FUNC int MinDist(const CKSEntity &pFirst, const CKSDrawInst *pDrawInst1,
                     const CKSEntity &pSecond, const CKSDrawInst *pDrawInst2,
                     double &dDistance, CKSCoord &rFirstPoint,
                     int &nFirstSeg, double &dFirstParam,
                     CKSCoord &rSecondPoint, int &nSecondSeg,
                     double &dSecondParam, bool bExtendCurve = false,
                     const CKSMatrix *pMatrix = NULL);

// @cmember Computes the minimum distance between a position and an entity.
SDK_FUNC int NearPoint(const CKSEntity &rEntity, const CKSDrawInst *pDrawInst,
                       const CKSCoord &rCoord, bool bGlobalSearch,
                       CKSCoord &rNear, int &nSeg, double &dParam,
                       double &dDist, bool bExtendCurveStart = false,
                       bool bExtendCurveEnd = false,
                       const CKSMatrix *pProjMatrix = NULL,
                       const CKSMatrix *pWorldMatrix = NULL);

// @cmember Get the perpendicular vector to an entity at a given segment and parameter value.
SDK_FUNC int PerpToEnt(const CKSEntity &rEntity, const CKSDrawInst *pDrawInst,
                       int nSegment, double dParam, CKSCoord &vecPerp,
                       const CKSMatrix *pWorldMatrix);

// @cmember Convert polar coordinates to cartesian.
SDK_FUNC int PolarToCart(const CKSCoord &rOrigin, const CKSCoord &rPolar,
                         CKSCoord &rCart);

// @cmember Get the tangent vector to an entity at a given segment and parameter value.
SDK_FUNC int TanToEnt(const CKSEntity &rEntity, const CKSDrawInst *pDrawInst,
                      int nSegment, double dParam, CKSCoord &vecTangent,
                      const CKSMatrix *pWorldMatrix);

// @cmember Rotate the coordinate counter-clockwise.
SDK_FUNC void Rotate2DAxis(double ang, CKSCoord &rCoord);

// @cmember Rotate the coordinate counter-clockwise with an offset.
SDK_FUNC void Rotate2DAxisOffset(double ang, CKSCoord &rCoord,
                                 const CKSCoord &rOffset);

// @cmember Build a transformation matrix that will rotate the first
// vector to become the second vector, and store it in the matrix
// parameter.
SDK_FUNC int RotateVectorToVector(const CKSCoord &ckscFrom, 
                                  const CKSCoord &ckscTo,
                                  CKSMatrix &rMatrix);

// @cmember Generates 2 centers for an arc with the given radius and two end
// points of the arc.
SDK_FUNC int ArcFrom2PntRad(const CKSCoord &rPoint1, const CKSCoord &rPoint2,
                            double dRadius, CKSCoord &rCenter1,
                            CKSCoord &rCenter2);

// @cmember Computes the arc tangent of dy/dx in the range 0 - 2PI.
SDK_FUNC double atan3(double dy, double dx);

// @cmember Generate a matrix given three points.
SDK_FUNC int MatrixThreePoints(const CKSCoord &ckcFirst,
                               const CKSCoord &ckcSecond,
                               const CKSCoord &ckcThird,
                               CKSMatrix &rMatrix);

// @cmember Generate a matrix given x and y vectors.
SDK_FUNC int MatrixTwoVectors(const CKSCoord &vecFirst,
                              const CKSCoord &vecSecond,
                              CKSMatrix &rMatrix);

// @cmember Generate a matrix given two points describing a vector.
// The z axis will be along the provided line, while the x and y axes
// will be arbitrary.  The base point of the matrix will be at the start
// point.  The resulting matrix can be used to convert from the
// vector 0, 0, 1 to the corresponding vector in the WCS.
SDK_FUNC int MatrixVector(const CKSCoord &ckcFirst, const CKSCoord &ckcSecond,
                          CKSMatrix &rMatrix);

SDK_FUNC int GenerateVector(const CKSEntity &rEntOrig, const CKSEntity &rEntPlane,
                            double dAngle, CKSMatrix &rMatrix);

//// Assist functions for new XFORM funcs  _kg Oct/07 //// 

// @cmember  Matrix with X and Y translation components removed, but  keep the Z component
SDK_FUNC int MatrixTranslateZ(CKSMatrix &rMat);

 // @cmember Matrix defined by vector rotated in the axis defined by two positions
SDK_FUNC int MatrixRotateVectorAngle(const CKSCoord &ckcStart,
                                     const CKSCoord &ckcEnd,
                                     CKSMatrix &ckmPlane);

// @cmember Matrix generated from two positions
SDK_FUNC int MatrixTwoPositions(const CKSCoord &ckcStart,
                                const CKSCoord &ckcEnd, CKSMatrix &rMat);

};
#endif
