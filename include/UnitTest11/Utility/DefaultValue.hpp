#ifndef UNITTEST11_UTILITY_DEFAULTVALUE_HPP
#define UNITTEST11_UTILITY_DEFAULTVALUE_HPP

namespace ut11
{
	namespace Utility
	{
		/*! \brief Can be partially specialised to specify the default value of a custom type to be used by the Mock functor for what to return by default */
		template<typename T> struct DefaultValue { inline T operator()() const { return T(); } };
	}
}

#endif // UNITTEST11_UTILITY_DEFAULTVALUE_HPP
