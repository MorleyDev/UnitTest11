#ifndef UNITTEST11_TESTFIXTURE_HPP
#define UNITTEST11_TESTFIXTURE_HPP

#include "Output.hpp"
#include "Utility/TestStageBuilderImpl.hpp"

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

    class TestFixtureAbstract
    {
    public:
        virtual ~TestFixtureAbstract();

        virtual void Given(std::string, std::function<void(void)>) = 0;
        virtual void When(std::string, std::function<void(void)>) = 0;
        virtual void Then(std::string, std::function<void(void)>) = 0;
        virtual void Finally(std::string, std::function<void(void)>) = 0;

        virtual std::string GetName() = 0;

        virtual TestFixtureResults Run(Output&) = 0;
    };

    class TestFixture : public TestFixtureAbstract
    {
    public:
        void SetName(std::string name) { m_name = name; }
        virtual std::string GetName() { return m_name; }

        TestFixture();
        explicit TestFixture(std::string name);

        TestFixture(std::string name, std::unique_ptr<ut11::Utility::TestStageBuilder> builder);

        virtual ~TestFixture();
        virtual void Given(std::string description, std::function<void(void)> logic);
        virtual void When(std::string description, std::function<void(void)> logic);
        virtual void Then(std::string description, std::function<void(void)> logic);
        virtual void Finally(std::string description, std::function<void(void)> logic);

        virtual TestFixtureResults Run(Output& output);
        virtual void Run();

    private:
        std::string m_name;
        std::unique_ptr<ut11::Utility::TestStageBuilder> m_StageBuilder;
    };
}

#endif // UNITTEST11_TESTFIXTURE_HPP
