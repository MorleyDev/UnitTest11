#ifndef UNITTEST11_TESTFIXTURERUNNER_HPP
#define UNITTEST11_TESTFIXTURERUNNER_HPP

#include "IOutput.hpp"
#include "TestFixture.hpp"
#include <list>
#include <memory>

namespace ut11
{
    class TestFixtureRunner
    {
    public:
        void AddFixture(std::shared_ptr<ITestFixture> fixture);
        int Run(IOutput& output);

    private:
        std::list< std::shared_ptr<ITestFixture> > m_fixtures;
    };
}

#endif // UNITTEST11_TESTFIXTURERUNNER_HPP
