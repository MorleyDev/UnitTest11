#ifndef UNITTEST11_IS_ZERO_HPP
#define UNITTEST11_IS_ZERO_HPP

#include "../detail/BaseOperand.hpp"
#include "../utility/ToString.hpp"
#include <sstream>

namespace ut11
{
	namespace Operands
	{
		struct IsZero : public detail::BaseOperand<IsZero>
		{
			template<typename U> bool operator()(const U& value) const
			{
				return value == U(0);
			}

			template<typename U> inline std::string GetErrorMessage(const U& actual) const
			{
				std::stringstream errorMessage;
				errorMessage << "Expected zero but was " << ut11::utility::ToString(actual);
				return errorMessage.str();
			}
		};
	}

	namespace Is
	{
		/*! \brief Operand returns true if Actual == 0, otherwise false */
		extern Operands::IsZero Zero;

		namespace Not
		{
			/*! \brief Operand returns true if Actual != 0, otherwise false */
			extern detail::NotOperand<Operands::IsZero> Zero;
		}
	}
}

#endif // UNITTEST11_IS_ZERO_HPP
