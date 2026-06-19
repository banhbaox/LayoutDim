
#ifndef _sorted_ptr_set_h_
#define _sorted_ptr_set_h_

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

#include "GeMS/Containers/SortedTree.h"

template <class T> class sorted_smart_ptr_set;

class DECL_GEMS sorted_ptr_set_base : public sorted_ptr_container_base
	{
	private:
		// Do not allow copy constructor since behaviors  
		// should not simply be copied.  Do not implement this function.
		sorted_ptr_set_base(const sorted_ptr_set_base& right);

	public:
		sorted_ptr_set_base(const comparator<GAtom>*,
							g_behaviors Behaviors);
		sorted_ptr_set_base(const sorted_ptr_set_base&,
							g_behaviors Behaviors);

		sorted_ptr_set_base& operator=(const sorted_ptr_set_base& right);

		void swap(sorted_ptr_set_base& s) { sorted_ptr_container_base::swap(s); }
	};


/////////////////////////////////////////////////////////////////////////////////////
//
// The sorted_smart_ptr_set<> is an abstract base class representing the GeMS
// sorted pointer set.  It keeps its elements in the order determined by the
// comparator given in its constructor.  True to the definition of 'set',
// it disallows duplicate and NULL values.
//
template <class T> class sorted_smart_ptr_set : public sorted_ptr_set_base
	{
	private:
		// Do not allow copy constructor since behaviors  
		// should not simply be copied.  Do not implement this function.
		sorted_smart_ptr_set(const sorted_smart_ptr_set &right);

	public:
		//////////////////////////////////
		// iterator
		class iterator : public sorted_ptr_container_base::iterator
			{
			friend class sorted_smart_ptr_set<T>;
			protected:
				iterator(const sorted_ptr_container_base::iterator& i):sorted_ptr_container_base::iterator(i) {}
			public:
	            typedef typename sorted_smart_ptr_set<T>::value_type value_type;
	            typedef ptrdiff_t difference_type;
	            typedef difference_type distance_type;	// retained
	            typedef T* pointer;
	            typedef T& reference;
				iterator():sorted_ptr_container_base::iterator() {}
				iterator(const iterator& i):sorted_ptr_container_base::iterator(i) {}
				iterator(GSortedTree* s):sorted_ptr_container_base::iterator((GAvlTree*)s) {}

				iterator& operator=(const iterator& i) { ((sorted_ptr_container_base::iterator*)this)->operator=(i); return *this; }

				T* operator*()				{ return (T*)		((sorted_ptr_container_base::iterator*)this)->operator *(); }
				const T* operator* () const	{ return (const T*)	((sorted_ptr_container_base::iterator*)this)->operator *(); }
 			};
		typedef std::pair<iterator,iterator> erange;
		typedef const iterator const_iterator;
		typedef iterator reverse_iterator;

		sorted_smart_ptr_set(
						const sorted_smart_ptr_set& right,
						g_behaviors behave)
				:sorted_ptr_set_base(right,behave) {}

		sorted_smart_ptr_set(
						const comparator<T>* compIn,
						g_behaviors behave)
				:sorted_ptr_set_base((comparator<GAtom>*)compIn,behave) {}

		/////////////////////////////////////
		// System methods.
		sorted_smart_ptr_set<T>& operator=(const sorted_smart_ptr_set<T>& right)
			{ sorted_ptr_set_base::operator=(right); return *this; }

		/////////////////////////////////////
		// Functional methods.
		bool contains(const T* p) const						{ return sorted_ptr_set_base::contains(reinterpret_cast<const GAtom *>(p)); }
		bool contains(const self_comparator<T>* comp) const	{ return sorted_ptr_set_base::contains((self_comparator<GAtom>*)comp); }

		const comparator<T>* content_comparator() const		{ return (const comparator<T>*)sorted_ptr_set_base::content_comparator(); }

		size_t count(const T* p) const						{ return sorted_ptr_set_base::count(reinterpret_cast<const GAtom *>(p)); }
		size_t count(const self_comparator<T>* comp) const	{ return sorted_ptr_set_base::count((self_comparator<GAtom>*)comp); }

		iterator begin() const	{ return sorted_ptr_set_base::begin(); }
		iterator end() const	{ return iterator(); }
		iterator rbegin() const	{ return sorted_ptr_set_base::rbegin(); }
		iterator rend() const	{ return iterator(); }

		iterator find(const T* v) const			{ iterator i; sorted_ptr_set_base::find(i,reinterpret_cast<const GAtom *>(v)); return i; }
		iterator lower_bound(const T* v) const	{ return sorted_ptr_set_base::lower_bound(reinterpret_cast<const GAtom *>(v)); }
		iterator upper_bound(const T* v) const	{ return sorted_ptr_set_base::upper_bound(reinterpret_cast<const GAtom *>(v)); }
		erange equal_range(const T* v) const	{ erange r; sorted_ptr_set_base::equal_range_iterators(reinterpret_cast<const GAtom *>(v),r.first,r.second); return r; }

		iterator find(const self_comparator<T>* c) const		{ iterator i; sorted_ptr_set_base::find(i,(self_comparator<GAtom>*)c); return i; }
		iterator lower_bound(const self_comparator<T>* c) const	{ return sorted_ptr_set_base::lower_bound((self_comparator<GAtom>*)c); }
		iterator upper_bound(const self_comparator<T>* c) const	{ return sorted_ptr_set_base::upper_bound((self_comparator<GAtom>*)c); }
		erange equal_range(const self_comparator<T>* c) const	{ erange r; sorted_ptr_set_base::equal_range_iterators((self_comparator<GAtom>*)c,r.first,r.second); return r; }

		std::pair<iterator,bool> insert(T* v)
			{
			std::pair<iterator,bool> result;
			sorted_ptr_set_base::insert(result.first,result.second,reinterpret_cast<GAtom *>(v));
			return result;
			}

		size_type erase(T* v) { return sorted_ptr_set_base::erase(reinterpret_cast<GAtom *>(v)); }
		size_type erase(const self_comparator<T>* comp)	{ return sorted_ptr_set_base::erase((self_comparator<GAtom>*)comp); }
		void erase(iterator& i)							{ sorted_ptr_set_base::erase(i); }
		void erase(iterator& f,iterator& s)				{ sorted_ptr_set_base::erase(f,s); }

		void swap(sorted_smart_ptr_set<T>& s) { sorted_ptr_set_base::swap(s); }

		//////////////////////////////////////
		// Operators
		sorted_smart_ptr_set<T>& operator+=(const sorted_smart_ptr_set<T>& right)
			{ sorted_ptr_set_base::operator_plus_equals(right); return *this; }

		sorted_smart_ptr_set<T>& operator-=(const sorted_smart_ptr_set<T>& right)
			{ sorted_ptr_set_base::operator_minus_equals(right); return *this; }

		sorted_smart_ptr_set<T>& operator&=(const sorted_smart_ptr_set<T>& right)
			{ sorted_ptr_set_base::operator_and_equals(right); return *this; }
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// The sorted_ptr_set<> represents the GeMS strong pointer sorted_set.  Its name
// was shortened from sorted_strong_ptr_set<> to sorted_ptr_set<> simply because it
// is the most common type of sorted pointer set used. Since it contains strong
// pointers, each pointer owns and registers itself with the referenced object.  Like
// all sets, it disallows duplicate and NULL values.
//
// Note that it has no default constructor.  Since it is an 'sorted' collection,
// the user must, at the very least, provide the criteria by which the collection
// should be sorted.  This is done by providing a pointer to a comparator<T>.
//
template <class T> class sorted_ptr_set : public sorted_smart_ptr_set<T>
	{
	public:
		sorted_ptr_set(const comparator<T>* compIn):sorted_smart_ptr_set<T>(compIn,STRONG_PTR) {}
		sorted_ptr_set(const sorted_smart_ptr_set<T>& right):
			sorted_smart_ptr_set<T>(right,STRONG_PTR) {}
		sorted_ptr_set(const sorted_ptr_set<T>& right):
			sorted_smart_ptr_set<T>(right,STRONG_PTR) {}

		sorted_ptr_set<T>& operator=(const sorted_smart_ptr_set<T>& right)
			{ sorted_ptr_set_base::operator=(right); return *this; }
		sorted_ptr_set<T>& operator=(const sorted_ptr_set<T>& right)
			{ sorted_ptr_set_base::operator=(right); return *this; }
	};



/////////////////////////////////////////////////////////////////////////////////////
//
// The sorted_weak_ptr_set<> represents the GeMS sorted weak pointer set. Since it
// contains weak pointers, its elements to not own the referenced objects.  When the
// referenced objects die, the element is removed from the set by the GeMS system.
// Like all sets, it disallows duplicate and NULL values.
//
// Note that it has no default constructor.  Since it is an 'sorted' collection,
// the user must, at the very least, provide the criteria by which the collection
// should be sorted.  This is done by providing a pointer to a comparator<T>.
//
template <class T> class sorted_weak_ptr_set : public sorted_smart_ptr_set<T>
	{
	public:
		sorted_weak_ptr_set(const comparator<T>* comp2):sorted_smart_ptr_set<T>(comp2,WEAK_PTR) {}
		sorted_weak_ptr_set(const sorted_smart_ptr_set<T>& right):
						sorted_smart_ptr_set<T>(right,WEAK_PTR) {}
		sorted_weak_ptr_set(const sorted_weak_ptr_set<T>& right):
						sorted_smart_ptr_set<T>(right,WEAK_PTR) {}

		sorted_weak_ptr_set<T>& operator=(const sorted_smart_ptr_set<T>& right)
			{ sorted_ptr_set_base::operator=(right); return *this; }
		sorted_weak_ptr_set<T>& operator=(const sorted_weak_ptr_set<T>& right)
			{ sorted_ptr_set_base::operator=(right); return *this; }
	};


/////////////////////////////////////////////////////////////////////////////////////
//
// The sorted_omega_ptr_set<> acts like an sorted_ptr_set<> (a sorted set of strong
// pointers) except that it produces a g_forget() request for its owning atom when the
// GeMS system takes its state from non-empty to empty.  Like all sets, it disallows
// duplicate and NULL values.
//
template <class T> class sorted_omega_ptr_set : public sorted_smart_ptr_set<T>
	{
	public:
		sorted_omega_ptr_set(const comparator<T>* comp):sorted_smart_ptr_set<T>(comp,OMEGA_STRONG_PTR) {}
		sorted_omega_ptr_set(const sorted_smart_ptr_set<T>& right):
				sorted_smart_ptr_set<T>(right,OMEGA_STRONG_PTR) {}
		sorted_omega_ptr_set(const sorted_omega_ptr_set<T>& right):
				sorted_smart_ptr_set<T>(right,OMEGA_STRONG_PTR) {}

		sorted_omega_ptr_set<T>& operator=(const sorted_smart_ptr_set<T>& right)
			{ sorted_ptr_set_base::operator=(right); return *this; }
		sorted_omega_ptr_set<T>& operator=(const sorted_omega_ptr_set<T>& right)
			{ sorted_ptr_set_base::operator=(right); return *this; }
	};


/////////////////////////////////////////////////////////////////////////////////////
//
// The sorted_omega_weak_ptr_set<> acts like an sorted_weak_ptr_set<> (n sorted set
// of weak pointers) except that it produces a g_forget() request for its owning atom
// when the GeMS system takes its state from non-empty to empty.  Like all sets, it
// disallows duplicate and NULL values.
//
template <class T> class sorted_omega_weak_ptr_set : public sorted_smart_ptr_set<T>
	{
	public:
		sorted_omega_weak_ptr_set(const comparator<T>* comp):sorted_smart_ptr_set<T>(comp,OMEGA_WEAK_PTR) {}
		sorted_omega_weak_ptr_set(const sorted_smart_ptr_set<T>& right):
						sorted_smart_ptr_set<T>(right,OMEGA_WEAK_PTR) {}
		sorted_omega_weak_ptr_set(const sorted_omega_weak_ptr_set<T>& right):
						sorted_smart_ptr_set<T>(right,OMEGA_WEAK_PTR) {}

		sorted_omega_weak_ptr_set<T>& operator=(const sorted_smart_ptr_set<T>& right)
			{ sorted_ptr_set_base::operator=(right); return *this; }
		sorted_omega_weak_ptr_set<T>& operator=(const sorted_omega_weak_ptr_set<T>& right)
			{ sorted_ptr_set_base::operator=(right); return *this; }
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// The sorted_hard_ptr_set<> represents a local variable pointer set that guarantees
// that its contents will not die and the sorted set will not change, regardless of
// the actions of other threads.  In this way, the 'hard' pointers contained within
// the collection temporarily interfere with some GeMS memory management operations.
// For example, any g_forget() request enacted by another thread will break all of
// the strong references to the 'forgotten' object, but since the hard pointer
// itself is not broken, the object is not allowed to 'die' until all hard
// references go away.  When that happens, the object will finally 'die' and any
// weak references to the object will be broken as well.  Thus, hard references
// should be used with care.  In most situations, a sorted_ghost_ptr_set<> should
// be used instead of a sorted_hard_ptr_set<>.
//
// It is illegal to use a sorted_hard_ptr_set<> as an attribute of a GAtom derived
// class.  (i.e. They cannot be saved to file.) Like all sets, sorted_hard_ptr_set<>s
// disallow duplicate and NULL values.
//
template <class T> class sorted_hard_ptr_set : public sorted_smart_ptr_set<T>
	{
	public:
		sorted_hard_ptr_set(const comparator<T>* comp):sorted_smart_ptr_set<T>(comp,(g_behaviors)USE_COUNT_PTR) {}
		sorted_hard_ptr_set(const sorted_smart_ptr_set<T>& right):
						sorted_smart_ptr_set<T>(right,(g_behaviors)USE_COUNT_PTR) {}
		sorted_hard_ptr_set(const sorted_hard_ptr_set<T>& right):
						sorted_smart_ptr_set<T>(right,(g_behaviors)USE_COUNT_PTR) {}

		sorted_hard_ptr_set<T>& operator=(const sorted_smart_ptr_set<T>& right)
			{ sorted_ptr_set_base::operator=(right); return *this; }
		sorted_hard_ptr_set<T>& operator=(const sorted_hard_ptr_set<T>& right)
			{ sorted_ptr_set_base::operator=(right); return *this; }
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// The sorted_ghost_ptr_set<> represents a local variable sorted pointer set that
// guarantees that its elements will not be unexpectedly removed, regardless of
// the actions of other threads.  Sorted ghost pointer sets do not prevent the
// 'deaths' of the referenced objects, but they do prevent their actual destruction.
// Consequently, a 'ghost' sorted set is highly non-intrusive to the normal GeMS
// memory management operations.
//
// It is illegal to use a sorted_ghost_ptr_set<> as an attribute of a GAtom derived
// class. (i.e. They cannot be saved to file.) Ghost relationships are intended to
// be used as local variables.
//
// Like all sets, sorted_ghost_ptr_set<>s disallow duplicate and NULL values.
//
template <class T> class sorted_ghost_ptr_set : public sorted_smart_ptr_set<T>
	{
	public:
		sorted_ghost_ptr_set(const comparator<T>* comp):sorted_smart_ptr_set<T>(comp,(g_behaviors)(USE_COUNT_PTR|GHOST_PTR)) {}
		sorted_ghost_ptr_set(const sorted_smart_ptr_set<T>& right):
						sorted_smart_ptr_set<T>(right,(g_behaviors)(USE_COUNT_PTR|GHOST_PTR)) {}
		sorted_ghost_ptr_set(const sorted_ghost_ptr_set<T>& right):
						sorted_smart_ptr_set<T>(right,(g_behaviors)(USE_COUNT_PTR|GHOST_PTR)) {}

		sorted_ghost_ptr_set<T>& operator=(const sorted_smart_ptr_set<T>& right)
			{ sorted_ptr_set_base::operator=(right); return *this; }
		sorted_ghost_ptr_set<T>& operator=(const sorted_ghost_ptr_set<T>& right)
			{ sorted_ptr_set_base::operator=(right); return *this; }
	};

#endif
