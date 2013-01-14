#include <UnitTest11/Assert/Fail.hpp>

void ut11::Assert::Fail(std::size_t line, std::string file, std::string message)
{
    throw ut11::TestFailedException(line, file, message);
}
