#ifndef UNITTEST11_ASSERT_THAT_HPP
#define UNITTEST11_ASSERT_THAT_HPP

#include "Fail.hpp"
#include <string>

namespace ut11
{
	namespace Assert
	{
		template<typename Expected, typename Operand>
		inline void That(std::size_t line, std::string file, const Expected& expected, const Operand& operand)
		{
			if ( operand(expected) )
				return;
			Fail(line, file, operand.GetErrorMessage(expected));
		}

		template<typename Expected, typename Operand>
		inline void That(std::size_t line, std::string file, std::string message, const Expected& expected, const Operand& operand)
		{
			if ( operand(expected) )
				return;
			Fail(line, file, message);
		}
	}
}

#endif // UNITTEST11_ASSERT_THAT_HPP
