// Copyright Kubotek Corporation, 2001-2014
// All Rights Reserved
#if !defined(AFX_CKSTEMPPOLYLINEARRAY_INC)
#define AFX_CKSTEMPPOLYLINEARRAY_INC

#include "ck_sdk.h"
#include "CKSMatrix.h"

class CKTempPolylineArray;

// @doc EXTERNAL SDK

// @class This class provides the ability to control a variable number
// of temporary polylines.
class SDK_EXPORT CKSTempPolylineArray
    {
public:
    // @cmember The constructor takes a pointer to the part doc in which
    // the polylines will be created.
    CKSTempPolylineArray(CKPart &rPart);

    CKSTempPolylineArray();

    ~CKSTempPolylineArray();

    // @cmember Remove all the polylines.
    void Clear();

    // @cmember Remove all the polylines.
    void SetDoc(CKPart &rPart);

    // @cmember Add a new polyline to the end of the array.
    void Push(const CKSCoordArray &ackcPolyline, CKSLTypes ucStyle,
              Color nColor, UCHAR ucWidth, bool bUpdate = true,
              int quick_mode = 0);

    // @cmember Remove the last polyline from the array
    int Pop(bool bUpdate = true);

    // @cmember Insert a new polyline into the the array.
    void Insert(size_t nIndex, const CKSCoordArray &ackcPolyline,
                CKSLTypes ucStyle, Color nColor, UCHAR ucWidth, 
                bool bUpdate = true, int quick_mode = 0);

    // @cmember Remove a polyline from the the array.
    void Remove(size_t nIndex, bool bUpdate = true);

    // @cmember Change the color and style of a polyline in the array.
    void ChangePolyline(size_t nIndex, Color nColor, CKSLTypes ucStyle, 
                        UCHAR ucWidth, bool bUpdate = true);

    // @cmember Get the number of polylines
    size_t Count() const;

    // @cmember Get polyline coordinates.
    int GetPolylineCoord(size_t nIndex, CKSCoordArray &ackcPoints);

protected:
    std::unique_ptr<CKTempPolylineArray> m_pTempPolylineArray;
    };

#endif // !defined(AFX_CKSTEMPPOLYLINEARRAY_INC)

