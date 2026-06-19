// Copyright Kubotek Corporation, 2001-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose
//
// CKSTempLine.h: interface for the CKSTempLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CKSTEMPLINE_H__33B23CF2_EDED_11D3_8039_0050DA6A23B1__INCLUDED_)
#define AFX_CKSTEMPLINE_H__33B23CF2_EDED_11D3_8039_0050DA6A23B1__INCLUDED_

#include "stdafx.h"
#include "ck_sdk.h"
#include "CKSMatrix.h"
#include "ck_export.h"

class CKTempLine;

// @doc EXTERNAL SDK

class SDK_EXPORT CKSTempLine
    {
public:
    enum Type { Normal, Vector, Infinite};

    CKSTempLine ();
    CKSTempLine(CKPart &rPart, const CKSCoord &rStart, const CKSCoord &rEnd,
                Type nType = Normal, CKSLTypes ucStyle = CK_DASHED,
                Color nColor = RubberbandColor, UCHAR ucWidth = 1,
                bool bUpdate = true, int quick_mode = 0);

    virtual ~CKSTempLine();

protected:
    std::unique_ptr<CKTempLine> m_pTempLine;
    };

#endif // !defined(AFX_CKSTEMPLINE_H__33B23CF2_EDED_11D3_8039_0050DA6A23B1__INCLUDED_)
