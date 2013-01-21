#ifndef UNITTEST11_IS_LESSTHAN_HPP
#define UNITTEST11_IS_LESSTHAN_HPP

#include "../Utility/BaseOperand.hpp"

namespace ut11
{
    namespace Operands
    {
        template<typename U>
        struct IsLessThan : public Utility::BaseOperand
        {
            const U& high;

            IsLessThan(const U& high) : high(high) { }

            template<typename T> inline bool operator()(const T& value) const { return value < high; }
        };
    }

    namespace Is
    {
        template<typename U> inline Operands::IsLessThan<U> LessThan(const U& high)
        {
            return Operands::IsLessThan<U>(high);
        }

        namespace Not
        {
            template<typename U> inline Utility::NotOperand< Operands::IsLessThan<U> > LessThan(const U& high)
            {
                return Utility::NotOperand< Operands::IsLessThan<U> >(high);
            }
        }
    }
}

#endif // UNITTEST11_IS_LESSTHAN_HPP
