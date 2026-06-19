
#ifndef _g_memory_h_
#define _g_memory_h_

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

#include "GeMS/dcl_gems.h"

class DECL_GEMS g_free_store
	{
	private:
		static g_free_store* _global_free_store;

	public:
		virtual ~g_free_store() {}

		virtual void* alloc(size_t) = 0;
		virtual void  free(void*) = 0;

		virtual void  maintain_free_list(bool f,size_t max_fast_size=4096) = 0;
		virtual bool  recycle_free_list() = 0;	// Free current free-list (if any) without
												// changing memory handling state.  Returns
												// true if any memory was freed.

		static g_free_store* get_default_global_free_store();
		static g_free_store* get_global_free_store() { return _global_free_store; }
		static void set_global_free_store(g_free_store* pFreeStore) { _global_free_store = pFreeStore; }
	};

class DECL_GEMS g_free_store_impl : public g_free_store
	{
	struct g_free_block
		{
		size_t size;
		g_free_block* next;
		};

	private:
		bool			_maintain_free_list;
		g_free_block**	_array;
		size_t          _array_size;
	
	public:
		g_free_store_impl(bool f=false,size_t max_fast_size = 4096);
		virtual ~g_free_store_impl();

		virtual void* alloc(size_t);
		virtual void  free(void*);

		virtual void  maintain_free_list(bool f,size_t max_fast_size=4096);
		virtual bool  recycle_free_list();	// Frees current free-list (if any) without
											// changing memory handling state.  Returns
											// true if any memory was freed.
	};


inline DECL_GEMS void*	g_alloc(size_t sz)		{ return g_free_store::get_global_free_store()->alloc(sz); }
inline DECL_GEMS void	g_free(void* p)			{ g_free_store::get_global_free_store()->free(p); }

inline DECL_GEMS void	g_maintain_free_list(bool f,size_t max_fast_size=4096)
					{ g_free_store::get_global_free_store()->maintain_free_list(f,max_fast_size); }
		// By default, the global value for 'maintain-free-list' is false,
		// because a free-list cannot be safely maintained for multithreaded
		// applications while still retaining all the speed benefits it offers.
		// (Even those using the apartment or course-grained multithreading model
		// are forbidden from maintaining a free-list.)  However, for single
		// threaded applications, GeMS++ execution can be sped up considerably
		// by passing a 'true' value into g_maintain_free_list().

inline DECL_GEMS bool	g_recycle_free_list()	{ return g_free_store::get_global_free_store()->recycle_free_list(); }
		// Frees memory blocks currently held in the free-list (if any) without
		// affecting whether a free-list will be maintained or not.

////////////////////////////////////////////////////////////
// g_prim_allocator
//   An allocator<> for primitive's (i.e. char, long, etc.)
//   or anything else that doesn't need a constructor.
//
template<class T>	class g_prim_allocator
	{
	public:
		typedef size_t size_type;
		typedef long difference_type;
		typedef T *pointer;
		typedef const T *const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T value_type;

		pointer address(reference pObj) const
			{ return (&pObj); }
		const_pointer address(const_reference rObj) const
			{ return (&rObj); }
		pointer allocate(size_type nBytes, const void *)
			{ return (pointer)g_alloc(nBytes); }
		void deallocate(void *pObj, size_type)
			{ g_free(pObj); }
		void construct(pointer pObj, const T& rVal)
			{ *pObj=rVal; }
		void destroy(pointer)
			{}
		size_type max_size() const
			{
			size_type _N = (size_type)(-1) / sizeof (T);
			return (0 < _N ? _N : 1);
			}

		// The following method is non-standard, but is
		// needed by Microsoft's STL, implementation. Yuk.
		char *_Charalloc(size_type nBytes)
			{ return (char*)g_alloc(nBytes); }

		bool operator==(const g_prim_allocator<T>&) const
			{ return true; } // One's as good as another. 
	};

////////////////////////////////////////////////////////////
// g_class_allocator
//   An allocator<> template for anything needing a
//   constructor.
template<class T>	class g_class_allocator
	{
	public:
		typedef size_t size_type;
		typedef long difference_type;
		typedef T *pointer;
		typedef const T *const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T value_type;

		class _TSub : public T
			{
			public:
				void* operator new(size_t sz,void* loc)
					{return loc;}
			};

		pointer address(reference pObj) const
			{ return (&pObj); }
		const_pointer address(const_reference rObj) const
			{ return (&rObj); }
		pointer allocate(size_type nBytes, const void *)
			{ return (pointer)g_alloc(nBytes); }
		void deallocate(void *pObj, size_type)
			{ g_free(pObj); }
		void construct(pointer pObj, const T& rVal)
			{ new (pObj) _TSub(rVal); }
		void destroy(pointer pObj)
			{ pObj->~T(); }
		size_type max_size() const
			{
			size_type _N = (size_type)(-1) / sizeof (T);
			return (0 < _N ? _N : 1);
			}

		// The following method is non-standard, but is
		// needed by Microsoft's STL, implementation. Yuk.
		char *_Charalloc(size_type nBytes)
			{ return (char*)g_alloc(nBytes); }

		bool operator==(const g_class_allocator<T>&) const
			{ return true; } // One's as good as another. 
	};

#endif
