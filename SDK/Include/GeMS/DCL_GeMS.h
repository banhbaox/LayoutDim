
//////////////////////////////////////////////////////////////////////
//
//      *GeMS++ V6.1
//
//      * U.S. Patent #6,421,690
//
//      © Honeywell Federal Manufacturing & Technologies, LLC, 2002
//
//  NOTICE: These data were produced by Honeywell Federal Manufacturing & Technologies, LLC 
//  under Contract No. DE-AC04-01AL66850 with the Department of Energy.  For 5 years 
//  from 4/1/2003, the Government is granted for itself and others acting on its behalf 
//  a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, 
//  prepare derivative works, and perform publicly and display publicly by or on behalf 
//  of the Government.  There is provision for the possible extension of the term of this 
//  license.  Subsequent to that period or any extension granted, the Government is granted 
//  for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide 
//  license in this data to reproduce, prepare derivative works, distribute copies to the
//  public, perform publicly and display publicly, and to permit others to do so.  The specific 
//  term of the license can be identified by inquiry made to the Contractor or DOE.  Neither 
//  the United States nor the United States Department of Energy, nor any of their employees, 
//  makes any warranty, express or implied, or assumes any legal liability or responsibility 
//  for the accuracy, completeness, or usefulness of any data, apparatus, product, or process 
//  disclosed, or represents that its use would not infringe privately owned rights.
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

/* $Id: DCL_GEMS.H,v 1.2 2004/02/12 00:24:27 jkirk Exp $ */

#ifndef DECL_GEMS

#pragma warning(disable: 4786)  // 'identifier' : identifier was truncated to 'number' characters in the debug information
//#pragma warning(disable: 4231)  // nonstandard extension used : 'identifier' before template explicit instantiation
#pragma warning(disable: 4251)  // using non-exported as public in exported

// This header file assumes that, during a build of the GeMS library,
// the macro 'EXPORT_GEMS' will be defined (by being passed in as
// a /D directive into the compiler.)  If the EXPORT_GEMS macro is
// not defined, the header assumes that the GeMS header files are
// simply being included by other libraries to use the functionality of
// GeMS as an imported library.

// In addition, during the GeMS build, this header assumes that one
// of the GeMS files will itself define the macro 'GENERATE_TEMPLATES'.
// This will be the file into which the compiler will be directed to
// expand all templates so that their implementations can be exported.

#include "GemsVersion.h"

#ifdef EXPORT_GEMS
#  ifndef _MSC_VER
#    define GEMS_TEMPLATE(x, ...) 
#    define DECL_GEMS  
#  else
#    define GEMS_TEMPLATE(x, ...) template x DECL_GEMS __VA_ARGS__
#    define DECL_GEMS __declspec(dllexport)
#  endif
#else
#  ifndef _MSC_VER
#    define GEMS_TEMPLATE(x, ...)
#    define DECL_GEMS  
#  else
#    define GEMS_TEMPLATE(x, ...) extern template x DECL_GEMS __VA_ARGS__
#    define DECL_GEMS __declspec(dllimport)
#    ifdef _WIN64
#      ifdef _DEBUG
#        pragma comment( lib, "Gems64du.lib") /* Debug Library x64 */
#      else
#        pragma comment( lib, "Gems64u.lib") /* Release Library x64 */
#      endif
#    else
#      ifdef _DEBUG
#        pragma comment( lib, "Gemsdu.lib") /* Debug Library */
#      else
#        pragma comment( lib, "Gemsu.lib") /* Release Library */
#      endif
#    endif
#  endif
#endif

#endif
