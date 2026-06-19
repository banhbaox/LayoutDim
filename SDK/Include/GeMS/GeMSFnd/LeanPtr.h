
#ifndef _LEAN_PTR_H_
#define _LEAN_PTR_H_

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

#include "Ptr.h"

/////////////////////////////////////////////////////////////////////////////////////
//
// Lean pointers are stripped down smart pointers.  To gain a speed and
// memory advantage, they have foregone the ability to register themselves
// with the referenced atom.  This causes the following restrictions:
//
//      1) They cannot be streamed to file (or any other high-level stream).
//         However, they can be streamed to fine-grained streams, which allows
//         them to participate in undo/redo.
//      2) They cannot be weak and cannot participate in g_forget()/omega
//         operations.

class DECL_GEMS lean_ptr_base
	{
	protected:
		GAtom*		_value;
		GAtom*		_owner;
		g_behaviors	_behaviors;

		lean_ptr_base(GAtom* right,g_behaviors behave,GAtom* dispatcher);

	public:
		lean_ptr_base(g_behaviors behave = USE_COUNT_PTR);
		lean_ptr_base(GAtom* right,g_behaviors behave = USE_COUNT_PTR);
		lean_ptr_base(const lean_ptr_base& right,g_behaviors behave = USE_COUNT_PTR);
		~lean_ptr_base();

		g_behaviors behaviors() const { return _behaviors; }
		void behaviors(g_behaviors b);

		GAtom*	owner() const { return _owner; }
		void	owner(GAtom* p) { _owner = p; }

		void live_to_ghost();
		void ghost_to_live();

		lean_ptr_base& operator=(GAtom* right);
		lean_ptr_base& operator=(const lean_ptr_base& right);

		bool operator!() const { return _value==0; }

		GAtom *cast() const	{ return _value; }

		void attach(GAtom* pValue)
			{
			if(_value)
				(*this) = nullptr;
			_value = pValue;
			}

		GAtom* detach()
			{
			GAtom* pValue = _value;
			_value = nullptr;
			return pValue;
			}
	};

#ifdef _HAS_CPP0X
inline bool operator==(nullptr_t, const lean_ptr_base &right)
    { return(right.cast() == nullptr); }

inline bool operator!=(nullptr_t, const lean_ptr_base &right)
    { return(right.cast() != nullptr); }
#endif

