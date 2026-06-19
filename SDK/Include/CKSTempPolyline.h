// Copyright Kubotek Corporation, 2001-2014
// All Rights Reserved
#ifndef CKSTEMPPOLYLINE_INC
#define CKSTEMPPOLYLINE_INC

#include "stdafx.h"

#include "ck_sdk.h"
#include "CKSMatrix.h"

class CKTempPolyline;

// @doc EXTERNAL SDK

class SDK_EXPORT CKSTempPolyline
    {
public:
    CKSTempPolyline(CKPart &rPart);

    CKSTempPolyline(CKPart &rPart, const CKSCoordArray &ackcPolyline,
                    CKSLTypes ucStyle = CK_SOLID,
                    Color nColor = RubberbandColor, UCHAR ucWidth = 1);

    virtual ~CKSTempPolyline();

    void DrawPolyline(CKPart &rPart, const CKSCoordArray &ackcPolyline,
                      CKSLTypes ucStyle = CK_SOLID,
                      Color nColor = RubberbandColor, UCHAR ucWidth = 1);

    void ErasePolyline(bool bUpdate = true);

    void SetPolyCoord(const CKSCoordArray &paCoord);

    void GetPolyCoord(CKSCoordArray &ackcCoord);

    void RefreshDisplay(CKPart &rPart, bool bUpdate = false);

protected:
    std::unique_ptr<CKTempPolyline> m_pTempPolyline;
    };

#endif // CKSTEMPPOLYLINE_INC
