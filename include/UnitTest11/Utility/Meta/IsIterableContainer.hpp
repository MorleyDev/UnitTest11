#ifndef UNITTEST11_utility_META_ISITERABLECONTAINER_HPP
#define UNITTEST11_utility_META_ISITERABLECONTAINER_HPP

#include <type_traits>
#include <cstdint>

namespace ut11
{
	namespace utility
	{
		namespace Meta
		{
			template<typename T>
			struct IsIterableContainer
			{
			private:
				typedef typename std::remove_const<T>::type test_type;

				template<typename U>
				static std::uint8_t test(U* pointer, 
										 U const* constPointer = nullptr,
										 decltype(pointer->begin())* = nullptr, 
										 decltype(pointer->end())* = nullptr,
										 decltype(pointer->begin())* = nullptr,
										 decltype(constPointer->end())* = nullptr,
										 typename U::iterator* = nullptr,
										 typename U::const_iterator* = nullptr,
										 typename U::value_type* = nullptr);

				template<typename A> static std::uint32_t test(...);

			public:
				enum : bool { value = sizeof(test<test_type>(nullptr)) == sizeof(std::uint8_t) };
			};
		}
	}
}

#endif // UNITTEST11_utility_META_ISITERABLECONTAINER_HPP
