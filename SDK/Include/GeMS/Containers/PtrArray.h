
#ifndef _ptr_array_h_
#define _ptr_array_h_

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
#include "GeMS/GemsFnd/Ptr.h"

#include "GeMS/GemsFnd/Gassert.h"

class DECL_GEMS ptr_array_base
	{
	friend class DECL_GEMS g_stream;

	private:
		mutable GAtom*	_owner;
		dyn_ptr_base*	_values;
		size_t 	        _size;
		size_t 	        _capacity;
		g_behaviors		_behaviors;

	protected:
		ptr_array_base();
		ptr_array_base(const ptr_array_base& right);

	public:
		//////////////////////////////////
		// iterator
		class DECL_GEMS iterator
			{
			friend class ptr_array_base;

			protected:
				mutable ptr_array_base*	_array;
				mutable ptrdiff_t		_index;	// May reference -1 for 'reverse end'.

			public:
				iterator() { _array=NULL; _index = 0; }
				iterator(const ptr_array_base* arr,ptrdiff_t i)
					{
					_array = (ptr_array_base*)arr;
					_index = i;
					}

				const iterator& operator++() const
					{ _index++; return *this; }
				iterator operator++(int) const;

				const iterator& operator--() const
					{ _index--; return *this; }
				iterator operator--(int) const;

				bool operator==(const iterator& r) const
					{ return (_index == r._index) && (_array == r._array); }
				bool operator!=(const iterator& r) const
					{ return (_index != r._index) || (_array != r._array); }

				iterator operator+(ptrdiff_t v) const
					{ return iterator(_array,_index+v); }
				iterator operator-(ptrdiff_t v) const
					{ return iterator(_array,_index-v); }

				ptrdiff_t operator-(const iterator& i) const
					{ return _index-i._index; }

				ptr_base&	operator*()
					{ return _array->_values[_index]; }
				const ptr_base& operator*() const
					{ return _array->_values[_index]; }

				bool valid() const
					{ return ((_index >= 0) && (_index < (ptrdiff_t)_array->size())); }
			};
		friend class iterator;
		typedef const iterator const_iterator;

		class DECL_GEMS reverse_iterator : public iterator
			{
			public:
				reverse_iterator():iterator() {}
				reverse_iterator(const ptr_array_base* arr,ptrdiff_t i):iterator(arr,i) {}
				reverse_iterator(const iterator& i):iterator(i) {}

				const reverse_iterator& operator++() const
					{ iterator::operator--(); return *this; }
				reverse_iterator operator++(int) const;

				const reverse_iterator& operator--() const
					{ iterator::operator++(); return *this; }
				reverse_iterator operator--(int) const;

				reverse_iterator operator+(ptrdiff_t v) const
					{ return reverse_iterator(_array,_index-v); }
				reverse_iterator operator-(ptrdiff_t v) const
					{ return reverse_iterator(_array,_index+v); }

				ptrdiff_t operator-(const reverse_iterator& i) const
					{ return i._index-_index; }

				operator iterator() const
					{ return iterator(_array,_index); }
			};
		friend class reverse_iterator;
		typedef const reverse_iterator const_reverse_iterator;

		ptr_array_base(size_t sz,g_behaviors behave);
		ptr_array_base(const ptr_array_base& right,g_behaviors behave);
		ptr_array_base(const iterator& first,const iterator& last,g_behaviors behave);

		virtual ~ptr_array_base();

		virtual void live_to_ghost();
		virtual void ghost_to_live();

		GAtom* owner() const { return _owner; }
		void owner(GAtom* own) const;

		ptr_array_base& operator=(const ptr_array_base& right);

		bool operator ==(const ptr_array_base& right) const;

		g_behaviors behaviors() const { return _behaviors; }
		void behaviors(g_behaviors behave);

		virtual void forget(const g_forget_event&);

		iterator begin() { return iterator(this,0); }
		const_iterator begin() const { return const_iterator(this,0); }

		iterator end() { return iterator(this,_size); }
		const_iterator end() const { return const_iterator(this,_size); }

		reverse_iterator rbegin() { return reverse_iterator(this,_size-1); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(this,_size-1); }

		reverse_iterator rend() { return reverse_iterator(this,-1); }
		const_reverse_iterator rend() const { return const_reverse_iterator(this,-1); }

		ptr_base& front() { return _values[0]; }
		const ptr_base& front() const { return _values[0]; }

		ptr_base& back() { return _values[_size-1]; }
		const ptr_base& back() const { return _values[_size-1]; }

		size_t capacity() { return _capacity; }
		virtual void capacity(size_t sz,bool retain_values = true);

		bool empty() const { return (_size==0); }

		size_t size() const { return _size; }
        virtual void size(size_t sz,bool retain_values = true);
		void resize(size_t sz,bool retain_values = true) { size(sz, retain_values); }

		size_t max_size() const { return (size_t(-1)/2); }

		void reserve (size_t c,bool retain_values=true);

		void swap(ptr_array_base& right);

		ptr_base&		value	(size_t index)		    { G_ASSERT(index < size()); return _values[index]; } 
		const ptr_base&	value	(size_t index) const	{ G_ASSERT(index < size()); return _values[index]; }

		void push_back(GAtom* x);
		void pop_back();

		void insert(const iterator& position, size_t n, GAtom* x = NULL);
		iterator insert(const iterator& position, GAtom* x = NULL);
		void insert(const iterator& position,const iterator& first,const iterator& last);
		void insert(const iterator& position,const reverse_iterator& first,const reverse_iterator& last);

		void erase(iterator& position);
		void erase(iterator& first,iterator& last);

		void clear();
	};

