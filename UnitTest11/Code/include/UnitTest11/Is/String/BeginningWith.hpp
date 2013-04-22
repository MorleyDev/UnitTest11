#ifndef UT11_IS_STRING_BEGINNINGWITH_HPP_INCLUDED
#define UT11_IS_STRING_BEGINNINGWITH_HPP_INCLUDED

#include <string>
#include <sstream>

namespace ut11
{
	namespace Operands
	{
        struct IsStringBeginningWith : public ut11::Utility::BaseOperand
        {
        	std::string m_expected;

        	IsStringBeginningWith(const std::string& expected)
        		: m_expected(expected)
			{
			}

        	inline bool operator()(const std::string& actual) const
            {
        		return ( actual.length() >= m_expected.length() && actual.substr(0, m_expected.length()) == m_expected);
            }

            inline std::string GetErrorMessage(const std::string& actual) const
            {
                std::stringstream errorMessage;
                errorMessage << "Expected string BeginningWith " << actual << " but was " << m_expected;
                return errorMessage.str();
            }
        };
	}

	namespace Is
	{
		namespace String
		{
			/*! \brief Operand returns true if string contains expected string, otherwise returns false */
			inline Operands::IsStringBeginningWith BeginningWith(std::string expected)
			{
				return Operands::IsStringBeginningWith(expected);
			}
		}

		namespace Not
		{
			namespace String
			{
				/*! \brief Operand returns false if string contains expected string, otherwise returns true */
				inline Utility::NotOperand<Operands::IsStringBeginningWith> BeginningWith(std::string expected)
				{
					return Utility::NotOperand<Operands::IsStringBeginningWith>(expected);
				}
			}
		}
	}
}


#endif /* UT11_IS_STRING_BEGINNINGWITH_HPP_INCLUDED */
