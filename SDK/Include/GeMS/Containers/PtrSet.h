
#ifndef _ptr_set_h_
#define _ptr_set_h_

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

#include "GeMS/GemsFnd/Ptr.h"
#include "GeMS/GemsFnd/Gsubatom.h"
#include "GeMS/Containers/Ginsert.h"
#include "GeMS/Containers/Avltree.h"

DECLARE_MINIMAL_GEMS_DLL_EXPORTS(GAtom,GEMS)
DECLARE_MINIMAL_GEMS_DLL_EXPORTS(GPtrSet,GEMS)
DECLARE_MINIMAL_GEMS_DLL_EXPORTS(GSetNode,GEMS)

template <class T> class smart_ptr_set;

class DECL_GEMS ptr_set_base : public ptr_container_base
	{
	friend class DECL_GEMS GPtrSet;

	protected:
		virtual GAvlTree* construct_container() const;

		GPtrSet* set() const { return (GPtrSet*)container(); }

		void insert(ptr_container_base::iterator&,bool& inserted,GAtom*);
		void insert(ptr_container_base::iterator&,bool& inserted,GAtom*,GInsertionType,const GAtom* = NULL);

	public:
		ptr_set_base();
		ptr_set_base(const ptr_set_base&);

		ptr_set_base(	g_behaviors b);
		ptr_set_base(	const ptr_set_base&, g_behaviors b);
		~ptr_set_base();

		ptr_set_base& operator=(const ptr_set_base& right);
 		bool operator==(const ptr_set_base& right) const;

		void stream(g_stream&);
			// The stream() method is rarely called directly.
			// Generally sets are streamed using the
			// aStream << aSet; syntax.

		std::pair<iterator,bool> insert(GAtom*);
			// Defaults to adding last but will not move
			// the element in the set if already contained.
		std::pair<iterator,bool> insert(GAtom*,GInsertionType,const GAtom* = NULL);
			// Inserts the passed value as indicated.  The
			// method supports the INSERT_FIRST, INSERT_LAST,
			// INSERT_BEFORE and INSERT_AFTER GInsertionTypes.
			// If the element is already in the set, it is
			// removed before re-insertion.  If the insertion
			// type is INSERT_ANYWHERE, it will add the new
			// element at the end of the set only if the 
			// element is not already contained within it.

		void swap(ptr_set_base&);
	};

template <class T> class ptr_set;
template <class T> class weak_ptr_set;

