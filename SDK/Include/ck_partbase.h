// Copyright Kubotek Corporation, 2000-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose
#ifndef CK_PARTBASE_INC
#define CK_PARTBASE_INC

// Care and handling of ck_partbase.h
//
//   To reduce dependancies, this header should not include any other headers.
//   This header shares values between the Core the SDK.
//

#ifndef CADKEY_EXPORT
#define CADKEY_EXPORT __declspec(dllimport)
#endif

class CADKEY_EXPORT CKPartDoc;

class CKPartBase
    {
public:
    CKPartBase(CKPartDoc *pDoc) : m_pDocHandle(pDoc) {}
    operator CKPartDoc *() const { return(m_pDocHandle); }
protected:
    friend CKPartDoc;
    CKPartDoc *m_pDocHandle;
    };

#endif
