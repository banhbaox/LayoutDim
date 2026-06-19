
#ifndef _ptr_h_
#define _ptr_h_

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


#include "GeMS/Dcl_gems.h"

#include "GAtom.h"

enum GBehaviors
	{
	USE_COUNT_PTR		=1,			// Ptr increments use-count.
	REGISTERED_PTR		=2,			// Ptr is registered with referenced object.
	OMEGA_PTR			=4,			// When pointer is NULLed via the GAtom::forget()
									// method, ptr generates a g_forget() for its
									// owning atom.
	ALPHA_PTR			=8,			// An alpha pointer will "kill" the object it
									// references upon the pointer's death.
	GHOST_PTR			=16,		// Ptr is ghost image.  If USE_COUNT_PTR flag
									// is set, will also increment system-count.
									// Overrides 'REGISTERED_PTR' flag, forcing the
									// pointer to be unregistered.  (Mainly used
									// by rollback system.)
	LONG_LIVED_PTR		=32,		// Used only by weak pointers.  A long-lived
									// weak-ptr is guaranteed to not be broken until
									// all non-long-lived weak pointers referencing
									// the same object have been broken.  The long-
									// lived flag is primarily intended for use by
									// system resources.  It should not be used for
									// normal data modelling.
	DELAYED_PTR			=64,		// Used only by weak pointers.  Will delay the
									// breaking of the relationship until just prior
									// to the referenced object's destruction.
									// Delayed pointers cannot be saved to file (since
									// they may reference dead objects awaiting
									// destruction).
	PROCESSING_PTR		=128,		// Used by the GeMS memory management system.
	READ_PTR_FLAGS_FROM_FILE=256	// Allow the behavior flags to be read from file.
									// If true, the READ_PTR_FLAGS_FROM_FILE flag
									// itself will remain set after the read operation.
	};

typedef unsigned short g_behaviors;

const int WEAK_PTR = REGISTERED_PTR;
const int STRONG_PTR = USE_COUNT_PTR + REGISTERED_PTR;
const int OMEGA_WEAK_PTR = OMEGA_PTR + REGISTERED_PTR;
const int OMEGA_STRONG_PTR = OMEGA_PTR + USE_COUNT_PTR + REGISTERED_PTR;

class DECL_GEMS g_mutex;

class DECL_GEMS ptr_base
	{
	friend class DECL_GEMS g_stream;
	friend class DECL_GEMS g_copy_stream;
	friend class DECL_GEMS GAtom;
	friend DECL_GEMS void g_forget(ptr_base&);

	protected:
		GAtom*		_value;
		g_behaviors	_behaviors;
		GAtom*		_owner;

		ptr_base* _next_registered_ptr;
		ptr_base* _prev_registered_ptr;

		void behaviors(g_behaviors b);

		ptr_base(GAtom* right,g_behaviors behave,GAtom* dispatcher);

	public:
		ptr_base();
		ptr_base(GAtom* right,g_behaviors behave);
		ptr_base(const ptr_base& right,g_behaviors behave = STRONG_PTR);
		virtual ~ptr_base();

		g_behaviors behaviors() const { return _behaviors; }

		GAtom*	owner() const { return _owner; }
		void	owner(GAtom* p) { _owner = p; }

		void live_to_ghost();
		void ghost_to_live();

		bool operator!() const { return _value==0; }

		ptr_base& operator=(GAtom* right);
		ptr_base& operator=(const ptr_base& right);

		GAtom* cast() const	{ return _value; }

#if defined _DEBUG || defined _PSEUDO_DEBUG
		ptr_base* debug_next_registered_ptr() const { return _next_registered_ptr; }
			// Useful in debugging, but breaks encapsulation in a very
			// big way, so use ONLY for debugging purposes!!
#endif
	};

#ifdef _HAS_CPP0X
inline bool operator==(nullptr_t, const ptr_base &right)
    { return(right.cast() == nullptr); }

inline bool operator!=(nullptr_t, const ptr_base &right)
    { return(right.cast() != nullptr); }
#endif

