#ifndef UNITTEST11_IS_NULL_HPP
#define UNITTEST11_IS_NULL_HPP

#include "../Utility/BaseOperand.hpp"
#include <memory>

namespace ut11
{
    namespace Operands
    {
        struct IsNull : public Utility::BaseOperand
        {
            template<typename U> bool operator()(std::weak_ptr<U> value) const
            {
                return value.lock() == std::shared_ptr<U>(nullptr);
            }

            template<typename U> bool operator()(const U& value) const
            {
                return value == U(nullptr);
            }

            template<typename U> inline std::string getErrorMessage(const U& actual) const
            {
                std::stringstream errorMessage;
                errorMessage << "Expected null but was " << ut11::Utility::ToString(actual);
                return errorMessage.str();
            }
        };
    }

    namespace Is
    {
        extern Operands::IsNull Null;

        namespace Not
        {
            extern Utility::NotOperand<Operands::IsNull> Null;
        }
    }
}

#endif // UNITTEST11_IS_NULL_HPP
