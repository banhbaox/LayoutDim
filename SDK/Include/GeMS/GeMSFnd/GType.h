
//////////////////////////////////////////////////////////////////////
//
//      *GeMS++ V6.1
//
//      * U.S. Patent #6,421,690
//
//      © Honeywell Federal Manufacturing & Technologies, LLC, 2002
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

#ifndef tqType_h
#define tqType_h 1

#pragma warning(push, 3)
#include <string>
#pragma warning(pop)
#pragma warning(disable: 4275)  // non – DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
#pragma warning(disable: 4710)  // 'function' : function not inlined

#include "GeMS/Dcl_gems.h"
#include "GeMS/Utility/GBasicString.h"

class DECL_GEMS g_type;
class DECL_GEMS GAtom;

//////////////////////////////////////////////////////////////////////
// The parameters to the macros in this header file 
// have the following meanings:
//      S:  Tag Space Name (i.e. GMS,KCP,etc. - Each vendor using
//                          GeMS should come up with its own _short_
//                          & unique tag space name to prevent name
//                          clashes with other vendors).
//      T:  Class Name (Type) (i.e. GObject)
//      P:  Class Parent Name (i.e. GAtom)
//      N:  Tag token to be used to identify class in output files.
//            (This may be different from the class name in order
//             to reduce file size.  It must be at least 2 characters,
//             start with an alpha and consist of alphanumeric and
//             underscores.  It must be unique within each tag space)
//      V:  Current Version# of the class. (Must be greater than 0).
//      M:  Dll Module Name (finer granularity than Tag Space Name).

//////////////////////////////////////////////////////////////////
// The DECLARE_..._GEMS_CLASS and DEFINE_..._GEMS_CLASS macros
// declare and instantiate several GeMS methods and capabilities
// which every GeMS class must support.  The macros assume
// that another macro named DECL_'ModuleName' exists which has
// been defined as __declspec(dllexport) or __declspec(dllimport).
// (Or as nothing if static libraries are being built.)
// 'ModuleName', of course, should be replaced with the name of
// the module in which the exported class resides.
//
// The DECLARE macros should be placed within the class declaration
// in the header file.  The DEFINE macros must appear somewhere in
// the class's .cpp file.

// Note that, when using fine-grain multithreading, only
// smart pointers to GAtoms are allowable.  Consequently,
// the downcast() operators are more restricted.

#define G_DECLARE_DOWNCAST(T)                               \
        inline static T *downcast(GAtom *p)                 \
            { return(((p != NULL) && (p->type()->is_a(T::Class()))) ? (T *)p :NULL); }          \
        inline static const T *downcast(const GAtom *p)     \
            { return(((p != NULL) && (p->type()->is_a(T::Class()))) ? (const T*)p : NULL); }    \

#define G_DEFINE_DOWNCAST(T)

#define DECLARE_GEMS_CLASS(T,M)                     \
    public:                                         \
        class DECL_##M GType : public g_type        \
            {                                       \
            public:                                 \
                GType();                            \
                ~GType();                           \
                GAtom *construct() const;           \
                void force_link() const;            \
                g_type_data* type_data() const;     \
            };                                      \
        inline static g_type_data* type_data();     \
        static GType Type;                          \
        static g_type& Class() { return Type; }     \
        virtual g_type* type() const;               \
        virtual T * copy() const;                   \
        G_DECLARE_DOWNCAST(T)

