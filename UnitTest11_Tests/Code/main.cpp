#include <UnitTest++/UnitTest++.h>
#include <UnitTest11.hpp>

int main()
{
    return UnitTest::RunAllTests() + ut11::Run();
}
