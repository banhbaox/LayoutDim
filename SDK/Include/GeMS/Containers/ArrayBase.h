
#ifndef _array_base_h_
#define _array_base_h_

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

#pragma warning(push, 3)
#pragma warning(disable: 4514)  // 'function' : unreferenced inline function has been removed
#include <vector>
#pragma warning(pop)
#pragma warning(disable: 4710)  // 'function' : function not inlined

#include "GeMS/Dcl_gems.h"

#include "GeMS/GemsFnd/Gassert.h"
#include "GeMS/GemsFnd/Error.h"
#include "GeMS/Utility/GMemory.h"

//--------------------------------------------------------------------------------------
// Declare g_construct() and g_destruct() templates that call the
// constructors and destructors of the template parameter for single
// elements and for arrays of the elements.  This will enable us to
// create specializations of the templates for primitive types (int,
// float, etc.) that are much higher speed since we can use
// CopyMemory() for the special cases.
template <class T> T* g_new_array(size_t n,const T* pSource)
    {
    T* pDest = new T[n];
    if(pSource)
        {
        T* pCurrent = pDest;
        for(size_t i=0;i<n;++i,++pCurrent,++pSource)
            *pCurrent = *pSource;
        }
    return pDest;
    }

template <class T, class U, class V>
T *g_new_array(size_t n, const std::vector<U, V> &rSource)
    {
    T* pDest = new T[n];
    T* pCurrent = pDest;
    for(size_t i = 0; i < n; ++i, ++pCurrent)
        *pCurrent = rSource[i];
    return pDest;
    }

template <class T> void g_delete_array(size_t,T* pT)
    {
    delete [] pT;
    }

template <class T> void g_copy(T* pDest,const T& rSource) { *pDest = rSource; }
template <class T> void g_copy(size_t n,T* pDest,const T* pSource)
    {
    for(size_t i=0;i<n;++i,++pDest,++pSource)
        *pDest = *pSource;
    }
template <class T> void g_no_overlap_copy(size_t n,T* pDest,const T* pSource)
    {
    for(size_t i=0;i<n;++i,++pDest,++pSource)
        *pDest = *pSource;
    }

//--------------------------------------------------------------------------------------
// Declare macros that will create the special case specializations.
#define G_DECLARE_NOCONSTRUCT(T,M) \
    DECL_##M T* g_new_array(size_t,const T*); \
    DECL_##M void g_delete_array(size_t,T*); \

#define G_DEFINE_NOCONSTRUCT(T,M)   \
    DECL_##M T* g_new_array(size_t n,const T* pSource)  \
        { \
        T* pDest = (T*)g_alloc(n*sizeof(T)); \
        if(pSource && pDest)    \
            memcpy(pDest,pSource, n*sizeof(T)); \
        return pDest; \
        } \
    DECL_##M void g_delete_array(size_t,T* pT) { g_free(pT); } \

#define G_DECLARE_BITWISE_COPY(T,M) \
    DECL_##M void g_copy(size_t n,T* pDest,const T* pSource); \
    DECL_##M void g_no_overlap_copy(size_t n,T* pDest,const T* pSource); 

#define G_DEFINE_BITWISE_COPY(T,M)  \
    DECL_##M void g_copy(size_t n,T* pDest,const T* pSource) \
        { memmove(pDest, pSource, n * sizeof(T)); } \
    DECL_##M void g_no_overlap_copy(size_t n,T* pDest,const T* pSource) \
        { memcpy(pDest, pSource, n * sizeof(T)); }

G_DECLARE_NOCONSTRUCT(bool,GEMS)
G_DECLARE_NOCONSTRUCT(char,GEMS)
G_DECLARE_NOCONSTRUCT(unsigned char,GEMS)
G_DECLARE_NOCONSTRUCT(short,GEMS)
G_DECLARE_NOCONSTRUCT(unsigned short,GEMS)
#ifdef _WIN64
G_DECLARE_NOCONSTRUCT(int,GEMS)
G_DECLARE_NOCONSTRUCT(unsigned int,GEMS)
#endif
G_DECLARE_NOCONSTRUCT(long,GEMS)
G_DECLARE_NOCONSTRUCT(unsigned long,GEMS)
G_DECLARE_NOCONSTRUCT(ptrdiff_t,GEMS)
G_DECLARE_NOCONSTRUCT(size_t,GEMS)
G_DECLARE_NOCONSTRUCT(float,GEMS)
G_DECLARE_NOCONSTRUCT(double,GEMS)

