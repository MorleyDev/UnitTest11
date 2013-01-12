#ifndef UNITTEST11_UTILITY_DEFAULTVALUE_HPP
#define UNITTEST11_UTILITY_DEFAULTVALUE_HPP

namespace ut11
{
    namespace Utility
    {
        template<typename T> struct DefaultValue { T operator()() const { return T(); } };
    }
}

#endif // UNITTEST11_UTILITY_DEFAULTVALUE_HPP
