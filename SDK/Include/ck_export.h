// Copyright Kubotek Corporation, 1999-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose

#ifndef CK_EXPORT_INC
#define CK_EXPORT_INC

#if defined(SDK_MAIN)
#define SDK_EXPORT __declspec(dllexport)
#elif defined(CADKEY_MAIN) || defined(CADL_MAIN)
#define SDK_EXPORT
#else
#define SDK_EXPORT __declspec(dllimport)
#endif

#define SDK_FUNC extern SDK_EXPORT

#endif