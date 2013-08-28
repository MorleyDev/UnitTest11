#ifndef UNITTEST11_IS_STRING_CONTAINING_HPP
#define UNITTEST11_IS_STRING_CONTAINING_HPP

#include "../../Utility/BaseOperand.hpp"
#include <string>
#include <sstream>

namespace ut11
{
    namespace Operands
    {
		struct IsStringContainingSubstring : public ut11::Utility::BaseOperand<IsStringContainingSubstring>
        {
            std::string m_expected;

            IsStringContainingSubstring(const std::string& expected)
                : m_expected(expected)
            {
            }

            inline bool operator()(const std::string& actual) const
            {
                return actual.find(m_expected) != std::string::npos;
            }

            inline std::string GetErrorMessage(const std::string& actual) const
            {
                std::stringstream errorMessage;
                errorMessage << "Expected string containing " << m_expected << " but was " << actual;
                return errorMessage.str();
            }
        };

		struct IsStringContainingCharacter : public ut11::Utility::BaseOperand<IsStringContainingCharacter>
        {
            const char m_expected;

            IsStringContainingCharacter(const char expected)
                : m_expected(expected)
            {
            }

            inline bool operator()(const std::string& actual) const
            {
                return actual.find(m_expected) != std::string::npos;
            }

            inline std::string GetErrorMessage(const std::string& actual) const
            {
                std::stringstream errorMessage;
                errorMessage << "Expected string containing " << m_expected << " but was " << actual;
                return errorMessage.str();
            }
        };
    }

    namespace Is
    {
        namespace String
        {
            /*! \brief Operand returns true if string contains expected string, otherwise returns false */
            inline Operands::IsStringContainingSubstring Containing(std::string expected)
            {
                return Operands::IsStringContainingSubstring(expected);
            }

            /*! \brief Operand returns true if string contains expected character, otherwise returns false */
            inline Operands::IsStringContainingCharacter Containing(const char expected)
            {
                return Operands::IsStringContainingCharacter(expected);
            }

            namespace Not
            {
                /*! \brief Operand returns false if string contains expected string, otherwise returns true */
                inline Utility::NotOperand<Operands::IsStringContainingSubstring> Containing(std::string expected)
                {
                    return !Operands::IsStringContainingSubstring(expected);
                }

                /*! \brief Operand returns false if string contains expected character, otherwise returns true */
                inline Utility::NotOperand<Operands::IsStringContainingCharacter> Containing(const char expected)
                {
                    return !Operands::IsStringContainingCharacter(expected);
                }
            }
        }

    }
}

#endif /* UNITTEST11_IS_STRING_CONTAINING_HPP */
