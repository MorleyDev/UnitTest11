#ifndef UNITTEST11_TESTFIXTURERUNNER_HPP
#define UNITTEST11_TESTFIXTURERUNNER_HPP

#include "Output.hpp"
#include "TestFixture.hpp"
#include <map>
#include <memory>

namespace ut11
{
    class TestFixtureRunner
    {
    public:
        void AddFixture(std::shared_ptr<TestFixtureAbstract> fixture);

        int Run(Output& output);

        int RunCategories(Output& output, std::vector<std::string>);

    private:
        std::vector<std::shared_ptr<ut11::TestFixtureAbstract>> GetFixtures() const;
        std::vector<std::shared_ptr<ut11::TestFixtureAbstract>> GetFixturesThatMatchCategories(const std::vector<std::string>& desiredCategories) const;

        static bool DoesFixtureMatchCategories(std::shared_ptr<ut11::TestFixtureAbstract> fixture, const std::vector<std::string>& desiredCategories);
        static ut11::TestFixtureResults RunTestFixtures(std::vector<std::shared_ptr<ut11::TestFixtureAbstract>> fixtures, ut11::Output& output);

        std::map< std::string, std::shared_ptr<TestFixtureAbstract> > m_fixtures;
    };
}

#endif // UNITTEST11_TESTFIXTURERUNNER_HPP
