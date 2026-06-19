
#ifndef _g_experiment_h_
#define _g_experiment_h_

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

#include "GeMS/GemsFnd/GMolecule.h"

class DECL_GEMS g_experiment
	{
	friend class DECL_GEMS g_molecule;

	private:
		g_molecule*			_molecule;			// The document on which the experiment is being performed.
		g_time_line*		_time_line;
		g_object_manager*	_prev_time_line;	// The previously active time-line, if any.
		g_experiment*		_next;				// To allow stacks of experiments.
		bool				_running;

		g_experiment(const g_experiment&) {}
		g_experiment& operator=(const g_experiment&) { return *this; }

	protected:
		virtual void on_destruction(GAtom*);
		virtual void on_insertion(GAtom*);
		virtual void on_backup(GAtom*);

	public:
		g_experiment(g_molecule* m,g_time_line* tline=NULL,bool bForceDistinctState=false);
			// Constructs a new experiment with a new time line.  The time-
			// line is made the 'active' time-line, so any data-model changes
			// will be recorded in the experiment.  If a time-line is provided,
			// the experiment will use it.  Otherwise, a default GeMS
			// g_time_line will be created.

		virtual ~g_experiment();
			// Destructs the experiment and makes the previously active
			// time-line active.  If the experiment is active,
			// any un-accepted changed to the data-model will automatically
			// be undone.  This behavior allows a g_experiment local
			// variable to be declared which will restore the data-model to
			// its original state if a throw out of the experiment occurs.

		// It is possible to perform note-states and undo/redo's
		// during an experiment, though they are rarely performed.
		virtual size_t note_state(bool bForceDistinctState=false);
		virtual void   note_state_without_stop_point(bool bForceDistinctState=false);

		size_t current_undo_state_id() const;

		bool	can_undo(unsigned int nStates=1) const;
		bool	can_redo(unsigned int nStates=1) const;

		virtual unsigned int undo(unsigned int nStates = 1,
                                  size_t *uNewCurrentUndoUnitId = NULL);
		virtual unsigned int redo(unsigned int nStates = 1,
                                  size_t *uNewCurrentUndoUnitId = NULL);

		virtual unsigned int undo_to(size_t uUndoUnitId,
                                     size_t *uNewCurrentUndoUnitId = NULL);
		virtual unsigned int redo_to(size_t uUndoUnitId,
                                     size_t *uNewCurrentUndoUnitId = NULL);

		virtual bool is_rolling_back() const;

		void	accept(bool bForceDistinctState=false);
			// Accepts the experiment's data-model changes, merging the
			// time-steps into the time-line which was active before
			// the experiment commenced.  The updated time-line will then
			// be made active.  (If there was no previously active time-line,
			// the changes will simply be commited.)

		void	reject(bool bForceDistinctState=false);
			// Rejects the experiment's data-model changes, undoing back to
			// its earliest time-step.  The time-line which was active before
			// the experiment commenced will once again be made active.

		void	resume();
			// Makes its own time-line the currently active one to
			// once again note any data-model changes.  Note that a 'resume'
			// can only be done when the experiment's own time-line contains
			// nothing.  Thus, it is only legal after initial construction of
			// the time-line (although it is unnecessary at this point) or
			// after an 'accept' or 'reject' has occurred.
	};

#endif
