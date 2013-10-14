#include <UnitTest11/detail/TestFixtureRunner.hpp>
#include <iostream>

void ut11::detail::TestFixtureRunner::AddFixture(std::shared_ptr<TestFixtureAbstract> fixture)
{
	m_fixtures.insert(std::make_pair(fixture->GetName(), std::move(fixture)));
}

int ut11::detail::TestFixtureRunner::Run(out::Output& output)
{
	output.Begin();

	auto fixtures = GetFixtures();
	auto results = RunTestFixtures(fixtures, output);

	output.Finish(results.ran, results.succeeded);
	return results.ran - results.succeeded;
}

int ut11::detail::TestFixtureRunner::RunCategories(out::Output& output, std::vector<std::string> desiredCategories)
{
	output.Begin();

	auto fixtures = GetFixturesThatMatchCategories(desiredCategories);
	auto results = RunTestFixtures(fixtures, output);

	output.Finish(results.ran, results.succeeded);
	return results.ran - results.succeeded;
}

std::vector<std::shared_ptr<ut11::detail::TestFixtureAbstract>> ut11::detail::TestFixtureRunner::GetFixtures() const
{
	std::vector<std::shared_ptr<ut11::detail::TestFixtureAbstract>> testFixtures;
	for(auto fixtureKeyValue : m_fixtures)
		testFixtures.push_back(fixtureKeyValue.second);

	return testFixtures;
}

std::vector<std::shared_ptr<ut11::detail::TestFixtureAbstract>> ut11::detail::TestFixtureRunner::GetFixturesThatMatchCategories(const std::vector<std::string>& desiredCategories) const
{
	std::vector<std::shared_ptr<ut11::detail::TestFixtureAbstract>> testFixtures;
	for(auto fixtureKeyValue : m_fixtures)
	{
		auto fixture = fixtureKeyValue.second;

		if ( DoesFixtureMatchCategories(fixture, desiredCategories) )
			testFixtures.push_back(fixture);
	}
	return testFixtures;
}

bool ut11::detail::TestFixtureRunner::DoesFixtureMatchCategories(std::shared_ptr<ut11::detail::TestFixtureAbstract> fixture, const std::vector<std::string>& desiredCategories)
{
	auto categories = fixture->GetCategories();
	for(auto category : categories)
		for(auto desiredCategory : desiredCategories)
			if (category.GetName() == desiredCategory)
				return true;

	return false;
}

ut11::detail::TestFixtureResults ut11::detail::TestFixtureRunner::RunTestFixtures(std::vector < std::shared_ptr < ut11::detail::TestFixtureAbstract >> fixtures, ut11::out::Output& output)
{
	ut11::detail::TestFixtureResults results;
	for(auto& fixture : fixtures)
	{
		auto result = fixture->Run(output);
		results.ran += result.ran;
		results.succeeded += result.succeeded;
	}
	return results;
}
