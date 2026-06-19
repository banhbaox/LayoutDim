// Copyright Kubotek Corporation, 2001-2014
// All Rights Reserved
#if !defined(AFX_CKSTEMPMARKERARRAY_H__33B23CF1_EDED_11D3_8039_0050DA6A23B1__INCLUDED_)
#define AFX_CKSTEMPMARKERARRAY_H__33B23CF1_EDED_11D3_8039_0050DA6A23B1__INCLUDED_

#include "stdafx.h"
#include "ck_sdk.h"
#include "CKSMatrix.h"

class CKCoord;
class CKTempMarkerArray;

// @doc EXTERNAL SDK

// @class This class provides the ability to control a variable number
// of temporary markers.
class SDK_EXPORT CKSTempMarkerArray
    {
public:
    // @cmember The constructor takes a pointer to the part doc in which
    // the markers will be created.
    CKSTempMarkerArray(CKPart &rPart);

    ~CKSTempMarkerArray();

    // @cmember Remove all the markers.
    void SetDoc(CKPart &rPart);

    // @cmember Remove all the markers.
    void Clear();

    // @cmember Add a new marker to the end of the array.
    void Push(const CKSCoord &rCoord, int nType = CK_MARKER_X,
              COLORREF crValue = COLORREF(-1));

    // @cmember Remove the last marker from the array
    int Pop();

    // @cmember Insert a new marker into the array.
    void Insert(size_t nIndex, const CKSCoord &rCoord, int nType = CK_MARKER_X,
                COLORREF crValue = COLORREF(-1));

    // @cmember Remove a marker from the the array.
    void Remove(size_t nIndex);

    // @cmember Change the color and style of a marker in the array.
    void ChangeMarker(int nType, COLORREF crValue = COLORREF(-1),
                      size_t nIndex = size_t(-1));

    // @cmember Change the color and style of a marker in the array.
    void MoveMarker(size_t nIndex, const CKSCoord &rCoord);

    // @cmember Get the number of markers
    size_t Count();

    // @cmember Get the coordinate of the marker
    int GetMarkerCoord(size_t nIndex, CKSCoord &rCoord);

    // @cmember Swap Markers
    int SwapMarkerByIdx(size_t idx_a, size_t idx_b);

protected:
    std::unique_ptr<CKTempMarkerArray> m_pTempMarkerArray;
    };

#endif // !defined(AFX_TEMPMARKERARRAY_H__33B23CF1_EDED_11D3_8039_0050DA6A23B1__INCLUDED_)
