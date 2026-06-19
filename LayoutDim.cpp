#include "StdAfx.h"

static AFX_EXTENSION_MODULE LayoutDimDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    if(dwReason == DLL_PROCESS_ATTACH)
    {
        AfxInitExtensionModule(LayoutDimDLL, hInstance);
        new CDynLinkLibrary(LayoutDimDLL);
    }
    else if(dwReason == DLL_PROCESS_DETACH)
    {
        AfxTermExtensionModule(LayoutDimDLL);
    }
    return 1;
}
