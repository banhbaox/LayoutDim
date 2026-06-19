
#ifndef _sorted_ptr_container_h_
#define _sorted_ptr_container_h_

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

#include "GeMS/GemsFnd/Ptr.h"
#include "GeMS/GemsFnd/Gsubatom.h"
#include "GeMS/Containers/Ginsert.h"
#include "GeMS/Utility/Compare.h"
#include "GeMS/Containers/Avltree.h"

DECLARE_MINIMAL_GEMS_DLL_EXPORTS(GAtom,GEMS)
DECLARE_MINIMAL_GEMS_DLL_EXPORTS(GSortedTree,GEMS)
DECLARE_MINIMAL_GEMS_DLL_EXPORTS(GAvlTreeNode,GEMS)

class DECL_GEMS sorted_ptr_container_base : public ptr_container_base
	{
	public:
		typedef GAtom* value_type;

	private:
		comparator<GAtom>*	_comparator;
		bool				_allow_duplicates;

		GSortedTree* sorted_tree() const { return (GSortedTree*)container(); }

	protected:
		virtual GAvlTree* construct_container() const;

		void equal_range_iterators(const GAtom* p,sorted_ptr_container_base::iterator& f,sorted_ptr_container_base::iterator& s) const
			{ ptr_container_base::equal_range(p,f,s); }
		void equal_range_iterators(const self_comparator<GAtom>*,sorted_ptr_container_base::iterator& f,sorted_ptr_container_base::iterator& s) const;

		void find(ptr_container_base::iterator& i,const GAtom* p) const { ptr_container_base::find(i,p); }
		void find(ptr_container_base::iterator& i,const self_comparator<GAtom>*) const;

	private:
		// Do not allow copy constructor since behaviors  
		// should not simply be copied.  Do not implement this function.
		sorted_ptr_container_base(const sorted_ptr_container_base&);

	public:
		sorted_ptr_container_base(	const comparator<GAtom>* comp,	// content comparator.
									g_behaviors Behaviors,
									bool allow_duplicates);

		sorted_ptr_container_base(	const sorted_ptr_container_base&,	// container to copy.
									g_behaviors Behaviors);			// behaviors not copied.
			// This is as close as we can get to a copy constructor.

		~sorted_ptr_container_base();

		///////////////////////////////////
		// System methods
		sorted_ptr_container_base& operator=(const sorted_ptr_container_base& right);
 		bool operator==(const sorted_ptr_container_base& right) const;

		void stream(g_stream&);
			// The stream() method is rarely called directly.
			// Generally collections are streamed using the
			// aStream << aSet; syntax.

		///////////////////////////////////
		// Functional methods.
		const comparator<GAtom>* content_comparator() const { return _comparator; }

		bool contains(const GAtom* p) const { return ptr_container_base::contains(p); }
		bool contains(const self_comparator<GAtom>*) const;

		size_t count(const GAtom* p) const { return ptr_container_base::count(p); }
		size_t count(const self_comparator<GAtom>*) const;

		iterator find(const GAtom* p) const			{ return ptr_container_base::find(p); }
		iterator lower_bound(const GAtom* p) const	{ return ptr_container_base::lower_bound(p); }
		iterator upper_bound(const GAtom* p) const	{ return ptr_container_base::upper_bound(p); }
		erange equal_range(const GAtom* p) const	{ return ptr_container_base::equal_range(p); }

		iterator find(const self_comparator<GAtom>*) const;
		iterator lower_bound(const self_comparator<GAtom>*) const;
		iterator upper_bound(const self_comparator<GAtom>*) const;
		erange equal_range(const self_comparator<GAtom>*) const;

		size_type erase(GAtom* p)		    { return ptr_container_base::erase(p); }
		void erase(iterator& i)				{ ptr_container_base::erase(i); }
		void erase(iterator& f,iterator& s)	{ ptr_container_base::erase(f,s); }
		size_type erase(const self_comparator<GAtom>*);

		virtual void sort();
			// If the 'key' values of the elements contained
			// within the collection change, the collection
			// will have to be re-sorted.
	};

#endif
