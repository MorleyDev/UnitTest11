#include <UnitTest11.hpp>
#include <vector>

namespace
{
	class FakeTestStageBuilder : public ut11::Utility::ITestStageBuilder
	{
	public:
		virtual ~FakeTestStageBuilder() { }

		MockAction(PushGiven, ut11::Utility::TestStep)
		MockAction(PushWhen, ut11::Utility::TestStep)
		MockAction(PushThen, ut11::Utility::TestStep)
		MockAction(PushFinally, ut11::Utility::TestStep)
		MockFunction(std::vector< std::shared_ptr<ut11::Utility::ITestStage> >, Stage)

	};

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
}

class TestFixtureTest : public ut11::TestFixture
{
public:
    virtual void Run()
    {
        Then("when calling the Given on a fixture, the expected call is made", [&]() {

            std::string m_description = "description";

            FakeTestStageBuilder* builder = new FakeTestStageBuilder;
            std::unique_ptr<FakeTestStageBuilder> StageBuilder(builder);

            ut11::TestFixture fixture("name", std::move(StageBuilder));
            fixture.Given(m_description, [](){});

            MockVerify(builder->mockPushGiven, ut11::Will::Pass([&](ut11::Utility::TestStep step) { return ( step.description == m_description ); }));
        });

        Then("when calling the When on a fixture, the expected call is made", [&]() {

            std::string m_description = "description";

            FakeTestStageBuilder* builder = new FakeTestStageBuilder;
            std::unique_ptr<FakeTestStageBuilder> StageBuilder(builder);

            ut11::TestFixture fixture("name", std::move(StageBuilder));
            fixture.When(m_description, [](){});

            MockVerify(builder->mockPushWhen, ut11::Will::Pass([&](ut11::Utility::TestStep step) { return ( step.description == m_description ); }));
        });

        Then("when calling the Then on a fixture, the expected call is made", [&]() {

            std::string m_description = "description";

            FakeTestStageBuilder* builder = new FakeTestStageBuilder;
            std::unique_ptr<FakeTestStageBuilder> StageBuilder(builder);

            ut11::TestFixture fixture("name", std::move(StageBuilder));
            fixture.Then(m_description, [](){});

            MockVerify(builder->mockPushThen, ut11::Will::Pass([&](ut11::Utility::TestStep step) { return ( step.description == m_description ); }));
        });

        Then("when calling the Finally on a fixture, the expected call is made", [&]() {

            std::string m_description = "description";

            FakeTestStageBuilder* builder = new FakeTestStageBuilder;
            std::unique_ptr<FakeTestStageBuilder> StageBuilder(builder);

            ut11::TestFixture fixture("name", std::move(StageBuilder));
            fixture.Finally(m_description, [](){});

            MockVerify(builder->mockPushFinally, ut11::Will::Pass([&](ut11::Utility::TestStep step) { return ( step.description == m_description ); }));
        });

        Then("when running a TestFixture", [&]() {

            FakeTestStageBuilder* builder = new FakeTestStageBuilder;
            std::unique_ptr<FakeTestStageBuilder> StageBuilder(builder);

            std::vector< std::shared_ptr<ut11::Utility::ITestStage> > Stages;
            std::shared_ptr< FakeTestStage<true> > mockTestStage(new FakeTestStage<true> );
            Stages.push_back(mockTestStage);
            builder->mockStage.SetReturn(Stages);

            std::string fixtureName = "fixtureName";
            ut11::TestFixture fixture(fixtureName, std::move(StageBuilder));

            FakeOutput mockOutput;
            auto results = fixture.Run(mockOutput);
            AssertThat(results.ran, ut11::Is::EqualTo(std::size_t(1)));
            AssertThat(results.succeeded, ut11::Is::EqualTo(std::size_t(1)));

            MockVerify(mockOutput.mockBeginFixture, fixtureName);
            MockVerify(mockOutput.mockEndFixture, fixtureName);
        });

        Then("when running a TestFixture with a failure", [&]() {

            FakeTestStageBuilder* builder = new FakeTestStageBuilder;
            std::unique_ptr<FakeTestStageBuilder> StageBuilder(builder);

            std::vector< std::shared_ptr<ut11::Utility::ITestStage> > Stages;
            std::shared_ptr< FakeTestStage<false> > mockTestStage(new FakeTestStage<false> );
            Stages.push_back(mockTestStage);
            builder->mockStage.SetReturn(Stages);

            std::string fixtureName = "fixtureName";
            ut11::TestFixture fixture(fixtureName, std::move(StageBuilder));

            FakeOutput mockOutput;
            auto results = fixture.Run(mockOutput);
            AssertThat(results.ran, ut11::Is::EqualTo(1u));
            AssertThat(results.succeeded, ut11::Is::EqualTo(0u));

            MockVerify(mockOutput.mockBeginFixture, fixtureName);
            MockVerify(mockOutput.mockEndFixture, fixtureName);
        });
    }
};
DeclareFixture(TestFixtureTest);