#define DEFINE_GEMS_CLASS(T,P,N,V,S)                    \
    g_type_data* T::type_data()                         \
        {                                               \
        static g_type_data tdata;                       \
        return &tdata;                                  \
        }                                               \
    T::GType T::Type;                                   \
    T::GType::GType():g_type(#S,#T,#N,&P::Class(),V)    \
        {                                               \
        ASSERT(&Class() != &P::Class());                \
        T::type_data()->add(this);                      \
        }                                               \
    T::GType::~GType()                                  \
        { T::type_data()->remove(this); }               \
    GAtom *T::GType::construct() const                  \
        { return new T;  }                              \
    void T::GType::force_link() const {}                \
    g_type_data* T::GType::type_data() const            \
        { return T::type_data(); }                      \
    g_type* T::type() const { return &T::Type; }        \
    T *T::copy() const { return new T(*this); }         \
    G_DEFINE_DOWNCAST(T)

/////////////////////////////////////////////////////////
// The DECLARE and DEFINE_ABSTRACT_GEMS_CLASS() macros
// should be used when implementing a GAtom-derived class
// which is abstract.  That is, a concrete instance
// cannot be created without sub-classing.
//
#define DECLARE_ABSTRACT_GEMS_CLASS(T,M)            \
    public:                                         \
        class DECL_##M GType : public g_type        \
            {                                       \
            public:                                 \
                GType();                            \
                ~GType();                           \
                bool is_abstract() const;           \
                void force_link() const;            \
                g_type_data* type_data() const;     \
            };                                      \
        inline static g_type_data* type_data();     \
        static GType Type;                          \
        static g_type& Class() { return Type; }     \
        virtual g_type* type() const;               \
        virtual T *copy() const =0;                 \
        G_DECLARE_DOWNCAST(T)

#define DEFINE_ABSTRACT_GEMS_CLASS(T,P,N,V,S)           \
    g_type_data* T::type_data()                         \
        {                                               \
        static g_type_data tdata;                       \
        return &tdata;                                  \
        }                                               \
    T::GType T::Type;                                   \
    T::GType::GType():g_type(#S,#T,#N,&P::Class(),V)    \
        { T::type_data()->add(this); }                  \
    T::GType::~GType()                                  \
        { T::type_data()->remove(this); }               \
    bool T::GType::is_abstract() const { return true; } \
    void T::GType::force_link() const {}                \
    g_type_data* T::GType::type_data() const            \
        { return T::type_data(); }                      \
    g_type* T::type() const { return &T::Type; }        \
    G_DEFINE_DOWNCAST(T)


/////////////////////////////////////////////////////////
// The DECLARE and DECLARE_GEMS_TEMPLATE_CLASS() macros
// should be used when implementing a GAtom-derived class
// which is a template.  One DEFINE_GEMS_TEMPLATE_CLASS()
// macro must be included in some .cpp file for _each_
// template instantiation.  This is so the file I/O will
// have a recognizable tag name for all of the possible
// template parameter combinations.  For an example of
// how these macros are used, look in the Lapis example
// under Examples\Lapis and search for GValueArray.
//
#define DECLARE_GEMS_TEMPLATE_CLASS(T)                          \
    public:                                                     \
        friend const char* g_template_tag_space_name(T*);       \
        friend const char* g_template_tag_name(T*);             \
        friend const char* g_template_name(T*);                 \
        friend g_type* g_template_parent(T*);                   \
        friend unsigned short g_template_version(T*);           \
        class GType : public g_type                             \
            {                                                   \
            public:                                             \
                typedef T _outer_class;                         \
                GType():g_type(                                 \
                        g_template_tag_space_name((T*)NULL),    \
                        g_template_tag_name((T*)NULL),          \
                        g_template_name((T*)NULL),              \
                        g_template_parent((T*)NULL),            \
                        g_template_version((T*)NULL))           \
                    { _outer_class::type_data()->add(this); }   \
                ~GType()                                        \
                    { _outer_class::type_data()->remove(this); } \
                GAtom *construct() const                        \
                    { return new T;  }                          \
                void force_link() const {}                      \
                g_type_data* type_data() const                  \
                    { return _outer_class::type_data(); }       \
            };                                                  \
        inline static g_type_data* type_data()                  \
            {                                                   \
            static g_type_data tdata;                           \
            return &tdata;                                      \
            }                                                   \
        static g_type& Type() { return Class(); }               \
        static g_type& Class();                                 \
        virtual g_type* type() const { return &(Type()); }      \
        virtual T *copy() const { return new T(*this); }        \
        G_DECLARE_DOWNCAST(T)


#define DEFINE_GEMS_TEMPLATE_CLASS(T,P,N,V,S)       \
    const char* g_template_tag_space_name(T*)       \
        { return #S; }                              \
    const char* g_template_tag_name(T*)             \
        { return #T; }                              \
    const char* g_template_name(T*)                 \
        { return #N; }                              \
    g_type* g_template_parent(T*)                   \
        { return &P::Class(); }                     \
    unsigned short g_template_version(T*)           \
        { return V; }                               \
    T::GType S##_##N##_Type;                        \
    g_type& T::Class() { return S##_##N##_Type; }   \
    G_DEFINE_DOWNCAST(T)

/////////////////////////////////////////////////////////
// The DECLARE and DEFINE_PRIVATE_GEMS_CLASS() macros
// should be used when implementing a GAtom-derived class
// which is to be used an an implementation detail of some
// greater context (i.e. a ListNode within a LinkedList
// class).  Such classes CANNOT be saved directly to file
// and are not considered part of a GeMS file format.
//
#define DECLARE_PRIVATE_GEMS_CLASS(T,M)             \
    public:                                         \
        class DECL_##M GType : public g_type        \
            {                                       \
            public:                                 \
                GType();                            \
                ~GType();                           \
                bool is_private() const;            \
                GAtom *construct() const;           \
                void force_link() const;            \
                g_type_data* type_data() const;     \
            };                                      \
        inline static g_type_data* type_data();     \
        static GType Type;                          \
        static g_type& Class() { return Type; }     \
        virtual g_type* type() const;               \
        virtual T *copy() const;                    \
        G_DECLARE_DOWNCAST(T)

#define DEFINE_PRIVATE_GEMS_CLASS(T,P,N,V,S)            \
    g_type_data* T::type_data()                         \
        {                                               \
        static g_type_data tdata;                       \
        return &tdata;                                  \
        }                                               \
    T::GType T::Type;                                   \
    T::GType::GType():g_type(#S,#T,#N,&P::Class(),V)    \
        { T::type_data()->add(this); }                  \
    T::GType::~GType()                                  \
        { T::type_data()->remove(this); }               \
    bool T::GType::is_private() const { return true; }  \
    GAtom *T::GType::construct() const                  \
        { return new T;  }                              \
    void T::GType::force_link() const {}                \
    inline g_type_data* T::GType::type_data() const     \
        { return T::type_data(); }                      \
    g_type* T::type() const { return &T::Type; }        \
    T *T::copy() const { return new T(*this); }         \
    G_DEFINE_DOWNCAST(T)

//  The DEFINE_OLD_GEMS_CLASS() macro should be used to identify
//  old tag-space/tag combinations for classes that still exist.
//  For this macro, V must be the highest version # for which the
//  tag-space/tag combination was valid.  P is the parent class
//  that was used at the time.  If the parent class no longer
//  exists, it must still be (somehow) identified in order to support
//  the writing of old file formats.  In these cases, use the
//  DECLARE_OUTDATED_GEMS_CLASS() and DEFINE_OUTDATED_GEMS_CLASS()
//  macros to provide a P::Type class that the macro can use.
#define DEFINE_OLD_GEMS_CLASS_NAME(T,P,N,V,M,S)     \
    class DECL_##M T##S##N : public g_type          \
        {                                           \
        public:                                     \
            T##S##N();                              \
            ~T##S##N();                             \
            GAtom *construct() const;               \
            g_type_data* type_data() const;         \
        };                                          \
    static T##S##N old##T##S##N;                    \
    T##S##N::T##S##N():g_type(#S,#T,#N,&P::Class(),V,&T::Type)  \
        { T::type_data()->add(this); }              \
    T##S##N::~T##S##N()                             \
        { T::type_data()->remove(this); }           \
    GAtom *T##S##N::construct() const               \
        { return new T; }                           \
    g_type_data* T##S##N::type_data() const         \
        { return T::type_data(); }                  \

//  The DECLARE_OUTDATED_GEMS_CLASS() and DEFINE_OUTDATED_GEMS_CLASS()
//  macros identify a class that used to be supported by GeMS but which
//  no longer exists in the data model.  The macros simply create
//  low-overhead dummy classes that provide a g_type class with all the
//  necessary information to support saving to old file formats.
//  The use of these macros is really only needed in cases where a still-
//  existant class was re-parented to a different class and its old
//  parent disappeared.  Even then, their use is still only necessary
//  when the old outdated parent class was used in an old application
//  but where the still-existant sub-class was not.  When in doubt, go
//  ahead and use the macros since they don't involve much overhead.
#define DECLARE_OUTDATED_GEMS_CLASS(T,M)        \
    class T                                     \
        {                                       \
        public:                                 \
        class DECL_##M GType : public g_type    \
            {                                   \
            public:                             \
                GType();                        \
                ~GType();                       \
                bool is_abstract() const;       \
                void force_link() const;        \
                g_type_data* type_data() const; \
            };                                  \
        inline static g_type_data* type_data(); \
        static GType Type;                      \
        static g_type& Class() { return Type; } \
        };                                      \

#define DEFINE_OUTDATED_GEMS_CLASS(T,P,N,V,S)       \
    g_type_data* T::type_data()                     \
        {                                           \
        static g_type_data tdata;                   \
        return &tdata;                              \
        }                                           \
    T::GType T::Type;                               \
    T::GType::GType():g_type(#S,#T,#N,&P::Class(),V)    \
        { T::type_data()->add(this); }              \
    T::GType::~GType()                              \
        { T::type_data()->remove(this); }           \
    bool T::GType::is_abstract() const { return true; } \
    void T::GType::force_link() const {}            \
    g_type_data* T::GType::type_data() const        \
        { return T::type_data(); }                  \

//////////////////////////////////////////////////////////////////
// The DECLARE_..._GEMS_DLL_EXPORTS macros instantiate
// several GeMS templates to ensure that their definitions
// are exported properly from dll's.  The macros assume
// that another macro named DECL_'ModuleName' exists which has
// beed defined as __declspec(dllexport) or __declspec(dllimport).
// (Or as nothing if static libraries are being built.)
// 'ModuleName', of course, should be replaced with the name of
// the module in which the exported class resides.

// The DECLARE_MINIMAL_GEMS_DLL_EXPORTS macro is intended for
// use on 'leaf' classes.  That is, classes that are concrete,
// being at the outermost extent of the class hierarchy where
// it is believed that applications will rarely need to make
// sets and lists of them.  Only the ptr<> and weak_ptr<>
// template exports are, therefore, necessary.
#define DECLARE_MINIMAL_GEMS_DLL_EXPORTS(T,M)   \
    class DECL_##M T;                                       \
    M##_TEMPLATE(class, smart_ptr<T>);      \
    M##_TEMPLATE(class, ptr<T>);            \
    M##_TEMPLATE(class, weak_ptr<T>);       \
    M##_TEMPLATE(class, omega_ptr<T>);      \
    M##_TEMPLATE(class, omega_weak_ptr<T>); \

// The DECLARE_MINIMAL_STRONG_GEMS_DLL_EXPORTS macro is intended for
// use on most leaf or abstract classes.  The macro should be used on
// any class which will likely need STRONG ptr and ptr_set 
// to be made of them and, consequently, incorporated generically
// into data models.  
//
// The main reason for this macro is to reduce file size in the 
// cpp files that include header files which use the DECLARE EXPORTS
// macros.  Excessive use of the DECLARE STANDARD and FULL Macros
// can cause 3 to 6 times larger object files and most of the
// time the GEMS objects are passed around with ptr or ptr_set
// declarations.  If the GEMS object really needs the STANDARD
// or FULL these can be placed in the particular cpp file that
// will use these instead of the Header file for the class.
#define DECLARE_MINIMAL_STRONG_GEMS_DLL_EXPORTS(T,M)        \
    class DECL_##M T;                                       \
    M##_TEMPLATE(class, smart_ptr<T>);      \
    M##_TEMPLATE(class, ptr<T>);            \
    M##_TEMPLATE(class, smart_ptr_set<T>);  \
    M##_TEMPLATE(class, ptr_set<T>);        \

#define DECLARE_MINIMAL_WEAK_GEMS_DLL_EXPORTS(T,M)  \
    class DECL_##M T;                                       \
    M##_TEMPLATE(class, smart_ptr<T>);      \
    M##_TEMPLATE(class, weak_ptr<T>);       \
    M##_TEMPLATE(class, smart_ptr_set<T>);  \
    M##_TEMPLATE(class, weak_ptr_set<T>);   \

#define DECLARE_MINIMAL_OMEGA_GEMS_DLL_EXPORTS(T,M) \
    class DECL_##M T;                                       \
    M##_TEMPLATE(class, smart_ptr<T>);      \
    M##_TEMPLATE(class, omega_ptr<T>);      \
    M##_TEMPLATE(class, smart_ptr_set<T>);  \
    M##_TEMPLATE(class, omega_ptr_set<T>);  \

#define DECLARE_MINIMAL_OMEGA_WEAK_GEMS_DLL_EXPORTS(T,M)    \
    class DECL_##M T;                                       \
    M##_TEMPLATE(class, smart_ptr<T>);      \
    M##_TEMPLATE(class, omega_weak_ptr<T>); \
    M##_TEMPLATE(class, smart_ptr_set<T>);  \
    M##_TEMPLATE(class, omega_weak_ptr_set<T>); \

#define DECLARE_MINIMAL_STRONG_LIST_GEMS_DLL_EXPORTS(T,M)   \
    class DECL_##M T;                                       \
    M##_TEMPLATE(class, smart_ptr<T>);      \
    M##_TEMPLATE(class, ptr<T>);            \
    M##_TEMPLATE(class, smart_ptr_list<T>); \
    M##_TEMPLATE(class, ptr_list<T>);       \

#define DECLARE_MINIMAL_WEAK_LIST_GEMS_DLL_EXPORTS(T,M) \
    class DECL_##M T;                                       \
    M##_TEMPLATE(class, smart_ptr<T>);      \
    M##_TEMPLATE(class, weak_ptr<T>);       \
    M##_TEMPLATE(class, smart_ptr_list<T>); \
    M##_TEMPLATE(class, weak_ptr_list<T>);  \

#define DECLARE_MINIMAL_OMEGA_LIST_GEMS_DLL_EXPORTS(T,M)    \
    class DECL_##M T;                                       \
    M##_TEMPLATE(class, smart_ptr<T>);      \
    M##_TEMPLATE(class, omega_ptr<T>);      \
    M##_TEMPLATE(class, smart_ptr_list<T>); \
    M##_TEMPLATE(class, omega_ptr_list<T>); \

#define DECLARE_MINIMAL_OMEGA_WEAK_LIST_GEMS_DLL_EXPORTS(T,M)   \
    class DECL_##M T;                                       \
    M##_TEMPLATE(class, smart_ptr<T>);      \
    M##_TEMPLATE(class, omega_weak_ptr<T>); \
    M##_TEMPLATE(class, smart_ptr_list<T>); \
    M##_TEMPLATE(class, omega_weak_ptr_list<T>); \

#define DECLARE_COMPARATOR_GEMS_DLL_EXPORTS(T,M)    \
    class DECL_##M T;                                       \
    M##_TEMPLATE(class, comparator<T>);     \
    M##_TEMPLATE(class, comparator_list<T>);

#define DECLARE_DISCRIM_GEMS_DLL_EXPORTS(T,M)   \
    class DECL_##M T;                                           \
    M##_TEMPLATE(class, discrim<T>);            \
    M##_TEMPLATE(class, discriminator_list<T>); \
    M##_TEMPLATE(class, discriminator_func<T>); \
    M##_TEMPLATE(class, type_discriminator<T>); \
    M##_TEMPLATE(class, not_discriminator<T>);

// The DECLARE_STANDARD_GEMS_DLL_EXPORTS macro is intended for
// use on most abstract classes.  The macro should be used on
// any class which will likely need collections (sets and lists)
// to be made of them and, consequently, incorporated generically
// into data models.  If a class is likely to have large numbers
// of instances where hash tables will be needed, use the
// DECLARE_FULL_GEMS_DLL_EXPORTS macro instead.
#define DECLARE_STANDARD_GEMS_DLL_EXPORTS(T,M)  \
    class DECL_##M T;                                           \
    M##_TEMPLATE(class, smart_ptr<T>);          \
    M##_TEMPLATE(class, ptr<T>);                \
    M##_TEMPLATE(class, weak_ptr<T>);           \
    M##_TEMPLATE(class, omega_ptr<T>);          \
    M##_TEMPLATE(class, omega_weak_ptr<T>);     \
    M##_TEMPLATE(class, smart_ptr_set<T>);      \
    M##_TEMPLATE(class, ptr_set<T>);            \
    M##_TEMPLATE(class, weak_ptr_set<T>);       \
    M##_TEMPLATE(class, omega_ptr_set<T>);      \
    M##_TEMPLATE(class, omega_weak_ptr_set<T>); \
    M##_TEMPLATE(class, smart_ptr_list<T>);     \
    M##_TEMPLATE(class, ptr_list<T>);           \
    M##_TEMPLATE(class, weak_ptr_list<T>);      \
    M##_TEMPLATE(class, omega_ptr_list<T>);     \
    M##_TEMPLATE(class, omega_weak_ptr_list<T>);\
    M##_TEMPLATE(class, ptr_list_iter<T>);      \
    M##_TEMPLATE(class, comparator<T>);         \
    M##_TEMPLATE(class, comparator_list<T>);    \
    M##_TEMPLATE(class, discrim<T>);            \
    M##_TEMPLATE(class, discriminator_list<T>); \
    M##_TEMPLATE(class, discriminator_func<T>); \
    M##_TEMPLATE(class, type_discriminator<T>); \
    M##_TEMPLATE(class, not_discriminator<T>);  \
    

// The DECLARE_FULL_GEMS_DLL_EXPORTS macro is intended for
// use on key abstract classes where flexibility in organizing
// the instances of the class is of primary importance.  The
// macro instantiates templates for all types of ptr<>s,
// ptr_set<>s, ptr_list<>s, ptr_arrays<>s, and ptr_hash_table<>s.
// (These exported interfaces will tend to swell the .dll's
// interface quickly if this macro is not used judiciously on
// only the most important foundational classes of any library.)
#define DECLARE_FULL_GEMS_DLL_EXPORTS(T,M)  \
    class DECL_##M T;                                           \
    M##_TEMPLATE(class, smart_ptr<T>);          \
    M##_TEMPLATE(class, ptr<T>);                \
    M##_TEMPLATE(class, weak_ptr<T>);           \
    M##_TEMPLATE(class, hard_ptr<T>);           \
    M##_TEMPLATE(class, ghost_ptr<T>);          \
    M##_TEMPLATE(class, dyn_ptr<T>);            \
    M##_TEMPLATE(class, omega_ptr<T>);          \
    M##_TEMPLATE(class, omega_weak_ptr<T>);     \
    M##_TEMPLATE(class, smart_ptr_set<T>);      \
    M##_TEMPLATE(class, ptr_set<T>);            \
    M##_TEMPLATE(class, weak_ptr_set<T>);       \
    M##_TEMPLATE(class, omega_ptr_set<T>);      \
    M##_TEMPLATE(class, omega_weak_ptr_set<T>); \
    M##_TEMPLATE(class, smart_ptr_list<T>);     \
    M##_TEMPLATE(class, ptr_list<T>);           \
    M##_TEMPLATE(class, weak_ptr_list<T>);      \
    M##_TEMPLATE(class, omega_ptr_list<T>);     \
    M##_TEMPLATE(class, omega_weak_ptr_list<T>);\
    M##_TEMPLATE(class, ptr_list_iter<T>);      \
    M##_TEMPLATE(class, smart_ptr_array<T>);    \
    M##_TEMPLATE(class, ptr_array<T>);          \
    M##_TEMPLATE(class, weak_ptr_array<T>);     \
    M##_TEMPLATE(class, smart_ptr_hash_table<T>);       \
    M##_TEMPLATE(class, ptr_hash_table<T>);             \
    M##_TEMPLATE(class, weak_ptr_hash_table<T>);        \
    M##_TEMPLATE(class, omega_ptr_hash_table<T>);       \
    M##_TEMPLATE(class, omega_weak_ptr_hash_table<T>);  \
    M##_TEMPLATE(class, comparator<T>);         \
    M##_TEMPLATE(class, comparator_list<T>);    \
    M##_TEMPLATE(class, discrim<T>);            \
    M##_TEMPLATE(class, discriminator_list<T>); \
    M##_TEMPLATE(class, discriminator_func<T>); \
    M##_TEMPLATE(class, type_discriminator<T>); \
    M##_TEMPLATE(class, not_discriminator<T>);  \


// For use with the DECLARE_MINIMAL_GEMS_DLL_EXPORTS() macro
#define DEFINE_MINIMAL_GEMS_DLL_EXPORTS(T,M)

// For use with the DECLARE_STANDARD_GEMS_DLL_EXPORTS() macro
#define DEFINE_STANDARD_GEMS_DLL_EXPORTS(T,M)

// For use with the DECLARE_FULL_GEMS_DLL_EXPORTS() macro
#define DEFINE_FULL_GEMS_DLL_EXPORTS(T,M)

class DECL_GEMS g_type_data;
class DECL_GEMS g_type_data_iter;
class DECL_GEMS g_tag_space;

class DECL_GEMS g_type 
    {
    friend class g_tag_space;
    friend class g_type_data;
    friend class g_type_data_iter;

    public:
        g_type( const char* tagspace_name,
                const char* name,
                const char* tag,
                g_type* parent, 
                unsigned short version,
                g_type* equiv = NULL);

        virtual ~g_type();

        bool operator==(const g_type &right) const;
        bool operator!=(const g_type &right) const;

        virtual GAtom* construct() const;

        virtual bool is_a(const g_type&type) const;

        std::wstring wname() const;
        const std::string& name() const;
        const std::string& tag() const;

        const g_type * parent_type() const;
        const g_type * next_type() const;

        const g_tag_space * tag_space() const;

        unsigned short version() const { return m_version; }
        const g_type*  equivalent() const { return m_equivalent; }

        virtual bool is_abstract() const;
        virtual bool is_private() const;
            // Returns true if the class is only intended to be used as an implementation detail
            // supporting some greater mechanism (i.e. a ListNode within a LinkedList class).
            // Such classes CANNOT be saved to file directly, and are not considered to be part
            // of any file format.  Default is false.

        static const g_type* lookup(const char* typespace_name,const char* str,bool str_is_name=true);

        virtual g_type_data* type_data() const;

        virtual void* unknown() const { return 0; }

    protected:
        g_type *m_next_in_type_data;
        g_type *m_prev_in_type_data;

    private:
        static g_type* m_global_list;

        g_tag_space*    m_tag_space;

        std::string   m_name;
        std::string   m_tag;

        unsigned short  m_version;
        g_type*         m_equivalent;
            // A g_type object may substitute for another one.  This can occur,
            // for example, when the token name used to save a given class is
            // changed to a shorter one to save disk space.  The old name will
            // still need to be read, so a g_type with its m_equivalent attribute
            // pointing to the g_type with the new name will be needed.

        void destruct();

        g_type *m_parent_type;
        g_type *m_next_type;
    };

class DECL_GEMS g_type_data
    {
    friend class g_type_data_iter;

    private:
        g_type* m_head;
        g_type* m_tail;

    public:
        g_type_data();
        virtual ~g_type_data();

        void add(g_type*);
        void remove(g_type*);
    };

class DECL_GEMS g_type_data_iter
    {
    private:
        const g_type_data*  m_data;
        const g_type*       m_type;

    public:
        g_type_data_iter(const g_type_data_iter&);
        g_type_data_iter(const g_type_data&);

        const g_type_data_iter& operator=(const g_type_data_iter&);

        void operator++();
        void operator++(int);

        void operator--();
        void operator--(int);

        void reset(const g_type_data&);
        void reset_end(const g_type_data&);

        bool valid() const { return (m_type != NULL); }

        const g_type* value() const { return m_type; }
    };

// Declare various GeMS templates.

// Sets.
template <class C> class smart_ptr_set;
template <class C> class ptr_set;
template <class C> class weak_ptr_set;

// Lists.
template <class C> class smart_ptr_list;
template <class C> class ptr_list;
template <class C> class weak_ptr_list;
template <class C> class ptr_list_iter;

// Arrays.
template <class C> class smart_ptr_array;
template <class C> class ptr_array;
template <class C> class weak_ptr_array;

// Hash Tables.
template <class C> class ptr_hash_table;
template <class C> class ptr_hash_table_iter;

// Comparators.
template <class C> class comparator;
template <class C> class comparator_list;

// Discriminators.
template <class C> class discrim;
template <class C> class discriminator_list;
template <class C> class discriminator_func;
template <class C> class type_discriminator;
template <class C> class not_discriminator;


#endif

