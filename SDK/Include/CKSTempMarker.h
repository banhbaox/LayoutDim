// Copyright Kubotek Corporation, 2001-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose
//
// CKSTempMarker.h : interface for the CKSTempMarker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CKSTEMPMARKER_H__33B23CF1_EDED_11D3_8039_0050DA6A23B1__INCLUDED_)
#define AFX_CKSTEMPMARKER_H__33B23CF1_EDED_11D3_8039_0050DA6A23B1__INCLUDED_

#include "stdafx.h"

#include "ck_sdk.h"
#include "CKSMatrix.h"
#include "ck_export.h"
#include "ck_enum.h"

class CKTempMarker;

// @doc EXTERNAL SDK

class SDK_EXPORT CKSTempMarker
    {
public:
    CKSTempMarker(CKPart &rPart, const CKSCoord &rCoord,
                  int nType = CK_MARKER_X);
    ~CKSTempMarker();

protected:
    std::unique_ptr<CKTempMarker> m_pTempMarker;
    };

#endif // !defined(AFX_CKSTEMPMARKER_H__33B23CF1_EDED_11D3_8039_0050DA6A23B1__INCLUDED_)
