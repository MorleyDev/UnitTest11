#ifndef UNITTEST11_UTILITY_TOSTRING_HPP
#define UNITTEST11_UTILITY_TOSTRING_HPP

#include "Meta/IsIterableContainer.hpp"
#include "Meta/IfElseTypes.hpp"

#include <memory>
#include <string>
#include <sstream>

namespace ut11
{
    namespace Utility
    {
    	template<typename V> inline std::string ToString(const V& value);

        template<typename T, typename = decltype(std::declval<std::ostream&>() << std::declval<T const&>())>
        std::true_type IsStreamWritable(const T&)
        {
            return std::true_type();
        }

        template<typename T, typename... Ignored>
        std::false_type IsStreamWritable(const T&, Ignored const&..., ...)
        {
            return std::false_type();
        }

        template<typename V> struct ParseNonIterableToString
        {
            inline std::string operator()(const V& value) const
            {
                return ToString(value, IsStreamWritable<V>(value));
            }

            inline std::string ToString(const V& value, std::true_type) const
            {
                std::stringstream stream;
                stream << value;
                return stream.str();
            }

            inline std::string ToString(const V& value, std::false_type) const
            {
                std::stringstream stream;
                stream << "[" << typeid(V).name() << "]";
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
                    stream << ToString(arg) << " ";
                stream << "}";
                return stream.str();
            }
        };

		/*! \brief Can be partially specialised to parse non-streamables to strings without making the type streamable */
        template<typename V> struct ParseToString
        {
            inline std::string operator()(const V& value) const
            {
				return typename Meta::IfElseTypes< Meta::IsIterableContainer<V>::value, ParseIterableToString<V>, ParseNonIterableToString<V> >::type()(value);
            }
        };

        template<> struct ParseToString<std::string>
        {
            inline std::string operator()(const std::string& value) const
            {
                return value;
            }
        };


        template<> struct ParseToString< void* >
        {
            inline std::string operator()(void* value) const
            {
                return value ? std::string("void_pointer:") + ParseNonIterableToString<void*>()(value) : "nullptr";
            }
        };
        template<typename T> struct ParseToString< T* >
        {
            inline std::string operator()(T* value) const
            {
                return value ? std::string("pointer:") + ParseToString<T>()(*value) : "nullptr";
            }
        };

        template<typename T, typename U> struct ParseToString< std::unique_ptr<T,U> >
        {
            inline std::string operator()(const std::unique_ptr<T,U>& value) const
            {
                return value ? std::string("unique_ptr:") + ParseToString<T>()(*value) : "nullptr";
            }
        };

        template<> struct ParseToString< std::shared_ptr<void> >
        {
            inline std::string operator()(const std::shared_ptr<void>& value) const
            {
                return value ? std::string("shared_ptr<void>:") + ParseNonIterableToString<void*>()(value.get()) : "nullptr";
            }
        };
        template<typename T> struct ParseToString< std::shared_ptr<T> >
        {
            inline std::string operator()(const std::shared_ptr<T>& value) const
            {
                return value ? std::string("shared_ptr:") + ParseToString<T>()(*value) : "nullptr";
            }
        };

        template<typename V> inline std::string ToString(const V& value)
        {
            return ParseToString<V>()(value);
        }
    }
}

#endif // UNITTEST11_UTILITY_TOSTRING_HPP
