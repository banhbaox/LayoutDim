
#ifndef _g_relate_h_
#define _g_relate_h_

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

/////////////////////////////////////////////
//
//  G*eMS++
//  R*elationship
//  I*nterface
//  D*efinition
//
#include "dcl_gems.h"

#include <utility>

///////////////////////////////////////////////////////////////////////////
//
// Macros to set up relationships between atoms.
//
// For historical compatibility, the methods defined by the following   
// macros use 'add' and 'remove' rather than 'insert' and 'erase'.
//
#define G_DECLARE_CONTAINER_CALLBACK_METHODS(RELNAME, AddFuncType, RemoveFuncType) \
	void add_##RELNAME##_added_callback(AddFuncType,void* client_data=0); \
	void add_##RELNAME##_removed_callback(RemoveFuncType,void* client_data=0); \
	void add_##RELNAME##_pre_remove_callback(RemoveFuncType,void* client_data=0); \
	void remove_##RELNAME##_added_callback(AddFuncType,void* client_data=0); \
	void remove_##RELNAME##_removed_callback(RemoveFuncType,void* client_data=0); \
	void remove_##RELNAME##_pre_remove_callback(RemoveFuncType,void* client_data=0); \

/////////////////////////////////////////////////////
//
// Declare methods for 'smart_ptr_set' relationship.
//
#define G_DECLARE_SET_METHODS(TOCLASS,RELNAME) \
	virtual size_t RELNAME##_list_size() const; \
	virtual g_behaviors RELNAME##_list_behaviors() const; \
	virtual void add_##RELNAME(TOCLASS*,GInsertionType=INSERT_ANYWHERE,const TOCLASS* other=NULL,std::pair<smart_ptr_set<TOCLASS >::iterator,bool>* result=NULL); \
	virtual size_t remove_##RELNAME(TOCLASS* p); \
	virtual void remove_##RELNAME(smart_ptr_set<TOCLASS >::iterator& i); \
	virtual void remove_##RELNAME##_range(smart_ptr_set<TOCLASS >::iterator& f,smart_ptr_set<TOCLASS >::iterator& s); \
	virtual smart_ptr_set<TOCLASS >::iterator RELNAME##_list_iterator(GIteratorAction=G_BEGIN,const TOCLASS* other=NULL) const; \

#define G_DECLARE_SET_RELATIONSHIP(TOCLASS,RELNAME) \
	G_DECLARE_SET_METHODS(TOCLASS,RELNAME) \
	G_DECLARE_CONTAINER_CALLBACK_METHODS(RELNAME, \
                                         g_element_added_callback, \
                                         g_element_removed_callback)

///////////////////////////////////////////////////////////
//
// Declare methods for 'smart_ptr_multiset' relationship.
//
#define G_DECLARE_MULTISET_METHODS(TOCLASS,RELNAME) \
	virtual size_t RELNAME##_list_size() const; \
	virtual g_behaviors RELNAME##_list_behaviors() const; \
	virtual void add_##RELNAME(TOCLASS*,GInsertionType=INSERT_ANYWHERE,smart_ptr_multiset<TOCLASS >::iterator* result=NULL); \
	virtual void add_##RELNAME(TOCLASS*,GInsertionType,const smart_ptr_multiset<TOCLASS >::iterator& loc,smart_ptr_multiset<TOCLASS >::iterator* result=NULL); \
	virtual size_t remove_##RELNAME(TOCLASS*); \
	virtual void remove_##RELNAME(smart_ptr_multiset<TOCLASS >::iterator&); \
	virtual void remove_##RELNAME##_range(smart_ptr_multiset<TOCLASS >::iterator& f,smart_ptr_multiset<TOCLASS >::iterator& s); \
	virtual smart_ptr_multiset<TOCLASS >::iterator RELNAME##_list_iterator(GIteratorAction=G_BEGIN,const TOCLASS* other=NULL) const; \

#define G_DECLARE_MULTISET_RELATIONSHIP(TOCLASS,RELNAME) \
	G_DECLARE_MULTISET_METHODS(TOCLASS,RELNAME) \
	G_DECLARE_CONTAINER_CALLBACK_METHODS(RELNAME, \
                                         g_element_added_callback, \
                                         g_element_removed_callback)


