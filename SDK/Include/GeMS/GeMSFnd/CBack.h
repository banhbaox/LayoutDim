#ifndef _cback_h_
#define _cback_h_

//////////////////////////////////////////////////////////////////////
//
//      *GeMS++ V6.1
//
//      * U.S. Patent #6,421,690
//
//  NOTICE: These data were produced by Honeywell Federal Manufacturing & Technologies, LLC 
//  under Contract No. DE-AC04-01AL66850 with the Department of Energy.  For 5 years 
//  from 4/1/2003, the Government is granted for itself and others acting on its behalf 
//  a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, 
//  prepare derivative works, and perform publicly and display publicly by or on behalf 
//  of the Government.  There is provision for the possible extension of the term of this 
//  license.  Subsequent to that period or any extension granted, the Government is granted 
//  for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide 
//  license in this data to reproduce, prepare derivative works, distribute copies to the
//  public, perform publicly and display publicly, and to permit others to do so.  The specific 
//  term of the license can be identified by inquiry made to the Contractor or DOE.  Neither 
//  the United States nor the United States Department of Energy, nor any of their employees, 
//  makes any warranty, express or implied, or assumes any legal liability or responsibility 
//  for the accuracy, completeness, or usefulness of any data, apparatus, product, or process 
//  disclosed, or represents that its use would not infringe privately owned rights.
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
#include <stdlib.h>

class DECL_GEMS GAtom;
class DECL_GEMS g_callback_list_body;

// The following is a simple callback_list wrapper
class DECL_GEMS g_callback_list_base
    {
private:
    g_callback_list_body *_list;

    // Implementation methods so we can inline methods
    // for fast returns when _list is NULL.
    void do_call_callbacks(void *call_data) const;
    size_t get_num_callbacks_requested() const;
    void destroy_list();

protected:
    g_callback_list_base() : _list(0) {}

    // When copying an object containing callbacks,
    // we do not want to copy any of its callbacks!
    g_callback_list_base(const g_callback_list_base &) : _list(0) {}

    ~g_callback_list_base() { if(_list) destroy_list(); }

    g_callback_list_base &operator=(const g_callback_list_base &)
        { return *this; }

    void add   (void *cb, void *client_data);
    void remove(void *cb, void *client_data);

    void call_callbacks(void *call_data) const
        {
        if(_list)
            do_call_callbacks(call_data);
        }

public:
    void owner(GAtom *);
    
    void clear() { if(_list) destroy_list(); }

    size_t num_callbacks_requested() const
        {
        if(0 == _list)
            return 0;

        return get_num_callbacks_requested();
        }
    };

template<class FuncType, class CallDataType>
class g_callback_list : public g_callback_list_base
    {
public:
    void call_callbacks(CallDataType *call_data = 0) const
        { g_callback_list_base::call_callbacks(call_data); }

    void add(FuncType cb, void *client_data = 0)
        { g_callback_list_base::add((void *)cb, client_data); }

    void remove(FuncType cb, void *client_data = 0)
        { g_callback_list_base::remove((void *)cb, client_data); }
    };

////////////////////////////////////////////////////////////////
//
// Note that, as yet, there is no 'pre_added_callback_list'
// contained within a callback group.  The reason for this is
// because of the difficulties involved in generating the
// call data for such a callback list (knowing exactly where
// the data is to be added before doing so) and the limited utility
// even if it was incorporated (what can you do with a 'pre
// added' callback list that a 'post added' callback list
// cannot handle).
//
class DECL_GEMS g_add_remove_callback_group_body;

