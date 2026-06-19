
#ifndef _ptr_map_h_
#define _ptr_map_h_

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
#include "GeMS/Utility/Compare.h"

DECLARE_MINIMAL_GEMS_DLL_EXPORTS(GAtom,GEMS)
DECLARE_MINIMAL_GEMS_DLL_EXPORTS(GPtrMap,GEMS)
DECLARE_MINIMAL_GEMS_DLL_EXPORTS(GPtrMapNode,GEMS)

template <class F,class S> class smart_ptr_map;

class DECL_GEMS g_mutex;
class DECL_GEMS ptr_map_base;

GEMS_TEMPLATE(class, lean_smart_ptr<GPtrMap>);
GEMS_TEMPLATE(class, lean_hard_ptr<GPtrMap>);

typedef g_insertion_call_data<ptr_map_base> g_ptr_map_insert_call_data;
typedef g_erasure_call_data<ptr_map_base> g_ptr_map_remove_call_data;

DECLARE_CALLBACK_TYPE(g_ptr_map_element_added_callback, 
                      g_ptr_map_insert_call_data, GEMS);
DECLARE_CALLBACK_TYPE(g_ptr_map_element_removed_callback,
                      g_ptr_map_remove_call_data, GEMS);

class DECL_GEMS ptr_map_base : public g_sub_atom
	{
	public:
		typedef std::pair<GAtom *, GAtom *> value_type;
        typedef value_type const_value_type;
		typedef size_t size_type;

		static value_type null_value_type() { return value_type(); }

		class DECL_GEMS iterator
			{
			friend class DECL_GEMS ptr_map_base;
			friend class DECL_GEMS GPtrMap;

			private:
				mutable ptr<GPtrMap>			_map;
				mutable weak_ptr<GPtrMapNode>	_node;
				mutable bool					_reverse_direction;		// default is false.
				mutable bool					_iterate_over_first;	// default is true.

			public:
				iterator();
				iterator(const iterator&);
				iterator(const ptr_map_base& t);
				iterator(const GPtrMap* t);
				iterator(const GPtrMap* t,const GPtrMapNode*n,bool reverse=false,bool iterate_over_first=true);
				~iterator();

				iterator& operator=(const iterator&);

				void operator++() const;
				void operator++(int) const;

				void operator--() const;
				void operator--(int) const;

				bool operator==(const iterator& i) const
					{ return _node == i._node; }
				bool operator!=(const iterator& i) const
					{ return _node != i._node; }

				value_type operator*() const;

				GAtom* first() const;
				GAtom* second() const;

				bool valid() const
					{ return (_node!=NULL); }

				size_t location_id() const;
			};

		typedef std::pair<iterator,iterator> erange;

		friend class DECL_GEMS ptr_map_base::iterator;
		friend class DECL_GEMS GPtrMap;

	private:
		mutable lean_hard_ptr <GPtrMap>	_map;
		g_behaviors						_first_behaviors,_second_behaviors;
		bool							_is_omega;
		bool							_first_allow_duplicates,_second_allow_duplicates;
		bool							_allow_duplicate_pairs;
		comparator<GAtom>*				_first_comparator;
		comparator<GAtom>*				_second_comparator;
		g_add_remove_callback_group<g_ptr_map_element_added_callback, 
                                    g_ptr_map_insert_call_data, 
                                    g_ptr_map_element_removed_callback, 
                                    g_ptr_map_remove_call_data>		_callback_group;

		void make_map() const;
		void forget_map() const;

	protected:
		void copy_map_base(ptr_map_base& right) const;

		void operator_plus(ptr_map_base& result,const ptr_map_base& right) const;
		void operator_plus_equals(const ptr_map_base& right);

		void operator_minus(ptr_map_base& result,const ptr_map_base& right) const;
		void operator_minus_equals(const ptr_map_base& right);

		void operator_and(ptr_map_base& result,const ptr_map_base& right) const;
		void operator_and_equals(const ptr_map_base& right);

		void call_element_added_callbacks(g_insertion_call_data<ptr_map_base>* call_data=0);
		void call_element_removed_callbacks(g_erasure_call_data<ptr_map_base>* call_data=0);
		void call_element_pre_remove_callbacks(g_erasure_call_data<ptr_map_base>* call_data=0);

		void pre_forget(const g_forget_event& event);
		void forget(const g_forget_event& event);

		void equal_range(const self_comparator<value_type>* comp,iterator& f,iterator& s) const;
		void equal_range(const value_type& value,iterator& f,iterator& s) const;
		void first_equal_range(const self_comparator<GAtom>*,iterator& f,iterator& s) const;
		void first_equal_range(const GAtom*,iterator& f,iterator& s) const;
		void second_equal_range(const self_comparator<GAtom>* v,iterator& f,iterator& s) const;
		void second_equal_range(const GAtom* v,iterator& f,iterator& s) const;

		// Disallow default constructor.
		ptr_map_base();

	public:
		ptr_map_base(	g_behaviors first_behaviors,g_behaviors second_behaviors,
							// Neither first nor second are allowed to have their 'OMEGA_PTR' flags set.
							// Thus, the only legal values are WEAK_PTR and STRONG_PTR.
						bool is_omega_map=false,
							// Specifies whether the map has omega behavior.
						bool first_allows_duplicates=false,bool second_allows_duplicates=false,
							// Do first and second allow duplicates?
						bool allow_duplicate_pairs=false,
							// May be true only if first and second both allow duplicates
						comparator<GAtom>* first_comparator=NULL,comparator<GAtom>* second_comparator=NULL
							// If the comparators are NULL, map sorts according to pointer values.
						);

		ptr_map_base(const ptr_map_base&);

		ptr_map_base(	const ptr_map_base& right,
							// Map to copy.
						g_behaviors first_behaviors,g_behaviors second_behaviors,
							// Neither first nor second are allowed to have their 'OMEGA_PTR' flags set.
							// Thus, the only legal values are WEAK_PTR and STRONG_PTR.
						bool is_omega_map=false,
							// Specifies whether the map has omega behavior.
						bool first_allows_duplicates=false,bool second_allows_duplicates=false,
							// Do first and second allow duplicates?
						bool allow_duplicate_pairs=false,
							// May be true only if first and second both allow duplicates
						comparator<GAtom>* first_comparator=NULL,comparator<GAtom>* second_comparator=NULL
							// If the comparators are NULL, map sorts according to pointer values.
						);
		~ptr_map_base();

		virtual void live_to_ghost();
		virtual void ghost_to_live();

		GAtom* owner() const { return _map.owner(); }
		void owner(GAtom* own) const { _map.owner(own); }

		ptr_map_base& operator=(const ptr_map_base& right);
 		bool operator==(const ptr_map_base& right) const;

		////////////////////////////////////////////////////////////////////////////////////////
		// System Methods.
		void stream(g_stream&);	// The stream() method is rarely called directly.
								// Generally tables are streamed using the
								// aStream << aHashTable; syntax.

		////////////////////////////////////////////////////////////////////////////////////////
		// Functional Methods.
		g_behaviors	first_behaviors() const		{ return _first_behaviors; }
		g_behaviors	second_behaviors() const	{ return _second_behaviors; }
		bool		is_omega() const			{ return _is_omega; }

		size_t size() const;

		void swap(ptr_map_base& right);

		void clear();
		bool empty() const;

		///////////////////////////////////////
		// value_type methods.
		size_t count(const value_type&) const;
		iterator find(const value_type&) const;
		iterator lower_bound(const value_type&) const;
		iterator upper_bound(const value_type&) const;
		erange equal_range(const value_type&) const;

		size_t count(const self_comparator<value_type>*) const;
		iterator find(const self_comparator<value_type>*) const;
		iterator lower_bound(const self_comparator<value_type>*) const;
		iterator upper_bound(const self_comparator<value_type>*) const;
		erange equal_range(const self_comparator<value_type>*) const;

		std::pair<iterator,bool> insert(const value_type&);
		size_type erase(const value_type &);
		void erase(iterator &iter);
		void erase(iterator &f,iterator &s);

		bool contains(const value_type&) const;
		bool contains_all(const ptr_map_base&) const;
		bool contains_any(const ptr_map_base&) const;
		bool contains_none(const ptr_map_base&) const;

		///////////////////////////////////////
		// first methods.
		//     These methods return iterators that
		//     iterate over first order.
		iterator begin() const;
		iterator end() const;
		iterator rbegin() const;
		iterator rend() const;

		size_t first_count(const GAtom* p) const;
		iterator first_find(const GAtom*) const;
		iterator first_lower_bound(const GAtom*) const;
		iterator first_upper_bound(const GAtom*) const;
		erange first_equal_range(const GAtom*) const;
		size_t first_erase(const GAtom*);

		size_t first_count(const self_comparator<GAtom>*) const;
		iterator first_find(const self_comparator<GAtom>*) const;
		iterator first_lower_bound(const self_comparator<GAtom>*) const;
		iterator first_upper_bound(const self_comparator<GAtom>*) const;
		erange first_equal_range(const self_comparator<GAtom>*) const;

		bool first_contains(const GAtom*) const;
		bool first_contains_all(const ptr_map_base&) const;
		bool first_contains_any(const ptr_map_base&) const;
		bool first_contains_none(const ptr_map_base&) const;

		///////////////////////////////////////
		// second methods.
		//      These methods return iterators that
		//      iterate over second order.
		iterator second_begin() const;
		iterator second_end() const;
		iterator second_rbegin() const;
		iterator second_rend() const;

		size_t second_count(const GAtom* p) const;
		iterator second_find(const GAtom*) const;
		iterator second_lower_bound(const GAtom*) const;
		iterator second_upper_bound(const GAtom*) const;
		erange second_equal_range(const GAtom*) const;
		size_t second_erase(const GAtom*);

		size_t second_count(const self_comparator<GAtom>*) const;
		iterator second_find(const self_comparator<GAtom>*) const;
		iterator second_lower_bound(const self_comparator<GAtom>*) const;
		iterator second_upper_bound(const self_comparator<GAtom>*) const;
		erange second_equal_range(const self_comparator<GAtom>*) const;

		bool second_contains(const GAtom*) const;
		bool second_contains_all(const ptr_map_base&) const;
		bool second_contains_any(const ptr_map_base&) const;
		bool second_contains_none(const ptr_map_base&) const;

		////////////////////////////////////////////////////////////////////////////////////////
		// Attrib Methods
		const smart_ptr_set<GAtom>&	attrib_list(const iterator&) const;
		void  attrib_list(const iterator&,const smart_ptr_set<GAtom>& atts);
		void  insert_attrib(const iterator&,const GAtom* att,GInsertionType = INSERT_ANYWHERE,const GAtom* = NULL);
		void  erase_attrib(const iterator&,const GAtom* att);

		////////////////////////////////////////////////////////////////////////////////////////
		// Callback List Methods

		// In the 'add-callback' methods, the 'owner' pointer sets the owner pointer
		// in the callback lists if it is non-zero.  Otherwise, it is ignored.
		void add_element_added_callback(g_ptr_map_element_added_callback,
                                        void *client_data = 0,
                                        GAtom *owner = 0);
		void add_element_pre_remove_callback(g_ptr_map_element_removed_callback,
                                             void *client_data = 0,
                                             GAtom *owner = 0);
		void add_element_removed_callback(g_ptr_map_element_removed_callback,
                                          void *client_data = 0,
                                          GAtom *owner = 0);
		void null_owner(); // Nulls the 'owner' pointer in both callback lists.
		
		void remove_element_added_callback(g_ptr_map_element_added_callback,
                                           void *client_data = 0);
		void remove_element_pre_remove_callback(g_ptr_map_element_removed_callback,
                                                void *client_data = 0);
		void remove_element_removed_callback(g_ptr_map_element_removed_callback,
                                             void *client_data = 0);

		bool element_added_callback_list_empty() const;
		bool element_pre_remove_callback_list_empty() const;
		bool element_removed_callback_list_empty() const;

		void add_update_callback(g_update_callback cb, 
                                 void *client_data = 0);
		void remove_update_callback(g_update_callback cb,
                                    void *client_data = 0);

#if defined (_DEBUG) || defined (_PSEUDO_DEBUG)
		// Method to allow access to internal data for test facilities.
		// Only accessible in debug mode.
		GPtrMap* map() const { return (GPtrMap*)_map; }
#endif
	};

