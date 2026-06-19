// Copyright Kubotek Corporation, 2001-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose


#include "ck_export.h"

class CKBlockAcisUserInterrupt;

// @doc EXTERNAL SDK

// @class This class is used to prevent user interrupts
class SDK_EXPORT CKSBlockUserInterrupt
    {
    private:
        CKBlockAcisUserInterrupt *m_pBlockAcisUserInterrupt;

    public:
        // @cmember Constructor of the class
        CKSBlockUserInterrupt();

        // @cmember Destructor of the class
        ~CKSBlockUserInterrupt();
    };