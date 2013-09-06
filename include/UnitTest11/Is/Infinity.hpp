#ifndef UNITTEST11_IS_INFINITY_HPP
#define UNITTEST11_IS_INFINITY_HPP

#include "../Utility/BaseOperand.hpp"
#include "../Utility/ToString.hpp"

#include <cmath>
#include <sstream>
#include <limits>

namespace ut11
{
	namespace Operands
	{
		struct IsInfinity : public Utility::BaseOperand<IsInfinity>
		{
			template<typename U> bool operator()(const U& value) const
			{
				return  std::numeric_limits<U>::has_infinity && (std::numeric_limits<U>::infinity() == value || -std::numeric_limits<U>::infinity() == value);
			}

			template<typename U> inline std::string GetErrorMessage(const U& actual) const
			{
				std::stringstream errorMessage;
				errorMessage << "Expected infinity but was " << ut11::Utility::ToString(actual);
				return errorMessage.str();
			}
		};

		struct IsPositiveInfinity : public Utility::BaseOperand<IsPositiveInfinity>
		{
			template<typename U> bool operator()(const U& value) const
			{
				return IsInfinity().operator()<U>(value) && value >= 0;
			}

			template<typename U> inline std::string GetErrorMessage(const U& actual) const
			{
				std::stringstream errorMessage;
				errorMessage << "Expected positive infinity but was " << ut11::Utility::ToString(actual);
				return errorMessage.str();
			}
		};

		struct IsNegativeInfinity : public Utility::BaseOperand<IsNegativeInfinity>
		{
			template<typename U> bool operator()(const U& value) const
			{
				return IsInfinity().operator()<U>(value) && value <= 0;
			}

			template<typename U> inline std::string GetErrorMessage(const U& actual) const
			{
				std::stringstream errorMessage;
				errorMessage << "Expected negative infinity but was " << ut11::Utility::ToString(actual);
				return errorMessage.str();
			}
		};
	}

	namespace Is
	{
		/*! \brief Operand returns true if Actual is Positive or Negative Infinity, otherwise false */
		extern Operands::IsInfinity Infinity;

		/*! \brief Operand returns true if Actual is Positive Infinity, otherwise false */
		extern Operands::IsPositiveInfinity PositiveInfinity;

		/*! \brief Operand returns true if Actual is Negative Infinity, otherwise false */
		extern Operands::IsNegativeInfinity NegativeInfinity;

		namespace Not
		{
			/*! \brief Operand returns false if Actual is Positive or Negative Infinity, otherwise true */
			extern Utility::NotOperand<Operands::IsInfinity> Infinity;

			/*! \brief Operand returns false if Actual is Positive Infinity, otherwise true */
			extern Utility::NotOperand<Operands::IsPositiveInfinity> PositiveInfinity;

			/*! \brief Operand returns false if Actual is Negative Infinity, otherwise true */
			extern Utility::NotOperand<Operands::IsNegativeInfinity> NegativeInfinity;
		}
	}
}

#endif // UNITTEST11_IS_INFINITY_HPP