class DECL_GEMS dyn_ptr_base : public ptr_base
	{
	friend class DECL_GEMS g_stream;

	protected:
		dyn_ptr_base(GAtom* right,g_behaviors b,GAtom* dispatcher):ptr_base(right,b,dispatcher){}

	public:
		dyn_ptr_base(GAtom* right=NULL,g_behaviors b = STRONG_PTR):ptr_base(right,b) {}
		dyn_ptr_base(const ptr_base& right,g_behaviors b):ptr_base(right,b) {}
		dyn_ptr_base(const dyn_ptr_base& right,g_behaviors b = 0):ptr_base(right,b) {}

		g_behaviors behaviors() const { return _behaviors; }
		void behaviors(g_behaviors b) { ptr_base::behaviors(b); }

		dyn_ptr_base& operator=(GAtom* right) { ptr_base::operator=(right); return *this; }
		dyn_ptr_base& operator=(const ptr_base& right) { ptr_base::operator=(right); return *this; }
		dyn_ptr_base& operator=(const dyn_ptr_base& right) { ptr_base::operator=(right); return *this; }
	};

template <class T> class smart_ptr : public ptr_base
	{
	private:
		smart_ptr(const smart_ptr<T>& right):ptr_base(right,STRONG_PTR) {}

	public:
		smart_ptr(T* v,g_behaviors behave):ptr_base((GAtom*&)v,behave) {}
		smart_ptr(const smart_ptr<T>& right,g_behaviors behave):ptr_base(right,behave) {}

		smart_ptr<T>& operator=(T* v) { ptr_base::operator=(reinterpret_cast<GAtom *>(v)); return *this; }
		smart_ptr<T>& operator=(const smart_ptr<T>& v) { ptr_base::operator=(v); return *this; }
		
		T* operator->() const	{ return (T*)_value; }

		T& operator*() const	{ return (T&)(*_value); }

		operator T* () const { return (T*)_value; }

		T* cast () const	{ return (T*)_value; }
	};

//template <class T> bool operator==(const T* left,const smart_ptr<T>& right)
//	{ return (right == left); }

//template <class T> bool operator!=(const T* left,const smart_ptr<T>& right)
//	{ return (right != left); }

