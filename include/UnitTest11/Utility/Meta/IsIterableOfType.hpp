/*
 * IsIterableOfType.hpp
 *
 *  Created on: 23 Apr 2013
 *	  Author: Jason
 */

#ifndef UT11_UTILITY_META_ISITERABLEOFTYPE_HPP_INCLUDED
#define UT11_UTILITY_META_ISITERABLEOFTYPE_HPP_INCLUDED

#include "IsIterableContainer.hpp"
#include <type_traits>
#include <iterator>

namespace ut11
{
	namespace Utility
	{
		namespace Meta
		{
			template<typename Iterable, typename Type, bool IsIterable = IsIterableContainer<Iterable>::value > struct IsIterableOfType
			{
				typedef typename std::iterator_traits< decltype(std::declval<const Iterable&>().begin()) >::value_type Iterator;

				enum { value = std::is_same<Type, Iterator>::value || std::is_base_of<Type, Iterator>::value };
			};

			template<typename A, typename B> struct IsIterableOfType<A,B,false>
			{
				enum { value = false };
			};
		}
	}
}


#endif /* UT11_UTILITY_META_ISITERABLEOFTYPE_HPP_INCLUDED */
