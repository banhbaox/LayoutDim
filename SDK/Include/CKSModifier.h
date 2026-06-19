// Copyright Kubotek Corporation, 2000-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose
#ifndef CKSMODIFIER_INCLUDED
#define CKSMODIFIER_INCLUDED

#include "ck_types.h"
#include "ck_export.h"

class CKModifier;
class CKSDKModifier;
class SDK_EXPORT CKSCoord;
class SDK_EXPORT CKSMatrix;
class SDK_EXPORT CKSModifier;
class SDK_EXPORT CKPart;
typedef std::vector<CKSModifier *> CKSModifierArray;

// @doc EXTERNAL SDK

// @type CKSModifierCallback | The type of the CKSModifier callback function:
// int function(<c CKSModifier> *pModifier);
typedef int (*CKSModifierCallback)(CKSModifier*);

// @type CKSModifierMenuCallback | The type of the CKSModifier menu callback function:
// int function(<c CKSModifier> *pModifier, int nMenu);
typedef int (*CKSModifierMenuCallback)(CKSModifier*, int nMenu);

// @class The class used for modifier interaction
class SDK_EXPORT CKSModifier
    {
public:
    // @cmember Construct a new CKSModifier object
    CKSModifier(UINT nType, CKSMatrix *pMatrix, bool bPrimary = true,
                CKSModifierCallback pCallback = NULL,
                CKSModifierMenuCallback pMenuCallback = NULL);

    ~CKSModifier();

    // @cmember Get modifier type flag
    UINT GetType() const;

    // @cmember Set modifier type flag
    void SetType(UINT nType);

    // @cmember Get modifier visible flag
    UINT GetVisibleFlag() const;

    // @cmember Set modifier visible flag
    void SetVisibleFlag(UINT nVisible);

    // @cmember Get modifier selectable flag
    UINT GetSelectableFlag() const;

    // @cmember Set modifier selectable flag
    void SetSelectableFlag(UINT nSelectable);

    // @cmember Get modifier tooltip flag
    UINT GetTooltipFlag() const;

    // @cmember Set modifier tooltip flag
    void SetTooltipFlag(UINT nTooltip);

    // @cmember Check if modifier tooltip is enabled
    bool IsTooltipEnabled() const;

    // @cmember Enable modifier tooltip
    void EnableTooltip(bool bEnable);

    // @cmember Get modifier tooltip units
    int GetTooltipUnits() const;

    // @cmember Set modifier tooltip units
    void SetTooltipUnits(int nUnits);

    // @cmember Get modifier position
    CKSCoord GetPosition() const;

    // @cmember Set modifier position
    void SetPosition(const CKSCoord &ckc);

    // @cmember Get modifier last position
    CKSCoord GetLastPosition() const;

    // @cmember Get modifier matrix
    CKSMatrix GetMatrix() const;

    // @cmember Set modifier matrix
    void SetMatrix(const CKSMatrix &ckm);

    // @cmember Set modifier matrix
    void SetMatrixPoints(const CKSCoord &ckc, const CKSCoord &ckcX, const CKSCoord &ckcY);

    // @cmember Get modifier base matrix
    CKSMatrix GetBaseMatrix() const;

    // @cmember Set modifier base matrix
    void SetBaseMatrix(const CKSMatrix &ckm);

    // @cmember Get modifier last matrix
    CKSMatrix GetLastMatrix() const;

    // @cmember Set modifier last matrix
    void SetLastMatrix(const CKSMatrix &ckm);

    // @cmember Translate modifier
    void Translate(double dX, double dY, double dZ);

    // @cmember Translate modifier
    void Translate(const CKSCoord &ckcOffset);

    // @cmember Translate modifier in local space
    void TranslateLocal(double dX, double dY, double dZ);

    // @cmember Translate modifier in local space
    void TranslateLocal(const CKSCoord &ckcOffset);

    // @cmember Rotate modifier
    void Rotate(double dXAng, double dYAng, double dZAng);

    // @cmember Rotate modifier in local space
    void RotateLocal(double dXAng, double dYAng, double dZAng);

    // @cmember Get modifier X vector
    CKSCoord GetVectorX() const;

    // @cmember Get modifier Y vector
    CKSCoord GetVectorY() const;

    // @cmember Get modifier Z vector
    CKSCoord GetVectorZ() const;

    // @cmember Get modifier vector
    CKSCoord GetVector(int nIndex) const;

    // @cmember Get modifier vectors
    void GetVectors(CKSCoord &ckcX, CKSCoord &ckcY, CKSCoord &ckcZ) const;

    // @cmember Get modifier X angle
    double GetAngleX() const;

    // @cmember Get modifier Y angle
    double GetAngleY() const;

    // @cmember Get modifier Z angle
    double GetAngleZ() const;

    // @cmember Get modifier angle
    double GetAngle(int nIndex) const;

    // @cmember Get modifier angles
    void GetAngles(double &dXAng, double &dYAng, double &dZAng) const;

    // @cmember Set modifier X angle
    void SetAngleX(double dAngle);

    // @cmember Set modifier Y angle
    void SetAngleY(double dAngle);

    // @cmember Set modifier Z angle
    void SetAngleZ(double dAngle);

    // @cmember Set modifier angle
    void SetAngle(int nIndex, double dAngle);

    // @cmember Set modifier angles
    void SetAngles(double dXAng, double dYAng, double dZAng);

    // @cmember Get modifier mirror flag
    UINT GetMirror() const;

    // @cmember Set modifier mirror flag
    void SetMirror(UINT nMirror);

    // @cmember Get modifier translation increment
    double GetTranslateInc() const;

    // @cmember Set modifier translation increment
    void SetTranslateInc(double dInc);

    // @cmember Get modifier rotation increment
    double GetRotateInc() const;

    // @cmember Set modifier rotation increment
    void SetRotateInc(double dInc);

    // @cmember Check if modifier is highlighted
    bool IsHighLighted() const;

    // @cmember Highlight modifier part
    void HighLight(bool bHighlight);

    // @cmember Highlight modifier
    void HighLightAll(bool bHighlight);

    // @cmember Check if modifier is selected
    bool IsSelected() const;

    // @cmember Select modifier part
    void Select(bool bSelect);

    // @cmember Select modifier
    void SelectAll(bool bSelect);

    // @cmember Update modifier display
    void Update(bool bHighlight, bool bSelect);

    // @cmember Get modifier hit flag
    UINT GetHit() const;

    // @cmember Set modifier position movement
    void SetPosMove(UINT nMove, CKCoord *pPosDir = NULL);

    //@cmember Returns a pointer to the modifier object
    CKModifier *GetModifier();

protected:
    CKSDKModifier *m_pModifier;
    CKPart m_pPart;
    };

#endif