/////////////////////////////////////////////////////////////
//
// Declare methods for 'sorted_smart_ptr_set' relationship.
//
#define G_DECLARE_SORTED_SET_METHODS(TOCLASS,RELNAME) \
	virtual size_t RELNAME##_list_size() const; \
	virtual g_behaviors RELNAME##_list_behaviors() const; \
	virtual void add_##RELNAME(TOCLASS*,std::pair<sorted_smart_ptr_set<TOCLASS >::iterator,bool>* result=NULL); \
	virtual size_t remove_##RELNAME(TOCLASS* p); \
	virtual void remove_##RELNAME(sorted_smart_ptr_set<TOCLASS >::iterator& i); \
	virtual void remove_##RELNAME##_range(sorted_smart_ptr_set<TOCLASS >::iterator& f,sorted_smart_ptr_set<TOCLASS >::iterator& s); \
	virtual sorted_smart_ptr_set<TOCLASS >::iterator RELNAME##_list_iterator(GIteratorAction=G_BEGIN,const TOCLASS* other=NULL) const; \
	virtual sorted_smart_ptr_set<TOCLASS >::iterator RELNAME##_list_iterator(GIteratorAction,const self_comparator<TOCLASS >* hint) const; \

#define G_DECLARE_SORTED_SET_RELATIONSHIP(TOCLASS,RELNAME) \
	G_DECLARE_SORTED_SET_METHODS(TOCLASS,RELNAME) \
	G_DECLARE_CONTAINER_CALLBACK_METHODS(RELNAME, \
                                         g_element_added_callback, \
                                         g_element_removed_callback)


////////////////////////////////////////////////////////////////
//
// Declare methods for 'sorted_smart_ptr_multiset' relationship.
//
#define G_DECLARE_SORTED_MULTISET_METHODS(TOCLASS,RELNAME) \
	virtual size_t RELNAME##_list_size() const; \
	virtual g_behaviors RELNAME##_list_behaviors() const; \
	virtual void add_##RELNAME(TOCLASS*,sorted_smart_ptr_multiset<TOCLASS>::iterator* i=0); \
	virtual size_t remove_##RELNAME(TOCLASS* p); \
	virtual void remove_##RELNAME(sorted_smart_ptr_multiset<TOCLASS >::iterator& i); \
	virtual void remove_##RELNAME##_range(sorted_smart_ptr_multiset<TOCLASS >::iterator& f,sorted_smart_ptr_multiset<TOCLASS >::iterator& s); \
	virtual sorted_smart_ptr_multiset<TOCLASS >::iterator RELNAME##_list_iterator(GIteratorAction=G_BEGIN,const TOCLASS* other=NULL) const; \
	virtual sorted_smart_ptr_multiset<TOCLASS >::iterator RELNAME##_list_iterator(GIteratorAction,const self_comparator<TOCLASS >* hint) const; \

#define G_DECLARE_SORTED_MULTISET_RELATIONSHIP(TOCLASS,RELNAME) \
	G_DECLARE_SORTED_MULTISET_METHODS(TOCLASS,RELNAME) \
	G_DECLARE_CONTAINER_CALLBACK_METHODS(RELNAME, \
                                         g_element_added_callback, \
                                         g_element_removed_callback)

////////////////////////////////////////////////////////////////
//
// Declare methods for 'smart_ptr_list' relationship.
//
#define G_DECLARE_LIST_METHODS(TOCLASS,RELNAME) \
	virtual size_t RELNAME##_list_size() const; \
	virtual g_behaviors RELNAME##_list_behaviors() const; \
	virtual void add_##RELNAME(TOCLASS*,GInsertionType=INSERT_ANYWHERE,ptrdiff_t index=-1,smart_ptr_list<TOCLASS >::iterator*result = NULL); \
	virtual void add_##RELNAME(const smart_ptr_list<TOCLASS >::iterator& hint,TOCLASS*v,GInsertionType=INSERT_BEFORE,smart_ptr_list<TOCLASS >::iterator*result = NULL); \
	virtual void remove_##RELNAME(smart_ptr_list<TOCLASS >::iterator& i); \
	virtual void remove_##RELNAME##_range(smart_ptr_list<TOCLASS >::iterator& f,smart_ptr_list<TOCLASS >::iterator& s); \
	virtual smart_ptr_list<TOCLASS >::iterator RELNAME##_list_iterator(GIteratorAction=G_BEGIN) const; \

#define G_DECLARE_LIST_RELATIONSHIP(TOCLASS,RELNAME) \
	G_DECLARE_LIST_METHODS(TOCLASS,RELNAME) \
	G_DECLARE_CONTAINER_CALLBACK_METHODS(RELNAME, \
                                         g_list_element_added_callback, \
                                         g_list_element_removed_callback)

#endif


