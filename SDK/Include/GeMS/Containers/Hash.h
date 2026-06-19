
#ifndef _hash_table_h_
#define _hash_table_h_

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

#ifdef _MSC_VER
#include "basetsd.h"
#endif

#include "GeMS/GemsFnd/Ptr.h"
#include "GeMS/GemsFnd/LeanPtr.h"
#include "GeMS/GemsFnd/Gsubatom.h"
#include "GeMS/Containers/Ginsert.h"
#include "GeMS/Utility/Compare.h"

DECLARE_MINIMAL_GEMS_DLL_EXPORTS(GAtom,GEMS)
DECLARE_MINIMAL_GEMS_DLL_EXPORTS(GHashTable,GEMS)
DECLARE_MINIMAL_GEMS_DLL_EXPORTS(GHashTableNode,GEMS)

template <class T> class smart_ptr_hash_table;
template <class T> class ptr_hash_table;
template <class T> class weak_ptr_hash_table;

class DECL_GEMS ptr_hash_table_base;

GEMS_TEMPLATE(class, lean_smart_ptr<GHashTable>);
GEMS_TEMPLATE(class, lean_hard_ptr<GHashTable>);

typedef g_insertion_call_data<ptr_hash_table_base> g_ptr_hash_table_insert_call_data;
typedef g_erasure_call_data<ptr_hash_table_base> g_ptr_hash_table_remove_call_data;

DECLARE_CALLBACK_TYPE(g_ptr_hash_table_element_added_callback, 
                      g_ptr_hash_table_insert_call_data, GEMS);
DECLARE_CALLBACK_TYPE(g_ptr_hash_table_element_removed_callback,
                      g_ptr_hash_table_remove_call_data, GEMS);

