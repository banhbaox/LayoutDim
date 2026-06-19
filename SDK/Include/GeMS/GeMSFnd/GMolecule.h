
#ifndef _g_molecule_h_
#define _g_molecule_h_

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

#include "GeMS/GemsFnd/Gsubatom.h"
#include "GeMS/GemsFnd/GAtom.h"

#include "GeMS/Containers/Ptrset.h"
#include "GeMS/Containers/PtrMap.h"

#include "GeMS/GRelate.h"

typedef size_t g_id;

class DECL_GEMS GMolecule;
class DECL_GEMS GMoleculeStack;
GEMS_TEMPLATE(class, smart_ptr<GMoleculeStack>);
GEMS_TEMPLATE(class, ptr<GMoleculeStack>);
GEMS_TEMPLATE(class, smart_ptr_map<GAtom, GAtom>);

class DECL_GEMS g_object_manager;
class DECL_GEMS g_time_line;
class DECL_GEMS g_experiment;
class DECL_GEMS g_experiment_start_call_data
	{
	public:
		g_experiment* experiment;
	};
	
class DECL_GEMS g_experiment_end_call_data
	{
	public:
		g_experiment* experiment;
		bool accepted;
	};
	
DECLARE_CALLBACK_TYPE(g_experiment_start_callback,
                      g_experiment_start_call_data, GEMS);
DECLARE_CALLBACK_TYPE(g_experiment_end_callback,
                      g_experiment_end_call_data, GEMS);

