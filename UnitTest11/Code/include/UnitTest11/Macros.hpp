#ifndef UNITTEST11_MACROS_HPP
#define UNITTEST11_MACROS_HPP

#include "Global.hpp"
#include "Assert/That.hpp"

/*! \brief Declare a Test Fixture, adding it to the runner
 *
 * Adds a text fixture of type T to the runner. Can not add the same fixture multiple times (compilation error).
 */
#define DeclareFixture(Fixture) namespace { ut11::DeclareFixtureObj<Fixture> ut11Fixture_##Fixture(#Fixture); }

/*! \brief Assert that for the given Actual, the Expectation is true */
#define AssertThat(Actual, Expectation) ut11::Assert::That(__LINE__, __FILE__, Actual, Expectation)

#endif // UNITTEST11_MACROS_HPP
