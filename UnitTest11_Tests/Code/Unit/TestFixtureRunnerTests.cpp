#include <UnitTest11.hpp>
#include <UnitTest11/TestFixtureRunner.hpp>

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

class TestFixtureRunnerTests : public ut11::TestFixture
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

            ut11::TestFixture* fixture = new ut11::TestFixture("fixture");
            fixture->Then("then", [](){});
            fixture->Then("then", [](){});
            fixture->Then("then", [](){});
            fixture->Then("then", [](){ throw int(5); });
            fixture->Then("then", [](){ throw int(5); });
            m_runner.AddFixture(std::unique_ptr<ut11::ITestFixture>(fixture));

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
