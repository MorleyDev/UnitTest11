#ifndef UNITTEST11_IS_BETWEEN_HPP
#define UNITTEST11_IS_BETWEEN_HPP

#include "../Utility/BaseOperand.hpp"

namespace ut11
{
    namespace Operands
    {
        template<typename U, typename V>
        struct IsBetween : public Utility::BaseOperand
        {
            const U& low;
            const V& high;

            IsBetween(const U& low, const V& high) : low(low), high(high) { }

            template<typename T> inline bool operator()(const T& value) const { return low < value && value <= high; }
        };
    }

    namespace Is
    {
        template<typename U, typename V> inline Operands::IsBetween<U,V> Between(const U& low, const V& high)
        {
            return Operands::IsBetween<U,V>(low, high);
        }

        namespace Not
        {
            template<typename U, typename V> inline Utility::NotOperand< Operands::IsBetween<U,V> > Between(const U& low, const V& high)
            {
                return Utility::NotOperand< Operands::IsBetween<U,V> >(low, high);
            }
        }
    }
}

#endif // UNITTEST11_IS_BETWEEN_HPP
