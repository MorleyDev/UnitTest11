/*
 * EndingWith.hpp
 *
 *  Created on: 22 Apr 2013
 *      Author: Jason
 */

#ifndef UT11_IS_STRING_ENDINGWITH_HPP_INCLUDED
#define UT11_IS_STRING_ENDINGWITH_HPP_INCLUDED

#include <string>
#include <sstream>

namespace ut11
{
	namespace Operands
	{
        struct IsStringEndingWith : public ut11::Utility::BaseOperand
        {
        	std::string m_expected;

        	IsStringEndingWith(const std::string& expected)
        		: m_expected(expected)
			{
			}

        	inline bool operator()(const std::string& actual) const
            {
        		return ( actual.length() >= m_expected.length() && actual.substr(actual.length()-m_expected.length(), m_expected.length()) == m_expected);
            }

            inline std::string GetErrorMessage(const std::string& actual) const
            {
                std::stringstream errorMessage;
                errorMessage << "Expected string EndingWith " << m_expected << " but was " << actual;
                return errorMessage.str();
            }
        };
	}

	namespace Is
	{
		namespace String
		{
			/*! \brief Operand returns true if string ends with expected string, otherwise returns false */
			inline Operands::IsStringEndingWith EndingWith(std::string expected)
			{
				return Operands::IsStringEndingWith(expected);
			}

			namespace Not
			{
				/*! \brief Operand returns false if string ends with expected string, otherwise returns true */
				inline Utility::NotOperand<Operands::IsStringEndingWith> EndingWith(std::string expected)
				{
					return Utility::NotOperand<Operands::IsStringEndingWith>(expected);
				}
			}
		}
	}
}

#endif /* UT11_IS_STRING_ENDINGWITH_HPP_INCLUDED */
