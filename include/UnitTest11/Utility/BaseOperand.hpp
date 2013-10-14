#ifndef UNITTEST11_UTILITY_BASEOPERAND_HPP
#define UNITTEST11_UTILITY_BASEOPERAND_HPP

#include "AndOperand.hpp"
#include "OrOperand.hpp"
#include "NotOperand.hpp"

#include <type_traits>
#include <string>

namespace ut11
{
	namespace utility
	{
		template<typename T> struct BaseOperand 
		{
			typedef T self;

			/*! \brief Returns an operand that composes both operands and will pass if both internal operands pass */
			template<typename U> AndOperand<T, U> operator&&(const U& o2) const
			{
				return AndOperand<T, U>(*static_cast<const T*>(this), o2);
			}

			/*! \brief Returns an operand that composes both operands and will pass if at least one of the internal operands pass */
			template<typename U> OrOperand<T, U> operator||(const U& o2) const
			{
				return OrOperand<T, U>(*static_cast<const T*>(this), o2);
			}

			/*! \brief Returns an operand that takes the operand and will pass if the operand fails */
			NotOperand<T> operator!() const
			{
				return NotOperand<T>(*static_cast<const T*>(this));
			}
		};

		template<typename Operand> struct IsOperand
		{
			enum : bool { value = std::is_base_of< BaseOperand<Operand>, Operand >::value };
		};
	}
}

#endif // UNITTEST11_UTILITY_BASEOPERAND_HPP
