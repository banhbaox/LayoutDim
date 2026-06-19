
#ifndef _avl_tree_h_
#define _avl_tree_h_

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
#include "GeMS/GemsFnd/Ptr.h"
#include "GeMS/GemsFnd/LeanPtr.h"
#include "GeMS/GemsFnd/Gsubatom.h"
#include "GeMS/Containers/Ginsert.h"

DECLARE_MINIMAL_GEMS_DLL_EXPORTS(GAtom,GEMS)
DECLARE_MINIMAL_GEMS_DLL_EXPORTS(GAvlTree,GEMS)
DECLARE_MINIMAL_GEMS_DLL_EXPORTS(GAvlTreeNode,GEMS)

GEMS_TEMPLATE(class, lean_smart_ptr<GAvlTree>);
GEMS_TEMPLATE(class, lean_hard_ptr<GAvlTree>);

class DECL_GEMS ptr_container_base;

typedef g_insertion_call_data<ptr_container_base> g_insert_call_data;
typedef g_erasure_call_data<ptr_container_base> g_remove_call_data;

DECLARE_CALLBACK_TYPE(g_element_added_callback,   g_insert_call_data, GEMS);
DECLARE_CALLBACK_TYPE(g_element_removed_callback, g_remove_call_data, GEMS);

// ptr_container_base has the concept of a sequence order and an (avl) tree order.
// The sequence order is any arbitrary ordering and, at the ptr_container_base
// level, is equivalent to the tree order.  However, the sequence order is not
// necessarily the same as the tree order and may be altered by sub-classes.  The
// sequence order is considered the primary order while the tree order is secondary.

