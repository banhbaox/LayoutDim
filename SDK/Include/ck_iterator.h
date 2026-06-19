// Copyright Kubotek Corporation, 2000-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose
#ifndef CK_ITERATOR_INCLUDED
#define CK_ITERATOR_INCLUDED

// @doc EXTERNAL SDK

#include "ck_types.h"

class CKDatabaseIterator;

// @class This class allows for iterating over the entire database of a
// given <c CKPart>.  This class is derived from <c CKSEntity>, so the
// iterator object can be used in any function that takes a CKSEntity
// to act on the current entity.  The increment and decrement operators
// (++ and --) are used to advance to the next or previous entity in the
// database respectively.  Adding entities to the database or removing
// entities from the database while iterating may invalidate the iterator.
//
// @base public | CKSEntity
class SDK_EXPORT CKSEntityIterator : public CKSEntity
    {
public:
    // @cmember Construct a new iterator on a part.
    CKSEntityIterator(CKPart &rPart);
    ~CKSEntityIterator();

    // @cmember Restart the iterator on a part.
    int Restart(CKPart &rPart);

    // @cmember Is the iterator currently valid?
    bool IsValid() const;

    // Prefix increment
    // @cmember Advance the iterator to the next entity.
    void operator++();

    // Postfix increment
    void operator++(int);

    // Prefix decrement
    // @cmember Advance the iterator to the previous entity.
    void operator--();

    // Postfix decrement
    void operator--(int);

protected:
    std::unique_ptr<CKDatabaseIterator> m_pIterator;
    };

#endif