G_DECLARE_BITWISE_COPY(bool,GEMS)
G_DECLARE_BITWISE_COPY(char,GEMS)
G_DECLARE_BITWISE_COPY(unsigned char,GEMS)
G_DECLARE_BITWISE_COPY(short,GEMS)
G_DECLARE_BITWISE_COPY(unsigned short,GEMS)
#ifdef _WIN64
G_DECLARE_BITWISE_COPY(int,GEMS)
G_DECLARE_BITWISE_COPY(unsigned int,GEMS)
#endif
G_DECLARE_BITWISE_COPY(long,GEMS)
G_DECLARE_BITWISE_COPY(unsigned long,GEMS)
G_DECLARE_BITWISE_COPY(ptrdiff_t,GEMS)
G_DECLARE_BITWISE_COPY(size_t,GEMS)
G_DECLARE_BITWISE_COPY(float,GEMS)
G_DECLARE_BITWISE_COPY(double,GEMS)

// The 'g_array<>' template defines an array type which
// can be resized and which 'knows' its size.  The array
// types which utilize the C++ primitives (char, int, double,
// etc.) are considered GeMS primitives which can be used
// in GAtom derived classes and which can be streamed out
// to a save file.  Note that normal C++ arrays
// (i.e. int arr[5];) are NOT considered GeMS primitives
// and cannot be so streamed.

