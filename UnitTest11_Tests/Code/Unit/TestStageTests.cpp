#include <UnitTest11.hpp>

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

class TestStageTests : public ut11::TestFixture
{
private:
    std::string givenDescription;
    std::string whenDescription;
    std::string thenDescription;
    std::string finallyDescription;

    ut11::Mock<void (void)> mockGiven;
    ut11::Mock<void (void)> mockWhen;
    ut11::Mock<void (void)> mockThen;
    ut11::Mock<void (void)> mockFinally;

    ut11::Utility::TestStep givenStep;
    ut11::Utility::TestStep whenStep;
    ut11::Utility::TestStep thenStep;
    ut11::Utility::TestStep finallyStep;

    ut11::Utility::TestStage Stage;

    FakeOutput output;
    ut11::TestFailedException testException;
    std::bad_alloc stdException;

    bool result;

public:
    virtual void Run()
    {
        Given("a Stage composed of a given, when, then and finally steps with descriptions", [&]() {

            givenDescription = "given_description";
            whenDescription = "when_description";
            thenDescription = "then_description";
            finallyDescription = "finally_description";

            mockGiven = ut11::Mock<void (void)>();
            mockWhen = ut11::Mock<void (void)>();
            mockThen = ut11::Mock<void (void)>();
            mockFinally = ut11::Mock<void (void)>();

            givenStep = ut11::Utility::TestStep( givenDescription, [&]() { mockGiven(); } );
            whenStep = ut11::Utility::TestStep( whenDescription, [&]() { mockWhen(); } );
            thenStep = ut11::Utility::TestStep( thenDescription, [&]() { mockThen(); } );
            finallyStep =ut11::Utility::TestStep( finallyDescription, [&]() { mockFinally(); } );

            Stage = ut11::Utility::TestStage(givenStep, whenStep, thenStep, finallyStep);

            output = FakeOutput();
            result = false;
        });

        When("running a Stage with an output", [&]() {

            result = Stage.Run(output);
        });

        Then("the result is true", [&]() {
            AssertThat(result, ut11::Is::True);
        });

        Then("the given occurred as expected", [&]() {

            output.mockBeginGiven.Verify(__LINE__, __FILE__, givenDescription);
            mockGiven.Verify(__LINE__, __FILE__);
            output.mockEndGiven.Verify(__LINE__, __FILE__, givenDescription);
        });

        Then("the when occurred as expected", [&]() {

            output.mockBeginWhen.Verify(__LINE__, __FILE__, whenDescription);
            mockWhen.Verify(__LINE__, __FILE__);
            output.mockEndWhen.Verify(__LINE__, __FILE__, whenDescription);
        });

        Then("the then occurred as expected", [&]() {

            output.mockBeginThen.Verify(__LINE__, __FILE__, thenDescription);
            mockThen.Verify(__LINE__, __FILE__);
            output.mockEndThen.Verify(__LINE__, __FILE__, thenDescription);
        });

        Then("the finally occurred as expected", [&]() {

            output.mockBeginFinally.Verify(__LINE__, __FILE__, finallyDescription);
            mockFinally.Verify(__LINE__, __FILE__);
            output.mockEndFinally.Verify(__LINE__, __FILE__, finallyDescription);
        });

        When("running a Stage with an output that throws a Test Exception", [&]() {

            testException = ut11::TestFailedException(__LINE__, __FILE__, "dsdsa");
            mockThen.SetCallback([&]() { throw testException; });

            result = Stage.Run(output);
        });

        Then("the result is false", [&]() {
            AssertThat(result, ut11::Is::False);
        });

        Then("Output.OnError was called as expected", [&]() {
            output.mockOnError.Verify(__LINE__, __FILE__, testException.GetLine(), testException.GetFile(), testException.GetMessage());
        });


        When("running a Stage with an output that throws a std::exception", [&]() {

            mockThen.SetCallback([&]() { throw stdException; });

            result = Stage.Run(output);
        });

        Then("the result is false", [&]() {
            AssertThat(result, ut11::Is::False);
        });

        Then("Output.OnError was called as expected", [&]() {
            output.mockOnError1.Verify(__LINE__, __FILE__, ut11::Is::Any<std::exception>());
        });

        When("running a Stage with an output that throws an unknown exception", [&]() {

            mockThen.SetCallback([&]() { throw "unknown exception"; });

            result = Stage.Run(output);
        });

        Then("the result is false", [&]() {
            AssertThat(result, ut11::Is::False);
        });

        Then("Output.OnError was called as expected", [&]() {
            output.mockOnUnknownError.Verify(__LINE__, __FILE__);
        });

        When("calling run with all Stages as invalid functions", [&]() {

            ut11::Utility::TestStep invalid;
            Stage = ut11::Utility::TestStage(invalid,invalid,invalid,invalid);
            result = Stage.Run(output);
        });

        Then("the result is true", [&]() {
            AssertThat(result, ut11::Is::True);
        });
    }
};
DeclareFixture(TestStageTests);