template <class T> class smart_ptr_array : public ptr_array_base
	{
public:
	typedef T* value_type;

	class iterator : public ptr_array_base::iterator
		{
		friend class smart_ptr_array<T>;

	protected:
		explicit iterator(const ptr_array_base::iterator& i):ptr_array_base::iterator(i) {}

	public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef typename smart_ptr_array<T>::value_type value_type;
        typedef ptrdiff_t difference_type;
        typedef difference_type distance_type;	// retained
        typedef T* pointer;
        typedef T& reference;

		iterator():ptr_array_base::iterator() {}
		iterator(const smart_ptr_array<T>* arr,ptrdiff_t i):ptr_array_base::iterator(arr,i) {}
		iterator(const iterator& r):ptr_array_base::iterator(r) {}

		const iterator& operator++() const { ((ptr_array_base::iterator*)this)->operator++(); return *this; }
		iterator operator++(int) const
			{
			return iterator(((ptr_array_base::iterator*)this)->operator++(1));
			}

		const iterator& operator--() const { ((ptr_array_base::iterator*)this)->operator--(); return *this; }
		iterator operator--(int) const
			{
			return iterator(((ptr_array_base::iterator*)this)->operator--(1));
			}

		bool operator==(const ptr_array_base::iterator& r) const { return ((ptr_array_base::iterator*)this)->operator==(r); }
		bool operator!=(const ptr_array_base::iterator& r) const { return ((ptr_array_base::iterator*)this)->operator!=(r); }

		iterator operator+(ptrdiff_t v) const
			{
			return iterator(((ptr_array_base::iterator*)this)->operator+(v));
			}
		iterator operator-(ptrdiff_t v) const
			{
			return iterator (((ptr_array_base::iterator*)this)->operator-(v));
			}

		ptrdiff_t operator-(const iterator& r) const { return ((ptr_array_base::iterator*)this)->operator-(r); }

		smart_ptr<T>&	operator*() { return (smart_ptr<T>&)((ptr_array_base::iterator*)this)->operator*(); }
		const smart_ptr<T>& operator*() const { return (const smart_ptr<T>&)((ptr_array_base::iterator*)this)->operator*(); }
		};
	typedef const iterator const_iterator;

	class reverse_iterator : public ptr_array_base::reverse_iterator
		{
		friend class smart_ptr_array<T>;

	protected:
		explicit reverse_iterator(const ptr_array_base::reverse_iterator& i):ptr_array_base::reverse_iterator(i) {}

	public:
		reverse_iterator():ptr_array_base::reverse_iterator() {}
		reverse_iterator(const smart_ptr_array<T>* arr,ptrdiff_t i):ptr_array_base::reverse_iterator(arr,i) {}
		reverse_iterator(const reverse_iterator& r):ptr_array_base::reverse_iterator(r) {}

		const reverse_iterator& operator++() const { ((ptr_array_base::reverse_iterator*)this)->operator++(); return *this; }
		reverse_iterator operator++(int) const
			{
			return reverse_iterator(((ptr_array_base::reverse_iterator*)this)->operator++(1));
			}

		const reverse_iterator& operator--() const { ((ptr_array_base::reverse_iterator*)this)->operator--(); return *this; }
		reverse_iterator operator--(int) const
			{
			return reverse_iterator(((ptr_array_base::reverse_iterator*)this)->operator--(1));
			}

		bool operator==(const ptr_array_base::iterator& r) const { return ((ptr_array_base::reverse_iterator*)this)->operator==(r); }
		bool operator!=(const ptr_array_base::iterator& r) const { return ((ptr_array_base::reverse_iterator*)this)->operator!=(r); }

		reverse_iterator operator+(ptrdiff_t v) const
			{
			return reverse_iterator(((ptr_array_base::reverse_iterator*)this)->operator+(v));
			}
		reverse_iterator operator-(ptrdiff_t v) const
			{
			return reverse_iterator(((ptr_array_base::reverse_iterator*)this)->operator-(v));
			}

		ptrdiff_t operator-(const reverse_iterator& r) const { return ((ptr_array_base::reverse_iterator*)this)->operator-(r); }

		smart_ptr<T>&	operator*() { return (smart_ptr<T>&)((ptr_array_base::reverse_iterator*)this)->operator*(); }
		const smart_ptr<T>& operator*() const { return (const smart_ptr<T>&)((ptr_array_base::reverse_iterator*)this)->operator*(); }

		operator iterator() const {	return smart_ptr_array<T>::iterator((smart_ptr_array<T>*)_array,_index); }
		};

	typedef const reverse_iterator const_reverse_iterator;

	smart_ptr_array(size_t sz,g_behaviors behave):ptr_array_base(sz,behave) {}
	smart_ptr_array(const smart_ptr_array<T>& right,g_behaviors behave):ptr_array_base(right,behave) {}
	smart_ptr_array(const iterator& first,const iterator& last,g_behaviors behave):ptr_array_base(first,last,behave) {}

	smart_ptr_array<T>& operator=(const smart_ptr_array<T>& right) { ptr_array_base::operator=(right); return *this; }

	smart_ptr<T>&		operator[] (size_t index)		{ G_ASSERT(index < size()); return (smart_ptr<T>&)ptr_array_base::value(index); } 
	const smart_ptr<T>&	operator[] (size_t index) const	{ G_ASSERT(index < size()); return (const smart_ptr<T>&)ptr_array_base::value(index); }

	iterator begin() { return iterator(ptr_array_base::begin()); }
	const_iterator begin() const { return const_iterator(ptr_array_base::begin()); }

	iterator end() { return iterator(ptr_array_base::end()); }
	const_iterator end() const { return const_iterator(ptr_array_base::end()); }

	reverse_iterator rbegin() { return reverse_iterator(ptr_array_base::rbegin()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(ptr_array_base::rbegin()); }

	reverse_iterator rend() { return reverse_iterator(ptr_array_base::rend()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(ptr_array_base::rend()); }

	smart_ptr<T>& front() { return (smart_ptr<T>&)ptr_array_base::front(); }
	const smart_ptr<T>& front() const { return (const smart_ptr<T>&)ptr_array_base::front(); }

	smart_ptr<T>& back() { return (smart_ptr<T>&)ptr_array_base::back(); }
	const smart_ptr<T>& back() const { return (const smart_ptr<T>&)ptr_array_base::back(); }

	void swap(smart_ptr_array<T>& right) { ptr_array_base::swap(right); }

	void insert(const iterator& p, size_t n, T* x = NULL) { ptr_array_base::insert(p,n,reinterpret_cast<GAtom *>(x)); }
	iterator insert(const iterator& p, GAtom* x = NULL) { return iterator(ptr_array_base::insert(p,reinterpret_cast<GAtom *>(x))); }
	void insert(const iterator& p,const iterator& f,const iterator& l) { ptr_array_base::insert(p,f,l); }
	void insert(const iterator& p,const reverse_iterator& f,const reverse_iterator& l) { ptr_array_base::insert(p,f,l); }

	void erase(iterator p) { ptr_array_base::erase(p); }
	void erase(iterator f,iterator l) { ptr_array_base::erase(f,l); }
	};

template <class T> class ptr_array : public smart_ptr_array<T>
	{
public:
    typedef typename smart_ptr_array<T>::iterator iterator;
	ptr_array():smart_ptr_array<T>(0,STRONG_PTR) {}
	ptr_array(size_t sz):smart_ptr_array<T>(sz,STRONG_PTR) {}
	ptr_array(const ptr_array<T>& right):smart_ptr_array<T>(right,STRONG_PTR) {}
	ptr_array(const smart_ptr_array<T>& right):smart_ptr_array<T>(right,STRONG_PTR) {}
	ptr_array(const iterator& first,const iterator& last):smart_ptr_array<T>(first,last,STRONG_PTR) {}

	ptr_array<T>& operator=(const ptr_array<T>& right)			{ ptr_array_base::operator=(right); return *this; }
	ptr_array<T>& operator=(const smart_ptr_array<T>& right)	{ ptr_array_base::operator=(right); return *this; }

	ptr<T>&			operator[] (size_t index)		{ G_ASSERT(index < size()); return (ptr<T>&)ptr_array_base::value(index); } 
	const ptr<T>&	operator[] (size_t index) const	{ G_ASSERT(index < size()); return (const ptr<T>&)ptr_array_base::value(index); }

	void swap(ptr_array<T>& right) { ptr_array_base::swap(right); }
	};

template <class T> class weak_ptr_array : public smart_ptr_array<T>
	{
public:
    typedef typename smart_ptr_array<T>::iterator iterator;
	weak_ptr_array():smart_ptr_array<T>(0,REGISTERED_PTR) {}
	weak_ptr_array(size_t sz):smart_ptr_array<T>(sz,REGISTERED_PTR) {}
	weak_ptr_array(const weak_ptr_array<T>& right):smart_ptr_array<T>(right,REGISTERED_PTR) {}
	weak_ptr_array(const smart_ptr_array<T>& right):smart_ptr_array<T>(right,REGISTERED_PTR) {}
	weak_ptr_array(const iterator& first,const iterator& last):smart_ptr_array<T>(first,last,REGISTERED_PTR) {}

	weak_ptr_array<T>& operator=(const weak_ptr_array<T>& right)	{ ptr_array_base::operator=(right); return *this; }
	weak_ptr_array<T>& operator=(const smart_ptr_array<T>& right)	{ ptr_array_base::operator=(right); return *this; }

	weak_ptr<T>&		operator[] (size_t index)		{ G_ASSERT(index < size()); return (weak_ptr<T>&)ptr_array_base::value(index); } 
	const weak_ptr<T>&	operator[] (size_t index) const	{ G_ASSERT(index < size()); return (const weak_ptr<T>&)ptr_array_base::value(index); }

	void swap(weak_ptr_array<T>& right) { ptr_array_base::swap(right); }
	};

template <class T> class hard_ptr_array : public smart_ptr_array<T>
	{
public:
    typedef typename smart_ptr_array<T>::iterator iterator;
	hard_ptr_array():smart_ptr_array<T>(0,USE_COUNT_PTR) {}
	hard_ptr_array(size_t sz):smart_ptr_array<T>(sz,USE_COUNT_PTR) {}
	hard_ptr_array(const hard_ptr_array<T>& right):smart_ptr_array<T>(right,USE_COUNT_PTR) {}
	hard_ptr_array(const smart_ptr_array<T>& right):smart_ptr_array<T>(right,USE_COUNT_PTR) {}
	hard_ptr_array(const iterator& first,const iterator& last):smart_ptr_array<T>(first,last,USE_COUNT_PTR) {}

	hard_ptr_array<T>& operator=(const hard_ptr_array<T>& right)	{ ptr_array_base::operator=(right); return *this; }
	hard_ptr_array<T>& operator=(const smart_ptr_array<T>& right)	{ ptr_array_base::operator=(right); return *this; }

	hard_ptr<T>&		operator[] (size_t index)		{ G_ASSERT(index < size()); return (hard_ptr<T>&)ptr_array_base::value(index); } 
	const hard_ptr<T>&	operator[] (size_t index) const	{ G_ASSERT(index < size()); return (const hard_ptr<T>&)ptr_array_base::value(index); }

	void swap(hard_ptr_array<T>& right) { ptr_array_base::swap(right); }
	};

template <class T> class ghost_ptr_array : public smart_ptr_array<T>
	{
public:
    typedef typename smart_ptr_array<T>::iterator iterator;
	ghost_ptr_array():smart_ptr_array<T>(0,(g_behaviors)(USE_COUNT_PTR + GHOST_PTR)) {}
	ghost_ptr_array(size_t sz):smart_ptr_array<T>(sz,(g_behaviors)(USE_COUNT_PTR + GHOST_PTR)) {}
	ghost_ptr_array(const ghost_ptr_array<T>& right):smart_ptr_array<T>(right,(g_behaviors)(USE_COUNT_PTR + GHOST_PTR)) {}
	ghost_ptr_array(const smart_ptr_array<T>& right):smart_ptr_array<T>(right,(g_behaviors)(USE_COUNT_PTR + GHOST_PTR)) {}

	ghost_ptr_array<T>& operator=(const ghost_ptr_array<T>& right)	{ ptr_array_base::operator=(right); return *this; }
	ghost_ptr_array<T>& operator=(const smart_ptr_array<T>& right)	{ ptr_array_base::operator=(right); return *this; }

	ghost_ptr<T>&		operator[] (size_t index)		{ return (ghost_ptr<T>&)ptr_array_base::value(index); } 
	const ghost_ptr<T>&	operator[] (size_t index) const	{ return (const ghost_ptr<T>&)ptr_array_base::value(index); }
	};

GEMS_TEMPLATE(class, smart_ptr_array<GAtom>);
GEMS_TEMPLATE(class, ptr_array<GAtom>);
GEMS_TEMPLATE(class, weak_ptr_array<GAtom>);

#endif
