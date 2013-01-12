#ifndef UNITTEST11_UTILITY_BASEOPERAND_HPP
#define UNITTEST11_UTILITY_BASEOPERAND_HPP

#include <type_traits>

namespace ut11
{
    namespace Utility
    {
        struct BaseOperand { };

        template<typename Operand> struct IsOperand
        {
            constexpr static bool value = std::is_base_of< BaseOperand, Operand >::value;
        };
    }
}

#endif // UNITTEST11_UTILITY_BASEOPERAND_HPP
