#ifndef UNITTEST11_TESTFIXTURE_HPP
#define UNITTEST11_TESTFIXTURE_HPP

#include "Category.hpp"
#include "out/Output.hpp"
#include "Utility/TestStageBuilderImpl.hpp"

#include <string>
#include <functional>
#include <set>

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

        virtual void AddCategory(ut11::Category) = 0;
        virtual std::set<ut11::Category> GetCategories() const = 0;

        virtual void Given(std::string, std::function<void(void)>) = 0;
        virtual void When(std::string, std::function<void(void)>) = 0;
        virtual void Then(std::string, std::function<void(void)>) = 0;
        virtual void Finally(std::string, std::function<void(void)>) = 0;

        virtual std::string GetName() const = 0;

		virtual TestFixtureResults Run(out::Output&) = 0;
    };

    class TestFixture : public TestFixtureAbstract
    {
    public:
        TestFixture();
        explicit TestFixture(std::string name);
        TestFixture(std::string name, std::unique_ptr<ut11::Utility::TestStageBuilder> builder);
        virtual ~TestFixture();

        virtual void AddCategory(ut11::Category);
        virtual std::set<ut11::Category> GetCategories() const;

        virtual void Given(std::string description, std::function<void(void)> logic);
        virtual void When(std::string description, std::function<void(void)> logic);
        virtual void Then(std::string description, std::function<void(void)> logic);
        virtual void Finally(std::string description, std::function<void(void)> logic);

        void SetName(std::string name) { m_name = name; }
        virtual std::string GetName() const { return m_name; }

		virtual TestFixtureResults Run(out::Output& output);
        virtual void Run();

    private:
        std::string m_name;
        std::unique_ptr<ut11::Utility::TestStageBuilder> m_StageBuilder;
        std::set<ut11::Category> m_categories;
    };
}

#endif // UNITTEST11_TESTFIXTURE_HPP
