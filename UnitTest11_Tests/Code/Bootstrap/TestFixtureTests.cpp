#include <UnitTest11/TestFixture.hpp>

#include <UnitTest11/Mock.hpp>
#include <UnitTest11/Will/Pass.hpp>

#include <UnitTest++/UnitTest++.h>
#include <memory>
#include <vector>

class FakeTestStageBuilder : public ut11::Utility::ITestStageBuilder
{
public:
    virtual ~FakeTestStageBuilder() { }

    ut11::Mock<void (ut11::Utility::TestStep)> mockGiven;
    ut11::Mock<void (ut11::Utility::TestStep)> mockWhen;
    ut11::Mock<void (ut11::Utility::TestStep)> mockThen;
    ut11::Mock<void (ut11::Utility::TestStep)> mockFinally;
    ut11::Mock<std::vector< std::shared_ptr<ut11::Utility::ITestStage> > (void)> mockStage;

    virtual void pushGiven(ut11::Utility::TestStep given) { mockGiven(given); }
    virtual void pushWhen(ut11::Utility::TestStep when) { mockWhen(when); }
    virtual void pushThen(ut11::Utility::TestStep then) { mockThen(then); }
    virtual void pushFinally(ut11::Utility::TestStep finally) { mockFinally(finally); }
    virtual std::vector< std::shared_ptr<ut11::Utility::ITestStage> > stage() { return mockStage(); }
};

TEST(TestFixtureGivenTest)
{
    std::string m_description = "description";

    FakeTestStageBuilder* builder = new FakeTestStageBuilder;
    std::unique_ptr<FakeTestStageBuilder> stageBuilder(builder);

    ut11::TestFixture fixture("name", std::move(stageBuilder));
    fixture.Given(m_description, [](){});

    builder->mockGiven.Verify(__LINE__, __FILE__, ut11::Will::Pass([&](ut11::Utility::TestStep step) { return ( step.description == m_description ); }));
}

TEST(TestFixtureWhenTest)
{
    std::string m_description = "description";

    FakeTestStageBuilder* builder = new FakeTestStageBuilder;
    std::unique_ptr<FakeTestStageBuilder> stageBuilder(builder);

    ut11::TestFixture fixture("name", std::move(stageBuilder));
    fixture.When(m_description, [](){});

    builder->mockWhen.Verify(__LINE__, __FILE__, ut11::Will::Pass([&](ut11::Utility::TestStep step) { return ( step.description == m_description ); }));
}

TEST(TestFixtureThenTest)
{
    std::string m_description = "description";

    FakeTestStageBuilder* builder = new FakeTestStageBuilder;
    std::unique_ptr<FakeTestStageBuilder> stageBuilder(builder);

    ut11::TestFixture fixture("name", std::move(stageBuilder));
    fixture.Then(m_description, [](){});

    builder->mockThen.Verify(__LINE__, __FILE__, ut11::Will::Pass([&](ut11::Utility::TestStep step) { return ( step.description == m_description ); }));
}

TEST(TestFixtureFinallyTest)
{
    std::string m_description = "description";

    FakeTestStageBuilder* builder = new FakeTestStageBuilder;
    std::unique_ptr<FakeTestStageBuilder> stageBuilder(builder);

    ut11::TestFixture fixture("name", std::move(stageBuilder));
    fixture.Finally(m_description, [](){});

    builder->mockFinally.Verify(__LINE__, __FILE__, ut11::Will::Pass([&](ut11::Utility::TestStep step) { return ( step.description == m_description ); }));
}

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

template<bool V>
class FakeTestStage : public ut11::Utility::ITestStage
{
public:
    virtual ~FakeTestStage() { }

    virtual bool Run(ut11::IOutput&)
    {
        return V;
    }
};

TEST(TestFixtureRunTest)
{
    FakeTestStageBuilder* builder = new FakeTestStageBuilder;
    std::unique_ptr<FakeTestStageBuilder> stageBuilder(builder);

    std::vector< std::shared_ptr<ut11::Utility::ITestStage> > stages;
    std::shared_ptr< FakeTestStage<true> > mockTestStage(new FakeTestStage<true> );
    stages.push_back(mockTestStage);
    builder->mockStage.setReturn(stages);

    std::string fixtureName = "fixtureName";
    ut11::TestFixture fixture(fixtureName, std::move(stageBuilder));

    FakeOutput mockOutput;
    auto results = fixture.Run(mockOutput);
    CHECK_EQUAL(1, results.ran);
    CHECK_EQUAL(1, results.succeeded);

    mockOutput.mockBeginFixture.Verify(__LINE__, __FILE__, fixtureName);
    mockOutput.mockEndFixture.Verify(__LINE__, __FILE__, fixtureName);
}

TEST(TestFixtureRunWithFailureTest)
{
    FakeTestStageBuilder* builder = new FakeTestStageBuilder;
    std::unique_ptr<FakeTestStageBuilder> stageBuilder(builder);

    std::vector< std::shared_ptr<ut11::Utility::ITestStage> > stages;
    std::shared_ptr< FakeTestStage<false> > mockTestStage(new FakeTestStage<false> );
    stages.push_back(mockTestStage);
    builder->mockStage.setReturn(stages);

    std::string fixtureName = "fixtureName";
    ut11::TestFixture fixture(fixtureName, std::move(stageBuilder));

    FakeOutput mockOutput;
    auto results = fixture.Run(mockOutput);
    CHECK_EQUAL(1, results.ran);
    CHECK_EQUAL(0, results.succeeded);

    mockOutput.mockBeginFixture.Verify(__LINE__, __FILE__, fixtureName);
    mockOutput.mockEndFixture.Verify(__LINE__, __FILE__, fixtureName);
}
