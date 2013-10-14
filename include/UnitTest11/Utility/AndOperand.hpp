#ifndef UT11_utility_ANDOPERAND_HPP_INCLUDED
#define UT11_utility_ANDOPERAND_HPP_INCLUDED

#include <string>

namespace ut11
{
	namespace utility
	{
		template<typename T> struct BaseOperand;

		template<typename Op1, typename Op2> struct AndOperand : public BaseOperand<AndOperand<Op1, Op2>>
		{
			Op1 operand1;
			Op2 operand2;

			AndOperand(const Op1& op1, const Op2& op2)
				: operand1(op1),
			      operand2(op2)
			{
			}

			template<typename T> bool operator()(const T& actual) const
			{
				return operand1(actual) && operand2(actual);
			}

			template<typename T> inline std::string GetErrorMessage(const T& actual) const
			{
				std::string errorMessage("Expected And failed: \n");
				if (!operand1(actual))
					errorMessage += operand1.GetErrorMessage(actual);
				if (!operand2(actual))
					errorMessage += operand2.GetErrorMessage(actual);
				return errorMessage;
			}
		};
	}
}

#endif // UT11_utility_ANDOPERAND_HPP_INCLUDED
