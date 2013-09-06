#ifndef UNITTEST11_UTILITY_AREEQUAL_HPP
#define UNITTEST11_UTILITY_AREEQUAL_HPP

#include "Meta/IsIterableContainer.hpp"

namespace ut11
{
	namespace Utility
	{
		template<typename A, typename B> inline bool AreEqual(const A& a, const B& b);

		/*! \brief Can be partially specialised to allow for comparing two types without providing an equality operator 
		 *
		 * \tparam A The left operand of the comparison
		 * \tparam B The right operand of the comparison
		 * \tparam IsAIterable True if A is determined by metaprogramming to be an iterable type
		 * \tparam IsBIterable True if B is determined by metaprogramming to be an iterable type
		 */
		template<typename A, typename B,
				 bool IsAIterable = Meta::IsIterableContainer<A>::value,
				 bool IsBIterable = Meta::IsIterableContainer<B>::value >
		struct Comparison
		{
			inline bool operator()(const A& a, const B& b) const
			{
				return a == b;
			}
		};

		template<typename A, typename B>
		struct Comparison<A,B,true,true>
		{
			inline bool operator()(const A& a, const B& b) const
			{
				auto i = a.begin();
				auto j = b.begin();

				for(;  i != a.end() && j != b.end(); ++i, ++j)
				{
					return AreEqual(*i, *j);
				}
				return i == a.end() && j == b.end();
			}
		};

		template<> struct Comparison<std::string, std::string, true, true>
		{
			inline bool operator()(const std::string& a, const std::string& b) const
			{
				return a == b;
			}
		};

		template<typename A, typename B> inline bool AreEqual(const A& a, const B& b)
		{
			return Comparison<A,B>()(a,b);
		}
	}
}

#endif // AREEQUAL_HPP
