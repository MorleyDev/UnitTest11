/*
 * IsIterableOfType.hpp
 *
 *  Created on: 23 Apr 2013
 *      Author: Jason
 */

#ifndef UT11_UTILITY_META_ISITERABLEOFTYPE_HPP_INCLUDED
#define UT11_UTILITY_META_ISITERABLEOFTYPE_HPP_INCLUDED

#include "HasBeginAndEndFunctions.hpp"

namespace ut11
{
	namespace Utility
	{
		namespace Meta
		{
			template<typename Iterable, typename Type, bool IsIterable = HasBeginAndEndFunctions<Iterable>::value > struct IsIterableOfType
			{
				typedef decltype( *(std::declval<Iterable>().begin()) ) Iterator;
				typedef typename std::remove_reference<Iterator>::type TIterator;
				constexpr static bool value = std::is_same<Type, TIterator>::value || std::is_base_of<Type, TIterator>::value;
			};

			template<typename A, typename B> struct IsIterableOfType<A,B,false>
			{
				constexpr static bool value = false;
			};
		}
	}
}


#endif /* UT11_UTILITY_META_ISITERABLEOFTYPE_HPP_INCLUDED */
