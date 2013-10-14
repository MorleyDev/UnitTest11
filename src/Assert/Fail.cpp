#include <UnitTest11/Assert/Fail.hpp>
#include <UnitTest11/detail/TestFailedException.hpp>

void ut11::Assert::Fail(std::size_t line, std::string file, std::string message)
{
	throw ut11::detail::TestFailedException(line, file, message);
}
