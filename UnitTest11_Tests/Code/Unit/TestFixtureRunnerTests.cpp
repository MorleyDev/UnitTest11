#include <UnitTest11.hpp>
#include <UnitTest11/TestFixtureRunner.hpp>

namespace
{
	class FakeOutput : public ut11::Output
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

class TestFixtureRunnerTests : public ut11::TestFixtureImpl
{
private:
    ut11::TestFixtureRunner m_runner;
    FakeOutput m_output;

    int m_expectedResult;
    int m_result;

public:
    virtual void Run()
    {
        Given("a TestFixtureRunner with added Fixture with failing tests", [&]() {
            m_runner = ut11::TestFixtureRunner();

            m_expectedResult = 2;

            ut11::TestFixtureImpl* fixture = new ut11::TestFixtureImpl("fixture");
            fixture->Then("then", [](){});
            fixture->Then("then", [](){});
            fixture->Then("then", [](){});
            fixture->Then("then", [](){ throw int(5); });
            fixture->Then("then", [](){ throw int(5); });
            m_runner.AddFixture(std::unique_ptr<ut11::TestFixture>(fixture));

        });

        When("running the TestFixtureRunner", [&]() {
            m_result = m_runner.Run(m_output);
        });

        Then("the number of failing tests is returned", [&]() {
            AssertThat(m_result, ut11::Is::EqualTo(m_expectedResult));
        });
    }
};
DeclareFixture(TestFixtureRunnerTests);
