// Copyright Kubotek Corporation, 1999-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose

#ifndef SDKMASK_INC
#define SDKMASK_INC

#include "ck_sdk.h"

class CKSystemMask;

// @doc EXTERNAL SDK

// @class This class implements entity masking.
class SDK_EXPORT CKSMask
    {
// @access Public members
public:
    CKSMask();
    ~CKSMask();

    // @cmember Clear all mask settings.
    void Clear();

    // @cmember Set the color mask flags
    void SetColor(ULONG ulFirst, ULONG ulSecond);

    // @cmember Get the color mask flags
    void GetColor(ULONG &ulFirst, ULONG &ulSecond) const;

    // @cmember Add the color to the colors that can be selected
    int AddColor(int nColor);

    // @cmember Remove the color from the colors that can be selected
    int RemoveColor(int nColor);

    // @cmember Set the style mask flags
    int SetStyle(BYTE bfStyle);

    // @cmember Get the style mask flags
    BYTE GetStyle() const;

    // @cmember Add the style to the styles that can be selected
    int AddStyle(int nStyle);

    // @cmember Remove the style from the styles that can be selected
    int RemoveStyle(int nStyle);

    // @cmember Set the width mask flags
    void SetWidth(BYTE bfWidth);

    // @cmember Get the width mask flags
    BYTE GetWidth() const;

    // @cmember Add the width to the widths that can be selected
    int AddWidth(int nWidth);

    // @cmember Remove the width from the widths that can be selected
    int RemoveWidth(int nWidth);

    // @cmember Set the pen mask flags
    void SetPen(BYTE bfPen);

    // @cmember Get the pen mask flags
    BYTE GetPen() const;

    // @cmember Add the pen to the pens that can be selected
    int AddPen(int nPen);

    // @cmember Remove the pen from the pens that can be selected
    int RemovePen(int nPen);

    // @cmember Set the entity mask flags
    int SetEntities(const std::vector<CKMaskTypes> &anEntities);

    // @cmember Get the entity mask flags
    int GetEntities(std::vector<CKMaskTypes> &anEntities) const;

    // @cmember Add the entity to the entities that can be selected
    int AddEntity(CKMaskTypes nEntity);

    // @cmember Remove the entity from the entities that can be selected
    int RemoveEntity(CKMaskTypes nEntity);

    // @cmember Set the system mask's allowable levels.
    int SetLevels(const CKSLevelArray &apLevels);

    // @cmember Get the system mask's allowable levels.
    int GetLevels(CKSLevelArray &apLevels) const;

    // @cmember Add the level to the levels that can be selected
    int AddLevel(const CKSLevel &rLevel);

    // @cmember Remove the level from the levels that can be selected
    int RemoveLevel(const CKSLevel &rLevel);

    // @cmember Checks to see if a given entity passes the current mask 
    // settings
    static bool CheckEntity(CKSEntity &pEntity);

private:
    std::unique_ptr<CKSystemMask> m_pMask;
    void *operator new(size_t);
    void *operator new(size_t, void *);
    void *operator new[](size_t);
    void *operator new[](size_t, void *);
    };

#endif
