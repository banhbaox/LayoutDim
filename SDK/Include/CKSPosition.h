// Copyright Kubotek Corporation, 1999-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose

#ifndef CKS_POSITION_H
#define CKS_POSITION_H

class CKSCoord;

typedef struct
    {
    std::wstring csName;
    bool    bCPlane;
    CKSCoord ckscCoord;
    } CKS_CUSTOM_POS;

#endif // CKS_POSITION_H
