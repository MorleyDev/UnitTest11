#ifndef UNITTEST11_UTILITY_TOSTRING_HPP
#define UNITTEST11_UTILITY_TOSTRING_HPP

#include <string>
#include <sstream>

namespace ut11
{
    namespace Utility
    {
        template<typename V> struct ParseToString
        {
            inline std::string operator()(const V& value) const
            {
                std::stringstream stream;
                stream << value;
                return stream.str();
            }
        };
        template<typename V> inline std::string ToString(const V& value) { return ParseToString<V>()(value); }
    }
}

#endif // UNITTEST11_UTILITY_TOSTRING_HPP
