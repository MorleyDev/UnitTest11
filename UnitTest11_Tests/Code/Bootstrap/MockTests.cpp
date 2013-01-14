#include <UnitTest11/Mock.hpp>


#include <UnitTest++/UnitTest++.h>
#include <UnitTest11/TestFailedException.hpp>
#include <functional>

TEST(MockCallTest)
{
    ut11::Mock<int (char)> mock;

    bool bWasCallbackCalled = false;
    mock.setCallback([&](char c) { bWasCallbackCalled = true; CHECK_EQUAL(c, 'A'); });
    mock.setReturn(5);

    CHECK_EQUAL(5, mock('A'));
    CHECK(bWasCallbackCalled);

    mock.VerifyAny(__LINE__, __FILE__);
    mock.Verify(__LINE__, __FILE__, 'A');
    mock.VerifyTimes(__LINE__, __FILE__, 1, 'A');
}

TEST(MockCallVoidTest)
{
    ut11::Mock<void (void)> mock;

    mock();

    mock.Verify(__LINE__, __FILE__);
    mock.VerifyTimes(__LINE__, __FILE__, 1);
}

TEST(MockCallFailsTest)
{
    ut11::Mock<int (char)> mock;

    mock.setReturn(5);

    CHECK_EQUAL(5, mock('A'));

    try
    {
        mock.Verify(__LINE__, __FILE__, 'B');
    }
    catch(const ut11::TestFailedException& ex)
    {
        return;
    }

    CHECK(false);
}

TEST(MockCallFailsTimesTest)
{
    ut11::Mock<int (char)> mock;

    mock.setReturn(5);

    CHECK_EQUAL(5, mock('A'));

    try
    {
        mock.VerifyTimes(__LINE__, __FILE__, 2, 'A');
    }
    catch(const ut11::TestFailedException& ex)
    {
        return;
    }

    CHECK(false);
}

TEST(MockCallFailsAnyTest)
{
    ut11::Mock<int (char)> mock;

    try
    {
        mock.VerifyAny(__LINE__, __FILE__);
    }
    catch(const ut11::TestFailedException& ex)
    {
        return;
    }

    CHECK(false);
}