/////////////////////////////////////////////////////////////////////////////////////
//
// The smart_ptr_map<> is a template representing the GeMS pointer map.
//
template <class F,class S> class smart_ptr_map : public ptr_map_base
	{
	public:
		typedef std::pair<F *, S *> value_type;

		class iterator : public ptr_map_base::iterator
			{
			friend class smart_ptr_map<F,S>;

			protected:
				iterator(const ptr_map_base::iterator& i):ptr_map_base::iterator(i) {}
			public:
                typedef smart_ptr_map<F, S> Mybase;
            	typedef std::bidirectional_iterator_tag iterator_category;
	            typedef typename Mybase::value_type value_type;
	            typedef ptrdiff_t difference_type;
	            typedef S* pointer;
	            typedef S& reference;

				iterator(){}
				iterator(const smart_ptr_map<F,S>& lst):ptr_map_base::iterator(lst) {}
				iterator(GPtrMap* m):ptr_map_base::iterator(m) {}
					// This is a dangerous constructor since it circumvents type checking.
					// However, it allows us to create maps of maps.

				iterator& operator=(const iterator& i) { ((ptr_map_base::iterator*)this)->operator=(i); return *this; }

				value_type operator*() const
                    { return(std::make_pair(first(), second())); }

				F* first() const	{ return (F*)((ptr_map_base::iterator*)this)->first(); }
				S* second() const	{ return (S*)((ptr_map_base::iterator*)this)->second(); }
			};

		typedef std::pair<iterator, iterator> erange;

	protected:
		smart_ptr_map():
			ptr_map_base() {}

	public:
		smart_ptr_map(	g_behaviors first_behaviors,g_behaviors second_behaviors,
							// Neither first nor second are allowed to have their 'OMEGA_PTR' flags set.
							// Thus, they may be either WEAK_PTR or STRONG_PTR
						bool is_omega_map=false,
							// Specifies whether the map has omega behavior.
						bool first_allows_duplicates=false,bool second_allows_duplicates=false,
							// Do first and second allow duplicates?
						bool allow_duplicate_pairs=false,
							// May be true only if first and second both allow duplicates
						comparator<F>* first_comparator=NULL,comparator<S>* second_comparator=NULL
							// If the comparators are NULL, map sorts according to pointer values.
							// Is this a 'temporary' map?
						):
			ptr_map_base(	first_behaviors,second_behaviors,is_omega_map,
							first_allows_duplicates,second_allows_duplicates,allow_duplicate_pairs,
							(comparator<GAtom>*)first_comparator,(comparator<GAtom>*)second_comparator) {}

		smart_ptr_map(const smart_ptr_map<F,S>& right):
			ptr_map_base(right)
				{}

		smart_ptr_map(	const smart_ptr_map<F,S>& right,
							// Map to copy.
						g_behaviors first_behaviors,g_behaviors second_behaviors,
							// Neither first nor second are allowed to have their 'OMEGA_PTR' flags set.
						bool is_omega_map=false,
							// Specifies whether the map has omega behavior.
						bool first_allows_duplicates=false,bool second_allows_duplicates=false,
							// Do first and second allow duplicates?
						bool allow_duplicate_pairs=false,
							// May be true only if first and second both allow duplicates
						comparator<F>* first_comparator=NULL,comparator<S>* second_comparator=NULL
							// If the comparators are NULL, map sorts according to pointer values.
						):
			ptr_map_base(	right,
							first_behaviors,second_behaviors,is_omega_map,
							first_allows_duplicates,second_allows_duplicates,allow_duplicate_pairs,
							(comparator<GAtom>*)first_comparator,(comparator<GAtom>*)second_comparator) {}

		smart_ptr_map<F,S>& operator=(const smart_ptr_map<F,S>& right)
			{ ptr_map_base::operator=(right); return *this; }

		/////////////////////////////////////
		// Functional Methods.
		std::pair<iterator,bool> insert(const value_type& v)
			{
			std::pair<ptr_map_base::iterator,bool> retval = ptr_map_base::insert(v); 
			return std::pair<iterator,bool>(iterator(retval.first),retval.second);
			}

		void erase(const value_type &v) { ptr_map_base::erase(v); }
		void erase(iterator &iter) { ptr_map_base::erase(iter); }
		void erase(iterator &f,iterator &s) { ptr_map_base::erase(f,s); }

		/////////////////////////////////////
		// value_type Methods.
		size_t count(const value_type& v) const	{ return ptr_map_base::count(v); }
		bool contains(const value_type& v) const		{ return ptr_map_base::contains(v); }
		iterator find(const value_type& v) const		{ return ptr_map_base::find(v); }
		iterator lower_bound(const value_type& v) const	{ return ptr_map_base::lower_bound(v); }
		iterator upper_bound(const value_type& v) const	{ return ptr_map_base::upper_bound(v); }
		erange equal_range(const value_type& v) const	{ erange r; ptr_map_base::equal_range(v,r.first,r.second); return r; }

		iterator find(const self_comparator<value_type>* c) const			{ return ptr_map_base::find((self_comparator<ptr_map_base::value_type>*)c); }
		iterator lower_bound(const self_comparator<value_type>* c) const	{ return ptr_map_base::lower_bound((self_comparator<ptr_map_base::value_type>*)c); }
		iterator upper_bound(const self_comparator<value_type>* c) const	{ return ptr_map_base::upper_bound((self_comparator<ptr_map_base::value_type>*)c); }
		erange equal_range(const self_comparator<value_type>* c) const		{ erange r; ptr_map_base::equal_range((self_comparator<ptr_map_base::value_type>*)c,r.first,r.second); return r; }

		/////////////////////////////////////
		// first Methods.
		iterator begin() const	{ return ptr_map_base::begin(); }
		iterator end() const	{ return ptr_map_base::end(); }
		iterator rbegin() const	{ return ptr_map_base::rbegin(); }
		iterator rend() const	{ return ptr_map_base::rend(); }

		size_t first_count(const F* p) const		{ return ptr_map_base::first_count(reinterpret_cast<const GAtom *>(p)); }
		bool first_contains(const F* v) const			{ return ptr_map_base::first_contains(reinterpret_cast<const GAtom *>(v)); }
		iterator first_find(const F* v) const			{ return ptr_map_base::first_find(reinterpret_cast<const GAtom *>(v)); }
		iterator first_lower_bound(const F* v) const	{ return ptr_map_base::first_lower_bound(reinterpret_cast<const GAtom *>(v)); }
		iterator first_upper_bound(const F* v) const	{ return ptr_map_base::first_upper_bound(reinterpret_cast<const GAtom *>(v)); }
		erange first_equal_range(const F* v) const		{ erange r; ptr_map_base::first_equal_range(reinterpret_cast<const GAtom *>(v),r.first,r.second); return r; }

		iterator first_find(const self_comparator<F>* c) const		{ return ptr_map_base::first_find((self_comparator<GAtom>*)c); }
		iterator first_lower_bound(const self_comparator<F>* c) const	{ return ptr_map_base::first_lower_bound((self_comparator<GAtom>*)c); }
		iterator first_upper_bound(const self_comparator<F>* c) const	{ return ptr_map_base::first_upper_bound((self_comparator<GAtom>*)c); }
		erange first_equal_range(const self_comparator<F>* c) const	{ erange r; ptr_map_base::first_equal_range((self_comparator<GAtom>*)c,r.first,r.second); return r; }
			// These methods return iterators that iterate over first order.

		/////////////////////////////////////
		// second Methods.
		iterator second_begin() const	{ return ptr_map_base::second_begin(); }
		iterator second_end() const		{ return ptr_map_base::second_end(); }
		iterator second_rbegin() const	{ return ptr_map_base::second_rbegin(); }
		iterator second_rend() const	{ return ptr_map_base::second_rend(); }

		size_t second_count(const S* p) const	{ return ptr_map_base::second_count(reinterpret_cast<const GAtom *>(p)); }
		bool second_contains(const S* v) const			{ return ptr_map_base::second_contains(reinterpret_cast<const GAtom *>(v)); }
		iterator second_find(const S* v) const			{ return ptr_map_base::second_find(reinterpret_cast<const GAtom *>(v)); }
		iterator second_lower_bound(const S* v) const	{ return ptr_map_base::second_lower_bound(reinterpret_cast<const GAtom *>(v)); }
		iterator second_upper_bound(const S* v) const	{ return ptr_map_base::second_upper_bound(reinterpret_cast<const GAtom *>(v)); }
		erange second_equal_range(const S* v) const		{ erange r; ptr_map_base::second_equal_range(reinterpret_cast<const GAtom *>(v),r.first,r.second); return r; }

		iterator second_find(const self_comparator<S>* c) const			{ return ptr_map_base::second_find((self_comparator<GAtom>*)c); }
		iterator second_lower_bound(const self_comparator<S>* c) const	{ return ptr_map_base::second_lower_bound((self_comparator<GAtom>*)c); }
		iterator second_upper_bound(const self_comparator<S>* c) const	{ return ptr_map_base::second_upper_bound((self_comparator<GAtom>*)c); }
		erange second_equal_range(const self_comparator<S>* c) const	{ erange r; ptr_map_base::second_equal_range((self_comparator<GAtom>*)c,r.first,r.second); return r; }
			// These methods return iterators that iterate over second order.

		/////////////////////////////////////
		// Operators.
		smart_ptr_map<F,S>& operator+=(const smart_ptr_map<F,S>& right)
					{ ptr_map_base::operator_plus_equals(right); return *this; }

		smart_ptr_map<F,S>& operator-=(const smart_ptr_map<F,S>& right)
					{ ptr_map_base::operator_minus_equals(right); return *this; }

		smart_ptr_map<F,S>& operator&=(const smart_ptr_map<F,S>& right)
					{ ptr_map_base::operator_and_equals(right); return *this; }
	};

GEMS_TEMPLATE(struct, g_insertion_call_data<ptr_map_base>);
GEMS_TEMPLATE(struct, g_erasure_call_data<ptr_map_base>);

DECL_GEMS void g_reverse_call_data(const g_ptr_map_insert_call_data& in,g_ptr_map_remove_call_data& out);
DECL_GEMS void g_reverse_call_data(const g_ptr_map_remove_call_data& in,g_ptr_map_insert_call_data& out);

#endif
