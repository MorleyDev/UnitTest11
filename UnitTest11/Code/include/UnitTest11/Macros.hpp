#ifndef UNITTEST11_MACROS_HPP
#define UNITTEST11_MACROS_HPP

#include "Global.hpp"
#include "Assert/That.hpp"
#include "Mock.hpp"

/*! \brief Declare a Test Fixture, adding it to the runner
 *
 * Adds a text fixture of type T to the runner. Can not add the same fixture multiple times (compilation error).
 */
#define DeclareFixture(Fixture) namespace { ut11::DeclareFixtureObj<Fixture> ut11Fixture_##Fixture(#Fixture); }

/*! \brief Assert that for the given Actual, the Expectation is true */
#define AssertThat(Actual, Expectation) ut11::Assert::That(__LINE__, __FILE__, Actual, Expectation)

#define UT11_MACRO_CONCAT(func, suffix) func##suffix

// There is probably some way to auto-generate these via recursive macros.
#define UT11_MOCK_ACTION_1(Name) ut11::Mock<void (void)> mock##Name; virtual void Name() { mock##Name(); }
#define UT11_MOCK_ACTION_2(Name, Arg1) ut11::Mock<void (Arg1)> mock##Name; virtual void Name(Arg1 a1) { mock##Name(a1); }
#define UT11_MOCK_ACTION_3(Name, Arg1, Arg2) ut11::Mock<void (Arg1, Arg2)> mock##Name; virtual void Name(Arg1 a1, Arg2 a2) { mock##Name(a1, a2); }
#define UT11_MOCK_ACTION_4(Name, Arg1, Arg2, Arg3) ut11::Mock<void (Arg1, Arg2, Arg3)> mock##Name; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3) { mock##Name(a1, a2, a3); }
#define UT11_MOCK_ACTION_5(Name, Arg1, Arg2, Arg3, Arg4) ut11::Mock<void (Arg1, Arg2, Arg3, Arg4)> mock##Name; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4) { mock##Name(a1, a2, a3, a4); }
#define UT11_MOCK_ACTION_6(Name, Arg1, Arg2, Arg3, Arg4, Arg5) ut11::Mock<void (Arg1, Arg2, Arg3, Arg4, Arg5)> mock##Name; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5) { mock##Name(a1, a2, a3, a4, a5); }
#define UT11_MOCK_ACTION_7(Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) ut11::Mock<void (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)> mock##Name; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6) { mock##Name(a1, a2, a3, a4, a5, a6); }
#define UT11_MOCK_ACTION_8(Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) ut11::Mock<void (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)> mock##Name; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7) { mock##Name(a1, a2, a3, a4, a5, a6, a7); }
#define UT11_MOCK_ACTION_9(Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) ut11::Mock<void (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)> mock##Name; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8) { mock##Name(a1, a2, a3, a4, a5, a6, a7, a8, a9); }
#define UT11_MOCK_ACTION_10(Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9) ut11::Mock<void (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)> mock##Name; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9) { mock##Name(a1, a2, a3, a4, a5, a6, a7, a8, a9); }

#define UT11_MOCK_FUNCTION_2(Return, Name) ut11::Mock<Return (void)> mock##Name; virtual Return Name() { return mock##Name(); }
#define UT11_MOCK_FUNCTION_3(Return, Name, Arg1) ut11::Mock<Return (Arg1)> mock##Name; virtual Return Name(Arg1 a1) { return mock##Name(a1); }
#define UT11_MOCK_FUNCTION_4(Return, Name, Arg1, Arg2) ut11::Mock<Return (Arg1, Arg2)> mock##Name; virtual Return Name(Arg1 a1, Arg2 a2) { return mock##Name(a1, a2); }
#define UT11_MOCK_FUNCTION_5(Return, Name, Arg1, Arg2, Arg3) ut11::Mock<Return (Arg1, Arg2, Arg3)> mock##Name; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3) { return mock##Name(a1, a2, a3); }
#define UT11_MOCK_FUNCTION_6(Return, Name, Arg1, Arg2, Arg3, Arg4) ut11::Mock<Return (Arg1, Arg2, Arg3, Arg4)> mock##Name; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4) { return mock##Name(a1, a2, a3, a4); }
#define UT11_MOCK_FUNCTION_7(Return, Name, Arg1, Arg2, Arg3, Arg4, Arg5) ut11::Mock<Return (Arg1, Arg2, Arg3, Arg4, Arg5)> mock##Name; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5) { return mock##Name(a1, a2, a3, a4, a5); }
#define UT11_MOCK_FUNCTION_8(Return, Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) ut11::Mock<Return (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)> mock##Name; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6) { return mock##Name(a1, a2, a3, a4, a5, a6); }
#define UT11_MOCK_FUNCTION_9(Return, Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) ut11::Mock<Return (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)> mock##Name; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7) { return mock##Name(a1, a2, a3, a4, a5, a6, a7); }
#define UT11_MOCK_FUNCTION_10(Return, Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) ut11::Mock<Return (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)> mock##Name; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8) { return mock##Name(a1, a2, a3, a4, a5, a6, a7, a8, a9); }
#define UT11_MOCK_FUNCTION_11(Return, Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9) ut11::Mock<Return (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)> mock##Name; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9) { return mock##Name(a1, a2, a3, a4, a5, a6, a7, a8, a9); }

#define UT11_MOCK_ACTION_N(N, args...) UT11_MACRO_CONCAT(UT11_MOCK_ACTION_, N)(args)
#define UT11_MOCK_FUNCTION_N(N, args...) UT11_MACRO_CONCAT(UT11_MOCK_FUNCTION_, N)(args)

#define UT11_VA_NARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, N, args...) N
#define UT11_VA_NARGS(args...) UT11_VA_NARGS_IMPL(args, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

/*! \brief A mock action with no return values (Name, Arguments...) */
#define MockAction(args...) UT11_MOCK_ACTION_N(UT11_VA_NARGS(args), args)

/*! \brief A mock function with a return value (Name, Return, Arguments...) */
#define MockFunction(args...) UT11_MOCK_FUNCTION_N(UT11_VA_NARGS(args), args)

#endif // UNITTEST11_MACROS_HPP
