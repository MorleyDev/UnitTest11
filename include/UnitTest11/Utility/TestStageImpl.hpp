#ifndef UNITTEST11_utility_TESTSTAGEIMPL_HPP
#define UNITTEST11_utility_TESTSTAGEIMPL_HPP

#include "TestStage.hpp"
#include "TestStep.hpp"

namespace ut11
{
	namespace utility
	{
		class TestStageImpl : public TestStage
		{
		public:
			TestStep m_given, m_when, m_then, m_finally;

			TestStageImpl();
			TestStageImpl(TestStep given, TestStep when, TestStep then, TestStep finally);
			virtual ~TestStageImpl();

			virtual bool Run(out::Output& output);

			virtual void Given(out::Output& output);
			virtual void When(out::Output& output);
			virtual void Then(out::Output& output);
			virtual void Finally(out::Output& output);
		};
	}
}

#endif // UNITTEST11_utility_TESTSTAGEIMPL_HPP