class DECL_GEMS ptr_hash_table_base : public g_sub_atom
	{
	public:
		typedef std::pair<ptrdiff_t, GAtom *> value_type;
        typedef value_type const_value_type;
		typedef size_t size_type;

		static value_type null_value_type() { return value_type(); }

		class DECL_GEMS iterator
			{
			friend class DECL_GEMS ptr_hash_table_base;
			friend class DECL_GEMS GHashTable;

			private:
				mutable lean_hard_ptr<GHashTable>	_table;
				mutable weak_ptr<GHashTableNode>	_node;
				mutable bool						_reverse_direction;	// default is false.
				mutable bool						_iterate_over_keys;	// default is true.

			public:
	            typedef std::bidirectional_iterator_tag iterator_category;

				iterator();
				iterator(const iterator&);
				iterator(const ptr_hash_table_base& t);
				iterator(const GHashTable* t);
				iterator(const GHashTable* t,const GHashTableNode*n,bool reverse=false,bool iterate_over_keys=true);
				~iterator();

				iterator& operator=(const iterator& right);

				void operator++() const;
				void operator++(int) const;

				void operator--() const;
				void operator--(int) const;

				bool operator==(const iterator& i) const
					{ return _node == i._node; }
				bool operator!=(const iterator& i) const
					{ return _node != i._node; }

				value_type operator*() const;

				ptrdiff_t first() const;
				GAtom* second() const;

				bool valid() const
					{ return (_node!=NULL); }

				size_t location_id() const;
			};

		typedef std::pair<iterator,iterator> erange;

		friend class DECL_GEMS ptr_hash_table_base::iterator;
		friend class DECL_GEMS GHashTable;

	private:
		mutable lean_hard_ptr<GHashTable>	_table;
		g_behaviors							_behaviors;
		bool								_first_allow_duplicates,_second_allow_duplicates;
		bool								_allow_duplicate_pairs;
		comparator<GAtom>*					_comparator;
		g_add_remove_callback_group<g_ptr_hash_table_element_added_callback, 
                                    g_ptr_hash_table_insert_call_data, 
                                    g_ptr_hash_table_element_removed_callback, 
                                    g_ptr_hash_table_remove_call_data> _callback_group;

		void make_table() const;
		void forget_table() const;

	protected:
		void copy_table_base(ptr_hash_table_base& right) const;

		void operator_plus(ptr_hash_table_base& result,const ptr_hash_table_base& right) const;
		void operator_plus_equals(const ptr_hash_table_base& right);

		void operator_minus(ptr_hash_table_base& result,const ptr_hash_table_base& right) const;
		void operator_minus_equals(const ptr_hash_table_base& right);

		void operator_and(ptr_hash_table_base& result,const ptr_hash_table_base& right) const;
		void operator_and_equals(const ptr_hash_table_base& right);

		void call_element_added_callbacks(g_insertion_call_data<ptr_hash_table_base>* call_data=0);
		void call_element_pre_remove_callbacks(g_erasure_call_data<ptr_hash_table_base>* call_data=0);
		void call_element_removed_callbacks(g_erasure_call_data<ptr_hash_table_base>* call_data=0);

		void pre_forget(const g_forget_event& event);
		void forget(const g_forget_event& event);

		void equal_range(const value_type& value,iterator& f,iterator& s) const;
		void first_equal_range(ptrdiff_t key,iterator& f,iterator& s) const;
		void second_equal_range(const GAtom* v,iterator& f,iterator& s) const;
		void second_equal_range(const self_comparator<GAtom>*c,iterator& f,iterator& s) const;

		ptr_hash_table_base();
		ptr_hash_table_base(const ptr_hash_table_base&);

	public:
		ptr_hash_table_base(	g_behaviors Behaviors,
								bool allow_duplicate_keys=false,bool allow_duplicate_ptrs=false,
								bool allow_duplicate_pairs=false,
								const comparator<GAtom>* ptr_comparator=NULL);
									// If NULL compares by ptr value.
		ptr_hash_table_base(	const ptr_hash_table_base&,
								g_behaviors Behaviors);
		~ptr_hash_table_base();

		virtual void live_to_ghost();
		virtual void ghost_to_live();

		GAtom* owner() const { return _table.owner(); }
		void owner(GAtom* own) const { _table.owner(own); }

		ptr_hash_table_base& operator=(const ptr_hash_table_base& right);
 		bool operator==(const ptr_hash_table_base& right) const;

		////////////////////////////////////////////////////////////////////////////////////////
		// System Methods.
		void stream(g_stream&);

		////////////////////////////////////////////////////////////////////////////////////////
		// Functional Methods.
		g_behaviors behaviors() const { return _behaviors; }

		size_type size() const;

		std::pair<iterator,bool> insert(const value_type&);

		void erase(iterator &iter);
		void erase(iterator &f,iterator &s);

		void clear();
		bool empty() const;

		///////////////////////////////////////
		// value_type methods.
		size_type count(const value_type&) const;
		iterator find(const value_type&) const;
		iterator lower_bound(const value_type&) const;
		iterator upper_bound(const value_type&) const;
		erange equal_range(const value_type&) const;
		size_type erase(const value_type&);

		bool contains(const value_type&) const;
		bool contains_all(const ptr_hash_table_base&) const;
		bool contains_any(const ptr_hash_table_base&) const;
		bool contains_none(const ptr_hash_table_base&) const;

		///////////////////////////////////////
		// first methods.
		//     These methods return iterators that
		//     iterate over key order.
		iterator begin() const;
		iterator end() const;
		iterator rbegin() const;
		iterator rend() const;

		size_type first_count(ptrdiff_t key) const;
		iterator first_find(ptrdiff_t key) const;
		iterator first_lower_bound(ptrdiff_t key) const;
		iterator first_upper_bound(ptrdiff_t key) const;
		erange first_equal_range(ptrdiff_t key) const;
		size_type first_erase(ptrdiff_t);

		bool first_contains(ptrdiff_t key) const;
		bool first_contains_all(const ptr_hash_table_base&) const;
		bool first_contains_any(const ptr_hash_table_base&) const;
		bool first_contains_none(const ptr_hash_table_base&) const;

		///////////////////////////////////////
		// second methods.
		//      These methods return iterators that
		//      iterate over ptr order.
		iterator second_begin() const;
		iterator second_end() const;
		iterator second_rbegin() const;
		iterator second_rend() const;

		size_type second_count(const GAtom*) const;
		iterator second_find(const GAtom*) const;
		iterator second_lower_bound(const GAtom*) const;
		iterator second_upper_bound(const GAtom*) const;
		erange second_equal_range(const GAtom*) const;
		size_type second_erase(const GAtom*);

		size_type second_count(const self_comparator<GAtom>*) const;
		iterator second_find(const self_comparator<GAtom>*) const;
		iterator second_lower_bound(const self_comparator<GAtom>*) const;
		iterator second_upper_bound(const self_comparator<GAtom>*) const;
		erange second_equal_range(const self_comparator<GAtom>*) const;

		bool second_contains(const GAtom*) const;
		bool second_contains_all(const ptr_hash_table_base&) const;
		bool second_contains_any(const ptr_hash_table_base&) const;
		bool second_contains_none(const ptr_hash_table_base&) const;

		///////////////////////////////////////
		// Callback List Methods

		// In the 'add-callback' methods, the 'owner' pointer sets the owner pointer
		// in the callback lists if it is non-zero.  Otherwise, it is ignored.
		void add_element_added_callback(g_ptr_hash_table_element_added_callback,
		                                void *client_data = 0,
                                        GAtom *owner = 0);
		void add_element_removed_callback(g_ptr_hash_table_element_removed_callback,
                                          void *client_data = 0,
                                          GAtom *owner = 0);
		void add_element_pre_remove_callback(g_ptr_hash_table_element_removed_callback,
                                             void *client_data = 0,
                                             GAtom *owner = 0);
		void null_owner(); // Nulls the 'owner' pointer in both callback lists.
		
		void remove_element_added_callback(g_ptr_hash_table_element_added_callback,
                                           void *client_data = 0);
		void remove_element_removed_callback(g_ptr_hash_table_element_removed_callback,
                                             void *client_data = 0);
		void remove_element_pre_remove_callback(g_ptr_hash_table_element_removed_callback,
                                                void *client_data = 0);

		bool element_added_callback_list_empty() const;
		bool element_removed_callback_list_empty() const;
		bool element_pre_remove_callback_list_empty() const;

		void add_update_callback(g_update_callback cb, void *client_data = 0);
		void remove_update_callback(g_update_callback cb, void *client_data = 0);

		///////////////////////////////////////
		// Attribute methods.
		const smart_ptr_set<GAtom>&	attrib_list(const iterator&iter) const;
		void  attrib_list(const iterator&,const smart_ptr_set<GAtom>& atts);
		void  insert_attrib(const iterator&,const GAtom* att,GInsertionType = INSERT_ANYWHERE,const GAtom* = NULL);
		void  erase_attrib(const iterator&,const GAtom* att);

#if defined (_DEBUG) || defined (_PSEUDO_DEBUG)
		// Method to allow access to internal data for test facilities.
		// Only accessible in debug mode.
		GHashTable* table() const { return (GHashTable*)_table.cast(); }
#endif
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// The smart_ptr_hash_table<> is an abstract base class representing the GeMS pointer
// hash_table.  It disallows duplicate and NULL key values.
//
template <class T> class smart_ptr_hash_table : public ptr_hash_table_base
	{
	public:
		typedef std::pair<ptrdiff_t, T *> value_type;

		class iterator : public ptr_hash_table_base::iterator
			{
			friend class smart_ptr_hash_table<T>;
			protected:
				iterator(const ptr_hash_table_base::iterator& i):ptr_hash_table_base::iterator(i) {}
			public:
	            typedef typename smart_ptr_hash_table<T>::value_type value_type;
	            typedef ptrdiff_t difference_type;
	            typedef difference_type distance_type;	// retained
	            typedef T* pointer;
	            typedef T& reference;

				iterator(){}
				iterator(const smart_ptr_hash_table<T>& lst):ptr_hash_table_base::iterator(lst) {}
				iterator(GHashTable* t):ptr_hash_table_base::iterator(t) {}
					// This is a dangerous constructor since it circumvents type checking.
					// However, it allows us to create sets of sets.

				iterator& operator=(const iterator& i) { ptr_hash_table_base::iterator::operator=(i); return *this; }

				value_type operator*() const
                    { return(std::make_pair(first(), second())); }

				T* second() const { return (T*)ptr_hash_table_base::iterator::second(); }
			};

		typedef std::pair<iterator, iterator> erange;

	protected:
		smart_ptr_hash_table():
						ptr_hash_table_base() {}
		smart_ptr_hash_table(	const smart_ptr_hash_table<T>& right):
						ptr_hash_table_base(right) {}

	public:
		smart_ptr_hash_table(	g_behaviors behave,
								bool allow_duplicate_keys=false,bool allow_duplicate_ptrs=false,
								bool allow_duplicate_pairs=false,
								const comparator<T>* ptr_comparator=NULL):
						ptr_hash_table_base(behave,allow_duplicate_keys,allow_duplicate_ptrs,
											allow_duplicate_pairs,(comparator<GAtom>*)ptr_comparator) {}
		smart_ptr_hash_table(	const smart_ptr_hash_table<T>& right,
								g_behaviors behave):
						ptr_hash_table_base(right,behave) {}

		smart_ptr_hash_table<T>& operator=(const smart_ptr_hash_table<T>& right)
			{ ptr_hash_table_base::operator=(right); return *this; }

		////////////////////////////////////////////////////////////////////////////////////////
		// Functional Methods.
		std::pair<iterator,bool> insert(const value_type& v)
			{
			std::pair<ptr_hash_table_base::iterator, bool> retval =
                ptr_hash_table_base::insert(v);
			return std::make_pair(iterator(retval.first),retval.second);
			}

		size_type erase(const value_type &v)		{ return ptr_hash_table_base::erase(v); }
		void erase(iterator &iter)			{ ptr_hash_table_base::erase(iter); }
		void erase(iterator &f,iterator &s) { ptr_hash_table_base::erase(f,s); }

		void copy_to_table(smart_ptr_hash_table<T>& table) const
					{ ptr_hash_table_base::copy_table_base(table);}

		///////////////////////////////////////
		// value_type methods.
		bool contains(const value_type& v) const		{ return ptr_hash_table_base::contains(v); }

		size_type count(const value_type& v) const	{ return ptr_hash_table_base::count(v); }
		iterator find(const value_type& v) const		{ return ptr_hash_table_base::find(v); }
		iterator lower_bound(const value_type& v) const	{ return ptr_hash_table_base::lower_bound(v); }
		iterator upper_bound(const value_type& v) const	{ return ptr_hash_table_base::upper_bound(v); }
		erange equal_range(const value_type& v) const	{ erange r; ptr_hash_table_base::equal_range(v,r.first,r.second); return r; }

		///////////////////////////////////////
		// first methods.
		//     These methods return iterators that
		//     iterate over key order.
		iterator begin() const	{ return ptr_hash_table_base::begin(); }
		iterator end() const	{ return ptr_hash_table_base::end(); }
		iterator rbegin() const	{ return ptr_hash_table_base::rbegin(); }
		iterator rend() const	{ return ptr_hash_table_base::rend(); }

		size_type first_count(ptrdiff_t k) const { return ptr_hash_table_base::first_count(k); }
		iterator first_find(ptrdiff_t v) const { return ptr_hash_table_base::first_find(v); }
		iterator first_lower_bound(ptrdiff_t v) const { return ptr_hash_table_base::first_lower_bound(v); }
		iterator first_upper_bound(ptrdiff_t v) const { return ptr_hash_table_base::first_upper_bound(v); }
		erange first_equal_range(ptrdiff_t v) const { erange r; ptr_hash_table_base::first_equal_range(v,r.first,r.second); return r; }
		size_type first_erase(ptrdiff_t key)	{ return ptr_hash_table_base::first_erase(key); }

		bool first_contains(ptrdiff_t k) const { return ptr_hash_table_base::first_contains(k); }

		///////////////////////////////////////
		// second methods.
		//      These methods return iterators that
		//      iterate over ptr order.

		// These 'ptr' methods return iterators that iterate in ptr value order.
		size_type second_count(const T* v) const { return ptr_hash_table_base::second_count(reinterpret_cast<const GAtom *>(v)); }
		iterator second_find(const T* v) const { return ptr_hash_table_base::second_find(reinterpret_cast<const GAtom *>(v)); }
		iterator second_lower_bound(const T* v) const { return ptr_hash_table_base::second_lower_bound(reinterpret_cast<const GAtom *>(v)); }
		iterator second_upper_bound(const T* v) const { return ptr_hash_table_base::second_upper_bound(reinterpret_cast<const GAtom *>(v)); }
		erange second_equal_range(const T* v) const { erange r; ptr_hash_table_base::second_equal_range(reinterpret_cast<const GAtom *>(v),r.first,r.second); return r; }
		size_type second_erase(T* v)		{ return ptr_hash_table_base::second_erase(reinterpret_cast<const GAtom *>(v)); }

		iterator second_find(const self_comparator<T>* c) const			{ return ptr_hash_table_base::second_find((self_comparator<GAtom>*)c); }
		iterator second_lower_bound(const self_comparator<T>* c) const	{ return ptr_hash_table_base::second_lower_bound((self_comparator<GAtom>*)c); }
		iterator second_upper_bound(const self_comparator<T>* c) const	{ return ptr_hash_table_base::second_upper_bound((self_comparator<GAtom>*)c); }
		erange second_equal_range(const self_comparator<T>* c) const		{ erange r; ptr_hash_table_base::second_equal_range((self_comparator<GAtom>*)c,r.first,r.second); return r; }

		bool second_contains(const T* v) const { return ptr_hash_table_base::second_contains(reinterpret_cast<const GAtom *>(v)); }

		///////////////////////////////////////
		// Operators.
		smart_ptr_hash_table<T>& operator+=(const smart_ptr_hash_table<T>& right)
					{ ptr_hash_table_base::operator_plus_equals(right); return *this; }

		smart_ptr_hash_table<T>& operator-=(const smart_ptr_hash_table<T>& right)
					{ ptr_hash_table_base::operator_minus_equals(right); return *this; }

		smart_ptr_hash_table<T>& operator&=(const smart_ptr_hash_table<T>& right)
					{ ptr_hash_table_base::operator_and_equals(right); return *this; }
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// The ptr_hash_table<> represents the GeMS strong pointer hash table.  Its name was shortened from
// strong_ptr_hash_table<> to ptr_hash_table<> simply because it is the most common type of 
// hash table used. Since it contains strong pointers, each pointer owns and registers itself
// with the referenced object.  Like all hash tables, it disallows NULL values.
//
template <class T> class ptr_hash_table : public smart_ptr_hash_table<T>
	{
	public:
		ptr_hash_table(		bool allow_duplicate_keys=false,bool allow_duplicate_ptrs=false,
							bool allow_duplicate_pairs=false,
							const comparator<T>* ptr_comparator=NULL):
				smart_ptr_hash_table<T>((g_behaviors)(STRONG_PTR),
							allow_duplicate_keys,allow_duplicate_ptrs,
							allow_duplicate_pairs,ptr_comparator) {}

		ptr_hash_table(const smart_ptr_hash_table<T>& right):
				smart_ptr_hash_table<T>(right,STRONG_PTR) {}

		ptr_hash_table(const ptr_hash_table<T>& right):smart_ptr_hash_table<T>(right,STRONG_PTR) {}

		ptr_hash_table<T>& operator=(const smart_ptr_hash_table<T>& right)
			{ ptr_hash_table_base::operator=(right); return *this; }
		ptr_hash_table<T>& operator=(const ptr_hash_table<T>& right)
			{ ptr_hash_table_base::operator=(right); return *this; }
	};



/////////////////////////////////////////////////////////////////////////////////////
//
// The weak_ptr_hash_table<> represents the GeMS weak pointer hash table. Since it contains weak
// pointers, its elements to not own the referenced objects.  When the referenced
// objects die, the element is removed from the hash table by the GeMS system.  Like all
// tables, it disallows NULL values.
//
template <class T> class weak_ptr_hash_table : public smart_ptr_hash_table<T>
	{
	public:
		weak_ptr_hash_table(bool allow_duplicate_keys=false,bool allow_duplicate_ptrs=false,
							bool allow_duplicate_pairs=false,
							const comparator<T>* ptr_comparator=NULL):
				smart_ptr_hash_table<T>((g_behaviors)(WEAK_PTR),
							allow_duplicate_keys,allow_duplicate_ptrs,
							allow_duplicate_pairs,ptr_comparator) {}

		weak_ptr_hash_table(const smart_ptr_hash_table<T>& right):
				smart_ptr_hash_table<T>(right,WEAK_PTR) {}

		weak_ptr_hash_table(const weak_ptr_hash_table<T>& right):
						smart_ptr_hash_table<T>(right,WEAK_PTR) {}

		weak_ptr_hash_table<T>& operator=(const smart_ptr_hash_table<T>& right)
			{ ptr_hash_table_base::operator=(right); return *this; }
		weak_ptr_hash_table<T>& operator=(const weak_ptr_hash_table<T>& right)
			{ ptr_hash_table_base::operator=(right); return *this; }
	};


/////////////////////////////////////////////////////////////////////////////////////
//
// The omega_ptr_hash_table<> acts like a ptr_hash_table<> (a table of strong pointers)
// except that it produces a g_forget() request for its owning atom when the GeMS
// system takes its state from non-empty to empty.
//
template <class T> class omega_ptr_hash_table : public smart_ptr_hash_table<T>
	{
	public:
		omega_ptr_hash_table(	bool allow_duplicate_keys=false,bool allow_duplicate_ptrs=false,
								bool allow_duplicate_pairs=false,
								const comparator<T>* ptr_comparator=NULL):
				smart_ptr_hash_table<T>((g_behaviors)(OMEGA_STRONG_PTR),
							allow_duplicate_keys,allow_duplicate_ptrs,
							allow_duplicate_pairs,ptr_comparator) {}

		omega_ptr_hash_table(	const smart_ptr_hash_table<T>& right):
				smart_ptr_hash_table<T>(right,OMEGA_STRONG_PTR) {}

		omega_ptr_hash_table(const omega_ptr_hash_table<T>& right):
						smart_ptr_hash_table<T>(right,OMEGA_STRONG_PTR) {}

		omega_ptr_hash_table<T>& operator=(const smart_ptr_hash_table<T>& right)
			{ ptr_hash_table_base::operator=(right); return *this; }
		omega_ptr_hash_table<T>& operator=(const omega_ptr_hash_table<T>& right)
			{ ptr_hash_table_base::operator=(right); return *this; }
	};


/////////////////////////////////////////////////////////////////////////////////////
//
// The omega_weak_ptr_hash_table<> acts like a weak_ptr_hash_table<> (a table of weak pointers)
// except that it produces a g_forget() request for its owning atom when the GeMS
// system takes its state from non-empty to empty.
//
template <class T> class omega_weak_ptr_hash_table : public smart_ptr_hash_table<T>
	{
	public:
		omega_weak_ptr_hash_table(	bool allow_duplicate_keys=false,bool allow_duplicate_ptrs=false,
									bool allow_duplicate_pairs=false,
									const comparator<T>* ptr_comparator=NULL):
				smart_ptr_hash_table<T>((g_behaviors)(OMEGA_WEAK_PTR),
							allow_duplicate_keys,allow_duplicate_ptrs,
							allow_duplicate_pairs,ptr_comparator) {}

		omega_weak_ptr_hash_table(	const smart_ptr_hash_table<T>& right):
				smart_ptr_hash_table<T>(right,OMEGA_WEAK_PTR) {}

		omega_weak_ptr_hash_table(const omega_weak_ptr_hash_table<T>& right):
						smart_ptr_hash_table<T>(right,(g_behaviors)(OMEGA_WEAK_PTR)) {}

		omega_weak_ptr_hash_table<T>& operator=(const smart_ptr_hash_table<T>& right)
			{ ptr_hash_table_base::operator=(right); return *this; }
		omega_weak_ptr_hash_table<T>& operator=(const omega_weak_ptr_hash_table<T>& right)
			{ ptr_hash_table_base::operator=(right); return *this; }
	};

//////////////////////////////////////////////////////////////////////////////////////
//
// The hard_ptr_hash_table<> represents a local variable pointer hash table
// that guarantees that its contents will not die and the table will
// not change, regardless of the actions of other threads.  In this way, the
// 'hard' pointers contained within the collection temporarily interfere with
// some GeMS memory management operations.  For example, any g_forget() request
// enacted by another thread will break all of the 'strong' references to the
// forgotten' object, but since the hard pointer itself is not broken, the
// object is not allowed to 'die' until all hard references go away.  When that
// happens, the object will finally 'die' and any weak references to the object
// will be broken as well.  Thus, hard references should be used with care.  In
// most situations, a sorted_ghost_ptr_hash_table<> should be used instead of a
// sorted_hard_ptr_hash_table<>.
//
// It is illegal to use a sorted_hard_ptr_hash_table<> as an attribute
// of a GAtom derived class.  (i.e. They cannot be saved to file.)
// Like all hash tables, sorted_hard_ptr_hash_table<>s disallow NULL values.
//
template <class T> class hard_ptr_hash_table : public smart_ptr_hash_table<T>
	{
	public:
		hard_ptr_hash_table(bool allow_duplicate_keys=false,bool allow_duplicate_ptrs=false,
							bool allow_duplicate_pairs=false,
							const comparator<T>* ptr_comparator=NULL):
				smart_ptr_hash_table<T>((g_behaviors)(USE_COUNT_PTR),
							allow_duplicate_keys,allow_duplicate_ptrs,
							allow_duplicate_pairs,ptr_comparator) {}

		hard_ptr_hash_table(const smart_ptr_hash_table<T>& right):
				smart_ptr_hash_table<T>(right,USE_COUNT_PTR) {}

		hard_ptr_hash_table(const hard_ptr_hash_table<T>& right):
						smart_ptr_hash_table<T>(right,USE_COUNT_PTR) {}

		hard_ptr_hash_table<T>& operator=(const smart_ptr_hash_table<T>& right)
			{ ptr_hash_table_base::operator=(right); return *this; }
		hard_ptr_hash_table<T>& operator=(const hard_ptr_hash_table<T>& right)
			{ ptr_hash_table_base::operator=(right); return *this; }
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// The ghost_ptr_hash_table<> represents a local variable hash table
// that guarantees that its elements will not be unexpectedly removed,
// regardless of the actions of other threads.  Sorted ghost pointer
// hash tables do not prevent the 'deaths' of the referenced objects,
// but they do prevent their actual destruction.  Consequently, a
// 'ghost' pointer hash table is highly non-intrusive to the normal
// GeMS memory management operations.
//
// It is illegal to use a ghost_ptr_hash_table<> as an attribute of a
// GAtom derived class (i.e. They cannot be saved to file.). Ghost
// relationships are mainly intended to be used as local variables.
//
// Like all hash tables, ghost_ptr_hash_table<>s disallow NULL values.
//
template <class T> class ghost_ptr_hash_table : public smart_ptr_hash_table<T>
	{
	public:
		ghost_ptr_hash_table(bool allow_duplicate_keys=false,bool allow_duplicate_ptrs=false,
							bool allow_duplicate_pairs=false,
							const comparator<T>* ptr_comparator=NULL):
				smart_ptr_hash_table<T>((g_behaviors)(USE_COUNT_PTR|GHOST_PTR),
							allow_duplicate_keys,allow_duplicate_ptrs,
							allow_duplicate_pairs,ptr_comparator) {}

		ghost_ptr_hash_table(const smart_ptr_hash_table<T>& right):
				smart_ptr_hash_table<T>(right,(g_behaviors)(USE_COUNT_PTR|GHOST_PTR)) {}

		ghost_ptr_hash_table(const ghost_ptr_hash_table<T>& right):
						smart_ptr_hash_table<T>(right,(g_behaviors)(USE_COUNT_PTR|GHOST_PTR)) {}

		ghost_ptr_hash_table<T>& operator=(const smart_ptr_hash_table<T>& right)
			{ ptr_hash_table_base::operator=(right); return *this; }
		ghost_ptr_hash_table<T>& operator=(const ghost_ptr_hash_table<T>& right)
			{ ptr_hash_table_base::operator=(right); return *this; }
	};


/////////////////////////////////////////////////////////////////////////////////////
//
// The ptr_hash_table_iter<> provides access to the contents of a ptr_hash_table<>.
//
template <class T> class ptr_hash_table_iter : public ptr_hash_table<T>::iterator
	{
	public:
		ptr_hash_table_iter(const smart_ptr_hash_table<T>& lst):ptr_hash_table<T>::iterator(lst) {}
		ptr_hash_table_iter(GHashTable* t):ptr_hash_table<T>::iterator(t) {}
	};

GEMS_TEMPLATE(struct, g_insertion_call_data<ptr_hash_table_base>);
GEMS_TEMPLATE(struct, g_erasure_call_data<ptr_hash_table_base>);

DECL_GEMS void g_reverse_call_data(const g_ptr_hash_table_insert_call_data& in,g_ptr_hash_table_remove_call_data& out);
DECL_GEMS void g_reverse_call_data(const g_ptr_hash_table_remove_call_data& in,g_ptr_hash_table_insert_call_data& out);

// For historical compatibility
#define temp_ptr_hash_table ptr_hash_table
#define temp_weak_ptr_hash_table weak_ptr_hash_table

#endif
