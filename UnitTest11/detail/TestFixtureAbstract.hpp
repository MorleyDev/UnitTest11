#ifndef UT11_DETAIL_TESTFIXTUREABSTRACT_HPP_INCLUDED
#define UT11_DETAIL_TESTFIXTUREABSTRACT_HPP_INCLUDED

#include "TestFixtureResults.hpp"
#include "../Category.hpp"
#include "../out/Output.hpp"

#include <string>
#include <functional>
#include <set>

namespace ut11
{
	namespace detail
	{
		class TestFixtureAbstract
		{
		public:
			virtual ~TestFixtureAbstract();

			virtual void AddCategory(ut11::Category) = 0;
			virtual std::set<ut11::Category> GetCategories() const = 0;

			virtual void Given(std::string, std::function<void(void) >) = 0;
			virtual void When(std::string, std::function<void(void) >) = 0;
			virtual void Then(std::string, std::function<void(void) >) = 0;
			virtual void Finally(std::string, std::function<void(void) >) = 0;

			virtual std::string GetName() const = 0;

			virtual TestFixtureResults Run(out::Output&) = 0;
		};
	}
}

#endif // UT11_DETAIL_TESTFIXTUREABSTRACT_HPP_INCLUDED
