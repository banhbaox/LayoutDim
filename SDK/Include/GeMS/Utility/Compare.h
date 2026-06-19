
#ifndef _comparator_h_
#define _comparator_h_

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

#include "GeMS/GemsFnd/ptr.h"
#include "GeMS/GemsFnd/GType.h"

enum GCompareResult
    {
	G_LEFT  = -1,
	G_EQUAL =  0,
	G_RIGHT =  1
    };

inline GCompareResult GComparePointers(const void *left, const void *right)
    {
    if(left < right)
        return(G_LEFT);

    if(left > right)
        return(G_RIGHT);

    return(G_EQUAL);
    }

template<typename T> GCompareResult GCompareValues(T left, T right)
    {
    if(left < right)
        return(G_LEFT);

    if(left > right)
        return(G_RIGHT);

    return(G_EQUAL);
    }

inline GCompareResult GCompareResultFromInt(int nResult)
    {
    if(nResult < 0)
        return(G_LEFT);

    if(nResult > 0)
        return(G_RIGHT);

    return(G_EQUAL);
    }

// A comparator will compare two given objects (via its () operator)
// and return an integer value.  A return value < 0 indicates the left
// parameter is less than the right.  A return value > 0 indicates the
// left parameter is greater than the right, and a return value == 0
// indicates the two parameters are of equal value.
class DECL_GEMS comparator_base
	{
	public:
		virtual ~comparator_base() {}
		virtual GCompareResult operator()(const void *left,
                                          const void *right) const = 0;

		virtual comparator_base* copy() const = 0;
			// Creates a copy on the heap.
	};

// A self-comparator compares a given object to its own (internal) data.
// A return value < 0 indicates the internal data has a value less
// than the given object.  A return value > 0 indicates the internal
// data is greater than the given value, and a return value ==0 indicates
// the internal data has equal value to the given data.
class DECL_GEMS self_comparator_base
	{
	public:
		virtual ~self_comparator_base() {}
		virtual GCompareResult operator()(const void *other) const = 0;

		virtual self_comparator_base* copy() const = 0;
			// Creates a copy on the heap.
	};

template <class T> class comparator : public comparator_base
	{
	private:
		GCompareResult operator()(const void *left, const void *right) const
			{ return operator()((T*)left,(T*)right); }
	public:
		virtual GCompareResult operator()(const T *, const T *) const = 0;
		virtual comparator<T> *copy() const = 0;
	};

template <class T> class self_comparator : public self_comparator_base
	{
	private:
		GCompareResult operator()(const void * other) const
			{ return operator()((T*)other); }
	public:
		virtual GCompareResult operator()(const T *) const = 0;
		virtual self_comparator<T> *copy() const = 0;
	};

struct DECL_GEMS comparator_node;

class DECL_GEMS comparator_list_base : public comparator_base
	{
	private:
		comparator_node* _comparators;

	public:
		comparator_list_base();
		comparator_list_base(const comparator_list_base&);
		virtual ~comparator_list_base();

		comparator_list_base& operator=(const comparator_list_base&);

		virtual GCompareResult operator()(const void *left,
                                          const void *right) const;

		virtual comparator_list_base* copy() const;

		comparator_base* add(comparator_base*);
		void clear();
	};

struct DECL_GEMS self_comparator_node;

class DECL_GEMS self_comparator_list_base : public self_comparator_base
	{
	private:
		self_comparator_node* _comparators;

	public:
		self_comparator_list_base();
		self_comparator_list_base(const self_comparator_list_base&);
		virtual ~self_comparator_list_base();

		self_comparator_list_base& operator=(const self_comparator_list_base&);

		virtual GCompareResult operator()(const void *other) const;

		virtual self_comparator_list_base* copy() const;

		self_comparator_base* add(self_comparator_base*);
		void clear();
	};

template <class T> class comparator_list : public comparator<T>
	{
	private:
		comparator_list_base _list;

	    GCompareResult operator()(const void *left, const void *right) const
			{ return operator()((T*)left,(T*)right); }
	public:
		comparator_list<T>() {}

		virtual GCompareResult operator()(const T *left,
                                          const T *right) const
			{ return _list((void*)left,(void*)right); }

		comparator_list<T>* copy() const { return new comparator_list<T>(*this); }

		comparator<T>* add(comparator<T>& c) { return (comparator<T>*)_list.add(&c); }
		void clear() { _list.clear(); }
	};

