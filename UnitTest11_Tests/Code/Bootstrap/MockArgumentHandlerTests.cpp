#include <UnitTest11/Utility/MockArgumentHandler.hpp>
#include <UnitTest11/Is/EqualTo.hpp>
#include <UnitTest++/UnitTest++.h>

TEST(MockArgumentHandlerTest)
{
    ut11::Utility::MockArgumentHandler<int> argumentHandler;

    int expectedCalls[] = { 5, 7 };

    argumentHandler.AddCall(expectedCalls[0]);
    argumentHandler.AddCall(expectedCalls[0]);
    argumentHandler.AddCall(expectedCalls[0]);
    argumentHandler.AddCall(expectedCalls[1]);

    CHECK_EQUAL(4, argumentHandler.TotalCount());
    CHECK_EQUAL(3, argumentHandler.CountCalls(expectedCalls[0]) );
    CHECK_EQUAL(1, argumentHandler.CountCalls(expectedCalls[1]) );
    CHECK_EQUAL(0, argumentHandler.CountCalls(12) );
}

TEST(MockArgumentHandlerOperandTest)
{
    ut11::Utility::MockArgumentHandler<int> argumentHandler;

    int expectedCalls[] = { 5, 7 };

    argumentHandler.AddCall(expectedCalls[0]);
    argumentHandler.AddCall(expectedCalls[0]);
    argumentHandler.AddCall(expectedCalls[0]);
    argumentHandler.AddCall(expectedCalls[1]);

    CHECK_EQUAL(4, argumentHandler.TotalCount());
    CHECK_EQUAL(3, argumentHandler.CountCalls(ut11::Is::EqualTo(expectedCalls[0])));
    CHECK_EQUAL(1, argumentHandler.CountCalls(ut11::Is::EqualTo(expectedCalls[1])));
    CHECK_EQUAL(0, argumentHandler.CountCalls(ut11::Is::EqualTo(23)));
}
