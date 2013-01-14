#ifndef UNITTEST11_MACROS_HPP
#define UNITTEST11_MACROS_HPP

#include "Global.hpp"
#include "Assert/That.hpp"

#define DeclareFixture(Fixture) ut11::DeclareFixtureObj<Fixture> ut11Fixture_##Fixture(#Fixture)

#define AssertThat(Actual, Expectation) ut11::Assert::That(__LINE__, __FILE__, Actual, Expectation)

#endif // UNITTEST11_MACROS_HPP
