
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

#ifndef _g_atom_h_
#define _g_atom_h_

#include "GeMS/Dcl_gems.h"

class DECL_GEMS g_stream;
class DECL_GEMS g_primitive;

#include "GeMS/GemsFnd/Cback.h"
#include "GeMS/GemsFnd/Gtype.h"

class DECL_GEMS g_molecule;
class DECL_GEMS ptr_base;
template <class T> class ghost_ptr;

class DECL_GEMS GAtom;
class DECL_GEMS GAttrib;
class DECL_GEMS g_forget_event;
class g_data_preserve;

//	GAtom is the root foundation object for all objects
//	which take advantage of the GeMS system functionality
//	(i.e. persistence, rollback, etc.)
//
//	GAtom derived objects inherit a use-count and a
//	system-count (used mainly by the rollback system).
//	These integers give the object sufficient knowledge for
//	it to control its own lifetime (it 'knows' the number of
//	ptr<>s pointing to it).  When the use-count drops to
//	equal the system count, the object 'dies', triggering
//	any weak_ptr<>s referencing it to be NULLed.  When both
//	the use-count and system-count drop to zero, the object
//	deletes itself.  As such, no explicit delete should ever
//	be performed on any object derived from GAtom.
//
//	The following actions are EXTREMELY important:
//
//	1)  The object should not be assigned to a ptr<> (or
//	have its use() method called) before it is fully
//	constructed.
//
//	2)  The object MUST be assigned to a ptr<> after
//	construction (This will trigger the initialize() method
//	to be called and cause other initialization procedures
//	to be executed).
//
//	FLAGS:
//
//	The following (inline) methods provide system flags
//	giving information about the object's current state:
//
//	unsigned char  is_rolling_back() const
//
//	     This flag indicates whether the object is currently
//	being taken to a previous state by the rollback system.
//
//	unsigned char is_backup_image() const
//
//	     This flag indicates whether the object is merely an
//	image created by the rollback system to backup the state
//	of another object.
//
//	unsigned char is_backed_up() const
//
//	     This flag is used by the rollback system to
//	indicates whether the object has already been backed up
//	since the last noted state.
//
//	ADDITIONAL ROLLBACK METHODS:
//
//	void backup() const
//
//	     This method simply informs the rollback system that
//	the value of the object is about to change and that (if
//	it has not already been backed up since the last noted
//	state) a backup image should be created to allow for a
//	future possible rollback.  This method should ALWAYS be
//	called before any change is made to the object's value
//	(Only one time per method is needed).
//
//	CALLBACK METHODS:
//
//	   There are a number of methods which manage the
//	various callback mechanisms of all GAtom objects:
//
//	void add_lose_callback(callback cb,void* client_data=0);
//
//	void remove_lose_callback(callback cb,void*
//	client_data=0);
//
//	     These methods manage the 'lose' callback list.  The
//	callbacks in this list are called when the object is
//	lost (i.e. its use-count drop to a value no greater than
//	its backup-count).
//
//	void add_update_callback(callback cb,void*
//	client_data=0);
//
//	void remove_update_callback(callback cb,void*
//	client_data=0);
//
//	void call_update_callbacks(void* data=0) const;
//
//	     These methods manage the object's 'update'
//	callbacks.  These callbacks are called when a
//	note_state(), undo(), or redo() is performed in the
//	rollback system.  The update callbacks are only called
//	for those objects which were backed up since the
//	previous noted state.  Anyone may call the
//	update_callbacks themselves, however, using the
//	call_update_callbacks() method.  This is useful in
//	applications which do not use the rollback system.
//
//	DECLARE_GEMS_CLASS Methods
//
//	Every GAtom derived class should have the
//	DECLARE_GEMS_CLASS macro in its class declaration and
//	the DEFINE_GEMS_CLASS macro in its .cpp file.  These
//	macros provide implementations of some useful methods:
//
//	g_type* type() const;
//
//	     This method returns a pointer to a g_type class.
//	This class acts as an 'exemplar', or representation of
//	the object's class.  See GType for further details.
//
//	GAtom* copy() const;
//
//	    This method returns a duplicate of the object (as
//	defined by the object's copy constructor).

