// Copyright Kubotek Corporation, 1999-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose
#ifndef CKSSELECTIONSET_INC
#define CKSSELECTIONSET_INC

#include "ck_sdk.h"

class CADKEY_EXPORT CKSelectionSet;

// @doc EXTERNAL SDK

// @class Stores a list of selected entities.  Supports adding, removing, 
// removing all, and inquiring if an entity is already selected.
//
// An item being selected implies that it will be highlighted if highlighting
// is enabled for the set.
//
// An item being selected implies that it will be made unselectable if 
// selectability is enabled for the set.
class SDK_EXPORT CKSSelectionSet
    {
// @access Public Members
public:
    // @cmember Regular Constructor
    CKSSelectionSet(bool bHighlighting, bool bSelectability, Color nColor,
                    UCHAR ucWidth = 0);

private:
    // unimplemented private copy constructor
    CKSSelectionSet(const CKSSelectionSet &right);

    // unimplemented private assignment operator.
    CKSSelectionSet &operator =(const CKSSelectionSet &right);

public:
    // @cmember Destructor, calls DeSelectAll.
    virtual ~CKSSelectionSet();

    // @cmember Select an entity.  If <p bUpdate> is true, updates the display.
    void Select(const CKSEntity &pEntity, bool bUpdate);

    // @cmember Select an entity, and put it at the start of the list.
    // If <p bUpdate> is true, updates the display.
    void SelectFirst(const CKSEntity &pEntity, bool bUpdate);

    // @cmember Select an array of entities.  If <p bUpdate> is true,
    // updates the display.
    void Select(const CKSEntityArray &apEntities, bool bUpdate);

    // @cmember Select a set of entities.  If <p bUpdate> is true,
    // updates the display.
    void Select(const CKSSelectionSet &setEntities, bool bUpdate);

    // @cmember Deselect an entity.  If <p bUpdate> is true, updates the
    // display.
    bool DeSelect(const CKSEntity &pEntity, bool bUpdate);

    // @cmember Deselect an array of entities.  If <p bUpdate> is true,
    // updates the display.
    void DeSelect(const CKSEntityArray &asEntities, bool bUpdate);

    // @cmember Deselect all entities.  If <p bUpdate> is true, updates
    // the display.
    void DeSelectAll(bool bUpdate);

    // @cmember Deselect all entities and store in another selection set.
    // If <p bUpdate> is true, updates the display.
    void DeSelectTo(CKSSelectionSet &setEntities, bool bUpdate);

    // @cmember Replace an entity with another, does not update the display.
    void Replace(const CKSEntity &pCurrent, const CKSEntity &pNew);

    // @cmember Returns the number of entities in the set.
    size_t GetSize() const;

    // @cmember Is the list empty
    bool IsEmpty() const;

    // @cmember Does the list contain the specified entity?
    bool Contains(const CKSEntity &pEntity) const;

    // @cmember Does this set affect the highlighting of its entities?
    bool Highlighting() const;

    // @cmember Does this set affect the selectability of its entities?
    bool Selectability() const;

    // @cmember Which color is used for highlighting?
    Color GetColor() const;

    // @cmember Set which color is used for highlighting.  This only affects
    // entities which are selected after this call is made.  Existing entities
    // are not re-highlighted in the new color.
    void SetColor(Color nColor);

private:
    std::unique_ptr<CKSelectionSet> m_pSet;
    };

#endif