template <class T> class self_comparator_list : public self_comparator<T>
	{
	private:
		self_comparator_list_base _list;

	    GCompareResult operator()(const void *other) const
			{ return operator()((T*)other); }
	public:
		self_comparator_list<T>() {}

		virtual GCompareResult operator()(const T *other) const
			{ return _list((void*)other); }

		self_comparator_list<T>* copy() const { return new self_comparator_list<T>(*this); }

		self_comparator<T>* add(self_comparator<T>& c) { return (self_comparator<T>*)_list.add(&c); }
		void clear() { _list.clear(); }
	};

class DECL_GEMS discriminator_base
	{
	public:
		virtual ~discriminator_base() {}
		virtual bool operator() (const void* obj) const=0;

		virtual discriminator_base* copy() const = 0;
			// Creates a copy on the heap.
	};

template <class T> class discrim : public discriminator_base
	{
	private:
		bool operator() (const void* obj) const
			{ return evaluate(reinterpret_cast<const T*>(obj)); }
	public:
		virtual bool evaluate (const T*) const { return 0; }
		virtual discrim<T> *copy() const = 0;
	};

// The DiscrimTypes enumeration is used by
// the discriminator list.
enum DiscrimTypes
	{
	SATISFIES_ALL = 0,
	SATISFIES_AT_LEAST,
	SATISFIES_AT_MOST,
	};

// The DiscriminatorCriteria is here for
// use by your own specialized discriminators.
enum DiscriminatorCriteria
	{
	MATCHES_EXACTLY=0,
	MATCHES_ALL,
	MATCHES_ANY,
	MATCHES_NONE,
	};

struct DECL_GEMS discriminator_node;

class DECL_GEMS discriminator_list_base : public discriminator_base
	{
	private:
		discriminator_node*	_discriminators;
		DiscrimTypes	_operation_type;
		unsigned short		_count_criteria; // ignored when _operation_type==SATISFIES_ALL

	public:
		discriminator_list_base();
		discriminator_list_base(const discriminator_list_base &);
		discriminator_list_base& operator=(const discriminator_list_base& right);
		discriminator_list_base(DiscrimTypes,unsigned short countCriteria=1);

		virtual ~discriminator_list_base();

		virtual bool operator() (const void* obj) const;

		discriminator_list_base* copy() const;

		discriminator_base* add(discriminator_base*);
		void clear();

		DiscrimTypes operation_type() const	{ return _operation_type; }
		void operation_type(DiscrimTypes t)	{ _operation_type = t; }

		unsigned short count_criteria() const		{ return _count_criteria; }
		void count_criteria(unsigned short c)		{ _count_criteria = c; }
	};

template <class T> class discriminator_list : public discrim<T>
	{
private:
	discriminator_list_base _list;

	bool operator() (const void* obj) const
		{ return evaluate(reinterpret_cast<const T*>(obj)); }
public:
	discriminator_list<T>() {}
	discriminator_list<T>(const discriminator_list<T>& right):
		discrim<T>(),_list(right._list) {}
	discriminator_list<T>(	DiscrimTypes dt,
							unsigned short countCriteria=1 /* ignored when dt==SATISFIES_ALL */):
		discrim<T>(),
		_list(dt,countCriteria) {}

	discriminator_list<T>* copy() const
		{ return new discriminator_list<T>(*this); }

	virtual bool evaluate (const T* obj) const
		{ return _list(obj); }

	discrim<T>* add(discrim<T>& d) { return (discrim<T>*)_list.add(&d); }

	DiscrimTypes operation_type() const	{ return _list.operation_type(); }
	void operation_type(DiscrimTypes t)	{ _list.operation_type(t); }

	unsigned short count_criteria() const		{ return _list.count_criteria(); }
	void count_criteria(unsigned short c)		{ _list.count_criteria(c); }
	};

class DECL_GEMS discriminator_func_base : public discriminator_base
	{
	private:
		bool (*_disc_func)(const void*);

	public:
		discriminator_func_base(bool (*f)(const void*))
			{ _disc_func = f; }
		discriminator_func_base(const discriminator_func_base& right):
			discriminator_base(right) { _disc_func = right._disc_func; }

		bool operator() (const void * obj) const { return (*_disc_func)(obj); }

		discriminator_func_base* copy() const
			{ return new discriminator_func_base(*this); }
	};

