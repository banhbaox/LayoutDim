// Copyright Kubotek Corporation, 1999-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose

#ifndef SYSWINDOW_H
#define SYSWINDOW_H

#include "ck_export.h"

enum
    {
    SYS_CAMERAEYE,
    SYS_EXPLORER_VIEW,
    SYS_MAGNIFY_VIEW,
    SYS_MANIPULATE_VIEW,
    SYS_CLIP_VIEW,
    SYS_ZOOM_VIEW,
    SYS_SEGMENT_VIEW,
    };

enum
    {
    CAMERA_MODE_TILT = 1,
    CAMERA_MODE_PAN,
    };

enum
    {
    SYS_CAMERA_MATRIX = 1,
    SYS_CAMERA_DATA,
    SYS_CAMERA_PAN,
    SYS_CAMERA_PAN_BASE,
    SYS_CAMERA_TILT,
    SYS_CAMERA_TILT_BASE,
    SYS_CAMERA_ZOOM,
    SYS_CAMERA_SCOPE,
    SYS_CAMERA_TILTMAX,
    SYS_CAMERA_SCOPESIZE,
    SYS_CAMERA_SCOPECOLOR,
    SYS_CAMERA_SCOPETRANS,
    SYS_CAMERA_MODE,
    NUM_SYS_CAMERA
    };

struct CAMERA_DATA
    {
    float fPos[3];
    float fTarget[3];
    float fUp[3];
    float fAngle;
    };

typedef void (*sys_window_func)(const CWnd*, int, PVOID);

SDK_FUNC int sys_window_count(int nType, int &nCount);
SDK_FUNC int sys_window_new(int nType,
                            int nOp = 0, PVOID pParam = NULL);
SDK_FUNC int sys_window_new(int nType, CWnd *&pWnd,
                            int nOp = 0, PVOID pParam = NULL);
SDK_FUNC int sys_window_get(int nType, int nIndex, CWnd *&pWnd);
SDK_FUNC int sys_window_get(const CWnd *pWnd, int nOp, PVOID pParam);
SDK_FUNC int sys_window_set(const CWnd *pWnd, int nOp, PVOID pParam);
SDK_FUNC int sys_window_close(int nType);
SDK_FUNC int sys_window_close(CWnd *pWnd);
SDK_FUNC int sys_window_callback(const CWnd *pWnd, sys_window_func pCallback);

#endif // SYSWINDOW_H
