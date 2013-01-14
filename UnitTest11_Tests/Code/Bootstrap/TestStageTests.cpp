#include <UnitTest11/Utility/TestStage.hpp>
#include <UnitTest11/Mock.hpp>
#include <UnitTest++/UnitTest++.h>
#include <iostream>

class FakeOutput : public ut11::IOutput
{
public:
    ~FakeOutput() { }

    ut11::Mock<void(std::string)> mockBeginFixture, mockEndFixture;

    ut11::Mock<void(std::string)> mockBeginGiven, mockEndGiven;
    ut11::Mock<void(std::string)> mockBeginWhen, mockEndWhen;
    ut11::Mock<void(std::string)> mockBeginThen, mockEndThen;
    ut11::Mock<void(std::string)> mockBeginFinally,  mockEndFinally;

    ut11::Mock<void (std::size_t, std::string, std::string)> mockOnError;
    ut11::Mock<void (std::exception)> mockOnError1;
    ut11::Mock<void (void)> mockOnUnknownError;

    ut11::Mock<void (void)> mockBegin;
    ut11::Mock<void (std::size_t,std::size_t)> mockEnd;

    virtual void Begin() { mockBegin(); }
    virtual void Finish(std::size_t ran, std::size_t succeeded) { mockEnd(ran, succeeded); }

    virtual void BeginFixture(std::string name) { mockBeginFixture(name); }
    virtual void EndFixture(std::string name) { mockEndFixture(name); }

    virtual void BeginGiven(std::string str) { mockBeginGiven(str); }
    virtual void EndGiven(std::string str) { mockEndGiven(str); }

    virtual void BeginWhen(std::string str) { mockBeginWhen(str); }
    virtual void EndWhen(std::string str) { mockEndWhen(str); }

    virtual void BeginThen(std::string str) { mockBeginThen(str); }
    virtual void EndThen(std::string str) { mockEndThen(str); }

    virtual void BeginFinally(std::string str) { mockBeginFinally(str); }
    virtual void EndFinally(std::string str) { mockEndFinally(str); }

    virtual void OnError(std::size_t line, std::string file, std::string message) { mockOnError(line, file, message); }
    virtual void OnError(const std::exception& ex) { mockOnError1(ex); }
    virtual void OnUnknownError() { mockOnUnknownError(); }

};

TEST(TestStageTest)
{
    std::string givenDescription = "given_description";
    std::string whenDescription = "when_description";
    std::string thenDescription = "then_description";
    std::string finallyDescription = "finally_description";

    ut11::Mock<void (void)> mockGiven;
    ut11::Mock<void (void)> mockWhen;
    ut11::Mock<void (void)> mockThen;
    ut11::Mock<void (void)> mockFinally;

    ut11::Utility::TestStep givenStep = { givenDescription, [&]() { mockGiven(); } };
    ut11::Utility::TestStep whenStep = { whenDescription, [&]() { mockWhen(); } };
    ut11::Utility::TestStep thenStep = { thenDescription, [&]() { mockThen(); } };
    ut11::Utility::TestStep finallyStep = { finallyDescription, [&]() { mockFinally(); } };

    ut11::Utility::TestStage stage(givenStep, whenStep, thenStep, finallyStep);

    FakeOutput output;
    CHECK(stage.Run(output));

    output.mockBeginGiven.Verify(__LINE__, __FILE__, givenDescription);
    mockGiven.Verify(__LINE__, __FILE__);
    output.mockEndGiven.Verify(__LINE__, __FILE__, givenDescription);

    output.mockBeginWhen.Verify(__LINE__, __FILE__, whenDescription);
    mockWhen.Verify(__LINE__, __FILE__);
    output.mockEndWhen.Verify(__LINE__, __FILE__, whenDescription);

    output.mockBeginThen.Verify(__LINE__, __FILE__, thenDescription);
    mockThen.Verify(__LINE__, __FILE__);
    output.mockEndThen.Verify(__LINE__, __FILE__, thenDescription);

    output.mockBeginFinally.Verify(__LINE__, __FILE__, finallyDescription);
    mockFinally.Verify(__LINE__, __FILE__);
    output.mockEndFinally.Verify(__LINE__, __FILE__, finallyDescription);

}

TEST(TestStageFailsWithTestExceptionTest)
{
    ut11::TestFailedException exception(__LINE__, __FILE__, "dsdsa");

    ut11::Utility::TestStep givenStep = { "description", [&]() { throw exception; } };
    ut11::Utility::TestStep whenStep = { "whenDescription", [&]() { } };
    ut11::Utility::TestStep thenStep = { "thenDescription", [&]() { } };
    ut11::Utility::TestStep finallyStep = { "finallyDescription", [&]() { } };

    ut11::Utility::TestStage stage(givenStep, whenStep, thenStep, finallyStep);

    FakeOutput output;
    CHECK(!stage.Run(output));

    output.mockOnError.Verify(__LINE__, __FILE__, exception.getLine(), exception.getFile(), exception.getMessage());
}

TEST(TestStageNoGivenOrNoWhenOrNoThenOrNoFinallyTest)
{
    std::string givenDescription = "given_description";
    std::string whenDescription = "when_description";
    std::string thenDescription = "then_description";
    std::string finallyDescription = "finally_description";

    ut11::Mock<void (void)> mockGiven;
    ut11::Mock<void (void)> mockWhen;
    ut11::Mock<void (void)> mockThen;
    ut11::Mock<void (void)> mockFinally;

    ut11::Utility::TestStep givenStep;
    ut11::Utility::TestStep whenStep;
    ut11::Utility::TestStep thenStep;
    ut11::Utility::TestStep finallyStep;

    ut11::Utility::TestStage stage(givenStep, whenStep, thenStep, finallyStep);

    FakeOutput output;
    CHECK(stage.Run(output));

}

TEST(TestStageFailsWithStdExceptionTest)
{
    std::bad_alloc exception;

    ut11::Utility::TestStep givenStep = { "description", [&]() { throw exception; } };
    ut11::Utility::TestStep whenStep = { "whenDescription", [&]() { } };
    ut11::Utility::TestStep thenStep = { "thenDescription", [&]() { } };
    ut11::Utility::TestStep finallyStep = { "finallyDescription", [&]() { } };

    ut11::Utility::TestStage stage(givenStep, whenStep, thenStep, finallyStep);

    FakeOutput output;
    CHECK(!stage.Run(output));

    output.mockOnError1.VerifyAny(__LINE__, __FILE__);
}


TEST(TestStageFailsWithUnknownExceptionTest)
{
    std::bad_alloc exception;

    ut11::Utility::TestStep givenStep = { "description", [&]() { throw "exception"; } };
    ut11::Utility::TestStep whenStep = { "whenDescription", [&]() { } };
    ut11::Utility::TestStep thenStep = { "thenDescription", [&]() { } };
    ut11::Utility::TestStep finallyStep = { "finallyDescription", [&]() { } };

    ut11::Utility::TestStage stage(givenStep, whenStep, thenStep, finallyStep);

    FakeOutput output;
    CHECK(!stage.Run(output));

    output.mockOnUnknownError.VerifyAny(__LINE__, __FILE__);
}
