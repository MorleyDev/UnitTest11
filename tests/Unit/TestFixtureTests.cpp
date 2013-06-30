#include <UnitTest11.hpp>
#include <vector>

namespace
{
    class FakeTestStageBuilder : public ut11::Utility::TestStageBuilder
    {
    public:
        virtual ~FakeTestStageBuilder() { }

        MockAction(PushGiven, ut11::Utility::TestStep)
        MockAction(PushWhen, ut11::Utility::TestStep)
        MockAction(PushThen, ut11::Utility::TestStep)
        MockAction(PushFinally, ut11::Utility::TestStep)
        MockFunction(std::vector< std::shared_ptr<ut11::Utility::TestStage> >, Stage)
    };

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

    class FakeTestStage : public ut11::Utility::TestStage
    {
    private:
        bool m_result;

    public:
        bool WasTestStageRun;

        FakeTestStage(bool result)
            : m_result(result), WasTestStageRun(false)
        {
        }

        virtual ~FakeTestStage() { }


        virtual bool Run(ut11::Output&)
        {
            WasTestStageRun = true;
            return m_result;
        }
    };
}

class TestFixtureConstructionTests : public ut11::TestFixture
{
private:
    std::unique_ptr<ut11::TestFixture> m_fixture;
    std::string m_name;

public:
    virtual void Run()
    {
        Given("a fixture constructed with a name", [&]() {

            std::unique_ptr<FakeTestStageBuilder> StageBuilder(new FakeTestStageBuilder);
            m_name = std::string("name");

            m_fixture = std::move(std::unique_ptr<ut11::TestFixture>(new ut11::TestFixture(m_name, std::move(StageBuilder))));
        });
        Then("the name is as expected", [&]() {

            AssertThat(m_fixture->GetName(), ut11::Is::EqualTo(m_name));
        });

        When("setting the name", [&]() {
            m_name = "other_name";
            m_fixture->SetName(m_name);
        });
        Then("the name is as expected", [&]() {

            AssertThat(m_fixture->GetName(), ut11::Is::EqualTo(m_name));
        });
    }
};
DeclareFixture(TestFixtureConstructionTests)(ut11::Category("unit"));

class TestFixtureGivenWhenThenTest : public ut11::TestFixture
{
private:
    std::unique_ptr<ut11::TestFixture> m_fixture;
    FakeTestStageBuilder* m_mockBuilder;
    std::string m_expectedDescription;

public:
    virtual void Run()
    {
        Given("a Test Fixture", [&]() {

            m_mockBuilder = new FakeTestStageBuilder;
            m_fixture = std::move(std::unique_ptr<ut11::TestFixture>(new ut11::TestFixture("name", std::unique_ptr<FakeTestStageBuilder>(m_mockBuilder))));
        });

        When("calling the Given", [&]() {

            m_expectedDescription = "description";

            m_fixture->Given(m_expectedDescription, [](){ });
        });
        Then("the expected call is made", [&]() {

            MockVerify(m_mockBuilder->mockPushGiven)(ut11::Will::Pass([&](ut11::Utility::TestStep step) { return ( step.description == m_expectedDescription ); }));
        });

        When("calling the When", [&]() {

            m_expectedDescription = "description";

            m_fixture->When(m_expectedDescription, [](){ });
        });
        Then("the expected call is made", [&]() {

            MockVerify(m_mockBuilder->mockPushWhen)(ut11::Will::Pass([&](ut11::Utility::TestStep step) { return ( step.description == m_expectedDescription ); }));
        });

        When("calling the Then", [&]() {

            m_expectedDescription = "description";

            m_fixture->Then(m_expectedDescription, [](){ });
        });
        Then("the expected call is made", [&]() {

            MockVerify(m_mockBuilder->mockPushThen)(ut11::Will::Pass([&](ut11::Utility::TestStep step) { return ( step.description == m_expectedDescription ); }));
        });

        When("calling the Finally", [&]() {

            m_expectedDescription = "description";

            m_fixture->Finally(m_expectedDescription, [](){ });
        });
        Then("the expected call is made", [&]() {

            MockVerify(m_mockBuilder->mockPushFinally)(ut11::Will::Pass([&](ut11::Utility::TestStep step) { return ( step.description == m_expectedDescription ); }));
        });
    }
};
DeclareFixture(TestFixtureGivenWhenThenTest)(ut11::Category("unit"));

