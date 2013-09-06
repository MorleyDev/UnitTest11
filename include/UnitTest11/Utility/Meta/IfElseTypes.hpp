/*
 * IfElseTypes.hpp
 *
 *  Created on: 23 Apr 2013
 *	  Author: Jason
 */

#ifndef UT11_UTILITY_META_IFELSETYPES_HPP_INCLUDED
#define UT11_UTILITY_META_IFELSETYPES_HPP_INCLUDED

namespace ut11
{
	namespace Utility
	{
		namespace Meta
		{
			template<bool First, typename A, typename B> struct IfElseTypes { typedef A type; };
			template<typename A, typename B> struct IfElseTypes<false,A,B> { typedef B type; };
		}
	}
}

#endif /* UT11_UTILITY_IFELSETYPES_HPP_INCLUDED */
