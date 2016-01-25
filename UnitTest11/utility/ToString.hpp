#ifndef UNITTEST11_UTILITY_TOSTRING_HPP
#define UNITTEST11_UTILITY_TOSTRING_HPP

#include "Meta/IsIterableContainer.hpp"
#include "Meta/IfElseTypes.hpp"

#include <memory>
#include <string>
#include <sstream>

namespace ut11
{
	namespace utility
	{
		template<typename V> inline std::string ToString(const V& value);

		namespace detail
		{
			template<typename S, typename T>
			class IsStreamWritable
			{
				template<typename SS, typename TT>
				static auto test(int) -> decltype(std::declval<SS&>() << std::declval<TT>(), std::true_type());

				template<typename, typename> static auto test(...) -> std::false_type;

			public:
				typedef decltype(test<S, T>(0)) Result;
			};

			template<typename V> struct ParseNonIterableToString
			{
				inline std::string operator()(const V& value) const
				{
					return ToString(value, IsStreamWritable<std::stringstream, V>::Result());
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
					for (const auto& arg : value)
						stream << ToString(arg) << " ";
					stream << "}";
					return stream.str();
				}
			};
		}

		/*! \brief Can be partially specialised to parse non-streamables to strings without making the type streamable */
		template<typename V> struct ParseToString
		{
			inline std::string operator()(const V& value) const
			{
				return typename Meta::IfElseTypes< Meta::IsIterableContainer<V>::value, detail::ParseIterableToString<V>, detail::ParseNonIterableToString<V> >::type()(value);
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
				return value ? std::string("void_pointer:") + detail::ParseNonIterableToString<void*>()(value) : "nullptr";
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
				return value ? std::string("shared_ptr<void>:") + detail::ParseNonIterableToString<void*>()(value.get()) : "nullptr";
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
