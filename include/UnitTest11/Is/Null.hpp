#ifndef UNITTEST11_IS_NULL_HPP
#define UNITTEST11_IS_NULL_HPP

#include "../detail/BaseOperand.hpp"
#include "../utility/ToString.hpp"

#include <memory>
#include <sstream>

namespace ut11
{
	namespace Operands
	{
		struct IsNull : public detail::BaseOperand<IsNull>
		{
			template<typename U> bool operator()(std::weak_ptr<U> value) const
			{
				return value.lock() == std::shared_ptr<U>(nullptr);
			}

			template<typename U> bool operator()(const U& value) const
			{
				return value == U(nullptr);
			}

			template<typename U> inline std::string GetErrorMessage(const U& actual) const
			{
				std::stringstream errorMessage;
				errorMessage << "Expected null but was " << ut11::utility::ToString(actual);
				return errorMessage.str();
			}
		};
	}

	namespace Is
	{
		/*! \brief Operand returns true if Actual is null, otherwise false */
		extern Operands::IsNull Null;

		namespace Not
		{
			/*! \brief Operand returns true if Actual is not null, otherwise false */
			extern detail::NotOperand<Operands::IsNull> Null;
		}
	}
}

#endif // UNITTEST11_IS_NULL_HPP