/////////////////////////////////////////////////////////////////////////////////////
//
// The smart_ptr_set<> is an abstract base class representing the GeMS pointer set.
// True to the definition of 'set', it disallows duplicate and NULL values.
//
template <class T> class smart_ptr_set : public ptr_set_base
	{
	public:
		typedef T* value_type;

		class iterator : public ptr_set_base::iterator
			{
			friend class smart_ptr_set<T>;

			protected:
				iterator(const ptr_set_base::iterator& i):ptr_set_base::iterator(i) {}
			public:
	            typedef typename smart_ptr_set<T>::value_type value_type;
	            typedef ptrdiff_t difference_type;
	            typedef difference_type distance_type;	// retained
	            typedef T* pointer;
	            typedef T& reference;

				iterator():ptr_set_base::iterator() {}
				iterator(const smart_ptr_set<T>& lst):ptr_set_base::iterator(lst) {}
				iterator(const GPtrSet* s):ptr_set_base::iterator((const GAvlTree*)s) {}
					// This is a dangerous constructor since it circumvents type checking.
					// However, it allows us to create sets of sets.

				iterator& operator=(const iterator& r) { ((ptr_set_base::iterator*)this)->operator=(r); return *this; }

				T* operator*()				{ return (T*)		((ptr_set_base::iterator*)this)->operator *(); }
				const T* operator* () const	{ return (const T*)	((ptr_set_base::iterator*)this)->operator *(); }
			};

		typedef std::pair<iterator,iterator> erange;
		typedef const iterator const_iterator;
		typedef iterator reverse_iterator;

	public:
		smart_ptr_set(g_behaviors b) : ptr_set_base(b) {}
		smart_ptr_set(const smart_ptr_set<T>& right, g_behaviors b) :
            ptr_set_base(right,b) {}

		smart_ptr_set<T>& operator=(const smart_ptr_set<T>& right)
			{ ptr_set_base::operator=(right); return *this; }

		std::pair<iterator,bool> insert(T* v,GInsertionType t = INSERT_ANYWHERE,const T* loc= NULL)
			{
			std::pair<iterator,bool> result;
			ptr_set_base::insert(result.first,result.second,reinterpret_cast<GAtom *>(v),t,reinterpret_cast<const GAtom *>(loc)); 
			return result;
			}

		size_type erase(T *v) { return ptr_set_base::erase(reinterpret_cast<GAtom *>(v)); }
		void erase(iterator &i)	{ ptr_set_base::erase(i); }
		void erase(iterator &f, iterator &s) { ptr_set_base::erase(f,s); }

		void swap(smart_ptr_set<T>& s) { ptr_set_base::swap(s); }

		bool contains(const T* p) const { return ptr_set_base::contains(reinterpret_cast<const GAtom *>(p)); }
		size_t count(const T* p) const { return ptr_set_base::count(reinterpret_cast<const GAtom *>(p)); }

		iterator begin() const	{ return ptr_set_base::begin(); }
		iterator end() const	{ return iterator(); }
		iterator rbegin() const	{ return ptr_set_base::rbegin(); }
		iterator rend() const	{ return iterator(); }

		iterator find(const T* v) const			{ iterator i; ptr_set_base::find(i,reinterpret_cast<const GAtom *>(v)); return i; }
		iterator lower_bound(const T* v) const	{ return ptr_set_base::lower_bound(reinterpret_cast<const GAtom *>(v)); }
		iterator upper_bound(const T* v) const	{ return ptr_set_base::upper_bound(reinterpret_cast<const GAtom *>(v)); }
		erange equal_range(const T* v) const	{ erange r; ptr_set_base::equal_range(reinterpret_cast<const GAtom *>(v),r.first,r.second); return r; }

		smart_ptr_set<T> operator+(const smart_ptr_set<T>& right) const
			{ smart_ptr_set<T> set(behaviors()); ptr_set_base::operator_plus(set,right); return set; }
		smart_ptr_set<T>& operator+=(const smart_ptr_set<T>& right)
			{ ptr_set_base::operator_plus_equals(right); return *this; }

		smart_ptr_set<T> operator-(const smart_ptr_set<T>& right) const
			{ smart_ptr_set<T> set(behaviors()); ptr_set_base::operator_minus(set,right); return set; }
		smart_ptr_set<T>& operator-=(const smart_ptr_set<T>& right)
			{ ptr_set_base::operator_minus_equals(right); return *this; }

		smart_ptr_set<T> operator&(const smart_ptr_set<T>& right) const
			{ smart_ptr_set<T> set(behaviors()); ptr_set_base::operator_and(set,right); return set; }
		smart_ptr_set<T>& operator&=(const smart_ptr_set<T>& right)
			{ ptr_set_base::operator_and_equals(right); return *this; }
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// The dyn_ptr_set<> represents the GeMS++ dynamic pointer set.  Its main
// characteristic that distinguishes it from other smart_ptr_set<> types is that
// its behaviors (STRONG, WEAK, etc.) can be dynamically changed at runtime. Like
// all sets, it disallows duplicate and NULL values.
//
template <class T> class dyn_ptr_set : public smart_ptr_set<T>
	{
	protected:
		dyn_ptr_set(const smart_ptr_set<T>& right) : smart_ptr_set<T>(right) {}

	public:
		dyn_ptr_set(const smart_ptr_set<T>& right,g_behaviors b) :
            smart_ptr_set<T>(right,b) {}
		dyn_ptr_set(g_behaviors b) : smart_ptr_set<T>(b) {}
		dyn_ptr_set(const dyn_ptr_set<T>& right, g_behaviors b) :
            smart_ptr_set<T>(right,b) {}

		g_behaviors behaviors() const { return smart_ptr_set<T>::behaviors(); }
		void behaviors(g_behaviors b) { smart_ptr_set<T>::behaviors(b); }

		dyn_ptr_set<T>& operator=(const smart_ptr_set<T>& right)
			{ ptr_set_base::operator=(right); return *this; }
		dyn_ptr_set<T>& operator=(const dyn_ptr_set<T>& right)
			{ ptr_set_base::operator=(right); return *this; }
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// The ptr_set<> represents the GeMS strong pointer set.  Its name was shortened from
// strong_ptr_set<> to ptr_set<> simply because it is the most common type of pointer
// set used. Since it contains strong pointers, each pointer owns and registers itself
// with the referenced object.  Like all sets, it disallows duplicate and NULL values.
//
template <class T> class ptr_set : public smart_ptr_set<T>
	{
	public:
		ptr_set():smart_ptr_set<T>((g_behaviors)STRONG_PTR) {}
		ptr_set(const smart_ptr_set<T>& right):smart_ptr_set<T>(right,(g_behaviors)STRONG_PTR) {}
		ptr_set(const ptr_set<T>& right):smart_ptr_set<T>(right,(g_behaviors)STRONG_PTR) {}

		ptr_set<T>& operator=(const smart_ptr_set<T>& right)
			{ ptr_set_base::operator=(right); return *this; }
		ptr_set<T>& operator=(const ptr_set<T>& right)
			{ ptr_set_base::operator=(right); return *this; }
	};



/////////////////////////////////////////////////////////////////////////////////////
//
// The weak_ptr_set<> represents the GeMS weak pointer set. Since it contains weak
// pointers, its elements do not own the referenced objects.  When the referenced
// objects die, the element is removed from the set by the GeMS system.  Like all
// sets, it disallows duplicate and NULL values.
//
template <class T> class weak_ptr_set : public smart_ptr_set<T>
	{
	public:
		weak_ptr_set():smart_ptr_set<T>((g_behaviors)WEAK_PTR) {}
		weak_ptr_set(const smart_ptr_set<T>& right):
						smart_ptr_set<T>(right,(g_behaviors)WEAK_PTR) {}
		weak_ptr_set(const weak_ptr_set<T>& right):
						smart_ptr_set<T>(right,(g_behaviors)WEAK_PTR) {}

		weak_ptr_set<T>& operator=(const smart_ptr_set<T>& right)
			{ ptr_set_base::operator=(right); return *this; }
		weak_ptr_set<T>& operator=(const weak_ptr_set<T>& right)
			{ ptr_set_base::operator=(right); return *this; }
	};


/////////////////////////////////////////////////////////////////////////////////////
//
// The omega_ptr_set<> acts like a ptr_set<> (a set of strong pointers) except that
// it produces a g_forget() request for its owning atom when the GeMS system takes
// its state from non-empty to empty.  Like all sets, it disallows duplicate and
// NULL values.
//
template <class T> class omega_ptr_set : public smart_ptr_set<T>
	{
	public:
		omega_ptr_set():smart_ptr_set<T>((g_behaviors)OMEGA_STRONG_PTR) {}
		omega_ptr_set(const smart_ptr_set<T>& right):
						smart_ptr_set<T>(right,(g_behaviors)OMEGA_STRONG_PTR) {}
		omega_ptr_set(const omega_ptr_set<T>& right):
						smart_ptr_set<T>(right,(g_behaviors)OMEGA_STRONG_PTR) {}

		omega_ptr_set<T>& operator=(const smart_ptr_set<T>& right)
			{ ptr_set_base::operator=(right); return *this; }
		omega_ptr_set<T>& operator=(const omega_ptr_set<T>& right)
			{ ptr_set_base::operator=(right); return *this; }
	};


/////////////////////////////////////////////////////////////////////////////////////
//
// The omega_weak_ptr_set<> acts like a weak_ptr_set<> (a set of weak pointers)
// except that it produces a g_forget() request for its owning atom when the GeMS
// system takes its state from non-empty to empty.  Like all sets, it disallows
// duplicate and NULL values.
//
template <class T> class omega_weak_ptr_set : public smart_ptr_set<T>
	{
	public:
		omega_weak_ptr_set():smart_ptr_set<T>((g_behaviors)OMEGA_WEAK_PTR) {}
		omega_weak_ptr_set(const smart_ptr_set<T>& right):
						smart_ptr_set<T>(right,(g_behaviors)OMEGA_WEAK_PTR) {}
		omega_weak_ptr_set(const omega_weak_ptr_set<T>& right):
						smart_ptr_set<T>(right,(g_behaviors)OMEGA_WEAK_PTR) {}

		omega_weak_ptr_set<T>& operator=(const smart_ptr_set<T>& right)
			{ ptr_set_base::operator=(right); return *this; }
		omega_weak_ptr_set<T>& operator=(const omega_weak_ptr_set<T>& right)
			{ ptr_set_base::operator=(right); return *this; }
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// The hard_ptr_set<> represents a local variable pointer set that guarantees
// that its contents will not die and the set will not change, regardless of the
// actions of other threads.  In this way, the 'hard' pointers contained within
// the collection temporarily interfere with some GeMS memory management operations.
// For example, any g_forget() request enacted by another thread will break all of
// the strong references to the 'forgotten' object, but since the hard pointer
// itself is not broken, the object is not allowed to 'die' until all hard
// references go away.  When that happens, the object will finally 'die' and any
// weak references to the object will be broken as well.  Thus, hard references
// should be used with care.  In most situations, a ghost_ptr_set<> should be used
// instead of a hard_ptr_set<>.
//
// It is illegal to use a hard_ptr_set<> as an attribute
// of a GAtom derived class.  (i.e. They cannot be saved to file.)
// Like all sets, hard_ptr_set<>s disallow duplicate and NULL values.
//
template <class T> class hard_ptr_set : public smart_ptr_set<T>
	{
	public:
		hard_ptr_set():smart_ptr_set<T>((g_behaviors)USE_COUNT_PTR) {}
		hard_ptr_set(const smart_ptr_set<T>& right):smart_ptr_set<T>(right,(g_behaviors)USE_COUNT_PTR) {}
		hard_ptr_set(const hard_ptr_set<T>& right):smart_ptr_set<T>(right,(g_behaviors)USE_COUNT_PTR) {}

		hard_ptr_set<T>& operator=(const smart_ptr_set<T>& right)
			{ ptr_set_base::operator=(right); return *this; }
		hard_ptr_set<T>& operator=(const hard_ptr_set<T>& right)
			{ ptr_set_base::operator=(right); return *this; }
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// The ghost_ptr_set<> represents a local variable pointer set that guarantees
// that its elements will not be unexpectedly removed, regardless of the actions
// of other threads.  Ghost pointer sets do not prevent the 'deaths' of the
// referenced objects, but they do prevent their actual destruction.  Consequently,
// a 'ghost' set is highly non-intrusive to the normal GeMS memory management
// operation.
//
// It is illegal to use a ghost_ptr_set<> as an attribute of a GAtom derived class.
// (i.e. They cannot be saved to file.) Ghost relationships are intended to be
// used as local variables.
//
// Like all sets, ghost_ptr_set<>s disallow duplicate and NULL values.
//
template <class T> class ghost_ptr_set : public smart_ptr_set<T>
	{
	public:
		ghost_ptr_set():smart_ptr_set<T>((g_behaviors)(USE_COUNT_PTR|GHOST_PTR)) {}
		ghost_ptr_set(const smart_ptr_set<T>& right):smart_ptr_set<T>(right,(g_behaviors)(USE_COUNT_PTR|GHOST_PTR)) {}
		ghost_ptr_set(const ghost_ptr_set<T>& right):smart_ptr_set<T>(right,(g_behaviors)(USE_COUNT_PTR|GHOST_PTR)) {}

		ghost_ptr_set<T>& operator=(const smart_ptr_set<T>& right)	{ ptr_set_base::operator=(right); return *this; }
		ghost_ptr_set<T>& operator=(const ghost_ptr_set<T>& right)	{ ptr_set_base::operator=(right); return *this; }
	};

#endif
