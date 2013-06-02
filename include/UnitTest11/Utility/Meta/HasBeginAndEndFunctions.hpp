/*
 * HasBeginAndEndFunctions.hpp
 *
 *  Created on: 23 Apr 2013
 *      Author: Jason
 */

#ifndef UT11_UTILITY_META_HASBEGINANDENDFUNCTIONS_HPP_INCLUDED
#define UT11_UTILITY_META_HASBEGINANDENDFUNCTIONS_HPP_INCLUDED

#include <utility>

namespace ut11
{
	namespace Utility
	{
    	namespace Meta
    	{
			template<typename> struct VoidType { typedef void type; };
			template<typename T, typename Sfinae = void> struct HasBeginFunction : std::false_type {};
			template<typename T, typename Sfinae = void> struct HasEndFunction : std::false_type {};

			template<typename T> struct HasBeginFunction<T, typename VoidType< decltype( std::declval<const T&>().begin() ) >::type> : std::true_type {};
			template<typename T> struct HasEndFunction<T, typename VoidType< decltype( std::declval<const T&>().end() ) >::type> : std::true_type {};

			template<typename T> struct HasBeginAndEndFunctions
			{
				constexpr static bool value = std::is_base_of<std::true_type, HasBeginFunction<T> >::value && std::is_base_of<std::true_type, HasEndFunction<T> >::value;
			};
    	}
	}
}



#endif /* UT11_UTILITY_META_HASBEGINANDENDFUNCTIONS_HPP_INCLUDED */
