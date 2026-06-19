
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


#ifndef gsubatom_h
#define gsubatom_h 1

#include "GeMS/Dcl_gems.h"

class DECL_GEMS g_stream;
class DECL_GEMS g_forget_event;


//	The g_sub_atom exists to provide a 'hook' into the GeMS++
//	streaming mechanisms for support classes intended to be
//	embedded directly within objects derived from GAtom.
//	For example, the ptr_set<>s and ptr_list<>s are derived
//	from g_sub_atom and override the g_sub_atom stream()
//	method to provide their own streaming capabilities.

class DECL_GEMS g_sub_atom 
	{
	public:
		g_sub_atom() {}
		virtual ~g_sub_atom() {}
		
		virtual void stream (g_stream&) {}
		
		virtual bool is_affected_by(const g_forget_event&) const;
		virtual void forget(const g_forget_event&);
		virtual void forget_ghost(const g_forget_event&);

		virtual void* unknown() const { return 0; }
	};

#endif
