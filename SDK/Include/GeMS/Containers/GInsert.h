
#ifndef _g_insert_h_
#define _g_insert_h_

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
#include "GInsertEnums.h"
#include <stdlib.h>

class DECL_GEMS GAtom;

//////////////////////////////////////////////////////////////
// In the following call_data structures, the location_id's
// are given to provide the capability to identify a
// specific affected entry in collections which allow
// duplicate entries.
//
// In such collections, the location_id's are guaranteed to
// be unique within the collection as long as the element
// remains within the collection.  The id is not preserved
// between runtime sessions.  Other than being unique, the given
// integer value has no significance.  It is NOT, for example,
// the index of the location in the collection.
//
// It matches the value returned by the location_id() methods
// of some iterators.  It can be used, for example, to
// distinguish between two different occurances of a given
// pointer value within a ptr_list<>.
//
// Note that ptr_set<>s, ptr_tree<>s, and other collections
// which do not allow duplicate entries do not provide unique
// location_id values.  In general, however, the pointer value
// combined with the location_id is always guaranteed to be
// unique.

template <class CONTAINER> struct g_insertion_call_data
	{
    typedef typename CONTAINER::value_type       value_type;
    typedef typename CONTAINER::const_value_type const_value_type;

	GInsertionType	    insertion_type;
	value_type	        inserted_node;		// Points to inserted object.
	size_t 			    index;				// Valid for insertion_type of INSERT_AT_INDEX.
	size_t 			    location_id;		// Location id of the inserted node.
	const_value_type	other_node;			// Valid for insertion_types of INSERT_AFTER
											// and INSERT_BEFORE.
	size_t 				other_location_id;	// Provides the location_id of the 'other_node'
											// in INSERT_BEFORE and INSERT_AFTER operations.

	g_insertion_call_data():
		insertion_type(INSERT_ANYWHERE),
		inserted_node(CONTAINER::null_value_type()),
		index(0),
		location_id(0),
		other_node(CONTAINER::null_value_type()),
		other_location_id(0)
		{
		}

	g_insertion_call_data(const value_type& inserted, GInsertionType itype) :
		insertion_type(itype),
		inserted_node(inserted),
		index(0),
		location_id(0),
		other_node(CONTAINER::null_value_type()),
		other_location_id(0)
		{
		}

	g_insertion_call_data(const value_type &inserted,
						  GInsertionType itype,
					      const const_value_type &other,
						  size_t i = 0):
		insertion_type(itype),
		inserted_node(inserted),
		index(i),
		location_id(0),
		other_node(other),
		other_location_id(0)
		{
		}

	g_insertion_call_data(const value_type &inserted,
						  size_t inserted_loc_id,
						  GInsertionType itype,
						  const const_value_type &other,
						  size_t other_loc_id):
		insertion_type(itype),
		inserted_node(inserted),
		index(0),
		location_id(inserted_loc_id),
		other_node(other),
		other_location_id(other_loc_id)
		{
		}
	};

template <class CONTAINER> struct g_erasure_call_data
	{
    typedef typename CONTAINER::value_type       value_type;
    typedef typename CONTAINER::const_value_type const_value_type;

	GRemovalType		removal_type;
	value_type	        removed_node;
	size_t 				index;				// Valid for removal_type of REMOVE_FROM_INDEX.
	size_t 				location_id;		// Location id of the removed node, if any.
	const_value_type	other_node;			// Valid for types of REMOVE_FROM_BEFORE or REMOVE_FROM_AFTER.
	size_t 				other_location_id;	// Provides the location_id of the 'other_node'
											// in REMOVE_FROM_BEFORE and REMOVE_FROM_AFTER operations.
	g_erasure_call_data():
		removal_type(REMOVE_FROM_ANYWHERE),
		removed_node(CONTAINER::null_value_type()),
		index(0),
		location_id(0),
		other_node(CONTAINER::null_value_type()),
		other_location_id(0)
		{
		}

	g_erasure_call_data(const value_type &removed, GRemovalType rtype):
		removal_type(rtype),
		removed_node(removed),
		index(0),
		location_id(0),
		other_node(CONTAINER::null_value_type()),
		other_location_id(0)
		{
		}

	g_erasure_call_data(const value_type &removed,
						GRemovalType rtype,
						const const_value_type &other,
						size_t i = 0):
		removal_type(rtype),
		removed_node(removed),
		index(i),
		location_id(0),
		other_node(other),
		other_location_id(0)
		{
		}

	g_erasure_call_data(const value_type &removed,
						size_t loc_id, GRemovalType rtype):
		removal_type(rtype),
		removed_node(removed),
		index(0),
		location_id(loc_id),
		other_node(CONTAINER::null_value_type()),
		other_location_id(0)
		{
		}

	g_erasure_call_data(const value_type &removed,
						size_t removed_loc_id, GRemovalType rtype,
						const const_value_type &other,
						size_t other_loc_id):
		removal_type(rtype),
		removed_node(removed),
		index(0),
		location_id(removed_loc_id),
		other_node(other),
		other_location_id(other_loc_id)
		{
		}
	};

template <class I,class E> void g_reverse_insertion_call_data(const I& in,E& out)
	{
	out.removed_node = in.inserted_node;
	out.index = in.index;
	out.location_id = in.location_id;
	out.other_node = in.other_node;
	out.other_location_id = in.other_location_id;

	switch(in.insertion_type)
		{
		case INSERT_ANYWHERE:
			out.removal_type = REMOVE_FROM_ANYWHERE;
			break;
		case INSERT_LAST:
			out.removal_type = REMOVE_FROM_LAST;
			break;
		case INSERT_FIRST:
			out.removal_type = REMOVE_FROM_FIRST;
			break;
		case INSERT_AFTER:
			out.removal_type = REMOVE_FROM_AFTER;
			break;
		case INSERT_BEFORE:
			out.removal_type = REMOVE_FROM_BEFORE;
			break;
		case INSERT_AT_INDEX:
			out.removal_type = REMOVE_FROM_INDEX;
			break;
		case INSERT_AT_LOCATION:
			out.removal_type = REMOVE_FROM_LOCATION;
			break;
		}
	}

template <class I,class E> void g_reverse_erasure_call_data(const E& in,I& out)
	{
	out.inserted_node = in.removed_node;
	out.index = in.index;
	out.location_id = in.location_id;
	out.other_node = in.other_node;
	out.other_location_id = in.other_location_id;

	switch(in.removal_type)
		{
		case REMOVE_FROM_ANYWHERE:
			out.insertion_type = INSERT_ANYWHERE;
			break;
		case REMOVE_FROM_LAST:
			out.insertion_type = INSERT_LAST;
			break;
		case REMOVE_FROM_FIRST:
			out.insertion_type = INSERT_FIRST;
			break;
		case REMOVE_FROM_BEFORE:
			out.insertion_type = INSERT_BEFORE;
			break;
		case REMOVE_FROM_AFTER:
			out.insertion_type = INSERT_AFTER;
			break;
		case REMOVE_FROM_INDEX:
			out.insertion_type = INSERT_AT_INDEX;
			break;
		case REMOVE_FROM_LOCATION:
			out.insertion_type = INSERT_AT_LOCATION;
			break;
		}
	}

#endif
