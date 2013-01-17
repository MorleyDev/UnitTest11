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

    ut11::Utility::TestStage stage;

    FakeOutput output;
    ut11::TestFailedException testException;
    std::bad_alloc stdException;

    bool result;

public:
    virtual void Run()
    {
        Given("a stage composed of a given, when, then and finally steps with descriptions", [&]() {

            givenDescription = "given_description";
            whenDescription = "when_description";
            thenDescription = "then_description";
            finallyDescription = "finally_description";

            mockGiven = ut11::Mock<void (void)>();
            mockWhen = ut11::Mock<void (void)>();
            mockThen = ut11::Mock<void (void)>();
            mockFinally = ut11::Mock<void (void)>();

            givenStep = { givenDescription, [&]() { mockGiven(); } };
            whenStep = { whenDescription, [&]() { mockWhen(); } };
            thenStep = { thenDescription, [&]() { mockThen(); } };
            finallyStep = { finallyDescription, [&]() { mockFinally(); } };

            stage = ut11::Utility::TestStage(givenStep, whenStep, thenStep, finallyStep);

            output = FakeOutput();
            result = false;
        });

        When("running a stage with an output", [&]() {

            result = stage.Run(output);
        });

        Then("the result is true", [&]() {
            AssertThat(result, ut11::Is::True);
        });

        Then("the given occured as expected", [&]() {

            output.mockBeginGiven.Verify(__LINE__, __FILE__, givenDescription);
            mockGiven.Verify(__LINE__, __FILE__);
            output.mockEndGiven.Verify(__LINE__, __FILE__, givenDescription);
        });

        Then("the when occured as expected", [&]() {

            output.mockBeginWhen.Verify(__LINE__, __FILE__, whenDescription);
            mockWhen.Verify(__LINE__, __FILE__);
            output.mockEndWhen.Verify(__LINE__, __FILE__, whenDescription);
        });

        Then("the then occured as expected", [&]() {

            output.mockBeginThen.Verify(__LINE__, __FILE__, thenDescription);
            mockThen.Verify(__LINE__, __FILE__);
            output.mockEndThen.Verify(__LINE__, __FILE__, thenDescription);
        });

        Then("the finally occured as expected", [&]() {

            output.mockBeginFinally.Verify(__LINE__, __FILE__, finallyDescription);
            mockFinally.Verify(__LINE__, __FILE__);
            output.mockEndFinally.Verify(__LINE__, __FILE__, finallyDescription);
        });

        When("running a stage with an output that throws a Test Exception", [&]() {

            testException = ut11::TestFailedException(__LINE__, __FILE__, "dsdsa");
            mockThen.setCallback([&]() { throw testException; });

            result = stage.Run(output);
        });

        Then("the result is false", [&]() {
            AssertThat(result, ut11::Is::False);
        });

        Then("Output.OnError was called as expected", [&]() {
            output.mockOnError.Verify(__LINE__, __FILE__, testException.getLine(), testException.getFile(), testException.getMessage());
        });


        When("running a stage with an output that throws a std::exception", [&]() {

            mockThen.setCallback([&]() { throw stdException; });

            result = stage.Run(output);
        });

        Then("the result is false", [&]() {
            AssertThat(result, ut11::Is::False);
        });

        Then("Output.OnError was called as expected", [&]() {
            output.mockOnError1.Verify(__LINE__, __FILE__, ut11::Is::Any<std::exception>());
        });

        When("running a stage with an output that throws an unknown exception", [&]() {

            mockThen.setCallback([&]() { throw "unknown exception"; });

            result = stage.Run(output);
        });

        Then("the result is false", [&]() {
            AssertThat(result, ut11::Is::False);
        });

        Then("Output.OnError was called as expected", [&]() {
            output.mockOnUnknownError.Verify(__LINE__, __FILE__);
        });

        When("calling run with all stages as invalid functions", [&]() {

            ut11::Utility::TestStep invalid;
            stage = ut11::Utility::TestStage(invalid,invalid,invalid,invalid);
            result = stage.Run(output);
        });

        Then("the result is true", [&]() {
            AssertThat(result, ut11::Is::True);
        });
    }
};
DeclareFixture(TestStageTests);
