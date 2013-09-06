#ifndef UNITTEST11_ASSERT_FAIL_HPP
#define UNITTEST11_ASSERT_FAIL_HPP

#include <string>

namespace ut11
{
	namespace Assert
	{
		extern void Fail(std::size_t line, std::string file, std::string message);
	}
}

#endif // UNITTEST11_ASSERT_FAIL_HPP
