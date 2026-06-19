
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

#ifndef _g_error_h_
#define _g_error_h_


#include "GeMS/Dcl_gems.h"
#include "GeMS/Utility/Gstring.h"

class DECL_GEMS g_error
	{
	private:
		unsigned short	_code;
		g_string		_message;
	public:
		g_error() { _code = 0; }
		g_error(unsigned short err_code,const wchar_t *m):
			_message(m) { _code = err_code; }
		g_error(unsigned short err_code,const std::wstring &m):
			_message(m) { _code = err_code; }
		virtual ~g_error() { }

		virtual const wchar_t *message() const
						{ return _message; }
		void message(const wchar_t *m)
						{ _message = m; }

		unsigned short code() const { return _code; }
		void code(unsigned short c) { _code = c; }

		enum error_codes
			{
			ILLEGAL_ERROR = 0,
			ILLEGAL_PRIMITIVE_TYPE,
			ILLEGAL_TYPE,
			INSUFFICIENT_MEMORY,
			EXCEPTION_DURING_ROLLBACK,
			EXCEPTION_DURING_CALLBACK,
			SEMAPHORE_CREATION_ERROR,
			SEMAPHORE_DESTRUCTION_ERROR,
			SEMAPHORE_OPERATION_FAILED,
			SEMAPHORE_TIME_OUT,
			OBJECT_UNAVAILABLE,
			MONIKER_CANNOT_BE_RESOLVED,
			UNDO_REDO_DISABLED,
			ILLEGAL_OPERATION,
			FILE_ERROR,
			NUM_GEMS_ERROR_CODES,
			};
	};

class DECL_GEMS g_rollback_error : public g_error
	{
	public:
		g_rollback_error():g_error() {}
		g_rollback_error(unsigned short err_code,const wchar_t *m):
			g_error(err_code,m) {}
	};

class DECL_GEMS g_timeout_error : public g_error
	{
	public:
		g_timeout_error():g_error(SEMAPHORE_TIME_OUT,L"") {}
		g_timeout_error(const wchar_t *m):
			g_error(SEMAPHORE_TIME_OUT,m) {}
	};

#endif
