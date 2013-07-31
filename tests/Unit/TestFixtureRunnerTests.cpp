#include <UnitTest11.hpp>
#include <UnitTest11/TestFixtureRunner.hpp>

namespace ut11
{
    namespace Utility
    {
        template<> struct ParseToString<ut11::Output*>
        {
            inline std::string operator()(ut11::Output* value) const
            {
                std::stringstream stream;
                stream << value;
                return stream.str();
            }
        };
    }
}

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

        MockAction(BeginTest)
        MockAction(EndTest)

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

    class FakeTestFixture : public ut11::TestFixtureAbstract
    {
    private:
        ut11::TestFixtureResults m_runResults;

    public:
        ut11::Output* RunOutputUsed;

        FakeTestFixture(ut11::TestFixtureResults runResults)
            : m_runResults(runResults), RunOutputUsed(nullptr)
        {
        }

        MockAction(AddCategory, ut11::Category);
        MockFunctionConst(std::set<ut11::Category>, GetCategories);

        MockAction(Given, std::string, std::function<void(void)>);
        MockAction(When, std::string, std::function<void(void)>);
        MockAction(Then, std::string, std::function<void(void)>);
        MockAction(Finally, std::string, std::function<void(void)>);

        MockFunction(std::string, GetName);

        virtual ut11::TestFixtureResults Run(ut11::Output& output)
        {
            RunOutputUsed = &output;
            return m_runResults;
        }
    };
}

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

            ut11::TestFixtureResults fixtureResults;
            fixtureResults.ran = 5;
            fixtureResults.succeeded = 3;

            FakeTestFixture* fixtureOne = new FakeTestFixture(fixtureResults);
            fixtureOne->mockGetName.SetReturn(std::string("nameOne"));

            fixtureResults.ran = 4;
            fixtureResults.succeeded = 4;

            FakeTestFixture* fixtureTwo = new FakeTestFixture(fixtureResults);
            fixtureTwo->mockGetName.SetReturn(std::string("nameTwo"));

            m_runner.AddFixture(std::unique_ptr<ut11::TestFixtureAbstract>(fixtureOne));
            m_runner.AddFixture(std::unique_ptr<ut11::TestFixtureAbstract>(fixtureTwo));
        });
        When("running the TestFixtureRunner", [&]() {
            m_result = m_runner.Run(m_output);
        });
        Then("the number of failing tests is returned", [&]() {
            AssertThat(m_result, ut11::Is::EqualTo(m_expectedResult));
        });
    }
};
DeclareFixture(TestFixtureRunnerTests)(ut11::Category("unit"));

class TestFixtureRunnerMultipleFixturesWithSameNameTests : public ut11::TestFixture
{
private:
    ut11::TestFixtureRunner m_runner;
    FakeOutput m_output;
    FakeTestFixture* m_fixtureOne;
    FakeTestFixture* m_fixtureTwo;

public:
    virtual void Run()
    {
        Given("a TestFixtureRunner where two fixtures with the same names are added", [&]() {
            m_runner = ut11::TestFixtureRunner();
            m_output = FakeOutput();

            m_fixtureOne = new FakeTestFixture(ut11::TestFixtureResults());
            m_fixtureTwo = new FakeTestFixture(ut11::TestFixtureResults());

            m_fixtureOne->mockGetName.SetReturn(std::string("name"));
            m_fixtureTwo->mockGetName.SetReturn(std::string("name"));

            m_runner.AddFixture(std::unique_ptr<ut11::TestFixtureAbstract>(m_fixtureOne));
            m_runner.AddFixture(std::unique_ptr<ut11::TestFixtureAbstract>(m_fixtureTwo));
        });
        When("Running the test fixture runner", [&]() {
            m_runner.Run(m_output);
        });
        Then("the first test fixture is ran", [&]() {
            AssertThat(m_fixtureOne->RunOutputUsed, ut11::Is::Not::Null);
        });
        Then("the second test fixture is not ran", [&](){
            AssertThat(m_fixtureTwo->RunOutputUsed, ut11::Is::Null);
        });
    }
};
DeclareFixture(TestFixtureRunnerMultipleFixturesWithSameNameTests)(ut11::Category("unit"));

class TestFixtureRunnerCategoryTests : public ut11::TestFixture
{
private:
    ut11::TestFixtureRunner m_runner;

    int m_expectedResult;
    int m_result;

public:
    virtual void Run()
    {
        Given("a TestFixtureRunner with added Fixture with failing tests", [&]() {
            m_runner = ut11::TestFixtureRunner();

            m_expectedResult = 2;

            ut11::TestFixtureResults fixtureResults;
            fixtureResults.ran = 5;
            fixtureResults.succeeded = 4;

            FakeTestFixture* fixtureOne = new FakeTestFixture(fixtureResults);
            fixtureOne->mockGetName.SetReturn(std::string("nameOne"));
            fixtureOne->mockGetCategoriesConst.SetReturn(std::set<ut11::Category>({ ut11::Category("category") }));

            fixtureResults.ran = 4;
            fixtureResults.succeeded = 1;

            FakeTestFixture* fixtureTwo = new FakeTestFixture(fixtureResults);
            fixtureTwo->mockGetName.SetReturn(std::string("nameTwo"));
            fixtureTwo->mockGetCategoriesConst.SetReturn(std::set<ut11::Category>({ ut11::Category("unrancategory") }));

            fixtureResults.ran = 7;
            fixtureResults.succeeded = 6;

            FakeTestFixture* fixtureThree = new FakeTestFixture(fixtureResults);
            fixtureThree->mockGetName.SetReturn(std::string("nameThree"));
            fixtureThree->mockGetCategoriesConst.SetReturn(std::set<ut11::Category>({ ut11::Category("category") }));

            m_runner.AddFixture(std::unique_ptr<ut11::TestFixtureAbstract>(fixtureOne));
            m_runner.AddFixture(std::unique_ptr<ut11::TestFixtureAbstract>(fixtureTwo));
            m_runner.AddFixture(std::unique_ptr<ut11::TestFixtureAbstract>(fixtureThree));
        });
        When("running the TestFixtureRunner", [&]() {
            FakeOutput output;
            m_result = m_runner.RunCategories(output, {"category"});
        });
        Then("the number of failing tests is returned", [&]() {
            AssertThat(m_result, ut11::Is::EqualTo(m_expectedResult));
        });
    }
};
DeclareFixture(TestFixtureRunnerCategoryTests)(ut11::Category("unit"));
