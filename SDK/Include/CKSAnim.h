// Copyright Kubotek Corporation, 2000-2014
// All Rights Reserved
#ifndef CKSANIM_INCLUDED
#define CKSANIM_INCLUDED

#include <memory>

#include "ck_types.h"
#include "CKSMatrix.h"
#include "ck_enum.h"
#include "ck_export.h"

class CKAnim;   
class SDK_EXPORT CKSAnim;
class CKSMatrix;
class SDK_EXPORT CKSCoord;
class SDK_EXPORT CKPart;
class CKEntity;
class CKSEntity;
class CKDrawInst;

// @doc EXTERNAL SDK

// @type CKSAnimCallback | The type of the CKSAnim callback function:
// int function(int nType, <c CKSAnim> *pAnimation);
typedef int (*CKSAnimCallback)(int nType, CKSAnim *pAnimation);

// @type CKAnimEntityCallback | The type of the CKAnim callback function for
// entity selection:
// int function(int nType, <lt>c CKAnim<gt> *pAnimation, const CKCoord &rCoord,
//              const ck_ptr<lt>CKEntity<gt> &rEntity,
//              const weak_ptr<lt>CKDrawInst<gt> &rDrawInst,
//              int nSeg, double dParam);
typedef int (*CKSAnimEntityCallback)(int nType, CKSAnim *pAnimation,
                                     const CKCoord &rCoord,
                                     const CKSEntity &rEntity,
                                     const CKSDrawInst &rDrawInst,
                                     int nSeg, double dParam);

