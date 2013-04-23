#ifndef UNITTEST11_UTILITY_TOSTRING_HPP
#define UNITTEST11_UTILITY_TOSTRING_HPP

#include "Meta/IfElseTypes.hpp"
#include "Meta/HasBeginAndEndFunctions.hpp"

#include <string>
#include <sstream>

namespace ut11
{
    namespace Utility
    {
        template<typename V> struct ParseNonIterableToString
        {
            inline std::string operator()(const V& value) const
            {
                std::stringstream stream;
                stream << value;
                return stream.str();
            }
        };

        template<typename V> struct ParseIterableToString
        {
            inline std::string operator()(const V& value) const
            {
                std::stringstream stream;
                stream << "{ ";
                for(const auto& arg : value)
                	stream << (int)arg << " ";
                stream << "}";
                return stream.str();
            }
        };

        template<typename V> struct ParseToString
        {
        	inline std::string operator()(const V& value) const
        	{
            	return typename Meta::IfElseTypes< Meta::HasBeginAndEndFunctions<V>::value, ParseIterableToString<V>, ParseNonIterableToString<V> >::type()(value);
        	}
        };

        template<> struct ParseToString<std::string>
        {
            inline std::string operator()(const std::string& value) const
            {
                return value;
            }
        };

        template<typename V> inline std::string ToString(const V& value)
        {
        	return ParseToString<V>()(value);
        }
    }
}

#endif // UNITTEST11_UTILITY_TOSTRING_HPP
