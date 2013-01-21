#ifndef UNITTEST11_IS_GREATERTHAN_HPP
#define UNITTEST11_IS_GREATERTHAN_HPP

#include "../Utility/BaseOperand.hpp"

namespace ut11
{
    namespace Operands
    {
        template<typename U>
        struct IsGreaterThan : public Utility::BaseOperand
        {
            const U& low;

            IsGreaterThan(const U& low) : low(low) { }

            template<typename T> inline bool operator()(const T& value) const { return value > low; }
        };
    }

    namespace Is
    {
        template<typename U> inline Operands::IsGreaterThan<U> GreaterThan(const U& low)
        {
            return Operands::IsGreaterThan<U>(low);
        }

        namespace Not
        {
            template<typename U> inline Utility::NotOperand< Operands::IsGreaterThan<U> > GreaterThan(const U& low)
            {
                return Utility::NotOperand< Operands::IsGreaterThan<U> >(low);
            }
        }
    }
}

#endif // UNITTEST11_IS_GREATERTHAN_HPP