template <class T> class discriminator_func : public discrim<T>
	{
protected:
	discriminator_func_base _disc_func;

	bool operator() (const void* obj) const
		{ return evaluate(reinterpret_cast<const T*>(obj)); }

public:
	discriminator_func<T>(const discriminator_func<T>& right):
		discrim<T>(),_disc_func(right._disc_func) {}

	discriminator_func<T>(bool (*f)(const T*)):discrim<T>(),
		_disc_func((bool(*)(const void*))f) {}

	discriminator_func<T>(bool (*f)(T*)):discrim<T>(),
		_disc_func((bool(*)(const void*))f) {}

	bool evaluate (const T* obj) const { return _disc_func(obj); }

	discriminator_func<T> * copy() const
		{ return new discriminator_func<T>(*this); }
	};

template <class P, class T> class discriminator_parameter_func : public discrim<T>
	{
protected:
	bool (*_disc_func)(const void*,const void*);

	bool operator() (const GAtom* obj) const
		{ return evaluate(reinterpret_cast<const T*>(obj)); }

	P m_p;

public:
	discriminator_parameter_func<P,T>(const discriminator_parameter_func<P,T>& right):
		discrim<T>(),_disc_func(right._disc_func),m_p(right.m_p) {}

	discriminator_parameter_func<P,T>(P& p,bool (*f)(const P*,const T*)):discrim<T>(),
		_disc_func((bool(*)(const void*,const void*))f), m_p(p) {}

	discriminator_parameter_func<P,T>(P& p,bool (*f)(P*,T*)):discrim<T>(),
		_disc_func((bool(*)(const void*,const void*))f), m_p(p) {}

	bool evaluate (const T* obj) const { return _disc_func(&m_p,obj); }

	discriminator_parameter_func<P,T>* copy() const
		{ return new discriminator_parameter_func<P,T>(*this); }
	};

class DECL_GEMS type_discriminator_base : private discriminator_base
	{
private:
	const g_type*	_type;
	bool			_matches_exactly;

	bool operator() (const void* obj) const
        { return (*this)(reinterpret_cast<const GAtom *>(obj)); }

public:
	type_discriminator_base(const type_discriminator_base& right):
		discriminator_base(),_type(right._type),_matches_exactly(right._matches_exactly) {}

	type_discriminator_base(const g_type& t,bool matches_exactly=false):discriminator_base(),
		_type(&t),_matches_exactly(matches_exactly) {}

	virtual bool operator() (const GAtom* obj) const;

	type_discriminator_base* copy() const
		{ return new type_discriminator_base(*this); }
	};

template <class T> class type_discriminator : public discrim<T>
	{
protected:
	type_discriminator_base _type_disc;

	bool operator() (const void* obj) const
		{ return evaluate(reinterpret_cast<const T*>(obj)); }

public:
	type_discriminator<T>(const type_discriminator<T>& right):
		discrim<T>(right),_type_disc(right._type_disc) {}

	type_discriminator<T>(const g_type& t,bool matches_exactly=false):discrim<T>(),
		_type_disc(t,matches_exactly) {}

	bool evaluate (const T* obj) const { return _type_disc((GAtom*)obj); }

	type_discriminator<T>* copy() const
		{ return new type_discriminator<T>(*this); }
	};

template <class T> class not_discriminator : public discrim<T>
	{
protected:
	discrim<T>* _disc;

	bool operator() (const void* obj) const
		{ return evaluate(reinterpret_cast<const T*>(obj)); }

public:
	not_discriminator<T>(const not_discriminator<T>& right):
		discrim<T>(right),_disc(right._disc->copy())
		{}

	not_discriminator<T>(const discrim<T>& d):discrim<T>(),
		_disc(d.copy()) {}

	~not_discriminator<T>() { delete _disc; }

	bool evaluate (const T* obj) const { return !_disc->evaluate(obj); }

	not_discriminator<T>* copy() const
		{ return new not_discriminator<T>(*this); }
	};

template<class T> class not_type_discriminator : public not_discriminator<T>
	{
	public:
		 not_type_discriminator(const g_type &t, bool matches_exactly = false) :
			 not_discriminator<T>(type), type(t, matches_exactly) {}

	protected:
		 type_discriminator<T> type;
	};

GEMS_TEMPLATE(class, comparator<GAtom>);

////////////////////////////
// Common comparators
//

class DECL_GEMS g_ptr_comparator : public comparator<GAtom>
	{
public:
	GCompareResult operator()(const GAtom *left, const GAtom *right) const
        { return(GComparePointers(left, right)); }

	g_ptr_comparator* copy() const { return new g_ptr_comparator(*this); }
	};

#endif

