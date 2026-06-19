// Copyright Kubotek Corporation, 2000-2014
// All Rights Reserved
#ifndef CKSTEMPMESH_INC
#define CKSTEMPMESH_INC

#include "stdafx.h"
#include "ck_sdk.h"
#include "CKSMatrix.h"
#include "ck_export.h"

class CKTempMesh;

// @doc EXTERNAL SDK
class SDK_EXPORT CKSTempMesh
    {
public:
    CKSTempMesh(CKPart &rPart, const CKSCoordArray &ackcMesh,
                int nRows, int nCols, bool bLines = true, bool bPoints = false);

    ~CKSTempMesh();

protected:
    std::unique_ptr<CKTempMesh> m_pTempMesh;
    };
#endif //define CKSTEMPMESH_INC
