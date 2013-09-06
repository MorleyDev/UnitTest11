#ifndef UNITTEST11_TESTFIXTURERUNNER_HPP
#define UNITTEST11_TESTFIXTURERUNNER_HPP

#include "out/Output.hpp"
#include "TestFixture.hpp"
#include <map>
#include <memory>

namespace ut11
{
	class TestFixtureRunner
	{
	public:
		void AddFixture(std::shared_ptr<TestFixtureAbstract> fixture);

		int Run(out::Output& output);

		int RunCategories(out::Output& output, std::vector<std::string>);

	private:
		std::vector<std::shared_ptr<TestFixtureAbstract>> GetFixtures() const;
		std::vector<std::shared_ptr<TestFixtureAbstract>> GetFixturesThatMatchCategories(const std::vector<std::string>& desiredCategories) const;

		static bool DoesFixtureMatchCategories(std::shared_ptr<ut11::TestFixtureAbstract> fixture, const std::vector<std::string>& desiredCategories);
		static TestFixtureResults RunTestFixtures(std::vector<std::shared_ptr<ut11::TestFixtureAbstract>> fixtures, out::Output& output);

		std::map< std::string, std::shared_ptr<TestFixtureAbstract> > m_fixtures;
	};
}

#endif // UNITTEST11_TESTFIXTURERUNNER_HPP
