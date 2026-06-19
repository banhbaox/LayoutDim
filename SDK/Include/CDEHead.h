// Copyright Kubotek Corporation, 1999-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose

#ifndef CDEHEAD_INC
#define CDEHEAD_INC

#include <windows.h>
#include <tchar.h>

// Defines for CDE_data type fields
#define CDE_VOID         0x0000
#define CDE_UCHAR        0x0001
#define CDE_CHAR         0x0002
#define CDE_UINT         0x0003
#define CDE_INT          0x0004
#define CDE_USHORT       0x0005
#define CDE_SHORT        0x0006
#define CDE_ULONG        0x0007
#define CDE_LONG         0x0008
#define CDE_FLOAT        0x0009
#define CDE_DOUBLE       0x000A
#define CDE_STRING       0x000B
#define CDE_HANDLE       0x000C
#define CDE_PROTO        0x000D          // Unknown type, call function
#define CDE_BASICATTRIB  0x000E
#define CDE_ENTITYATTRIB 0x000F
#define CDE_REFARC       0x0010
#define CDE_WITNESSARC   0x0011
#define CDE_LEADERARC    0x0012
#define CDE_REFLINE      0x0013
#define CDE_WITNESS      0x0014
#define CDE_LEADER       0x0015
#define CDE_CSTRING      0x0016
#define CDE_BOOL         0x0017
#define CDE_CKSENTITY    0x0018
#define CDE_CKSLEVEL     0x0019
#define CDE_CKSLAYOUT    0x001A
#define CDE_CKSDRAWINST  0x001B
#define CDE_CKSCOPIOUS   0x001C
#define CDE_SIZET        0x001D

#define CDE_STRUCT(n)   ((n)+0x0020)
#define CDE_TYPE(n)     ((n)&0x0FFF)    // Just the type

// Special bits in the type field for modifiers
#define CDE_IN          0x1000    // Data is passed into the function only
#define CDE_OUT         0x2000    // Data is returned from the function only
#define CDE_INOUT       0x0000    // Data goes both ways
#define CDE_REFERENCE   0x4000    // The variable is a C++ reference.
#define CDE_FLAG(n)     ((n)>>12) // Just the flags

// Defines for CDE_code flags field
#define CDE_ANY         0x0000  // Place function anywhere
#define CDE_CLOSE       0x8000  // Call function when CDE is closed
#define CDE_OPEN        0x4000  // Call function when CDE is opened
#define CDE_FIRST       0x2000  // Place function first in overlay chain
#define CDE_LAST        0x1000  // Place function last in overlay chain
#define CDE_SYSTEM      0x0800  // System function
#define CDE_LOCKED      0x0200  // Overlays of this function are not allowed

#define CDEF_ROOT       0x0000
#define CDEF_IMMED      0x0001
#define CDEF_CLASSIC    0x0002
#define CDEF_TOOLBAR    0x0004
#define CDEF_GROUP      0x0008
#define CDEF_SEPARATOR  0x0010
#define CDEF_NOMODDB    0x0020
#define CDEF_BLANK      0x0040

/**
** Note:
**   CDE_data can be either function parameters, or structure members.
**   For functions:  the first name is the name of the function.
**                   the first dim is NULL.
**                   the first type is the number of paramters.
**                   the second entry is the name, dim, and type of the
**                           return value.
**                   the third entry is for the 1st parameter, etc...
**
**   For structures: the first name is the name of the structure.
**                   the first dim is NULL.
**                   the first type is the number of members.
**                   the second entry is the name, dim, and type of the
**                           1st. member.
**                   the third entry is for the 2nd. member, etc...
*/

struct CDE_data
    {
    LPCTSTR name;     // Name of data
    LPCTSTR dim;      // Array declaration, if any
    USHORT type;      // Type of data (see above)
    };

struct CDE_code
    {
    LPCTSTR lpszName;      // Function name
    LPCTSTR lpszHidePass;  // Hide password if any
    LPCTSTR lpszAlias;     // Alias if any
    USHORT  usFlags;       // Flag information
    const CDE_data *p;     // Parameter list
    int (*pFunc)();        // Function pointer
    };

struct CDE_CommonData
    {
    // The two different ways of specifying a title
    LPCTSTR lpszTitle;
    ULONG_PTR ulTitle;

    ULONG_PTR ulStatus;   // string table id for status/tooltip
    ULONG_PTR ulBitmap;   // id for the bitmap
    ULONG_PTR ulBitmapL;  // id for the large bitmap
    };

struct CDE_Function
    {
    USHORT usFuncHash;

    // The three different ways of specifying a function
    int (*pFunction)(ULONG);
    LPCTSTR lpszFunction;
    ULONG_PTR ulFunction;

    CDE_CommonData cd;

    ULONG ulFlags;    // the flags specified for the function
    ULONG ulPrompt;   // the prompt number
    LPCTSTR lpszClassic; // the location in the classic menus
    };

struct CDE_Funcmenu
    {
    CDE_CommonData cd;

    ULONG ulNumFunctions;  // the number of items in this funcmenu
    // Pointers to the functions.  If a pointer is null,
    // a separator is placed in that position.
    const CDE_Function **pFunctions;
    };

struct CDE_Button
    {
    // One and only one of these two pointers shall be non-NULL.
    const CDE_Function *pFunction;
    const CDE_Funcmenu *pFuncMenu;

    // Place a separator after this item in the automatically generated menu
    bool bSeparator;
    };

struct CDE_Appmenu
    {
    CDE_CommonData cd;

    ULONG ulNumButtons;          // number of buttons in this appmenu
    const CDE_Button **pButtons; // Pointers to the buttons
    };

struct CDE_App
    {
    CDE_CommonData cd;

    bool bCreatePopup;

    ULONG ulNumAppmenus;         // The number of app menus in this app
    const CDE_Appmenu **pMenus;  // Pointers to the app menus
    };

struct CDE_MenuItem;

struct CDE_Menu
    {
    CDE_CommonData cd;

    ULONG ulNumMenuItems;        // The number of items in this menu.
    const CDE_MenuItem **pItems; // Pointers to the items.
    };

struct CDE_MenuItem
    {
    // One and only one of these two pointers shall be non-NULL.
    const CDE_Function *pFunction;
    const CDE_Menu *pMenu;
    };

struct CDE_Popup
    {
    ULONG ulNumMenuItems;        // The number of popup menus in this menu.
    const CDE_MenuItem **pItems; // Pointers to the popup menus.
    };

struct CDE_Classic
    {
    LPCTSTR lpszMenu;
    ULONG_PTR ulText;
    };

struct CDE_module
    {
    short nCDEFuncs;                // Number of functions
    const CDE_code **apCDEFuncs;    // Function declaration section

    short nData;                    // Number of data types
    const CDE_data **apData;        // Data declaration section

    short nApps;                    // Number of applications
    const CDE_App **apApps;         // Application declaration section

    short nPopups;                  // Number of popups
    const CDE_Popup **apPopups;     // Popup declaration section

    short nImports;                 // Number of Import definitions
    const CDE_Function *pImports;   // Import declaration section

    short nExports;                 // Number of Export definitions
    const CDE_Function *pExports;   // Export declaration section

    short nFunctions;               // Number of unassociated functions
    const CDE_Function *pFunctions; // Unassociated function section

    short nCMenus;                  // Number of classic menus
    const CDE_Classic *pCMenus;     // Classic menu section

    LPCTSTR lpszHelpFile;           // Name of the help file.
    LPCTSTR lpszResource;           // Name of the resource dll.
    LPCTSTR lpszProduct;            // The product name
    };

#endif
