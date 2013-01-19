#ifndef UNITTEST11_IS_FALSE_HPP
#define UNITTEST11_IS_FALSE_HPP

#include "../Utility/BaseOperand.hpp"
#include "../Utility/ToString.hpp"

#include <string>
#include <sstream>

namespace ut11
{
    namespace Operands
    {
        struct FalseOperand : public Utility::BaseOperand
        {
            template<typename T> bool operator()(const T& value) const { return !static_cast<bool>(value); }

            template<typename T> inline std::string getErrorMessage(const T& actual) const
            {
                std::stringstream errorMessage;
                errorMessage << "Expected false but was " << Utility::ToString(actual);
                return errorMessage.str();
            }
        };
    }

    namespace Is
    {
        extern Operands::FalseOperand False;
        namespace Not { extern Utility::NotOperand<Operands::FalseOperand> False; }
    }
}

#endif // UNITTEST11_IS_FALSE_HPP