class DECL_GEMS g_add_remove_callback_group_base
    {
private:
    mutable g_add_remove_callback_group_body *_group;
    GAtom *_owner;

protected:
    // Implementation methods so we can inline methods
    // for fast returns when _group is NULL.
    void do_call_post_add_callbacks(void* call_data) const;
    void do_call_pre_remove_callbacks(void* call_data) const;
    void do_call_post_remove_callbacks(void* call_data) const;

    size_t get_num_post_add_callbacks_requested() const;
    size_t get_num_pre_remove_callbacks_requested() const;
    size_t get_num_post_remove_callbacks_requested() const;

    void make_group() const;
    void destroy_group() const;
    bool unused() const;

    g_add_remove_callback_group_base() : _group(0), _owner(0) {}

    g_add_remove_callback_group_base(const g_add_remove_callback_group_base &) :
        _group(0), _owner(0) {}

    ~g_add_remove_callback_group_base() { if(_group) destroy_group(); }

    g_add_remove_callback_group_base &operator=(const g_add_remove_callback_group_base &)
        { return *this; }

    void call_post_add_callbacks(void *call_data) const
        { if(_group) do_call_post_add_callbacks(call_data); }

    void call_pre_remove_callbacks(void *call_data) const
        { if(_group) do_call_pre_remove_callbacks(call_data); }

    void call_post_remove_callbacks(void *call_data) const
        { if(_group) do_call_post_remove_callbacks(call_data); }

    void add_post_add_callback      (void *cb, void *client_data);
    void add_pre_remove_callback    (void *cb, void *client_data);
    void add_post_remove_callback   (void *cb, void *client_data);

    void remove_post_add_callback   (void *cb, void *client_data);
    void remove_pre_remove_callback (void *cb, void *client_data);
    void remove_post_remove_callback(void *cb, void *client_data);

public:
    void owner(GAtom *);

    size_t num_post_add_callbacks_requested() const
        {
        if(!_group)
            return 0;
        return get_num_post_add_callbacks_requested();
        }

    size_t num_pre_remove_callbacks_requested() const
        {
        if(!_group)
            return 0;
        return get_num_pre_remove_callbacks_requested();
        }

    size_t num_post_remove_callbacks_requested() const
        {
        if(!_group)
            return 0;
        return get_num_post_remove_callbacks_requested();
        }
    };

template<class AddFuncType, class AddCallDataType, 
         class RemoveFuncType, class RemoveCallDataType> 
class g_add_remove_callback_group : public g_add_remove_callback_group_base
    {
public:
    void call_post_add_callbacks(AddCallDataType *call_data = 0) const
        {
        g_add_remove_callback_group_base::call_post_add_callbacks(call_data);
        }

    void call_pre_remove_callbacks(RemoveCallDataType *call_data = 0) const
        {
        g_add_remove_callback_group_base::call_pre_remove_callbacks(call_data);
        }

    void call_post_remove_callbacks(RemoveCallDataType *call_data = 0) const
        {
        g_add_remove_callback_group_base::call_post_remove_callbacks(call_data);
        }

    void add_post_add_callback(AddFuncType cb, void *client_data = 0)
        {
        g_add_remove_callback_group_base::add_post_add_callback((void *)cb, client_data);
        }

    void add_pre_remove_callback(RemoveFuncType cb, void *client_data = 0)
        {
        g_add_remove_callback_group_base::add_pre_remove_callback((void *)cb, client_data);
        }

    void add_post_remove_callback(RemoveFuncType cb, void *client_data = 0)
        {
        g_add_remove_callback_group_base::add_post_remove_callback((void *)cb, client_data);
        }

    void remove_post_add_callback(AddFuncType cb, void *client_data = 0)
        {
        g_add_remove_callback_group_base::remove_post_add_callback((void *)cb, client_data);
        }

    void remove_pre_remove_callback(RemoveFuncType cb, void *client_data = 0)
        {
        g_add_remove_callback_group_base::remove_pre_remove_callback((void *)cb, client_data);
        }

    void remove_post_remove_callback(RemoveFuncType cb, void *client_data = 0)
        {
        g_add_remove_callback_group_base::remove_post_remove_callback((void *)cb, client_data);
        }
    };

#define DECLARE_CALLBACK_TYPE(FuncType, CallDataType, N)           \
typedef void (*FuncType)(GAtom *pOwner, void *pClientData,         \
                         CallDataType *pCallData);                 \
typedef g_callback_list<FuncType, CallDataType> FuncType##_list;   \
N##_TEMPLATE(class, g_callback_list<FuncType, CallDataType>);

#endif
