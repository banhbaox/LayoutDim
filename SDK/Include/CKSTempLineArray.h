// Copyright Kubotek Corporation, 1999-2014
// All Rights Reserved
#if !defined(AFX_CKSTempLineArray_H__33B23CF1_EDED_11D3_8039_0050DA6A23B1__INCLUDED_)
#define AFX_CKSTempLineArray_H__33B23CF1_EDED_11D3_8039_0050DA6A23B1__INCLUDED_

#include "stdafx.h"
#include "ck_sdk.h"
#include "CKSMatrix.h"
#include "CKSTempLine.h"

class CKCoord;
class CKTempLineArray;

// @doc EXTERNAL SDK


// @class This class provides the ability to control a variable number
// of temporary Polylines.
class SDK_EXPORT CKSTempLineArray
    {
public:
    // @cmember The empty constructor.
    CKSTempLineArray();

    // @cmember The constructor with a CKPart ref and arrowhead.
    CKSTempLineArray(CKPart &rPart,
                     CKSTempLine::Type nType = CKSTempLine::Normal);

    // @cmember The destructor.
    ~CKSTempLineArray();

    // @cmember Set the document to ths part.
    void SetDoc(CKPart &rPart);

    // @cmember Remove all the Lines.
    void Clear();

    // @cmember Add a new Line to the end of the array.
    void Push(const CKSCoord &rStart, const CKSCoord &rEnd,
              CKSLTypes ucStyle, Color nColor, UCHAR ucWidth,
              bool bUpdate = true, int quick_mode = NoQuickMove);

    // @cmember Remove the last Line from the array.
    int Pop(bool bUpdate = true);

    // @cmember Insert a new Line into the the array.
    void Insert(size_t nIndex, const CKSCoord &rStart, const CKSCoord &rEnd,
                CKSLTypes ucStyle, Color nColor, UCHAR ucWidth,
                bool bUpdate = true, int quick_mode = NoQuickMove);

    // @cmember Remove a Line from the the array.
    void Remove(size_t nIndex, bool bUpdate = true);

    // @cmember Change the color, style and width of a Line in the array.
    void ChangeLine(size_t nIndex, Color nColor, CKSLTypes ucStyle,
                    UCHAR ucWidth, bool bUpdate = true);

    // @cmember Get the number of Lines.
    size_t Count() const;

    // @cmember Get info on whether line has an arrowhead.
    CKSTempLine::Type GetType() const;

    // @cmember Set the Line to have (or not) an arrowhead.
    void SetType(CKSTempLine::Type nType);

    // @cmember Get the start/end positions of a Line indexed in the array.
    int GetLineCoords(size_t nIndex, CKSCoord &rStart, CKSCoord &rEnd);

protected:
    std::unique_ptr<CKTempLineArray> m_pTempLineArray;
    };

#endif // !defined(AFX_CKSTempLineArray_H__33B23CF1_EDED_11D3_8039_0050DA6A23B1__INCLUDED_)
