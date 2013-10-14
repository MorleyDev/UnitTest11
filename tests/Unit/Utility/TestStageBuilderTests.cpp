#include <UnitTest11/Core.hpp>
#include <UnitTest11/Is/EqualTo.hpp>
#include <UnitTest11/Is/Empty.hpp>

class TestStageBuilderTests : public ut11::TestFixture
{
private:
	std::vector<ut11::utility::TestStep> m_steps;
	ut11::utility::TestStageBuilderImpl m_builder;

	std::vector< std::shared_ptr<ut11::utility::TestStageImpl> > m_expectedStages;
	std::vector< std::shared_ptr<ut11::utility::TestStageImpl> > m_resultingStages;

public:
	virtual void Run()
	{
		Given("TestSteps and a TestStageBuilder", [&](){

			m_builder = ut11::utility::TestStageBuilderImpl();

			m_steps =
			{
				ut11::utility::TestStep("0", [](){}), ut11::utility::TestStep("1", [](){}), ut11::utility::TestStep("2", [](){}),
				ut11::utility::TestStep("3", [](){}), ut11::utility::TestStep("4", [](){}), ut11::utility::TestStep("5", [](){}), 
				ut11::utility::TestStep("6", [](){}), ut11::utility::TestStep("7", [](){}), ut11::utility::TestStep("8", [](){}),
				ut11::utility::TestStep("9", [](){}), ut11::utility::TestStep("10", [](){})
			};
		});

		When("Stages are pushed to a builder and it is Built", [&]() {

			m_expectedStages = std::vector< std::shared_ptr<ut11::utility::TestStageImpl> >();
			m_resultingStages = std::vector< std::shared_ptr<ut11::utility::TestStageImpl> >();

			m_builder.PushGiven(m_steps[0]);
			m_builder.PushWhen(m_steps[1]);
			m_builder.PushThen(m_steps[2]);
			m_builder.PushThen(m_steps[3]);
			m_builder.PushWhen(m_steps[4]);
			m_builder.PushThen(m_steps[5]);
			m_builder.PushFinally(m_steps[6]);
			
			m_builder.PushWhen(m_steps[9]);
			m_builder.PushThen(m_steps[10]);
			m_builder.PushGiven(m_steps[7]);
			m_builder.PushThen(m_steps[8]);

			m_expectedStages.push_back(std::make_shared<ut11::utility::TestStageImpl>(m_steps[0], m_steps[1], m_steps[2], m_steps[6]));
			m_expectedStages.push_back(std::make_shared<ut11::utility::TestStageImpl>(m_steps[0], m_steps[1], m_steps[3], m_steps[6]));
			m_expectedStages.push_back(std::make_shared<ut11::utility::TestStageImpl>(m_steps[0], m_steps[4], m_steps[5], m_steps[6]));
			m_expectedStages.push_back(std::make_shared<ut11::utility::TestStageImpl>(ut11::utility::TestStep(), m_steps[9], m_steps[10], ut11::utility::TestStep()));
			m_expectedStages.push_back(std::make_shared<ut11::utility::TestStageImpl>(m_steps[7], ut11::utility::TestStep(), m_steps[8], ut11::utility::TestStep()));

			auto stages = m_builder.Build();
			for (std::size_t i = 0; i < stages.size(); ++i)
				m_resultingStages.push_back(std::static_pointer_cast<ut11::utility::TestStageImpl>(stages[i]));

		});

		Then("the expected amount of Stages are returned", [&]() {
			AssertThat(m_resultingStages.size(), ut11::Is::EqualTo(m_expectedStages.size()));
		});
		Then("the Stages are the expected Stages", [&]() {
			for (auto i = 0u; i < m_expectedStages.size(); ++i)
			{
				AssertThat(m_resultingStages[i]->m_given.description, ut11::Is::EqualTo(m_expectedStages[i]->m_given.description));
				AssertThat(m_resultingStages[i]->m_when.description, ut11::Is::EqualTo(m_expectedStages[i]->m_when.description));
				AssertThat(m_resultingStages[i]->m_then.description, ut11::Is::EqualTo(m_expectedStages[i]->m_then.description));
				AssertThat(m_resultingStages[i]->m_finally.description, ut11::Is::EqualTo(m_expectedStages[i]->m_finally.description));
			}
		});
		Then("Build has cleared the stages and another build results in an empty array", [&]() {
			AssertThat(m_builder.Build(), ut11::Is::Empty);
		});
	}
};
DeclareFixture(TestStageBuilderTests)(ut11::Category("unit"));