template <class T> class lean_smart_ptr : public lean_ptr_base
	{
	private:
		// A lean_smart_ptr should never be created itself, and so nothing should ever
		// directly call its copy constructor.
		lean_smart_ptr(const lean_smart_ptr<T>& right):lean_ptr_base(right,STRONG_PTR) {}

	public:
		lean_smart_ptr(T* v,g_behaviors behave) : 
          lean_ptr_base(reinterpret_cast<GAtom *>(v),behave) {}
		lean_smart_ptr(const lean_smart_ptr<T>& right,g_behaviors behave):lean_ptr_base(right,behave) {}

		lean_smart_ptr<T>& operator=(T* v)
            { lean_ptr_base::operator=(reinterpret_cast<GAtom *>(v)); return *this; }
		lean_smart_ptr<T>& operator=(const lean_smart_ptr<T>& v) { lean_ptr_base::operator=(v); return *this; }
		
		T*			operator->()		{ return (T*)_value; }
		const T*	operator->() const	{ return (const T*)_value; }

		T&			operator*()			{ return (T&)(*_value); }
		const T&	operator*() const	{ return (const T&)(*_value); }

		operator T* () const { return (T*)_value; }

		T*			cast ()			{ return (T*)_value; }
		const T*	cast () const	{ return (const T*)_value; }
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// The lean_hard_ptr<> is a strong smart pointer that does not register itself
// with its referenced atom.  Therefore, it cannot be nullptred via a g_forget()
// or alpha/omega operation.  It also cannot be saved to file but can participate
// in undo/redo.
//
template <class T> class lean_hard_ptr : public lean_smart_ptr<T>
	{
	public:
		lean_hard_ptr():lean_smart_ptr<T>(nullptr,USE_COUNT_PTR) {}
		lean_hard_ptr(T* v):lean_smart_ptr<T>(v,USE_COUNT_PTR) {}
		lean_hard_ptr(const lean_smart_ptr<T>& right):lean_smart_ptr<T>(right,USE_COUNT_PTR) {}
		lean_hard_ptr(const lean_hard_ptr<T>& right):lean_smart_ptr<T>(right,USE_COUNT_PTR) {}

		lean_hard_ptr<T>& operator=(T* v) { lean_ptr_base::operator=(reinterpret_cast<GAtom *>(v)); return *this; }
		lean_hard_ptr<T>& operator=(const lean_smart_ptr<T>& v)	{ lean_ptr_base::operator=(v); return *this; }
		lean_hard_ptr<T>& operator=(const lean_hard_ptr<T>& v)		{ lean_ptr_base::operator=(v); return *this; }
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// If the other GeMS++ pointer types are "smart", then blind_ptr<>s can
// accurately be described as "stupid".  Although technically they are
// smart pointers, they actually do almost nothing that a normal C++ pointer
// can't do.  They don't increment any use-counts and cannot register themselves
// with their referenced atoms.  Therefore, blind pointers may dangle!  Be careful
// in their use.  They are particularly dangerous in multithreaded apps.  Their
// single redeeming virtue is that they can participate in undo/redo and are no
// larger than a normal C++ pointer.  Blind pointers are burdened with the
// following restrictions:
//
//      1) They cannot be streamed to file (or any other high-level stream).
//         However, they can be streamed to fine-grained streams (which is 
//         what allows them to participate in undo/redo).
//      2) They cannot be strong or weak and cannot participate in g_forget()/
//         omega operations.
//      3) Their behavior is fixed (as doing nothing) (thus their behavior cannot
//         be dynamically changed at runtime).
//      4) They may dangle.  Preventing this occurance is entirely up to you.

class DECL_GEMS blind_ptr_base
	{
	protected:
		GAtom*		_value;

	public:
		blind_ptr_base() { _value = nullptr; }
		blind_ptr_base(GAtom* right) { _value = right; }
		blind_ptr_base(const blind_ptr_base& right) { _value = right._value; }

		bool operator!() const { return _value==nullptr; }

		blind_ptr_base& operator=(GAtom* right) { _value = right; return *this; }
		blind_ptr_base& operator=(const blind_ptr_base& right) { _value = right._value; return *this; }

		GAtom *cast() const	{ return _value; }
	};

#ifdef _HAS_CPP0X
inline bool operator==(nullptr_t, const blind_ptr_base &right)
    { return(right.cast() == nullptr); }

inline bool operator!=(nullptr_t, const blind_ptr_base &right)
    { return(right.cast() != nullptr); }
#endif

template <class T> class blind_ptr : public blind_ptr_base
	{
	public:
		blind_ptr():blind_ptr_base() {}
		blind_ptr(T* v):blind_ptr_base(v) {}
		blind_ptr(const blind_ptr<T>& right):blind_ptr_base(right) {}

		blind_ptr<T>& operator=(T* v) { blind_ptr_base::operator=(v); return *this; }
		blind_ptr<T>& operator=(const blind_ptr<T>& v) { blind_ptr_base::operator=(v); return *this; }
		
		T *operator->() const	{ return  (T*)_value; }
		T &operator*() const	{ return *(T*)_value; }
		operator T*() const     { return  (T*)_value; }
		T *cast() const	        { return  (T*)_value; }
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// Extra lean pointers are highly stripped down smart pointers.  In
// fact, they are as bare-bones as possible, storing no other information
// than the pointer value itself.  Because of this, they are burdened with
// the following restrictions:
//
//      1) They cannot be streamed at all (causing them to lose file I/O
//         and undo/redo capability)
//      2) They cannot register themselves with the referenced atom (and
//         so cannot be weak and cannot participate in g_forget()/omega
//         operations).
//      3) Their behavior is fixed (thus the behavior cannot be
//         dynamically changed at runtime).

template <class T> class extra_lean_ghost_ptr
	{
	public:
		extra_lean_ghost_ptr() { m_pValue=nullptr; }

		extra_lean_ghost_ptr(const T* pT)
			{
			m_pValue = const_cast<T*>(pT);
			if(m_pValue)
				m_pValue->increment_system_count();
			}

		extra_lean_ghost_ptr(const extra_lean_ghost_ptr<T>& pT)
			{
			m_pValue = pT.m_pValue;
			if(m_pValue != nullptr)
				m_pValue->increment_system_count();
			}

		~extra_lean_ghost_ptr()
			{
			if(m_pValue)
				m_pValue->decrement_system_count();
			}

		operator T*() const { return m_pValue; }

		T& operator*() const
			{
			G_ASSERT(m_pValue!=nullptr);
			return *m_pValue;
			}

		T* cast() const { return m_pValue; }

		T* operator->() const
			{
			G_ASSERT(m_pValue!=nullptr);
			return m_pValue;
			}

		const extra_lean_ghost_ptr<T>& operator=(T* pT)
			{
			if(pT)
				pT->increment_system_count();
			if(m_pValue)
				m_pValue->decrement_system_count();
			m_pValue = pT;
			return *this;
			}

		const extra_lean_ghost_ptr<T>& operator=(const extra_lean_ghost_ptr<T>& lp)
			{
			if(lp.m_pValue)
				lp.m_pValue->increment_system_count();
			if(m_pValue)
				m_pValue->decrement_system_count();
			m_pValue = lp.m_pValue;
			return *this;
			}

		bool operator!() const { return !m_pValue; }

		void attach(T* pT)
			{
			if(m_pValue)
				m_pValue->decrement_system_count();
			m_pValue = pT;
			}

		T* detach()
			{
			T* pT = m_pValue;
			m_pValue = nullptr;
			return pT;
			}

	private:
		T* m_pValue;
	};

// An extra-lean hard pointer cannot support death and resurrection and so has
// very limited utility.
template <class T> class extra_lean_hard_ptr
	{
	public:
		extra_lean_hard_ptr() { m_pValue=nullptr; }

		extra_lean_hard_ptr(const T* pT)
			{
			m_pValue = const_cast<T*>(pT);
			if(m_pValue)
				m_pValue->use();
			}

		extra_lean_hard_ptr(const extra_lean_hard_ptr<T>& pT)
			{
			m_pValue = pT.m_pValue;
			if(m_pValue != nullptr)
				m_pValue->use();
			}

		~extra_lean_hard_ptr()
			{
			if(m_pValue)
				m_pValue->lose();
			}

		operator T*() const { return m_pValue; }

		T& operator*() const
			{
			G_ASSERT(m_pValue!=nullptr);
			return *m_pValue;
			}

		T* cast() const { return m_pValue; }

		T* operator->() const
			{
			G_ASSERT(m_pValue!=nullptr);
			return m_pValue;
			}

		const extra_lean_hard_ptr<T>& operator=(T* pT)
			{
			if(pT)
				pT->use();
			if(m_pValue)
				m_pValue->lose();
			m_pValue = pT;
			return *this;
			}

		const extra_lean_hard_ptr<T>& operator=(const extra_lean_hard_ptr<T>& lp)
			{
			if(lp.m_pValue)
				lp.m_pValue->use();
			if(m_pValue)
				m_pValue->lose();
			m_pValue = lp.m_pValue;
			return *this;
			}

		bool operator!() const { return !m_pValue; }

		void attach(T* pT)
			{
			if(m_pValue)
				m_pValue->lose();
			m_pValue = pT;
			}

		T* detach()
			{
			T* pT = m_pValue;
			m_pValue = nullptr;
			return pT;
			}

	private:
		T* m_pValue;
	};

#endif
