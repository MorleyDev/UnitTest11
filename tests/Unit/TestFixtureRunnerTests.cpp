#include <UnitTest11/Core.hpp>
#include <UnitTest11/Mock.hpp>
#include <UnitTest11/Is/EqualTo.hpp>
#include <UnitTest11/Is/Null.hpp>
#include <UnitTest11/TestFixtureRunner.hpp>

namespace
{
	class FakeOutput : public ut11::out::Output
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

	class FakeTestFixture : public ut11::detail::TestFixtureAbstract
	{
	private:
		ut11::detail::TestFixtureResults m_runResults;

	public:
		ut11::out::Output* RunOutputUsed;

		FakeTestFixture(ut11::detail::TestFixtureResults runResults)
			: m_runResults(runResults), RunOutputUsed(nullptr)
		{
		}

		MockAction(AddCategory, ut11::Category);
		MockFunctionConst(std::set<ut11::Category>, GetCategories);

		MockAction(Given, std::string, std::function<void(void)>);
		MockAction(When, std::string, std::function<void(void)>);
		MockAction(Then, std::string, std::function<void(void)>);
		MockAction(Finally, std::string, std::function<void(void)>);

		MockFunctionConst(std::string, GetName);

		virtual ut11::detail::TestFixtureResults Run(ut11::out::Output& output)
		{
			RunOutputUsed = &output;
			return m_runResults;
		}
	};
}

class TestFixtureRunnerTests : public ut11::TestFixture
{
private:
	ut11::detail::TestFixtureRunner m_runner;
	::FakeOutput m_output;

	int m_expectedResult;
	int m_result;

public:
	virtual void Run()
	{
		Given("a TestFixtureRunner with added Fixture with failing tests", [&]() {
			m_runner = ut11::detail::TestFixtureRunner();

			m_expectedResult = 2;

			ut11::detail::TestFixtureResults fixtureResults;
			fixtureResults.ran = 5;
			fixtureResults.succeeded = 3;

			FakeTestFixture* fixtureOne = new FakeTestFixture(fixtureResults);
			fixtureOne->mockGetNameConst.SetReturn(std::string("nameOne"));

			fixtureResults.ran = 4;
			fixtureResults.succeeded = 4;

			FakeTestFixture* fixtureTwo = new FakeTestFixture(fixtureResults);
			fixtureTwo->mockGetNameConst.SetReturn(std::string("nameTwo"));

			m_runner.AddFixture(std::unique_ptr<ut11::detail::TestFixtureAbstract>(fixtureOne));
			m_runner.AddFixture(std::unique_ptr<ut11::detail::TestFixtureAbstract>(fixtureTwo));
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
	ut11::detail::TestFixtureRunner m_runner;
	::FakeOutput m_output;
	std::shared_ptr<FakeTestFixture> m_fixtureOne;
	std::shared_ptr<FakeTestFixture> m_fixtureTwo;

public:
	virtual void Run()
	{
		Given("a TestFixtureRunner where two fixtures with the same names are added", [&]() {
			m_runner = ut11::detail::TestFixtureRunner();
			m_output = FakeOutput();

			m_fixtureOne = std::make_shared<FakeTestFixture>(ut11::detail::TestFixtureResults());
			m_fixtureTwo = std::make_shared<FakeTestFixture>(ut11::detail::TestFixtureResults());

			std::string fixtureName("name");
			m_fixtureOne->mockGetNameConst.SetReturn(fixtureName);
			m_fixtureTwo->mockGetNameConst.SetReturn(fixtureName);

			m_runner.AddFixture(std::shared_ptr<ut11::detail::TestFixtureAbstract>(m_fixtureOne));
			m_runner.AddFixture(std::shared_ptr<ut11::detail::TestFixtureAbstract>(m_fixtureTwo));
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
	ut11::detail::TestFixtureRunner m_runner;

	int m_expectedResult;
	int m_result;

public:
	virtual void Run()
	{
		Given("a TestFixtureRunner with added Fixture with failing tests", [&]() {
			m_runner = ut11::detail::TestFixtureRunner();

			m_expectedResult = 2;

			ut11::detail::TestFixtureResults fixtureResults;
			fixtureResults.ran = 5;
			fixtureResults.succeeded = 4;

			FakeTestFixture* fixtureOne = new FakeTestFixture(fixtureResults);
			fixtureOne->mockGetNameConst.SetReturn(std::string("nameOne"));
			fixtureOne->mockGetCategoriesConst.SetReturn(std::set<ut11::Category>({ ut11::Category("category") }));

			fixtureResults.ran = 4;
			fixtureResults.succeeded = 1;

			FakeTestFixture* fixtureTwo = new FakeTestFixture(fixtureResults);
			fixtureTwo->mockGetNameConst.SetReturn(std::string("nameTwo"));
			fixtureTwo->mockGetCategoriesConst.SetReturn(std::set<ut11::Category>({ ut11::Category("notcategory") }));

			fixtureResults.ran = 7;
			fixtureResults.succeeded = 6;

			FakeTestFixture* fixtureThree = new FakeTestFixture(fixtureResults);
			fixtureThree->mockGetNameConst.SetReturn(std::string("nameThree"));
			fixtureThree->mockGetCategoriesConst.SetReturn(std::set<ut11::Category>({ ut11::Category("category") }));

			m_runner.AddFixture(std::unique_ptr<ut11::detail::TestFixtureAbstract>(fixtureOne));
			m_runner.AddFixture(std::unique_ptr<ut11::detail::TestFixtureAbstract>(fixtureTwo));
			m_runner.AddFixture(std::unique_ptr<ut11::detail::TestFixtureAbstract>(fixtureThree));
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
