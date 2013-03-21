#ifndef UNITTEST11_IS_STRING_CONTAINING_HPP
#define UNITTEST11_IS_STRING_CONTAINING_HPP

namespace ut11
{
	namespace Operands
	{
        struct IsStringContaining : public ut11::Utility::BaseOperand
        {
        	std::string m_expected;

        	IsStringContaining(const std::string& expected)
        		: m_expected(expected)
			{
			}

            bool operator()(const std::string& actual) const
            {
                return actual.find(m_expected) != std::string::npos;
            }

            inline std::string GetErrorMessage(const std::string& actual) const
            {
                std::stringstream errorMessage;
                errorMessage << "Expected string containing " << actual << " but was " << m_expected;
                return errorMessage.str();
            }
        };
	}

	namespace Is
	{
		namespace String
		{
			/*! \brief Operand returns true if string contains expected string, otherwise returns false */
			inline Operands::IsStringContaining Containing(std::string expected)
			{
				return Operands::IsStringContaining(expected);
			}
		}

		namespace Not
		{
			namespace String
			{
				/*! \brief Operand returns false if string contains expected string, otherwise returns true */
				inline Utility::NotOperand<Operands::IsStringContaining> Containing(std::string expected)
				{
					return Utility::NotOperand<Operands::IsStringContaining>(expected);
				}
			}
		}
	}
}

#endif /* UNITTEST11_IS_STRING_CONTAINING_HPP */