class DECL_GEMS ptr_container_base : public g_sub_atom
	{
	public:
		typedef GAtom* value_type;
		typedef const GAtom* const_value_type;
		typedef size_t size_type;

		static value_type null_value_type() { return 0; }

		///////////////////////////////////////////////////
		// iterator
		//    Cannot be saved to file and should be used 
		//    as a local variable only since it locks the
		//    referenced collection!
		class DECL_GEMS iterator
			{
			friend class GAvlTree;
			friend class ptr_container_base;

			private:
				mutable lean_hard_ptr<GAvlTree>	_container;
				mutable weak_ptr<GAvlTreeNode>	_node;
				mutable bool					_reverse_direction;
				mutable bool					_iterates_in_tree_order;

				void reset(const GAvlTree* c,const GAvlTreeNode* n)
					{ _container = (GAvlTree*)c; _node = (GAvlTreeNode*)n; }

			public:
	            typedef std::bidirectional_iterator_tag iterator_category;
            	typedef ptr_container_base::value_type value_type;
	            typedef ptrdiff_t difference_type;
	            typedef difference_type distance_type;	// retained
	            typedef GAtom *pointer;
	            typedef GAtom &reference;

				iterator();
				iterator(const ptr_container_base& s);
				iterator(const iterator&);
				iterator(const GAvlTree* s);
				iterator(const GAvlTree* s,const GAvlTreeNode* n,bool reverse=false,bool tree_order=false);
				~iterator();

				inline bool valid() const { return (_node!=NULL); }

				iterator& operator=(const iterator& right);

				void operator++() const;
				void operator++(int) const;

				void operator--() const;
				void operator--(int) const;

				inline bool operator==(const iterator& i) const
					{ return _node == i._node; }
				inline bool operator!=(const iterator& i) const
					{ return _node != i._node; }

				GAtom *operator*() const;

				size_type location_id() const;
			};

		typedef std::pair<iterator,iterator> erange;
		typedef iterator reverse_iterator;

		friend class DECL_GEMS ptr_container_base::iterator;
		friend class DECL_GEMS GAvlTree;

	private:
		mutable lean_hard_ptr <GAvlTree>	_container;
		g_behaviors							_behaviors;
		g_add_remove_callback_group<g_element_added_callback, 
                                    g_insert_call_data, 
                                    g_element_removed_callback, 
                                    g_remove_call_data>		_callback_group;

	protected:
		GAvlTree* container() const { return _container; }
		void container(GAvlTree* t) { _container = t; }

		virtual GAvlTree* construct_container() const;

		virtual void make_container() const;	// calls construct_container() if _container==NULL.
		virtual void forget_container() const;

		virtual void behaviors(g_behaviors Behaviors);

		void call_element_added_callbacks(g_insertion_call_data<ptr_container_base>* call_data=0);
		void call_element_removed_callbacks(g_erasure_call_data<ptr_container_base>* call_data=0);
		void call_element_pre_remove_callbacks(g_erasure_call_data<ptr_container_base>* call_data=0);

		void pre_forget(const g_forget_event& event);
		void forget(const g_forget_event& event);

		void equal_range(const GAtom*,iterator&,iterator&) const;

		void operator_plus(ptr_container_base& result,const ptr_container_base& right) const;
		void operator_plus_equals(const ptr_container_base& right);

		void operator_minus(ptr_container_base& result,const ptr_container_base& right) const;
		void operator_minus_equals(const ptr_container_base& right);

		void operator_and(ptr_container_base& result,const ptr_container_base& right) const;
		void operator_and_equals(const ptr_container_base& right);

		void insert(iterator& resultIter,bool&resultInserted,GAtom*);
		void find(iterator& resultIter,const GAtom*) const;

		static void reset(iterator& iter,const GAvlTree* tree,const GAvlTreeNode* node)
			{ iter.reset(tree,node); }

		ptr_container_base();
		ptr_container_base(const ptr_container_base&);

	public:
		ptr_container_base(	g_behaviors Behaviors);
		ptr_container_base(	const ptr_container_base&,
						g_behaviors Behaviors);
		virtual ~ptr_container_base();

		ptr_container_base& operator=(const ptr_container_base& right);
 		bool operator==(const ptr_container_base& right) const;

		virtual void live_to_ghost();
		virtual void ghost_to_live();

		GAtom* owner() const { return _container.owner(); }
		void owner(GAtom* own) const { _container.owner(own); }

		g_behaviors behaviors() const { return _behaviors; }

		void stream(g_stream&);
			// The stream() method is rarely called directly.
			// Generally containers are streamed using the
			// aStream << aSet; syntax.

		size_type size() const;

		std::pair<iterator,bool> insert(GAtom*);

		size_type erase(GAtom* p);
		void erase(iterator &iter);
		void erase(iterator &f, iterator &s);

		void swap(ptr_container_base&);

		virtual void clear();
		bool empty() const;

		bool contains(const GAtom* p) const;
		bool contains_all(const ptr_container_base&) const;
		bool contains_any(const ptr_container_base&) const;
		bool contains_none(const ptr_container_base&) const;

		size_type count(const GAtom* p) const;

		iterator begin() const;		// Returned iterator iterates over sequence order.
		iterator end() const { return iterator(); }
		iterator rbegin() const;	// Returned iterator iterates over sequence order.
		iterator rend() const { return iterator(); }

		iterator find(const GAtom*) const;		// Returned iterator iterates over sequence order.

		iterator lower_bound(const GAtom*) const;	// Returned iterator iterates over tree order
		iterator upper_bound(const GAtom*) const;	// Returned iterator iterates over tree order
		erange equal_range(const GAtom*) const;		// Returned iterators iterate over tree order

		#ifdef G_COLLECTION_ATTRIBS

			// Attribute methods
			const smart_ptr_set<GAtom>&	attrib_list(const iterator&) const;
			void  attrib_list(const iterator&,const smart_ptr_set<GAtom>& atts);
			void  insert_attrib(const iterator&,GAtom* att,GInsertionType = INSERT_ANYWHERE,const GAtom* = NULL);
			void  erase_attrib(iterator&,GAtom* att);

		#endif

		// Callback Methods

		// In the 'add-callback' methods, the 'owner' pointer sets the owner pointer
		// in the callback lists if it is non-zero.  Otherwise, it is ignored.
		void add_element_added_callback(g_element_added_callback,
                                        void *client_data = 0,
                                        GAtom *owner = 0);
		void add_element_removed_callback(g_element_removed_callback,
                                          void *client_data = 0,
                                          GAtom *owner = 0);
		void add_element_pre_remove_callback(g_element_removed_callback,
                                             void *client_data = 0,
                                             GAtom *owner = 0);
		void null_owner(); // Nulls the 'owner' pointer in all callback lists.
		
		void remove_element_added_callback(g_element_added_callback,
                                           void *client_data = 0);
		void remove_element_removed_callback(g_element_removed_callback,
                                             void *client_data = 0);
		void remove_element_pre_remove_callback(g_element_removed_callback,
                                                void *client_data = 0);

		bool element_added_callback_list_empty() const;
		bool element_removed_callback_list_empty() const;
		bool element_pre_remove_callback_list_empty() const;

		void add_update_callback(g_update_callback cb,
                                 void *client_data = 0);

		void remove_update_callback(g_update_callback cb,
                                    void *client_data = 0);
	};

GEMS_TEMPLATE(struct, g_insertion_call_data<ptr_container_base>);
GEMS_TEMPLATE(struct, g_erasure_call_data<ptr_container_base>);

DECL_GEMS void g_reverse_call_data(const g_insert_call_data &in,
						           g_remove_call_data &out);

DECL_GEMS void g_reverse_call_data(const g_remove_call_data &in,
						           g_insert_call_data &out);

#endif