/////////////////////////////////////////////////////////////////////////////////////
//
// The ptr<> represents the GeMS strong pointer.  Its name was shortened from
// strong_ptr<> to ptr<> simply because it is the most common type of pointer used.
// As a strong pointer, it owns and registers itself with the referenced object.
//
template <class T> class ptr : public smart_ptr<T>
	{
	public:
		ptr():smart_ptr<T>(NULL,STRONG_PTR) {}
		ptr(T* v):smart_ptr<T>(v,STRONG_PTR) {}
		ptr(const smart_ptr<T>& right):smart_ptr<T>(right,STRONG_PTR) {}
		ptr(const ptr<T>& right):smart_ptr<T>(right,STRONG_PTR) {}

		ptr<T>& operator=(T* v) { ptr_base::operator=(reinterpret_cast<GAtom *>(v)); return *this; }
		ptr<T>& operator=(const smart_ptr<T>& v)	{ ptr_base::operator=(v); return *this; }
		ptr<T>& operator=(const ptr<T>& v)			{ ptr_base::operator=(v); return *this; }
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// The hard_ptr<> represents the GeMS 'strongest' pointer type.  It is even stronger
// than the strong pointer ptr<>.  Hard_ptr<>s are unaffected by g_forgets(), and
// so can guarantee that the referenced object exists.  Their use is limitted,
// however.  They cannot be used as attributes of GAtoms, since they would prevent
// the GeMS memory management concepts from working properly.  However, they are
// useful as local variables in multi-threaded applications where one thread can
// never be sure that another will call a g_forget() on the object it is currently
// using.
//
template <class T> class hard_ptr : public smart_ptr<T>
	{
	public:
		hard_ptr():smart_ptr<T>(NULL,USE_COUNT_PTR) {}
		hard_ptr(T* v):smart_ptr<T>(v,USE_COUNT_PTR) {}
		hard_ptr(const smart_ptr<T>& right):smart_ptr<T>(right,USE_COUNT_PTR) {}
		hard_ptr(const hard_ptr<T>& right):smart_ptr<T>(right,USE_COUNT_PTR) {}

		hard_ptr<T>& operator=(T* v) { ptr_base::operator=(v); return *this; }
		hard_ptr<T>& operator=(const smart_ptr<T>& v)	{ ptr_base::operator=(v); return *this; }
		hard_ptr<T>& operator=(const hard_ptr<T>& v)	{ ptr_base::operator=(v); return *this; }
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// The ghost_ptr<> is primarily used by GeMS for system functions.  Its purpose
// is to provide a smart pointer type that will not prevent the death of the
// referenced object, but will prevent its destruction.  It does this by using
// the 'increment_system_count()' and 'decrement_system_count()' methods rather
// than the 'use()' and 'lose()' methods.  If a ghost_ptr<> is used as the
// first smart-reference to a new GAtom, it will NOT call its initialize() method.
// Thus, ghost_ptr<>s are usually not applicable to user-code.
//
template <class T> class ghost_ptr : public smart_ptr<T>
	{
	public:
		ghost_ptr():smart_ptr<T>(NULL,(g_behaviors)(USE_COUNT_PTR + GHOST_PTR)) {}
		ghost_ptr(T* v):smart_ptr<T>(v,(g_behaviors)(USE_COUNT_PTR + GHOST_PTR)) {}
		ghost_ptr(const smart_ptr<T>& right):smart_ptr<T>(right,(g_behaviors)(USE_COUNT_PTR + GHOST_PTR)) {}
		ghost_ptr(const ghost_ptr<T>& right):smart_ptr<T>(right,(g_behaviors)(USE_COUNT_PTR + GHOST_PTR)) {}

		ghost_ptr<T>& operator=(T* v) {ptr_base::operator=(v); return *this; }
		ghost_ptr<T>& operator=(const smart_ptr<T>& v)	{ ptr_base::operator=(v); return *this; }
		ghost_ptr<T>& operator=(const ghost_ptr<T>& v)	{ ptr_base::operator=(v); return *this; }
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// The dyn_ptr<> is simply a smart pointer whose behavior can be dynamically
// changed at run-time.  It is mainly used in collection classes so that a
// single collection implementation may be used for a variety of pointer types.
//
template <class T> class dyn_ptr : public dyn_ptr_base
	{
	public:
		dyn_ptr()
			:dyn_ptr_base(NULL,STRONG_PTR) {}
		dyn_ptr(T* v,g_behaviors behave=STRONG_PTR)
			:dyn_ptr_base(v,behave) {}
		dyn_ptr(const smart_ptr<T>& right,
			g_behaviors behave=STRONG_PTR)
			:dyn_ptr_base(right,behave) {}
		dyn_ptr(const dyn_ptr<T>& right,
			g_behaviors behave=STRONG_PTR)
			:dyn_ptr_base(right,behave) {}

		dyn_ptr<T>& operator=(T* v) {dyn_ptr_base::operator=(v); return *this; }
		dyn_ptr<T>& operator=(const smart_ptr<T>& v)	{ dyn_ptr_base::operator=(v); return *this; }
		dyn_ptr<T>& operator=(const dyn_ptr<T>& v)		{ dyn_ptr_base::operator=(v); return *this; }
		
		T* operator->() const	{ return (T*)_value; }

		T& operator*() const	{ return (T&)(*_value); }

		operator T*() const { return (T*)_value; }

		T* cast() const	{ return (T*)_value; }
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// The weak_ptr<> represents the GeMS weak pointer.  Its name was altered from
// its historical back_ptr<> to weak_ptr<> to more closely match the industry's
// terminology. A weak pointer does not own the referenced object but is NULLed
// out when the referenced object dies.
//
template <class T> class weak_ptr : public smart_ptr<T>
	{
	public:
		weak_ptr():smart_ptr<T>(NULL,WEAK_PTR) {}
		weak_ptr(T* v):smart_ptr<T>(v,WEAK_PTR) {}
		weak_ptr(const smart_ptr<T>& right):smart_ptr<T>(right,WEAK_PTR) {}
		weak_ptr(const weak_ptr<T>& right):smart_ptr<T>(right,WEAK_PTR) {}

		weak_ptr<T>& operator=(T* v) {ptr_base::operator=(reinterpret_cast<GAtom *>(v)); return *this; }
		weak_ptr<T>& operator=(const smart_ptr<T>& v)	{ ptr_base::operator=(v); return *this; }
		weak_ptr<T>& operator=(const weak_ptr<T>& v)	{ ptr_base::operator=(v); return *this; }
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// The omega_ptr<> represents a strong omega pointer.  Its name was shortened from
// strong_omega_ptr<> to omega_ptr<> since the strong pointer is named ptr<>.
// As a strong pointer, it owns and registers itself with the referenced object.
// As an omega pointer, it will trigger a g_forget() on its containing object
// whenever the GeMS system NULLs its value.
//
template <class T> class omega_ptr : public smart_ptr<T>
	{
	public:
		omega_ptr():smart_ptr<T>(NULL,OMEGA_STRONG_PTR) {}
		omega_ptr(T* v):smart_ptr<T>(v,OMEGA_STRONG_PTR) {}
		omega_ptr(const smart_ptr<T>& right):smart_ptr<T>(right,OMEGA_STRONG_PTR) {}
		omega_ptr(const omega_ptr<T>& right):smart_ptr<T>(right,OMEGA_STRONG_PTR) {}

		omega_ptr<T>& operator=(T* v) {ptr_base::operator=(reinterpret_cast<GAtom *>(v)); return *this; }
		omega_ptr<T>& operator=(const smart_ptr<T>& v) { ptr_base::operator=(v); return *this; }
		omega_ptr<T>& operator=(const omega_ptr<T>& v) { ptr_base::operator=(v); return *this; }
	};


/////////////////////////////////////////////////////////////////////////////////////
//
// The weak_omega_ptr<> represents a weak omega pointer. As a weak pointer,
// it does not own the referenced object and is NULLed when the referenced
// object dies. As an omega pointer, it will trigger a g_forget() on its
// containing object whenever the GeMS system NULLs its value.
//
template <class T> class omega_weak_ptr : public smart_ptr<T>
	{
	public:
		omega_weak_ptr():smart_ptr<T>(NULL,OMEGA_WEAK_PTR) {}
		omega_weak_ptr(T* v):smart_ptr<T>(v,OMEGA_WEAK_PTR) {}
		omega_weak_ptr(const smart_ptr<T>& right):smart_ptr<T>(right,OMEGA_WEAK_PTR) {}
		omega_weak_ptr(const omega_weak_ptr<T>& right):smart_ptr<T>(right,OMEGA_WEAK_PTR) {}

		omega_weak_ptr<T>& operator=(T* v) {ptr_base::operator=(reinterpret_cast<GAtom *>(v)); return *this; }
		omega_weak_ptr<T>& operator=(const smart_ptr<T>& v)			{ ptr_base::operator=(v); return *this; }
		omega_weak_ptr<T>& operator=(const omega_weak_ptr<T>& v)	{ ptr_base::operator=(v); return *this; }
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// The 'this_atom_ptr' is an object which points to the atomic object in which it resides.
// Like the 'this' pointer, the 'this_atom_ptr' is initialized by the system during the
// initialize() method and should not be changed thereafter.  If you override the initialize
// method and do not call the GAtom::initialize() method, it is your reponsibility to set
// the value of any this_atom_ptrs.  For it to be initialized by the system, a this_atom_ptr
// must appear in the stream of the atomic object.  It will also be re-initialized whenever
// the 'update' method of the atomic object is called (in case a new 'this_atom_ptr' has been
// added to the object somewhere).
class DECL_GEMS this_atom_ptr
	{
	friend class DECL_GEMS g_update_stream;

	protected:
		GAtom* _value;

	public:
		this_atom_ptr() { _value = 0; }
		this_atom_ptr(GAtom*) { _value = 0; }
		this_atom_ptr(const this_atom_ptr&) { _value = 0; }

		this_atom_ptr& operator=(GAtom* v) { _value = v; return *this; }
		this_atom_ptr& operator=(const this_atom_ptr& v) { _value = v._value; return *this; }

		bool operator!() const { return _value==0; }

		bool operator==(const GAtom* right) const { return (right==_value); }
		bool operator!=(const GAtom* right) const { return !operator==(right); }

		operator GAtom*() const		{ return _value; }
		
		GAtom* operator->() const	{ return _value; }

		GAtom& operator*() const	{ return (*_value); }

		GAtom* cast() const	{ return _value; }
	};

GEMS_TEMPLATE(class, smart_ptr<GAtom>);
GEMS_TEMPLATE(class, ptr<GAtom>);
GEMS_TEMPLATE(class, dyn_ptr<GAtom>);
GEMS_TEMPLATE(class, weak_ptr<GAtom>);
GEMS_TEMPLATE(class, omega_ptr<GAtom>);
GEMS_TEMPLATE(class, omega_weak_ptr<GAtom>);
GEMS_TEMPLATE(class, ghost_ptr<GAtom>);

void DECL_GEMS g_forget(GAtom* pAtom);
void DECL_GEMS g_forget(ptr_base& obj);
void DECL_GEMS g_forget(ghost_ptr<GAtom> obj);

// Thanks go to Greg Marr of CADKEY Corporation for this nifty casting macro.
#define G_DYNAMIC_DOWNCAST(cname, p) (cname::downcast(p))

#endif