class DECL_GEMS g_molecule
	{
	friend class DECL_GEMS g_formatted_stream;
	friend class DECL_GEMS g_experiment;
	friend class DECL_GEMS GAtom;
	friend class DECL_GEMS g_molecule_read_manager;
	friend class DECL_GEMS g_object_manager;
	friend class DECL_GEMS g_suppress_object_manager;

	private:
		mutable ptr<GMoleculeStack>	_molecule_stack;
		g_object_manager*	_object_manager;
		g_experiment*		_experiment_stack;
		bool				_is_dirty;
		bool				_is_dying;
		
		GAtom* _newbie_cache_head;
		GAtom* _newbie_cache_tail;
		GAtom* _atom_list_head;
		GAtom* _atom_list_tail;

		// Methods used by 'pop_merge()' to perform its job.
		void merge_element_lists(GMolecule*);
		
		// Methods used by object managers to maintain atom states.
		void purge_newbie_cache();
		void move_to_newbie_cache(GAtom*);
		void move_to_atom_list(GAtom*);
		void add_to_newbie_cache(GAtom*);
		void remove_from_newbie_cache(GAtom*);
		void add_to_atom_list(GAtom*);
		void remove_from_atom_list(GAtom*);
		
		static GAtom* next_in_atom_list(GAtom*);
		static GAtom* prev_in_atom_list(GAtom*);

		g_experiment_start_callback_list m_experiment_start_callbacks;
		g_experiment_end_callback_list   m_experiment_end_callbacks;
		
		void start_experiment(g_experiment*);
		void end_experiment(bool bAccepted);

		virtual void push_experiment(g_experiment*);
		virtual void pop_experiment();
		
		void call_experiment_start_callbacks(g_experiment_start_call_data* pCallData);
		void call_experiment_end_callbacks(g_experiment_end_call_data* pCallData);

	protected:
		// Stack operations.
		virtual GMolecule* peek() const;
		virtual void push(GMolecule* m);

		virtual void destroy_object_manager();

		// Rollback operations.
		virtual void on_destruction(GAtom*);
		virtual void on_insertion(GAtom*);
		virtual void on_backup(GAtom*);
		
		virtual void on_begin_note_state();
		virtual void on_end_note_state();

		// Normal operations.
		virtual void make_molecule() const;
		virtual void forget_molecule() const;
		virtual void construct_molecule(ptr<GMolecule>&) const;
		virtual void copy_molecule(const g_molecule& right);

		virtual void stream_header(g_stream&,unsigned long version);

		// Element List methods.
		const ptr_set<GAtom>& element_list() const;
		void element_list(const smart_ptr_set<GAtom>& els);

		void add_element(GAtom*,GInsertionType=INSERT_ANYWHERE,const GAtom* = NULL);
		void remove_element(GAtom* p);
		void clear_element_list();
		bool element_list_empty() const;
		bool element_list_contains(const GAtom* p) const;
					// Returns true if 'p' is a top-level entity.

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
		void null_element_list_owner(); // Nulls the 'owner' pointer in both callback lists.
		
		void remove_element_added_callback(g_element_added_callback,
                                           void *client_data = 0);
		void remove_element_removed_callback(g_element_removed_callback,
                                             void *client_data = 0);
		void remove_element_pre_remove_callback(g_element_removed_callback,
                                                void *client_data = 0);

		virtual void scan(smart_ptr_set<GAtom>&) const;

	public:
		g_molecule();
		g_molecule(const g_molecule&);	// Performs deep copy of entire molecule.
		virtual ~g_molecule();

		g_molecule& operator=(const g_molecule&);
		bool	owns(const GAtom* p) const;
					// Returns true if the doc directly or indirectly owns 'p'.

		///////////////////////////////////////////////////////////////////////////////////
		// Stack operations.
		//
		virtual void push();
		virtual void pop();
		virtual void pop_merge();

		///////////////////////////////////////////////////////////////////////////////////
		// Methods to manage the g_molecule's undo/redo system.
		//
		bool	undo_enabled() const;
		bool	can_undo(unsigned int nStates=1) const;
		bool	can_redo(unsigned int nStates=1) const;

		virtual void	enable_undo(g_time_line* =NULL);
		virtual void	disable_undo();
		virtual size_t  note_state(bool bForceDistinctState=false);
		virtual void note_state_without_stop_point();

		virtual bool is_rolling_back() const;
		virtual bool is_performing_experiment() const;

		virtual bool commit_to(size_t nUndoStateId,
                               bool bSearchRedoStatesFirst = false);
				// Searches the time-line for the given state ID.  If found in the undo states,
				// throws away all states prior to the given state.  If found in the redo states,
				// throws away all states after the given state.  The bSearchRedoStatesFirst tells
				// the method whether to search the undo or redo states first.  Returns
				// 'true' upon success.
		virtual void commit();

		size_t current_undo_state_id() const;

		virtual unsigned int undo(unsigned int nStates = 1,
                                  size_t *newCurrentUndoStateId = NULL);
		virtual unsigned int redo(unsigned int nStates = 1,
                                  size_t *newCurrentUndoStateId = NULL);

		virtual unsigned int undo_to(size_t uUndoUnitId,
                                     size_t *newCurrentUndoStateId = NULL);
		virtual unsigned int redo_to(size_t uUndoUnitId,
                                     size_t *newCurrentUndoStateId = NULL);

		bool is_dirty() const { return _is_dirty; }
		virtual void is_dirty(bool f) { _is_dirty = f; }
		
		bool is_dying() const { return _is_dying; }

		g_object_manager* active_object_manager() const;
		
		// The experiment start and end callbacks are called whenever an experiment on the document
		// begins or ends.
		void add_experiment_start_callback(g_experiment_start_callback cb,
                                           void *client_data = 0);
		void remove_experiment_start_callback(g_experiment_start_callback cb,
                                              void *client_data = 0);

		void add_experiment_end_callback(g_experiment_end_callback cb,
                                         void *client_data = 0);
		void remove_experiment_end_callback(g_experiment_end_callback cb,
                                            void *client_data = 0);

		///////////////////////////////////////////////////////////////////////////////////
		// Methods that allow a GAtom to be assigned an identifier that is unique
		// within the context of this g_molecule.  It is an error to attempt to
		// generate an id for a GAtom that is not contained within the molecule.
		//
		g_id  existing_id(const GAtom* obj) const;
			// Returns id if obj already has one.
		g_id  id(GAtom* obj);
			// Returns id of obj.  If obj does not already have an id, generates one.
		
		ghost_ptr<GAtom> lookup(g_id id) const;
			// Returns GAtom* for given id.

		// ******* COCLASS SUPPORT METHODS *********
		// The following coclass methods are provided simply as 'hooks' that
		// you can use in implementing coclasses (or API classes) that
		// are associated with the g_molecule.  Thus, you could implement a COM
		// coclass and use these methods to manage a relationship between
		// it and the g_molecule.
		virtual void* unknown() const { return 0; }
		
		class DECL_GEMS g_atom_list_iterator
			{
			private:
				GAtom* m_pAtom;
				
			public:
				g_atom_list_iterator(GAtom* pAtom)
					{ m_pAtom = pAtom; }
				GAtom* operator*() { return m_pAtom; }
				void operator++();
				void operator--();
			};
		friend class g_atom_list_iterator;
		
	protected:
		g_atom_list_iterator newbie_cache_iterator(GIteratorAction act=G_BEGIN); // Also supports G_END.
		g_atom_list_iterator atom_list_iterator(GIteratorAction act=G_BEGIN); // Also supports G_END.
	};


#endif