DECLARE_CALLBACK_TYPE(g_update_callback,         void,  GEMS);
DECLARE_CALLBACK_TYPE(g_lose_callback,           GAtom, GEMS);
DECLARE_CALLBACK_TYPE(g_sys_initialize_callback, GAtom, GEMS);
DECLARE_CALLBACK_TYPE(g_sys_lose_callback,       GAtom, GEMS);
DECLARE_CALLBACK_TYPE(g_sys_unlose_callback,     GAtom, GEMS);

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GAtom
//
class DECL_GEMS GAtom
	{
	friend DECL_GEMS class ptr_base;
	friend DECL_GEMS class g_stream;
	friend DECL_GEMS class g_out_stream;
	friend DECL_GEMS class g_save_prep_stream;
	friend DECL_GEMS class g_molecule;
	friend DECL_GEMS class g_molecule_stream;
	friend DECL_GEMS void g_forget(ptr_base&);
	friend class g_system_callback_manager;

	public:
		GAtom();
		GAtom(const GAtom &right);
		virtual ~GAtom();

		const GAtom & operator=(const GAtom &right);
		
		bool operator==(const GAtom &right) const;
		bool operator!=(const GAtom &right) const;

		//--------------------------------------------------------------------------------
		// ******* MEMORY MANAGEMENT METHODS *********
		
		//	The use-count and system-count keep track of the number
		//  references to the object.  The use-count keeps track
		//  of all references, while the system-count keeps track
		//  of the number of references used by the GeMS system
		//  itself.  Thus, the use-count should always be greater
		//  than or equal to the system-count.
		const size_t use_count () const;
		const size_t system_count () const;
        const size_t save_index() const { return(m_save_index); }

		//	The fundamental purpose of these methods is to inform the
		//	object of the number of owning references pointing to it.
		//	For example, use() is called whenever the object is assigned
		//  to a ptr<> and lose() is called when the ptr<> no longer
		//  references it.
		//
		//	The first time use() is called, the object will call its
		//  'initialize()' method.
		size_t use ();
		size_t lose ();
		size_t increment_system_count ();
		size_t decrement_system_count ();
		
		// The forget() method instructs an object to remove a particular
		// reference to a given object.  The passed event provides the
		// address of the object being forgotten (via its value() method) and 
		// can be queried whether the event is intended for a particular
		// ptr<>, ptr_set<>, ptr_list<>, or other ptr or container type
		// (via the affects() methods).  If there are multiple references
		// to the forgotten object, a separate 'forget()' call will be made
		// for each reference.  In cases where a forget event occurs
		// in a container where more than a single instance of a ptr value may
		// exist (i.e. in a ptr_list<>), a g_remove_call_data structure will
		// also be available (via the call_data() method) to provide the
		// necessary information to determine which specific ptr value is about
		// to be NULLed.  An exception exists here with ptr_array<>s.
		// The g_forget_event's affects() methods will work on ptr_arrays, but
		// if the affected ptr value is contained within the array, you must then
		// call the event's 'affected_index()' method to discover its location
		// within the array.  Note that virtually all objects will be able to
		// use the default definition for forget(), so it shouldn't be necessary
		// to overload it.
		virtual void forget(const g_forget_event& event);

		//	The initialize() method is called the first time use() is called.
		//	This usually happens the first time the object is assigned to a
		//  ptr<>.  The method may be overridden to provide a convenient way
		//  to perform final initialization on the object.
		virtual void initialize ();
		virtual void finalize ();

		// The is_initialized and is_marked_for_destruction flags are read-only
		// flags describing the state of the object.  is_initialized will be
		// true only after the initialize() method is called (which generally
		// happens on the first assignment to a ptr<>.  The is_marked_for_destruction
		// flag will be true only after the use-count drops to zero and before
		// the actual deletion.
		bool is_initialized() const { return m_flags.m_is_initialized; }
		bool is_marked_for_destruction() const { return m_flags.m_is_marked_for_destruction; }
		bool is_ghost() const;
		virtual bool is_dying() const { return (m_flags.m_nulling_strong_ptrs || m_flags.m_nulling_weak_ptrs); }

		// The is_owned_by() method returns true if the GAtom is owned directly or
		// indirectly by the given GAtom.  (The query performs a search through
		// the entire tree of owning references - ~ O(n*m) where n is the average
		// number of references to an object (usually small) and m is the depth of
		// the ownership hierarchy (also usually small).
		virtual bool is_owned_by(const GAtom* obj) const;

		//--------------------------------------------------------------------------------
		// ******* STREAM SUPPORT METHODS *********

		//	The stream() method provides a standardized way for a
		//	system and object to communicate.  The stream method's
		//	most commonly understood function is to input and output
		//	data from a file.  However, it is used by the GeMS
		//	system for a wide variety of purposes.  Keep in mind
		//	that everything making up the object's value and all of
		//	the relationships the object has with other objects (via
		//	ptr<>s, ptr_set<>s, ptr_list<>s, etc.) should be
		//	streamed in this method.  Otherwise, these values cannot
		//	be made persistent and cannot be updated by the system
		//	when needed.
		virtual void stream (g_stream& str);

		// This method simply calls the stream() method and then, if there is
		// any data_preserve data, streams that as well.  It should not be overloaded.
		// Most streams should call the 'stream_all()' method rather than directly call
		// the 'stream()' method.  Only those that handle the g_data_preserve info
		// themselves should call stream() directly.
		void stream_all(g_stream& str);
	
		// These methods are called by the g_input_stream and g_output_stream
		// classes to allow the object to read from and write to old file
		// formats.
		virtual void pre_old_to_new (g_stream& str);
		virtual void post_old_to_new (g_stream& str);
		virtual void pre_new_to_old (g_stream& str);
		virtual void post_new_to_old (g_stream& str);
				
		// The data_preserve holds any data that was read in from file that
		// corresponds to a type whose library is not linked into the application.
		// The GAtom assumes ownership of the given g_data_preserve and once
		// it is changed to non-NULL may NOT be altered.
		const g_data_preserve*	data_preserve() const	{ return m_data_preserve; }
		void  data_preserve(g_data_preserve* dp);

		//--------------------------------------------------------------------------------
		// ******* ROLLBACK METHODS *********
		g_molecule* molecule() const { return m_molecule; }
		virtual void molecule(g_molecule*);

		// The backup() method informs the rollback system that a change is about to
		// occur in the object.  It should ALWAYS be called prior to any change or the
		// rollback system cannot adequately perform its job.  However, it needs
		// to be called only once per operation (or method).
		void backup() const;

		// The is_backed_up flag should be altered ONLY by the rollback mechanisms.
		// It is intended to let the rollback mechanism quickly know if an object
		// has already been backed up for a given undo/redo operation.
		bool is_backed_up() const { return m_flags.m_is_backed_up; }
		void is_backed_up(bool f) const { m_flags.m_is_backed_up = f; }
		
		// The is_in_rollback_system flag should be altered ONLY by the rollback
		// mechanisms.  It is intended to let the rollback mechanism quickly know
		// if an object has already been introduced into the undo/redo system.
		// Once set to true, it will remain so until a commit() is performed.
		bool is_in_rollback_system() const { return m_flags.m_is_in_rollback_system; }
		void is_in_rollback_system(bool f) { m_flags.m_is_in_rollback_system = f; }
		
		// The is_rolling_back flag should be set by the rollback system
		// when the object is in the process of rolling back (or forward).
		bool is_rolling_back() const { return m_flags.m_is_rolling_back; }
		void is_rolling_back(bool f) { m_flags.m_is_rolling_back = f; }

		bool is_rolling_to_newbie_state() const { return m_flags.m_is_rolling_to_newbie_state; }
		void is_rolling_to_newbie_state(bool f) { m_flags.m_is_rolling_to_newbie_state = f; }
		
		// The is_backup_image flag should be set by the rollback system
		// when the object is simply used as a backup image of another object.
		bool is_backup_image() const { return m_flags.m_is_backup_image; }
		void is_backup_image(bool f) { m_flags.m_is_backup_image = f; }
		
		// The spans_note_state_boundary flag should be set by the rollback system
		// when the object survives at least a single note-state boundary.
		// If no rollback system is active at the time of initialization,
		// 'spans_note_state_boundary' is set to true.
		bool spans_note_state_boundary() const { return m_flags.m_spans_note_state_boundary; }
		void spans_note_state_boundary(bool f) const { m_flags.m_spans_note_state_boundary = f; }
		
		// The is_in_newbie_cache flag should be set by the rollback system
		// when an object is added to the newbie cache and should be cleared
		// when it is removed.
		bool is_in_newbie_cache() const { return m_flags.m_is_in_newbie_cache; }
		void is_in_newbie_cache(bool f) const;
		
		bool is_in_atom_list() const { return m_flags.m_is_in_atom_list; }
		void is_in_atom_list(bool f) const;
		
		// The needs_updating flag should be set by the rollback system
		// prior to an undo/redo operation to keep track of whether the
		// update callbacks have already been called for this object.  When
		// they are called, the flag is cleared so that the callbacks are
		// only triggered once per atom on any given undo/redo.
		bool needs_updating() const { return m_flags.m_needs_updating; }
		void needs_updating(bool f) { m_flags.m_needs_updating = f; }

		// The suppress_rollback flag specifies whether this particular GAtom
		// should suppress any backup() requests to preserve its state in the
		// rollback system.  The consequence of this is that undo/redo operations
		// will not affect the object.  This flag should be set upon the GAtom's
		// construction and then left unaltered.  In fact, the flag will refuse to
		// be altered once the object has been initialized.  It is best to
		// simply set this flag in the constructor and leave it.  If necessary,
		// the flag can be set immediately after construction but before the atom
		// is assigned to any GeMS++ smart pointer.
		bool suppress_rollback() const { return m_flags.m_suppress_rollback; }
		void suppress_rollback(bool f) { if(!m_flags.m_is_initialized) m_flags.m_suppress_rollback = f; }
		
		//--------------------------------------------------------------------------------
		// ******* CALLBACK METHODS *********
		
		// The lose callbacks are called whenever the use-count of an object
		// drops to equal its system-count.
		void add_lose_callback(g_lose_callback cb, void *data = NULL)
            { m_lose_callbacks.owner(this); m_lose_callbacks.add(cb, data); }

		void remove_lose_callback(g_lose_callback cb, void *data = NULL)
            { m_lose_callbacks.remove(cb, data); }
		
		// The update callbacks are called whenever a change has been made to an object
		// and the document's note_state() method is called.
		void add_update_callback(g_update_callback cb, void *data = NULL)
            { 
            m_update_callbacks.owner(this);
            m_update_callbacks.add(cb, data);
            }

		void remove_update_callback(g_update_callback cb, void *data = NULL)
            { m_update_callbacks.remove(cb, data); }

		virtual void call_update_callbacks(void *data = NULL,
                                           bool delay_if_possible = true) const;
		
		// The sys-initialize callbacks are called whenever the system initializes
		// a new atom.
		static void add_sys_initialize_callback(g_sys_initialize_callback cb,
                                                void *data = NULL);
		static void remove_sys_initialize_callback(g_sys_initialize_callback cb,
                                                   void *data = NULL);
		
		// The sys-lose callbacks are called whenever the system loses an atom.
		static void add_sys_lose_callback(g_sys_lose_callback cb, 
                                          void *data = NULL);
		static void remove_sys_lose_callback(g_sys_lose_callback cb,
                                             void *data = NULL);
		
		// The sys-unlose callbacks are called whenever the system unloses an atom.
		static void add_sys_unlose_callback(g_sys_unlose_callback cb,
                                            void *data = NULL);
		static void remove_sys_unlose_callback(g_sys_unlose_callback cb,
                                               void *data = NULL);
		
		//--------------------------------------------------------------------------------
		// ******* COCLASS SUPPORT METHODS *********
		
		// The following unknown methods are provided simply as 'hooks' that
		// you can use in implementing coclasses (or API classes) that
		// are associated with the GAtom.  Thus, you could implement a COM
		// coclass and use these methods to manage a relationship between
		// it and the GAtom.
		virtual void* unknown() const { return 0; }
		virtual g_primitive* construct_primitive(size_t) { return NULL; }

		//--------------------------------------------------------------------------------
		// ******* DEBUG SUPPORT METHODS *********

		// The debug_check_flag() is used by the system for various debug checks.
		bool debug_check_flag() const { return m_flags.m_debug_check_flag; }

		//	 This method is called at various times to verify the contents
		//	 of the atom.
		enum VerifyType
			{
			UndefinedVerifyType = 0,
			VerifyNewbieOnNoteState = 1,
			VerifyOnNoteState = 2,
			NumVerifyTypes
			};
		virtual bool verify(VerifyType) const;

		static void* operator new(size_t sz) { return g_alloc(sz); }
		static void operator delete(void* p) { g_free(p); }

#if defined _DEBUG || defined _PSEUDO_DEBUG
		ptr_base* debug_registered_ptrs() const { return m_registered_ptrs; }
			// Useful in debugging, but breaks encapsulation in a very
			// big way, so use ONLY for debugging purposes!!
#endif

	protected:
		// Call this method whenever you add new pointers to the object.
		// (i.e. aNewPtr = new ptr<>;)  This will enable the newly allocated
		// pointer to be initialized.  (Don't forget to stream the newly
		// allocated pointer in the stream() method.)  Note that the collection
		// classes (ptr_array<>, ptr_set<>, etc.) alleviate the need to call this
		// method since they perform all the initialization work themselves.
		void update();

		// These methods are called whenever the object is taken from a
		// living state to a non-living state (or visa versa).  Note that
		// they may be overloaded.  However, it is important that any streamed
		// data is not altered in these methods since any such change will
		// have detrimental effects during rollback.  If they are overloaded,
		// the parent methods MUST be called.
		virtual void ghost_to_live();
		virtual void live_to_ghost();

		// The forget_ghost() method does the same task as the forget() method,
		// but does so for 'ghost' pointers.  It is called immediately prior
		// to the 'forgotten' object's destruction, however, so the forget_ghost()
		// method MUST be careful not to increment the referenced object's
		// use-count or system-count.  In this way, it is much more constrained
		// on its allowable activities than the forget() method.  (For example,
		// it does not respond to the 'OMEGA_PTR' flag for ghost pointers.)
		// By default, it should simpl set the pointer value to NULL.
	  	virtual void forget_ghost(const g_forget_event& event);

	protected:
		virtual void null_registered_strong_ptrs();	// Called by g_forget().
		virtual void null_registered_weak_ptrs();
		virtual void null_registered_ghost_ptrs();

		bool null_weak_ptrs(bool bLongLivedFlag);

		virtual void call_lose_callbacks() const;

		bool debug_skip_ownership_check() const
			{ return m_flags.m_debug_skip_ownership_check; }
		void debug_skip_ownership_check(bool f)
			{ m_flags.m_debug_skip_ownership_check = f; }

		void register_ptr(ptr_base*);
		void unregister_ptr(ptr_base*);

	private:
		// The pre_in_atom_list() and next_in_atom_list() methods are used to
		// construct a linked list of atoms within the containing molecule.
		GAtom* prev_in_atom_list() const;
		void prev_in_atom_list(GAtom* p);
		GAtom* next_in_atom_list() const;
		void next_in_atom_list(GAtom* n);

		// The prev_in_newbie_cache() and next_in_newbie_cache() pointers should
		// only be set by g_molecule to create a linked-list of newly
		// created atoms.
		GAtom* prev_in_newbie_cache() const;
		void prev_in_newbie_cache(GAtom* p);
		GAtom* next_in_newbie_cache() const;
		void next_in_newbie_cache(GAtom* n);

		g_molecule* m_molecule;

		size_t m_use_count;
		size_t m_system_count;

        size_t m_save_index;

#if defined _DEBUG || defined _PSEUDO_DEBUG
		g_type*		m_type;	// Points to type object - useful in debugging .dll's
#endif
	  
		ptr_base		*m_registered_ptrs;
		g_data_preserve	*m_data_preserve;	// Pointer to data for foreign object.

		GAtom			*m_next_in_list;	// Embedding these pointers into GAtom directly is ugly from
		GAtom			*m_prev_in_list;	// an OO perspective, but it reduces memory overhead significantly.

        g_lose_callback_list   m_lose_callbacks;
        g_update_callback_list m_update_callbacks;

		struct g_flags
			{
			unsigned int m_is_initialized:1;
			unsigned int m_is_marked_for_destruction:1;

			unsigned int m_is_backed_up:1;
			unsigned int m_is_rolling_back:1;
			unsigned int m_is_rolling_to_newbie_state:1;

			unsigned int m_is_backup_image:1;
			unsigned int m_is_in_rollback_system:1;
			unsigned int m_needs_updating:1;

			unsigned int m_spans_note_state_boundary:1;
			
			// The m_is_in_newbie_cache and m_is_in_atom_list flags are
			// mutually exclusive since they both use the m_next_in_list and
			// m_prev_in_list attributes to save memory space.  The intent is
			// that, prior to the 1st note_state() after construction, the
			// atom will be in the rollback system's newbie cache but not
			// in the molecule's list of atoms.  After the 1st note_state(),
			// the atom will be removed from the newbie cache and inserted into
			// the molecule's list.
			unsigned int m_is_in_newbie_cache:1;
			unsigned int m_is_in_atom_list:1;

			unsigned int m_nulling_strong_ptrs:1;
			unsigned int m_nulling_weak_ptrs:1;
			unsigned int m_nulling_ghost_ptrs:1;

			unsigned int m_suppress_rollback:1;

			unsigned int m_debug_check_flag:1;
				// Used to make sure that calling the parent's stream() method is the
				// first action in any derived stream() method. (Initially set to
				// false in GAtom::stream_all(), is set to true in GAtom::stream(),
				// and again set to false before exiting stream_all(). The out_stream
				// checks this flag, so if you can save to file without any debug
				// assertion failures, you're doing ok.)

			unsigned int m_debug_skip_ownership_check:1;
				// If true, tells GeMS++ to skip the check in debug mode that
				// ensures a strong reference exists from its containing molecule.
			};

		union
			{
			mutable g_flags m_flags;
			unsigned long m_iflags;
			};

		static g_sys_initialize_callback_list *m_pSysInitializeCallbacks;
		static g_sys_lose_callback_list       *m_pSysLoseCallbacks;
		static g_sys_unlose_callback_list     *m_pSysUnloseCallbacks;

		DECLARE_GEMS_CLASS(GAtom,GEMS)
		};

#endif
