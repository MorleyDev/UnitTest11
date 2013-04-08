#include <UnitTest11.hpp>

namespace
{
	class FakeOutput : public ut11::IOutput
	{
	public:
		virtual ~FakeOutput() { }

		MockAction(Begin)
		MockAction(Finish, std::size_t, std::size_t)

		MockAction(BeginFixture, std::string)
		MockAction(EndFixture, std::string)

		MockAction(BeginGiven, std::string)
		MockAction(EndGiven, std::string)

		MockAction(BeginWhen, std::string)
		MockAction(EndWhen, std::string)

		MockAction(BeginThen, std::string)
		MockAction(EndThen, std::string)

		MockAction(BeginFinally, std::string)
		MockAction(EndFinally, std::string)

		MockAction(OnError, std::size_t, std::string, std::string)
		MockAction(OnUnknownError)

		ut11::Mock<void (std::exception)> mockOnError1;
		virtual void OnError(const std::exception& ex) { mockOnError1(ex); }
	};
}

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

    std::unique_ptr<FakeOutput> output;
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

            output = std::unique_ptr<FakeOutput>(new FakeOutput());
            result = false;
        });

        When("running a Stage with an output", [&]() {

            result = Stage.Run(*output);
        });

        Then("the result is true", [&]() {
            AssertThat(result, ut11::Is::True);
        });

        Then("the given occurred as expected", [&]() {

            output->mockBeginGiven.Verify(__LINE__, __FILE__, givenDescription);
            mockGiven.Verify(__LINE__, __FILE__);
            output->mockEndGiven.Verify(__LINE__, __FILE__, givenDescription);
        });

        Then("the when occurred as expected", [&]() {

            output->mockBeginWhen.Verify(__LINE__, __FILE__, whenDescription);
            mockWhen.Verify(__LINE__, __FILE__);
            output->mockEndWhen.Verify(__LINE__, __FILE__, whenDescription);
        });

        Then("the then occurred as expected", [&]() {

            output->mockBeginThen.Verify(__LINE__, __FILE__, thenDescription);
            mockThen.Verify(__LINE__, __FILE__);
            output->mockEndThen.Verify(__LINE__, __FILE__, thenDescription);
        });

        Then("the finally occurred as expected", [&]() {

            output->mockBeginFinally.Verify(__LINE__, __FILE__, finallyDescription);
            mockFinally.Verify(__LINE__, __FILE__);
            output->mockEndFinally.Verify(__LINE__, __FILE__, finallyDescription);
        });

        When("running a Stage with an output that throws a Test Exception", [&]() {

            testException = ut11::TestFailedException(__LINE__, __FILE__, "dsdsa");
            mockThen.SetCallback([&]() { throw testException; });

            result = Stage.Run(*output);
        });

        Then("the result is false", [&]() {
            AssertThat(result, ut11::Is::False);
        });

        Then("Output.OnError was called as expected", [&]() {
            output->mockOnError.Verify(__LINE__, __FILE__, testException.GetLine(), testException.GetFile(), testException.GetMessage());
        });


        When("running a Stage with an output that throws a std::exception", [&]() {

            mockThen.SetCallback([&]() { throw stdException; });

            result = Stage.Run(*output);
        });

        Then("the result is false", [&]() {
            AssertThat(result, ut11::Is::False);
        });

        Then("Output.OnError was called as expected", [&]() {
            output->mockOnError1.Verify(__LINE__, __FILE__, ut11::Is::Any<std::exception>());
        });

        When("running a Stage with an output that throws an unknown exception", [&]() {

            mockThen.SetCallback([&]() { throw "unknown exception"; });

            result = Stage.Run(*output);
        });

        Then("the result is false", [&]() {
            AssertThat(result, ut11::Is::False);
        });

        Then("Output.OnError was called as expected", [&]() {
            output->mockOnUnknownError.Verify(__LINE__, __FILE__);
        });

        When("calling run with all Stages as invalid functions", [&]() {

            ut11::Utility::TestStep invalid;
            Stage = ut11::Utility::TestStage(invalid,invalid,invalid,invalid);
            result = Stage.Run(*output);
        });

        Then("the result is true", [&]() {
            AssertThat(result, ut11::Is::True);
        });
    }
};
DeclareFixture(TestStageTests);
