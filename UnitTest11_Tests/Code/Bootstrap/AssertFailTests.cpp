#include <UnitTest11/Assert/Fail.hpp>
#include <UnitTest11/TestFailedException.hpp>

#include <UnitTest++/UnitTest++.h>

#include <string>

TEST(AssertFailTest)
{
    std::size_t line = 132;
    std::string file = "some file";
    std::string message = "some message";

    try
    {
        ut11::Assert::Fail(line, file, message);
    }
    catch(const ut11::TestFailedException& ex)
    {
        CHECK_EQUAL(line, ex.getLine());
        CHECK_EQUAL(file, ex.getFile());
        CHECK_EQUAL(message, ex.getMessage());
        return;
    }

    CHECK(false);
}
