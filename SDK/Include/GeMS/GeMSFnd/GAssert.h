
//////////////////////////////////////////////////////////////////////
//
//  	*GeMS++ V6.1
//
//      * U.S. Patent #6,421,690
//
//  	© Honeywell Federal Manufacturing & Technologies, LLC, 2002
//
//	NOTICE:	These data were produced by Honeywell Federal Manufacturing & Technologies, LLC 
//	under Contract No. DE-AC04-01AL66850 with the Department of Energy.  For 5 years 
//	from 4/1/2003, the Government is granted for itself and others acting on its behalf 
//	a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, 
//	prepare derivative works, and perform publicly and display publicly by or on behalf 
//	of the Government.  There is provision for the possible extension of the term of this 
//	license.  Subsequent to that period or any extension granted, the Government is granted 
//	for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide 
//	license in this data to reproduce, prepare derivative works, distribute copies to the
//	public, perform publicly and display publicly, and to permit others to do so.  The specific 
//	term of the license can be identified by inquiry made to the Contractor or DOE.  Neither 
//	the United States nor the United States Department of Energy, nor any of their employees, 
//	makes any warranty, express or implied, or assumes any legal liability or responsibility 
//	for the accuracy, completeness, or usefulness of any data, apparatus, product, or process 
//	disclosed, or represents that its use would not infringe privately owned rights.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
//      This file may be sub-licensed and distributed in an unmodified
//      form to End Users, but only by a Licensee posessing a valid
//      Honeywell International Inc., Federal Manufacturing & Technology
//      Software License Agreement for Software Developers, Resellers
//      and Distributors of the FB-Tools software system.
//
//      Along with this header, the following .lib files may also
//      be sub-licensed and distributed under the same conditions:
//
//           Gems.lib,       Gemsd.lib,
//           GemsDll.lib,    GemsDlld.lib,
//           GemsDllm.lib,   GemsDlldm.lib,
//           GemsDllmu.lib,  GemsDlldmu.lib,
//           GemsDllu.lib,   GemsDlldu.lib
//
//////////////////////////////////////////////////////////////////////////

#ifndef _gassert_h_
#define _gassert_h_

#include "GeMS/Dcl_gems.h"
#include "GeMS/Utility/GBasicString.h"

#ifndef ASSERT
#  define ASSERT G_ASSERT
#endif

// Use the G_ASSERT macro if you want to use the GeMS exported _GAssert() function
// rather than your own.  (This can be handy if you are getting a name clash with
// ASSERT.)
#ifndef G_ASSERT
#if defined (_DEBUG) || defined (_PSEUDO_DEBUG)

#ifndef _MFC_VER
#define SKIPWORKAROUND
#endif

#include <BugSlayerUtil.h>

#define G_ASSERT(f) ASSERT(f)

#define G_FAIL_ASSERT(f)                                            \
do                                                                  \
    {                                                               \
    /* The local instance of the ignore count and the total hits. */\
    static int sIgnoreCount = 0 ;                                   \
    static int sFailCount   = 0 ;                                   \
    /* The local stack and frame at the assertion's location. */    \
    REG_TYPE dwAssertStack ;                                        \
    REG_TYPE dwAssertStackFrame ;                                   \
    /* Houston, we have a problem. */                               \
    GET_STACK_POINTER ( ) ;                                         \
    GET_FRAME_POINTER ( ) ;                                         \
    if ( TRUE == SuperAssertion ( L"Failure"                  ,     \
                                  f                           ,     \
                                  TEXT ( __FUNCTION__ )       ,     \
                                  TEXT ( __FILE__ )           ,     \
                                  __LINE__                    ,     \
                                  SUPERASSERT_EMAIL           ,     \
                                  (DWORD64)dwAssertStack      ,     \
                                  (DWORD64)dwAssertStackFrame ,     \
                                  &sFailCount                 ,     \
                                  &sIgnoreCount                ) )  \
        {                                                           \
        BREAK_IN ( ) ;                                              \
        }                                                           \
    } while(0)

#else

#define G_ASSERT(f)         ((void)0)
#define G_FAIL_ASSERT(s)    ((void)0)

// End If _DEBUG
#endif

// End If G_ASSERT
#endif

#endif
