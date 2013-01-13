#ifndef UNITTEST11_UTILITY_AREEQUAL_HPP
#define UNITTEST11_UTILITY_AREEQUAL_HPP

namespace ut11
{
    namespace Utility
    {
        template<typename A, typename B> struct Comparison
        {
            inline bool operator()(const A& a, const B& b) const
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
