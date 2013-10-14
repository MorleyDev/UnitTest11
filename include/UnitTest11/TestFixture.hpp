#ifndef UNITTEST11_TESTFIXTURE_HPP
#define UNITTEST11_TESTFIXTURE_HPP

#include "detail/TestFixtureAbstract.hpp"
#include "detail/TestStageBuilderImpl.hpp"

#include <memory>

namespace ut11
{
	/*! \brief The test fixture class all tests must inherit from */
	class TestFixture : public detail::TestFixtureAbstract
	{
	public:
		TestFixture();
		explicit TestFixture(std::string name);
		TestFixture(std::string name, std::unique_ptr<ut11::detail::TestStageBuilder> builder);
		virtual ~TestFixture();

		virtual void AddCategory(ut11::Category);
		virtual std::set<ut11::Category> GetCategories() const;

		virtual void Given(std::string description, std::function<void(void)> logic);
		virtual void When(std::string description, std::function<void(void)> logic);
		virtual void Then(std::string description, std::function<void(void)> logic);
		virtual void Finally(std::string description, std::function<void(void)> logic);

		inline void SetName(std::string name) { m_name = name; }
		virtual std::string GetName() const { return m_name; }

		virtual detail::TestFixtureResults Run(out::Output& output);

		/*! \brief The function to inherit from that is called to build the test Given/When/Then/Finally tree */
		virtual void Run();

	private:
		std::string m_name;
		std::unique_ptr<ut11::detail::TestStageBuilder> m_StageBuilder;
		std::set<ut11::Category> m_categories;
	};
}

#endif // UNITTEST11_TESTFIXTURE_HPP
