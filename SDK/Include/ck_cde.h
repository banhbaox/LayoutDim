// Copyright Kubotek Corporation, 1999-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose
#ifndef CK_CDE_H_INCLUDED
#define CK_CDE_H_INCLUDED

// @doc EXTERNAL SDK
#ifndef SDK_EXPORT
#ifdef SDK_MAIN
#define SDK_EXPORT __declspec(dllexport)
#else
#define SDK_EXPORT __declspec(dllimport)
#endif
#endif

#define SDK_FUNC extern SDK_EXPORT

// @type INT_FPTR | A pointer to a function returning int
typedef int (*INT_FPTR)();

// @module Functions for handling CDEs |
//
// <f ck_cde_open> Load a CDE.
//
// <f ck_cde_close> Close a CDE that is loaded.
//
// <f ck_cde_load> Retrieve a pointer to a CDE function.
//
// <f ck_cde_unhide> Unhide a hidden CDE function
//
// <f ck_cde_handle> Retrieve a handle to a CDE by name
//
// <f ck_cde_parent> Retrieve a pointer to an overlay
// function's parent
//
// <f ck_cde_isexecutable> Determine if a function pointer returned
// by <f ck_cde_load> can be used.
//
// <f ck_cde_lock> Lock or Unlock a CDE, to prevent or allow
// unloading it, both through <f ck_cde_close> and CDE Close.
//
// <f ck_cde_names> gets the names of all the loaded CDEs.
//
// <f ck_cde_funcname> gets the names of all the functions available through
// CDE Execute.

SDK_FUNC void *ck_cde_open(const std::wstring &lpszFilename, bool bCount = true);

SDK_FUNC int ck_cde_close(void *pData);

SDK_FUNC const INT_FPTR *ck_cde_load(void *pData,
                                     const std::wstring &lpszFunctionName);

SDK_FUNC int ck_cde_unhide(const std::wstring &lpszFuncName,
                           const std::wstring &lpszPassword);

SDK_FUNC void *ck_cde_handle(const std::wstring &lpszName);

SDK_FUNC const INT_FPTR *ck_cde_parent(INT_FPTR pFunc);

SDK_FUNC int ck_cde_isexecutable(const INT_FPTR *pFunction);

SDK_FUNC void ck_cde_lock(void *pData, bool bLock);

SDK_FUNC void ck_cde_names(std::vector<std::wstring> &);

SDK_FUNC void ck_cde_funcnames(std::vector<std::wstring> &);

SDK_FUNC void ck_cde_set_resources(HMODULE hResources);

SDK_FUNC void ck_cde_set_helpfile(const std::wstring &lpszHelpFile);

#endif
