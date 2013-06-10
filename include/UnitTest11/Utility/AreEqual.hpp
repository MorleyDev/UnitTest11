#ifndef UNITTEST11_UTILITY_AREEQUAL_HPP
#define UNITTEST11_UTILITY_AREEQUAL_HPP

#include "Meta/HasBeginAndEndFunctions.hpp"

namespace ut11
{
    namespace Utility
    {
    	template<typename A, typename B> inline bool AreEqual(const A& a, const B& b);

    	template<typename A, typename B,
    			 bool IsAIterable = Meta::HasBeginAndEndFunctions<A>::value,
    			 bool IsBIterable = Meta::HasBeginAndEndFunctions<B>::value>
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
            	auto j = a.begin();

            	for(;  i != a.end() && j != b.end(); ++i, ++j)
            	{
            		return AreEqual(*i, *j);
            	}
                return i == a.end() && j == b.end();
            }
    	};

        template<typename A, typename B> inline bool AreEqual(const A& a, const B& b)
        {
            return Comparison<A,B>()(a,b);
        }
    }
}

#endif // AREEQUAL_HPP
