#ifndef UNITTEST11_UTILITY_TOSTRING_HPP
#define UNITTEST11_UTILITY_TOSTRING_HPP

#include <string>
#include <sstream>

namespace ut11
{
    namespace Utility
    {
		template<typename> struct VoidType { typedef void type; };
		template<typename T, typename Sfinae = void> struct HasBeginFunction : std::false_type {};
		template<typename T> struct HasBeginFunction<T, typename VoidType< decltype( std::declval<const T&>().begin() ) >::type> : std::true_type {};
		template<typename T, typename Sfinae = void> struct HasEndFunction : std::false_type {};
		template<typename T> struct HasEndFunction<T, typename VoidType< decltype( std::declval<const T&>().end() ) >::type> : std::true_type {};

		template<bool First, typename A, typename B> struct IfElseTypes { typedef A type; };
		template<typename A, typename B> struct IfElseTypes<false,A,B> { typedef B type; };

		template<typename T> struct IsIterable
		{
			constexpr static bool value = std::is_base_of<std::true_type, HasBeginFunction<T> >::value && std::is_base_of<std::true_type, HasEndFunction<T> >::value;
		};

        template<typename V> struct ParseToString
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

        template<> struct ParseIterableToString<std::string>
        {
            inline std::string operator()(const std::string& value) const
            {
                return value;
            }
        };

        template<typename V> inline std::string ToString(const V& value)
        {
        	return typename IfElseTypes< IsIterable<V>::value,
        								 ParseIterableToString<V>,
        								 ParseToString<V>
        							   >::type()(value);
        }
    }
}

#endif // UNITTEST11_UTILITY_TOSTRING_HPP