template <class T> class g_array
    {
private:
    size_t          _size;
    size_t          _capacity;
    T*              _values;
    
public:
    typedef T value_type;

    class iterator
        {
        friend class g_array<T>;
        
    protected:
        const g_array<T> *_array;
        ptrdiff_t _index; // By storing as an index, iterators remain valid when array capacity is reallocated.
        
    public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef typename g_array<T>::value_type value_type;
        typedef ptrdiff_t difference_type;
        typedef difference_type distance_type;  // retained
        typedef T* pointer;
        typedef T& reference;

        iterator() : _array(NULL), _index(0) {}
        iterator(const g_array<T> *arr, ptrdiff_t i) : _array(arr), _index(i) {}
        
        iterator &operator=(const iterator &r) { _array = r._array; _index = r._index; return *this; }
        
        bool operator==(const iterator &r) const { return (_index == r._index) && (_array == r._array); }
        bool operator!=(const iterator &r) const { return !operator==(r); }
        
        reference operator*() const { return _array->_values[_index]; }
        
        iterator &operator++()    { _index++; return *this; }
        iterator  operator++(int) { iterator i=*this; _index++; return i; }
        
        iterator &operator--()    { _index--; return *this; }
        iterator  operator--(int) { iterator i=*this; _index--; return i; }
        
        iterator operator+(ptrdiff_t v) const { return iterator(_array,_index+v); }
        iterator operator-(ptrdiff_t v) const { return iterator(_array,_index-v); }
        
        ptrdiff_t operator-(const iterator &i) const { return _index-i._index; }

        bool operator<(const iterator &i) const { return(_index < i._index); }

        bool valid() const { return (_index>=0 && _array && (_index<(ptrdiff_t)_array->size())); }
        };
    friend class iterator;
    
    class reverse_iterator : public iterator
        {
    public:
        reverse_iterator() : iterator() {}
        reverse_iterator(const g_array<T> *arr, ptrdiff_t i) : iterator(arr, i) {}
        
        reverse_iterator &operator++()    { iterator::operator--(); return *this; }
        reverse_iterator  operator++(int) { reverse_iterator i=*this; iterator::operator--(); return i; }
        
        reverse_iterator &operator--()    { iterator::operator++(); return *this; }
        reverse_iterator  operator--(int) { reverse_iterator i=*this; iterator::operator++(); return i; }

        reverse_iterator operator+(ptrdiff_t v) const { return reverse_iterator(this->_array,this->_index-v); }
        reverse_iterator operator-(ptrdiff_t v) const { return reverse_iterator(this->_array,this->_index+v); }
        
        ptrdiff_t operator-(const reverse_iterator &i) const { return i._index - this->_index; }
        };
    
    typedef const iterator const_iterator;
    typedef const reverse_iterator const_reverse_iterator;
    
    g_array() { _size = 0; _capacity=0; _values = NULL; }
    g_array(size_t sz,const T* v = 0)
        {
        _size = sz;
        _capacity = sz;
        _values = NULL;
        if(_capacity)
            {
            _values = g_new_array<T>(_capacity,v);
            if(!_values)
                {
                _capacity = _size = 0;
                throw g_error(g_error::INSUFFICIENT_MEMORY,L"Insufficient Memory");
                }
            }
        }
    g_array(const T* first,const T* last)
        {
        _size = last-first;
        _capacity = _size;
        if(_capacity)
            {
            _values = g_new_array<T>(_capacity,first);
            if(!_values)
                {
                _capacity = _size = 0;
                throw g_error(g_error::INSUFFICIENT_MEMORY,L"Insufficient Memory");
                }
            }
        else
            _values = NULL;
        }
    g_array(const g_array<T>& right)
        {
        _size = right._size;
        _capacity = _size;
        if(_capacity)
            {
            _values = g_new_array<T>(_capacity,right._values);
            if(!_values)
                {
                _capacity = _size = 0;
                throw g_error(g_error::INSUFFICIENT_MEMORY,L"Insufficient Memory");
                }
            }
        else
            _values = NULL;
        }
    template<class U, class V> g_array(const std::vector<U, V> &right)
        {
        _size = right.size();
        _capacity = _size;
        if(_capacity)
            {
            _values = g_new_array<T, U>(_capacity, right);
            if(!_values)
                {
                _capacity = _size = 0;
                throw g_error(g_error::INSUFFICIENT_MEMORY,L"Insufficient Memory");
                }
            }
        else
            _values = NULL;
        }
    ~g_array()
        {
        if(_values!=NULL)
            g_delete_array<T>(_capacity,_values);
        }
    
    iterator begin()                { return iterator(this,0); }
    iterator end()                  { return iterator(this,_size); }
    const_iterator begin() const    { return const_iterator(this,0); }
    const_iterator end() const      { return const_iterator(this,_size); }
    
    reverse_iterator rbegin()               { return reverse_iterator(this,_size-1); }
    reverse_iterator rend()                 { return reverse_iterator(this,-1); }
    const_reverse_iterator rbegin() const   { return const_reverse_iterator(this,_size-1); }
    const_reverse_iterator rend() const     { return const_reverse_iterator(this,-1); }
    
    bool empty() const { return (_size==0); }
    
    size_t size() const { return _size; }

    void size(size_t sz) { resize(sz); }

    void resize(size_t sz)
        {
        if((sz <= _capacity) && ((sz > _size) || (sz >= _capacity/4)))
            {
            _size = sz;
            return;
            }
        capacity(sz);
        _size = sz;
        }

    size_t capacity() const { return _capacity; }

protected:
    void capacity (size_t c)
        {
        if(c==_capacity)
            return;
        
        if(_size > c)
            _size = c;
        
        T* new_values = NULL;
        if(c)
            {
            new_values = g_new_array<T>(c,(const T*)NULL);
            if(!new_values)
                throw g_error(g_error::INSUFFICIENT_MEMORY,L"Insufficient Memory");

            g_no_overlap_copy(_size,new_values,_values);
            }
            
        if(_values != NULL)
            g_delete_array<T>(_capacity,_values);

        _capacity = c;
        _values = new_values;
        }

public:
    void reserve (size_t c)
        {
        if(_capacity < c)
            capacity(c);
        }
    
    void swap(g_array<T>& right)
        {
        if(this==&right)
            return;
        T* temp_values = _values;
        size_t temp_size = _size;
        size_t temp_capacity = _capacity;
        
        _values = right._values;
        _size = right._size;
        _capacity = right._capacity;
        
        right._values = temp_values;
        right._size = temp_size;
        right._capacity = temp_capacity;
        }
    
    size_t max_size() const { return (size_t(-1)/2); }
    
    T& front() { return _values[0]; }
    const T& front() const { return _values[0]; }
    
    T& back() { return _values[_size-1]; }
    const T& back() const { return _values[_size-1]; }
    
    void push_back(const T& x)
        {
        T *old_values = NULL;
        size_t old_capacity = 0;
        
        if(_size == _capacity)
            capacity((_size == 0) ? 4 : _size * 2, old_capacity, old_values);
        
        _values[_size] = x;
        _size++;
        
        if(NULL != old_values)
            g_delete_array<T>(old_capacity, old_values);
        }

    void pop_back()
        {
        if(_size > 0)
            _size--;
        if(_size < _capacity/4)
            capacity(_size);
        }
    
    void insert(const iterator& position, size_t n, const T& x)
        {
        if ((ptrdiff_t)n > 0)
            {
            T *old_values = NULL;
            size_t old_capacity = 0;

            if(_size+n > _capacity)
                {
                if(n>_capacity)
                    capacity((_size+n<4)?4:(_size+n),old_capacity,old_values);
                else
                    capacity((_size+n)*2,old_capacity,old_values);
                }
            
            iterator to(this,_size-1+n);
            if(position._index < (ptrdiff_t)_size)
                {
                iterator from(this,_size-1);
                
                while(from._index >= position._index)
                    {
                    *to = *from;
                    --to;
                    --from;
                    }
                } 
            
            while (to._index >= position._index)
                {
                *to = x;
                --to;
                }
            
            _size+=n;

            if(NULL != old_values)
                g_delete_array<T>(old_capacity, old_values);
            }
        }
    
    iterator insert(const iterator& position, const T& x)
        {
        insert(position,1,x);
        return position;
        }
    
    void insert(const iterator& position,const T* first,const T* last)
        {
        size_t n = last-first;
        if ((ptrdiff_t)n > 0)
            {
            T *old_values = NULL;
            size_t old_capacity = 0;

            if(_size+n > _capacity)
                {
                if(n>_capacity)
                    capacity(_size+n,old_capacity,old_values);
                else
                    capacity((_size+n)*2,old_capacity,old_values);
                }
            
            if(position._index < (ptrdiff_t)_size)
                {
                iterator from(this,_size-1);
                iterator to(this,_size-1+n);
                
                while(from._index >= position._index)
                    {
                    *to = *from;
                    --to;
                    --from;
                    }
                }
            
            iterator pos = position;
            const T* current = first;
            while(current != last)
                {
                *pos = *current;
                ++current;
                ++pos;
                }
            _size+=n;

            if(NULL != old_values)
                g_delete_array<T>(old_capacity, old_values);
            }
        }
    
    void insert(const iterator& position,const iterator& first,const iterator& last)
        {
        ptrdiff_t n = last-first;
        
        // If the following assertion fails, are you sure that 'last' is
        // reachable by 'first'?
        G_ASSERT(n>=0);
        
        if(_size+n > _capacity)
            {
            if(n>(ptrdiff_t)_capacity)
                capacity(_size+n);
            else
                capacity((_size+n)*2);
            }
        
        if(position._index < (ptrdiff_t)_size)
            {
            iterator from(this,_size-1);
            iterator to(this,_size-1+n);
            
            while(from._index >= position._index)
                {
                *to = *from;
                --to;
                --from;
                }
            }
        
        iterator pos = position;
        iterator current = first;
        while(current != last)
            {
            *pos = *current;
            ++current;
            ++pos;
            }
        _size+=n;
        }
    
    void insert(const iterator& position,const reverse_iterator& first,const reverse_iterator& last)
        {
        ptrdiff_t n = last-first;
        
        // If the following assertion fails, are you sure that 'last' is
        // reachable by 'first'?
        G_ASSERT(n>=0);
        
        if(_size+n > _capacity)
            {
            if(n>(ptrdiff_t)_capacity)
                capacity(_size+n);
            else
                capacity((_size+n)*2);
            }
        
        if(position._index < (ptrdiff_t)_size)
            {
            iterator from(this,_size-1);
            iterator to(this,_size-1+n);
            
            while(from._index >= position._index)
                {
                *to = *from;
                --to;
                --from;
                }
            }
        
        iterator pos = position;
        reverse_iterator current = first;
        while(current != last)
            {
            *pos = *current;
            ++current;
            ++pos;
            }
        _size+=n;
        }
    
    void erase(const iterator& position)
        {
        iterator ito = position;
        iterator ifrom = ito;
        ++ifrom;
        
        iterator e = end();
        while(ifrom != e)
            {
            *ito = *ifrom;
            ++ito;
            ++ifrom;
            }
        _size--;
        if(_size < _capacity/4)
            capacity(_size);
        }
    
    void erase(const iterator& first,const iterator& last)
        {
        ptrdiff_t n = last-first;
        iterator ito = first;
        iterator ifrom = ito+n;
        
        iterator e = end();
        while(ifrom != e)
            {
            *ito = *ifrom;
            ito++;
            ifrom++;
            }
        _size-=n;
        if(_size < _capacity/4)
            capacity(_size);
        }
    
    void clear() { erase(begin(),end()); }
    
    g_array<T>& operator=(const g_array<T>& right)
        {
        if(this == &right)
            return *this;
        if((_capacity < right._size) || (right._size < _capacity/4))
            capacity(right._size);
        _size = right._size;
        if(_size)
            g_no_overlap_copy(_size,_values,right._values);
        return *this;
        }
    
    bool operator==(const g_array<T>& right) const
        {
        if(this == &right)
            return true;

        if(_size != right._size)
            return false;
        
        for(size_t i = 0; i < _size; i++)
            {
            if(_values[i]!=right._values[i])
                return false;
            }

        return true;
        }
    
    bool operator!=(const g_array<T>& right) const
        { return !operator==(right); }
    
    // Purposefully omitted since T does not always have an operator<().
    // bool operator<(const g_array<T>& right) const
    //  {
    //  for(size_t i=0;i<_size && i<right._size;i++)
    //      if(_values[i]<right._values[i])
    //          return true;
    //  if(right._size > _size)
    //      return true;
    //  return false;
    //  }
    
    T&          operator[] (size_t index)               { G_ASSERT(index < _size); return _values[index]; }
    const T&    operator[] (size_t index) const         { G_ASSERT(index < _size); return _values[index]; }

#ifdef _WIN32
    T&          operator[] (unsigned long index)        { G_ASSERT(index < _size); return _values[index]; }
    const T&    operator[] (unsigned long index) const  { G_ASSERT(index < _size); return _values[index]; }


#ifdef _WIN64
    T&          operator[] (unsigned int index)         { G_ASSERT(index < _size); return _values[index]; }
    const T&    operator[] (unsigned int index) const   { G_ASSERT(index < _size); return _values[index]; }
#endif

    T&          operator[] (unsigned short index)       { G_ASSERT(index < _size); return _values[index]; }
    const T&    operator[] (unsigned short index) const { G_ASSERT(index < _size); return _values[index]; }

    // The G_ASSERT()s below cleverly check for indices that
    // are <0 and >=_size in one quick comparison.

    T&          operator[] (ptrdiff_t index)            { G_ASSERT((size_t)index < _size); return _values[index]; }
    const T&    operator[] (ptrdiff_t index) const      { G_ASSERT((size_t)index < _size); return _values[index]; }

    T&          operator[] (long index)                 { G_ASSERT((size_t)index < _size); return _values[index]; }
    const T&    operator[] (long index) const           { G_ASSERT((size_t)index < _size); return _values[index]; }

#ifdef _WIN64
    T&          operator[] (int index)                  { G_ASSERT(index < _size); return _values[index]; }
    const T&    operator[] (int index) const            { G_ASSERT(index < _size); return _values[index]; }
#endif

    T&          operator[] (short index)                { G_ASSERT((size_t)index < _size); return _values[index]; }
    const T&    operator[] (short index) const          { G_ASSERT((size_t)index < _size); return _values[index]; }
#endif

    operator T*         ()          { return _values; }
    operator const T*   () const    { return _values; }

          T *data()       { return _values; }
    const T *data() const { return _values; }

    void shrink_to_fit() { capacity(size()); }

protected:
    // This version of capacity() is for internal use only, for growing
    // the array without immediately destroying the old array.  The
    // calling function is responsible for calling g_delete_array<>.
    // The old values are always copied into the new storage.  The new
    // capacity is expected to be greater than _size.
    void capacity (size_t c, size_t &old_capacity,T *&old_values)
         {
         if(c == _capacity)
             return;

         G_ASSERT(c > _size);

         old_capacity = _capacity;
         old_values   = _values;

         _capacity = c;
         T* new_values   = g_new_array<T>(_capacity, NULL);
         if(!new_values)
            throw g_error(g_error::INSUFFICIENT_MEMORY,L"Insufficient Memory");

         _values = new_values;
         g_no_overlap_copy(_size, _values, old_values);
         }
    };

#endif