// @class The class used for animation interaction
class SDK_EXPORT CKSAnim
    {
public:
    // @cmember Construct a new CKSAnim object
    CKSAnim(CKSAnimCallback pCallback = NULL,
            bool bCallbackOnDraw = false,
            bool bTransformEntities = true,
            bool bEnableAnim = true);

    // @cmember Construct a new CKSAnim object
    CKSAnim(const CKSMatrix &rView, const CKSCoord &rBasePt,
            double dRotation = 0.0, double dScale = 1.0,
            CKSAnimCallback pCallback = NULL,
            bool bCallbackOnDraw = false,
            bool bTransformEntities = true,
            bool bEnableAnim = true);

    // @cmember Construct a new CKSAnim object
    CKSAnim(CKSAnimEntityCallback pCallback,
            bool bCallbackOnDraw = false,
            bool bTransformEntities = true,
            bool bEnableAnim = true);

    // @cmember Construct a new CKSAnim object
    CKSAnim(const CKSMatrix &rView, const CKSCoord &rBasePt,
            double dRotation = 0.0, double dScale  = 1.0,
            CKSAnimEntityCallback pEntityCallback = NULL,
            bool bCallbackOnDraw = false,
            bool bTransformEntities = true,
            bool bEnableAnim = true);

    // When the object is destroyed, destroy the hoops key
    ~CKSAnim();

    // @cmember,menum The type of action for which the callback is
    // being called.
    enum CallbackActions
        {
        Draw = CKNoError,   // @@emem The animation is being drawn
        // The rest is same as Events enum defined in ck_enum.h
        };

    enum CoordMode
        {
        Position,
        Rotation,
        Scaling,
        RotationScale,
        Radius,
        Height,
        Rectangle
        };

    // @cmember Display this animation (static) in a particular part.
    // This can be done in multiple parts, but can not be undone except
    // by destroying the CKSAnim object.
    void Display(CKPart &rPart);

    // @cmember Set quick move mode.
    void SetQuickMove(QuickMoveMode nMode);

    // @cmember Get the current viewing matrix
    void GetViewMat(CKSMatrix &rMatrix);

    // @cmember Get the current base point
    void GetBasePt(CKSCoord &rBasePt);

    // @cmember Set the current positioning mode
    void SetMode(CoordMode nMode);

    // @cmember Set the base scale distance
    void SetScaleDistance(double dDistance);

    // @cmember Get the current rotation about the z axis
    double GetRotation() const;

    // @cmember Get the current scale.
    double GetScale() const;

    // @cmember Apply a transform to the current viewing matrix
    void Transform(const CKSMatrix &rMatrix);

    // @cmember Apply an offset to the current base point
    void Translate(const CKSCoord &rOffset);

    // @cmember Rotate the entities about the Z axis
    double Rotate(double dAngle);

    // @cmember Scale the entities
    double Scale(double dFactor);

    // @cmember Reset the viewing matrix, base point, rotation to zero, and
    // the scale to 1.
    void Reset();

    // @cmember Set the current base point set in world coordinates
    void SetBasePt(const CKSCoord &rBasePt);

    // @cmember Get the last change in the current base point
    void GetBasePtDelta(CKSCoord &rDelta);

    // @cmember Set the increment value for rotation, 0 means no rotation
    void SetRotationIncrement(double dIncrement);

    //  @cmember Compute the rotation for the current base point and the given point
    double ComputeRotation(const CKSCoord &rRotPoint);

    // @cmember Compute the scale for the current base point and the given point
    double ComputeScale(const CKSCoord &rScalePoint);

    // @cmember Get the current radius from the Z axis
    double GetRadius() const;

    // @cmember Set the current rasdius from the Z axis
    void SetRadius(double dRadius);

    // @cmember Get the current rectangle length along the X axis
    double GetLength() const;

    // @cmember Set the current rectange length along the X axis
    void SetLength(double dLength);

    // @cmember Get the current rectangle width along the Y axis
    double GetWidth() const;

    // @cmember Set the rectangle width along the Y axis
    void SetWidth(double dWidth);

    // @cmember Compute the rectangle length and width for the current
    // base point and the given point
    void ComputeRect(const CKSCoord &rRectPoint);

    // @cmember Get the current height from the XY plane.
    double GetHeight() const;

    // @cmember Set the current height from the XY plane
    void SetHeight(double dHeight);

    // @cmember Compute the height for the current base point and the
    // given point
    double ComputeHeight(const CKSCoord &rCorner);

    // @cmember Apply an offset to the current view matrix. The offset
    // is in world or local coordinates.
    void TranslateViewMat(const CKSCoord &rOffset, bool bInWorld);

    // @cmember Get the complete matrix, including the CPlane matrix,
    // and the base point.
    void GetMatrix(CKSMatrix &rMatrix);

    // @cmember Set projection matrix to be the entity's net matrix
    void SetProjectionMatrix(CKSEntity rEntity);

    // @cmember Set projection matrix to the provided matrix
    void SetProjectionMatrix(const CKSMatrix &rMatrix);

    // @cmember Get the part in which the animation is being done.
    CKPart GetPart() const;

    //@cmember Returns a pointer to the animation object
    CKAnim* GetAnim(); 

    // @cmember Add an entity to the animation.
    void AddEntity(CKSEntity &rEntity);

    // @cmember Remove an entity from the animation.
    void RemoveEntity(CKSEntity &rEntity);

    // @cmember Add an entity to the animation.
    void AddEntity(CKEntity *pEntity);

    // @cmember Remove an entity from the animation.
    void RemoveEntity(CKEntity *pEntity);

    static int Callback(int nType, CKAnim *pAnim);

    static int EntityCallback(int nType, CKAnim *pAnimation,
                              const CKCoord &rCoord,
                              const ck_ptr<CKEntity> &rEntity,
                              const weak_ptr<CKDrawInst> &rDrawInst,
                              int nSeg, double dParam);

    int DoCallback(int nType);

    int DoEntityCallback(int nType, const CKCoord &rCoord,
                         const ck_ptr<CKEntity> &rEntity,
                         const weak_ptr<CKDrawInst> &rDrawInst,
                         int nSeg, double dParam);

    // @cmember Tells all the entities in the animation to update themselves.
    void CallUpdateCallbacks();

     bool WantsGenericToggle() const;
     bool WantsContextMenu() const;
     void SetGenericToggle(bool bWantsGenericToggle);
     void SetContextMenu(bool bWantsContextMenu);

protected:
    std::unique_ptr<CKAnim> m_pAnim;

    // @cmember The user's callback function
    CKSAnimCallback m_pCallback;

    // @cmember The user's callback function
    CKSAnimEntityCallback m_pEntityCallback;

    // @cmember Is the object currently in a draw callback?
    bool m_bInCallback;
    };

#endif
