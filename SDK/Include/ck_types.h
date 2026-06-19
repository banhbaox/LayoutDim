// Copyright Kubotek Corporation, 1999-2014
// All Rights Reserved
// Confidential and Proprietary - Do Not Disclose
#ifndef CK_TYPES_INC
#define CK_TYPES_INC

#if !defined(SDK_MAIN) && !defined(CADKEY_MAIN)
#  if !defined(KCP_DLL)
#    define KCP_DLL
#    ifndef NT
#      define NT
#    endif // NT
#    ifndef ASSERT
#      define G_ASSERT(x)
#      define ASSERT(x)
#    else
#      define G_ASSERT ASSERT
#    endif
#    include "GeMS/GeMSFnd/ptr.h"
#    include "GeMS/Containers/Array.h"
#    include "GeMS/Containers/PtrArray.h"
#    include "GeMS/dcl_gems.h"
#  endif
#  ifndef _WIN64
#    ifndef CADKEY_VIEWER
#      ifdef _DEBUG
#        pragma comment(lib, "SDKd.lib")
#      else
#        pragma comment(lib, "SDK.lib")
#      endif
#    else
#      ifdef _DEBUG
#        pragma comment(lib, "SDKVWd.lib")
#      else
#        pragma comment(lib, "SDKVW.lib")
#      endif
#    endif
#  else
#    ifndef CADKEY_VIEWER
#      ifdef _DEBUG
#        pragma comment(lib, "SDK64d.lib")
#      else
#        pragma comment(lib, "SDK64.lib")
#      endif
#    else
#      ifdef _DEBUG
#        pragma comment(lib, "SDKVW64d.lib")
#      else
#        pragma comment(lib, "SDKVW64.lib")
#      endif
#    endif
#  endif
#endif

#include "ck_ptr.h"
#include "ck_export.h"

#define DECLARE_PTR_TO(type, name, base)                                      \
class type;                                                                   \
template<class T> class base##_set;                                           \
class name : public base<type>                                                \
    {                                                                         \
    friend class CKPartDoc;                                                   \
public:                                                                       \
    SDK_EXPORT name();                                                        \
    SDK_EXPORT name(const name &right);                                       \
    SDK_EXPORT name &operator=(const name &right);                            \
    SDK_EXPORT bool operator==(const name &right) const;                      \
    SDK_EXPORT bool operator!=(const name &right) const;                      \
    SDK_EXPORT bool IsValid() const;                                          \
    SDK_EXPORT ~name();                                                       \
    name(type *p);                                                            \
    name(const base<type> &right);                                            \
    SDK_EXPORT name &operator=(type *right);                                  \
    name &operator=(const base<type> &right);                                 \
    bool operator==(const type *right) const;                                 \
    bool operator!=(const type *right) const;                                 \
    };                                                                        \
typedef std::vector<name> name##Array;                                        \
template<class T> base##_set<T> &operator<<=(base##_set<T> &left,             \
                                             const name##Array &right)        \
	{                                                                         \
    name##Array::const_iterator iter = right.begin(), iterEnd = right.end();  \
    for( ; iter != iterEnd; ++iter)                                           \
        if(T *p = T::downcast(*iter)) left.insert(p);                         \
	return(left);                                                             \
	}                                                                         \
template<class T> name##Array &operator<<=(name##Array &left,                 \
                                           const base##_set<T> &right)        \
	{                                                                         \
    base##_set<T>::iterator iter = right.begin();                             \
    for( ; iter.valid(); ++iter)                                              \
        if(T *p = T::downcast(*iter)) left.push_back(p);                      \
	return(left)                                                              \
	}                                                                         \
template<> SDK_EXPORT base##_set<type> &operator<<=(base##_set<type> &left,   \
                                                    const name##Array &right);\
template<> SDK_EXPORT name##Array &operator<<=(name##Array &left,             \
                                               const base##_set<type> &right);

DECLARE_PTR_TO(CKEntity,   CKSEntity,   ck_ptr)
DECLARE_PTR_TO(CKLevel,    CKSLevel,    smart_ptr)
DECLARE_PTR_TO(CKLayout,   CKSLayout,   smart_ptr)
DECLARE_PTR_TO(CKDrawInst, CKSDrawInst, smart_ptr)
DECLARE_PTR_TO(CKCopious,  CKSCopious,  smart_ptr)
DECLARE_PTR_TO(CKHatchPattern, CKSHatchPattern, smart_ptr)

template<class T> smart_ptr_set<T> &operator<<=(smart_ptr_set<T> &left,
                                                const CKSEntityArray &right)
	{
    CKSEntityArray::const_iterator iter = right.begin(), iterEnd = right.end();
    for( ; iter != iterEnd; ++iter)
        if(T *p = T::downcast(*iter)) left.insert(p);
    return(left);
	}
template<class T> CKSEntityArray &operator<<=(CKSEntityArray &left,
                                              const smart_ptr_set<T> &right)
	{
    smart_ptr_set<T>::iterator iter = right.begin();
    for( ; iter.valid(); ++iter)
        if(T *p = T::downcast(*iter)) left.push_back(p);
	return(left);
	}
template<> SDK_EXPORT
smart_ptr_set<CKEntity> &operator<<=(smart_ptr_set<CKEntity> &left,
                                     const CKSEntityArray &right);
template<> SDK_EXPORT
CKSEntityArray &operator<<=(CKSEntityArray &left,
                            const smart_ptr_set<CKEntity> &right);

class CKSelectionSet;
SDK_FUNC CKSelectionSet &operator<<=(CKSelectionSet &left,
                                     const CKSEntityArray &right);
SDK_FUNC CKSEntityArray &operator<<=(CKSEntityArray &left,
                                     const CKSelectionSet &right);

#endif
