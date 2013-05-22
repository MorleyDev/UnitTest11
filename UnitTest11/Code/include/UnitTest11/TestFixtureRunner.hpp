#ifndef UNITTEST11_TESTFIXTURERUNNER_HPP
#define UNITTEST11_TESTFIXTURERUNNER_HPP

#include "Output.hpp"
#include "TestFixture.hpp"
#include <list>
#include <memory>

namespace ut11
{
    class TestFixtureRunner
    {
    public:
        void AddFixture(std::shared_ptr<TestFixtureAbstract> fixture);
        int Run(Output& output);

    private:
        std::list< std::shared_ptr<TestFixtureAbstract> > m_fixtures;
    };
}

#endif // UNITTEST11_TESTFIXTURERUNNER_HPP
