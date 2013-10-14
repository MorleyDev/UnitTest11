#ifndef UT11_DETAIL_NOTOPERAND_HPP_INCLUDED
#define UT11_DETAIL_NOTOPERAND_HPP_INCLUDED

#include <string>

namespace ut11
{
	namespace detail
	{
		template<typename T> struct BaseOperand;

		template<typename Op1> struct NotOperand : public BaseOperand<NotOperand<Op1>>
		{
			Op1 operand;

			explicit NotOperand(const Op1& op1)
				: operand(op1)
			{
			}

			template<typename T> bool operator()(const T& actual) const
			{
				return !operand(actual);
			}

			template<typename T> inline std::string GetErrorMessage(const T& actual) const
			{
				std::string errorMessage("Expected Not failed: \n");
				errorMessage += operand.GetErrorMessage(actual);
				return errorMessage;
			}
		};
	}
}

#endif // UT11_DETAIL_NOTOPERAND_HPP_INCLUDED
