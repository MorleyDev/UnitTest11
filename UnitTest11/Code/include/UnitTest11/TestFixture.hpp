#ifndef UNITTEST11_TESTFIXTURE_HPP
#define UNITTEST11_TESTFIXTURE_HPP

#include "IOutput.hpp"
#include "Utility/TestStageBuilder.hpp"

#include <string>
#include <functional>

namespace ut11
{
    struct TestFixtureResults
    {
        TestFixtureResults() : ran(0), succeeded(0) { }

        std::size_t ran;
        std::size_t succeeded;
    };

    class ITestFixture
    {
    public:
        virtual ~ITestFixture();

        virtual void Given(std::string, std::function<void(void)>) = 0;
        virtual void When(std::string, std::function<void(void)>) = 0;
        virtual void Then(std::string, std::function<void(void)>) = 0;
        virtual void Finally(std::string, std::function<void(void)>) = 0;

        virtual TestFixtureResults Run(IOutput&) = 0;
    };

    class TestFixture : public ITestFixture
    {
    public:
        void SetName(std::string name) { m_name = name; }

        TestFixture();
        explicit TestFixture(std::string name);

        TestFixture(std::string name, std::unique_ptr<ut11::Utility::ITestStageBuilder> builder);

        virtual ~TestFixture();
        virtual void Given(std::string description, std::function<void(void)> logic);
        virtual void When(std::string description, std::function<void(void)> logic);
        virtual void Then(std::string description, std::function<void(void)> logic);
        virtual void Finally(std::string description, std::function<void(void)> logic);

        virtual TestFixtureResults Run(IOutput& output);
        virtual void Run();

    private:
        std::string m_name;
        std::unique_ptr<ut11::Utility::ITestStageBuilder> m_StageBuilder;
    };
}

#endif // UNITTEST11_TESTFIXTURE_HPP
