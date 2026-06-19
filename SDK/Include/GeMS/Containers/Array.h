
#ifndef _array_h_
#define _array_h_

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

#include "ArrayBase.h"

// Declarations of valid GeMS primitives.
//#pragma warning(disable: 4231)  // nonstandard extension used : 'identifier' before template explicit instantiation

GEMS_TEMPLATE(class, g_array<signed char>);
GEMS_TEMPLATE(class, g_array<unsigned char>);
GEMS_TEMPLATE(class, g_array<short>);
GEMS_TEMPLATE(class, g_array<unsigned short>);
GEMS_TEMPLATE(class, g_array<int>);
GEMS_TEMPLATE(class, g_array<unsigned int>);
GEMS_TEMPLATE(class, g_array<long>);
GEMS_TEMPLATE(class, g_array<unsigned long>);
#ifdef _WIN64
GEMS_TEMPLATE(class, g_array<ptrdiff_t>);
GEMS_TEMPLATE(class, g_array<size_t>);
#endif
GEMS_TEMPLATE(class, g_array<bool>);
GEMS_TEMPLATE(class, g_array<float>);
GEMS_TEMPLATE(class, g_array<double>);


#endif