class TestFixtureRunTests : public ut11::TestFixture
{
private:
    std::unique_ptr<ut11::TestFixture> m_fixture;
    std::string m_fixtureName;

    FakeTestStageBuilder* m_mockBuilder;
    FakeOutput m_mockOutput;
    std::shared_ptr< FakeTestStage > m_mockTestStage;

    ut11::TestFixtureResults m_fixtureResults;

public:
    virtual void Run()
    {
        Given("a Test Fixture", [&]() {

            m_fixtureName = "name";

            m_mockBuilder = new FakeTestStageBuilder;
            m_fixture = std::move(std::unique_ptr<ut11::TestFixture>(new ut11::TestFixture(m_fixtureName, std::unique_ptr<FakeTestStageBuilder>(m_mockBuilder))));
        });

        When("running the test fixture with successful stages", [&]() {

            std::vector< std::shared_ptr<ut11::Utility::TestStage> > Stages;
            Stages.push_back(std::make_shared<FakeTestStage>(true));
            Stages.push_back(std::make_shared<FakeTestStage>(true));
            Stages.push_back(m_mockTestStage = std::make_shared<FakeTestStage>(true));
            Stages.push_back(std::make_shared<FakeTestStage>(true));
            m_mockBuilder->mockStage.SetReturn(Stages);

            m_mockOutput = FakeOutput();
            m_fixtureResults = m_fixture->Run(m_mockOutput);
        });
        Then("the output is told the fixture has begun", [&]() {
            MockVerify(m_mockOutput.mockBeginFixture)(m_fixtureName);
        });
        Then("the test stage was ran", [&]() {
            AssertThat(m_mockTestStage->WasTestStageRun, ut11::Is::True);
        });
        Then("the expected number of tests are ran", [&]() {
            AssertThat(m_fixtureResults.ran, ut11::Is::EqualTo(4u));
        });
        Then("the expected number of tests succeed", [&]() {
            AssertThat(m_fixtureResults.succeeded, ut11::Is::EqualTo(4u));
        });
        Then("the output is told the fixture has ended", [&]() {
            MockVerify(m_mockOutput.mockEndFixture)(m_fixtureName);
        });

        When("running the test fixture with a failing stage", [&]() {

            std::vector< std::shared_ptr<ut11::Utility::TestStage> > Stages;
            Stages.push_back(std::make_shared<FakeTestStage>(true));
            Stages.push_back(std::make_shared<FakeTestStage>(true));
            Stages.push_back(m_mockTestStage = std::make_shared<FakeTestStage>(false));
            Stages.push_back(std::make_shared<FakeTestStage>(true));
            Stages.push_back(std::make_shared<FakeTestStage>(false));
            m_mockBuilder->mockStage.SetReturn(Stages);

            m_mockOutput = FakeOutput();
            m_fixtureResults = m_fixture->Run(m_mockOutput);
        });
        Then("the expected number of tests are ran", [&]() {
            AssertThat(m_fixtureResults.ran, ut11::Is::EqualTo(5u));
        });
        Then("the expected number of tests succeed", [&]() {
            AssertThat(m_fixtureResults.succeeded, ut11::Is::EqualTo(3u));
        });
    }
};
DeclareFixture(TestFixtureRunTests)(ut11::Category("unit"));

class TestFixtureCategoryTests : public ut11::TestFixture
{
private:
    std::unique_ptr<ut11::TestFixture> m_fixture;
    std::string m_fixtureName;

    std::set<ut11::Category> m_categories;

public:
    virtual void Run()
    {
        Given("a Test Fixture with added categories", [&]() {

            m_fixtureName = "name";

            m_fixture = std::move(std::unique_ptr<ut11::TestFixture>(new ut11::TestFixture(m_fixtureName, std::unique_ptr<FakeTestStageBuilder>(new FakeTestStageBuilder))));
            m_fixture->AddCategory(ut11::Category("unit"));
            m_fixture->AddCategory(ut11::Category("integration"));
            m_fixture->AddCategory(ut11::Category("integration"));
            m_fixture->AddCategory(ut11::Category("piano"));
        });

        When("getting the categories", [&]() {
        	m_categories = m_fixture->GetCategories();
        });
        Then("the expected categories were returned", [&]() {
        	AssertThat(m_categories, ut11::Is::Iterable::EquivalentTo(std::vector<ut11::Category>({ ut11::Category("unit"), ut11::Category("integration"), ut11::Category("piano") })));
        });
    }
};
DeclareFixture(TestFixtureCategoryTests)(ut11::Category("unit"));

