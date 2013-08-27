#ifndef UNITTEST11_IS_BETWEEN_HPP
#define UNITTEST11_IS_BETWEEN_HPP

#include "../Utility/BaseOperand.hpp"
#include "../Utility/ToString.hpp"
#include <sstream>

namespace ut11
{
    namespace Operands
    {
        template<typename U, typename V>
		struct IsBetween : public Utility::BaseOperand<IsBetween<U,V>>
        {
            const U& low;
            const V& high;

            IsBetween(const U& low, const V& high) : low(low), high(high) { }

            template<typename T> inline bool operator()(const T& value) const { return low < value && value <= high; }

            template<typename Q> inline std::string GetErrorMessage(const Q& actual) const
            {
                std::stringstream errorMessage;
                errorMessage << "Expected between " << ut11::Utility::ToString(low) << " and " << ut11::Utility::ToString(high) << " but was " << ut11::Utility::ToString(actual);
                return errorMessage.str();
            }
        };
    }

    namespace Is
    {
        /*! \brief Operand returns true if Actual is greater than or equal to low, and Actual is less than or equal to high, otherwise false */
        template<typename U, typename V> inline Operands::IsBetween<U,V> Between(const U& low, const V& high)
        {
            return Operands::IsBetween<U,V>(low, high);
        }

        namespace Not
        {
            /*! \brief Operand returns true if Actual is less than low, or Actual is greater than high, otherwise false */
            template<typename U, typename V> inline Utility::NotOperand< Operands::IsBetween<U,V> > Between(const U& low, const V& high)
            {
                return !Operands::IsBetween<U,V>(low, high);
            }
        }
    }
}

#endif // UNITTEST11_IS_BETWEEN_HPP
