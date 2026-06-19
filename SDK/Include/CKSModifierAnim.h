// Copyright Kubotek Corporation, 2000-2014
// All Rights Reserved
#ifndef CKSMODIFIERANIM_INCLUDED
#define CKSMODIFIERANIM_INCLUDED

#include "CKSAnim.h"
#include "CKSModifier.h"

// @doc EXTERNAL SDK

// @class The class used for animation interaction
class SDK_EXPORT CKSModifierAnim : public CKSAnim
    {
public:
    // @cmember Construct a new CKSModifierAnim object
    CKSModifierAnim(UINT nModType, CKSMatrix *pMatrix = NULL,
                    CKSModifierCallback pCallback = NULL,
                    CKSModifierMenuCallback pMenuCallback = NULL,
                    CKSAnimCallback pAnimCallback = NULL,
                    bool bCallbackOnDraw = false,
                    bool bTransformEnts = true);

    // @cmember Construct a new CKSModifierAnim object
    CKSModifierAnim(const std::vector<UINT> &aModTypes,
                    CKSMatrixArray &aMatrix,
                    CKSModifierCallback pCallback = NULL,
                    CKSModifierMenuCallback pMenuCallback = NULL,
                    CKSAnimCallback pAnimCallback = NULL,
                    bool bCallbackOnDraw = false,
                    bool bTransformEnts = true);

    ~CKSModifierAnim();

    // @cmember Add modifier
    bool PushModifier(UINT nModType, CKSMatrix *pMatrix,
                      CKSModifierCallback pCallback = NULL,
                      CKSModifierMenuCallback pMenuCallback = NULL);

    // @cmember Remove last modifier
    bool PopModifier();

    // @cmember Remove all modifiers
    bool ClearModifier();

    // @cmember Get modifiers
    bool GetModifiers(CKSModifierArray &aModifiers) const;

    // @cmember Get active modifier
    CKSModifier *GetActiveModifier(size_t *pMod = NULL) const;

    // @cmember Get modifier matrix
    void GetModifierMatrix(CKSMatrix &rMatrix, size_t nIndex = 0) const;

    // @cmember Get modifier matrix
    void GetModifierMatrix(CKSMatrixArray &aMatrix) const;

    // @cmember Set modifier matrix
    void SetModifierMatrix(CKSMatrix &rMatrix, size_t nIndex = 0);

    // @cmember Set modifier matrix
    void SetModifierMatrix(CKSMatrixArray &aMatrix);
    };

#endif
