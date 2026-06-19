
#ifndef _g_doc_h_
#define _g_doc_h_

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
#include "GeMS/GemsFnd/GExperiment.h"

class DECL_GEMS g_doc : public g_molecule
	{
	public:
		g_doc():g_molecule() {}
		g_doc(const g_doc& right):g_molecule(right) {}	// Performs deep copy of entire document.
		virtual ~g_doc() {}

		g_doc& operator=(const g_doc& right);

		virtual void stream_header(g_stream& str,unsigned long version)
			{ g_molecule::stream_header(str,version); }

		///////////////////////////////////////////////////////////////////
		//
		// Element list methods (supports legacy interface).
		//
		const ptr_set<GAtom>& elements() const
			{ return g_molecule::element_list(); }

		void elements(const smart_ptr_set<GAtom>& els)
			{ g_molecule::element_list(els); }

		void	insert(GAtom* p,GInsertionType itype=INSERT_ANYWHERE,const GAtom* other = NULL)
			{
			g_molecule::add_element(p,itype,other);
			}

		void	erase(GAtom* p) { g_molecule::remove_element(p); }

		void	clear() { g_molecule::clear_element_list(); }
		bool	empty() const { return g_molecule::element_list_empty(); }
		bool	contains(const GAtom* p) const { return g_molecule::element_list_contains(p); }
					// Returns true if 'p' is a top-level entity.

		// In the 'add-callback' methods, the 'owner' pointer sets the owner pointer
		// in the callback lists if it is non-zero.  Otherwise, it is ignored.
		void add_element_added_callback(g_element_added_callback cb,
                                        void *client_data = 0,
                                        GAtom *owner = 0)
			{ g_molecule::add_element_added_callback(cb,client_data,owner); }
		void add_element_removed_callback(g_element_removed_callback cb,
                                          void *client_data = 0,
                                          GAtom *owner = 0)
			{ g_molecule::add_element_removed_callback(cb,client_data,owner); }
		void add_element_pre_remove_callback(g_element_removed_callback cb,
                                             void *client_data = 0,
                                             GAtom *owner = 0)
			{ g_molecule::add_element_pre_remove_callback(cb,client_data,owner); }

		void null_owner() { g_molecule::null_element_list_owner(); }
		
		void remove_element_added_callback(g_element_added_callback cb,
                                           void *client_data = 0)
			{ g_molecule::remove_element_added_callback(cb,client_data); }
		void remove_element_removed_callback(g_element_removed_callback cb,
                                             void *client_data = 0)
			{ g_molecule::remove_element_removed_callback(cb,client_data); }
		void remove_element_pre_remove_callback(g_element_removed_callback cb,
                                                void *client_data = 0)
			{ g_molecule::remove_element_pre_remove_callback(cb,client_data); }

		bool	owns(const GAtom* p) const { return g_molecule::owns(p); }
					// Returns true if the doc directly or indirectly owns 'p'.

		///////////////////////////////////////////////////////////////////////////////
		//
		// Identifier methods.
		//
		ptr<GAtom> lookup(g_id id) const
			{ return g_molecule::lookup(id); }
	};

#endif
