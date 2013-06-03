#ifndef UNITTEST11_MACROS_HPP
#define UNITTEST11_MACROS_HPP

#include "Global.hpp"
#include "Assert/That.hpp"
#include "Mock.hpp"

#define UT11_VA_NARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, N, args...) N
#define UT11_VA_NARGS(args...) UT11_VA_NARGS_IMPL(args, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)

#define UT11_MACRO_CONCAT(func, suffix) func##suffix

// There is probably some way to auto-generate these via recursive macros.
#define UT11_DECLARE_FIXTURE_2(line, Arguments...)  static auto ut11Fixture##line = ut11::DeclareFixtureObj<Arguments>(#Arguments)
#define UT11_DECLARE_FIXTURE_3(line, Arguments...)  static auto ut11Fixture##line = ut11::DeclareFixtureObj<Arguments>(#Arguments)
#define UT11_DECLARE_FIXTURE_4(line, Arguments...)  static auto ut11Fixture##line = ut11::DeclareFixtureObj<Arguments(#Arguments)
#define UT11_DECLARE_FIXTURE_5(line, Arguments...)  static auto ut11Fixture##line = ut11::DeclareFixtureObj<Arguments>(#Arguments)
#define UT11_DECLARE_FIXTURE_6(line, Arguments...)  static auto ut11Fixture##line = ut11::DeclareFixtureObj<Arguments>(#Arguments)
#define UT11_DECLARE_FIXTURE_7(line, Arguments...)  static auto ut11Fixture##line = ut11::DeclareFixtureObj<Arguments>(#Arguments)
#define UT11_DECLARE_FIXTURE_8(line, Arguments...)  static auto ut11Fixture##line = ut11::DeclareFixtureObj<Arguments>(#Arguments)
#define UT11_DECLARE_FIXTURE_9(line, Arguments...)  static auto ut11Fixture##line = ut11::DeclareFixtureObj<Arguments>(#Arguments)
#define UT11_DECLARE_FIXTURE_10(line, Arguments...) static auto ut11Fixture##line = ut11::DeclareFixtureObj<Arguments>(#Arguments)

#define UT11_MOCK_ACTION_1(Name) mutable ut11::Mock<void (void)> mock##Name; virtual void Name() { mock##Name(); }
#define UT11_MOCK_ACTION_2(Name, Arg1) mutable ut11::Mock<void (Arg1)> mock##Name; virtual void Name(Arg1 a1) { mock##Name(a1); }
#define UT11_MOCK_ACTION_3(Name, Arg1, Arg2) mutable ut11::Mock<void (Arg1, Arg2)> mock##Name; virtual void Name(Arg1 a1, Arg2 a2) { mock##Name(a1, a2); }
#define UT11_MOCK_ACTION_4(Name, Arg1, Arg2, Arg3) mutable ut11::Mock<void (Arg1, Arg2, Arg3)> mock##Name; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3) { mock##Name(a1, a2, a3); }
#define UT11_MOCK_ACTION_5(Name, Arg1, Arg2, Arg3, Arg4) mutable ut11::Mock<void (Arg1, Arg2, Arg3, Arg4)> mock##Name; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4) { mock##Name(a1, a2, a3, a4); }
#define UT11_MOCK_ACTION_6(Name, Arg1, Arg2, Arg3, Arg4, Arg5) mutable ut11::Mock<void (Arg1, Arg2, Arg3, Arg4, Arg5)> mock##Name; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5) { mock##Name(a1, a2, a3, a4, a5); }
#define UT11_MOCK_ACTION_7(Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) mutable ut11::Mock<void (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)> mock##Name; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6) { mock##Name(a1, a2, a3, a4, a5, a6); }
#define UT11_MOCK_ACTION_8(Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) mutable ut11::Mock<void (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)> mock##Name; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7) { mock##Name(a1, a2, a3, a4, a5, a6, a7); }
#define UT11_MOCK_ACTION_9(Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) mutable ut11::Mock<void (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)> mock##Name; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8) { mock##Name(a1, a2, a3, a4, a5, a6, a7, a8, a9); }
#define UT11_MOCK_ACTION_10(Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9) mutable ut11::Mock<void (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)> mock##Name; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9) { mock##Name(a1, a2, a3, a4, a5, a6, a7, a8, a9); }

#define UT11_MOCK_FUNCTION_2(Return, Name) mutable ut11::Mock<Return (void)> mock##Name; virtual Return Name() { return mock##Name(); }
#define UT11_MOCK_FUNCTION_3(Return, Name, Arg1) mutable ut11::Mock<Return (Arg1)> mock##Name; virtual Return Name(Arg1 a1) { return mock##Name(a1); }
#define UT11_MOCK_FUNCTION_4(Return, Name, Arg1, Arg2) mutable ut11::Mock<Return (Arg1, Arg2)> mock##Name; virtual Return Name(Arg1 a1, Arg2 a2) { return mock##Name(a1, a2); }
#define UT11_MOCK_FUNCTION_5(Return, Name, Arg1, Arg2, Arg3) mutable ut11::Mock<Return (Arg1, Arg2, Arg3)> mock##Name; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3) { return mock##Name(a1, a2, a3); }
#define UT11_MOCK_FUNCTION_6(Return, Name, Arg1, Arg2, Arg3, Arg4) mutable ut11::Mock<Return (Arg1, Arg2, Arg3, Arg4)> mock##Name; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4) { return mock##Name(a1, a2, a3, a4); }
#define UT11_MOCK_FUNCTION_7(Return, Name, Arg1, Arg2, Arg3, Arg4, Arg5) mutable ut11::Mock<Return (Arg1, Arg2, Arg3, Arg4, Arg5)> mock##Name; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5) { return mock##Name(a1, a2, a3, a4, a5); }
#define UT11_MOCK_FUNCTION_8(Return, Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) mutable ut11::Mock<Return (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)> mock##Name; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6) { return mock##Name(a1, a2, a3, a4, a5, a6); }
#define UT11_MOCK_FUNCTION_9(Return, Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) mutable ut11::Mock<Return (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)> mock##Name; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7) { return mock##Name(a1, a2, a3, a4, a5, a6, a7); }
#define UT11_MOCK_FUNCTION_10(Return, Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) mutable ut11::Mock<Return (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)> mock##Name; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8) { return mock##Name(a1, a2, a3, a4, a5, a6, a7, a8, a9); }
#define UT11_MOCK_FUNCTION_11(Return, Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9) mutable ut11::Mock<Return (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)> mock##Name; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9) { return mock##Name(a1, a2, a3, a4, a5, a6, a7, a8, a9); }

#define UT11_MOCK_ACTION_CONST_1(Name) mutable ut11::Mock<void (void)> mock##Name##Const; virtual void Name() const { mock##Name##Const(); }
#define UT11_MOCK_ACTION_CONST_2(Name, Arg1) mutable ut11::Mock<void (Arg1)> mock##Name##Const; virtual void Name(Arg1 a1) const { mock##Name##Const(a1); }
#define UT11_MOCK_ACTION_CONST_3(Name, Arg1, Arg2) mutable ut11::Mock<void (Arg1, Arg2)> mock##Name##Const; virtual void Name(Arg1 a1, Arg2 a2) const { mock##Name##Const(a1, a2); }
#define UT11_MOCK_ACTION_CONST_4(Name, Arg1, Arg2, Arg3) mutable ut11::Mock<void (Arg1, Arg2, Arg3)> mock##Name##Const; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3) const { mock##Name##Const(a1, a2, a3); }
#define UT11_MOCK_ACTION_CONST_5(Name, Arg1, Arg2, Arg3, Arg4) mutable ut11::Mock<void (Arg1, Arg2, Arg3, Arg4)> mock##Name##Const; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4) const { mock##Name##Const(a1, a2, a3, a4); }
#define UT11_MOCK_ACTION_CONST_6(Name, Arg1, Arg2, Arg3, Arg4, Arg5) mutable ut11::Mock<void (Arg1, Arg2, Arg3, Arg4, Arg5)> mock##Name##Const; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5) const { mock##Name##Const(a1, a2, a3, a4, a5); }
#define UT11_MOCK_ACTION_CONST_7(Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) mutable ut11::Mock<void (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)> mock##Name##Const; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6) const { mock##Name##Const(a1, a2, a3, a4, a5, a6); }
#define UT11_MOCK_ACTION_CONST_8(Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) mutable ut11::Mock<void (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)> mock##Name##Const; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7) const { mock##Name##Const(a1, a2, a3, a4, a5, a6, a7); }
#define UT11_MOCK_ACTION_CONST_9(Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) mutable ut11::Mock<void (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)> mock##Name##Const; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8) const { mock##Name##Const(a1, a2, a3, a4, a5, a6, a7, a8, a9); }
#define UT11_MOCK_ACTION_CONST_10(Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9) mutable ut11::Mock<void (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)> mock##Name##Const; virtual void Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9) const { mock##Name##Const(a1, a2, a3, a4, a5, a6, a7, a8, a9); }

#define UT11_MOCK_FUNCTION_CONST_2(Return, Name) mutable ut11::Mock<Return (void)> mock##Name##Const; virtual Return Name() const { return mock##Name##Const(); }
#define UT11_MOCK_FUNCTION_CONST_3(Return, Name, Arg1) mutable ut11::Mock<Return (Arg1)> mock##Name##Const; virtual Return Name(Arg1 a1) const { return mock##Name##Const(a1); }
#define UT11_MOCK_FUNCTION_CONST_4(Return, Name, Arg1, Arg2) mutable ut11::Mock<Return (Arg1, Arg2)> mock##Name##Const; virtual Return Name(Arg1 a1, Arg2 a2) const { return mock##Name##Const(a1, a2); }
#define UT11_MOCK_FUNCTION_CONST_5(Return, Name, Arg1, Arg2, Arg3) mutable ut11::Mock<Return (Arg1, Arg2, Arg3)> mock##Name##Const; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3) const { return mock##Name##Const(a1, a2, a3); }
#define UT11_MOCK_FUNCTION_CONST_6(Return, Name, Arg1, Arg2, Arg3, Arg4) mutable ut11::Mock<Return (Arg1, Arg2, Arg3, Arg4)> mock##Name##Const; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4) const { return mock##Name##Const(a1, a2, a3, a4); }
#define UT11_MOCK_FUNCTION_CONST_7(Return, Name, Arg1, Arg2, Arg3, Arg4, Arg5) mutable ut11::Mock<Return (Arg1, Arg2, Arg3, Arg4, Arg5)> mock##Name##Const; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5) const { return mock##Name##Const(a1, a2, a3, a4, a5); }
#define UT11_MOCK_FUNCTION_CONST_8(Return, Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) mutable ut11::Mock<Return (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)> mock##Name##Const; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6) const { return mock##Name##Const(a1, a2, a3, a4, a5, a6); }
#define UT11_MOCK_FUNCTION_CONST_9(Return, Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) mutable ut11::Mock<Return (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)> mock##Name##Const; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7) const { return mock##Name##Const(a1, a2, a3, a4, a5, a6, a7); }
#define UT11_MOCK_FUNCTION_CONST_10(Return, Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) mutable ut11::Mock<Return (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)> mock##Name##Const; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8) const { return mock##Name##Const(a1, a2, a3, a4, a5, a6, a7, a8, a9); }
#define UT11_MOCK_FUNCTION_CONST_11(Return, Name, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9) mutable ut11::Mock<Return (Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)> mock##Name##Const; virtual Return Name(Arg1 a1, Arg2 a2, Arg3 a3, Arg4 a4, Arg5 a5, Arg6 a6, Arg7 a7, Arg8 a8, Arg9 a9) const { return mock##Name##Const(a1, a2, a3, a4, a5, a6, a7, a8, a9); }

#define UT11_MOCK_VERIFY_1(mock) (mock).Verify(__LINE__, __FILE__)
#define UT11_MOCK_VERIFY_2(mock, Arg1) (mock).Verify(__LINE__, __FILE__, Arg1)
#define UT11_MOCK_VERIFY_3(mock, Arg1, Arg2) (mock).Verify(__LINE__, __FILE__, Arg1, Arg2)
#define UT11_MOCK_VERIFY_4(mock, Arg1, Arg2, Arg3) (mock).Verify(__LINE__, __FILE__, Arg1, Arg2, Arg3)
#define UT11_MOCK_VERIFY_5(mock, Arg1, Arg2, Arg3, Arg4) (mock).Verify(__LINE__, __FILE__, Arg1, Arg2, Arg3, Arg4)
#define UT11_MOCK_VERIFY_6(mock, Arg1, Arg2, Arg3, Arg4, Arg5) (mock).Verify(__LINE__, __FILE__, Arg1, Arg2, Arg3, Arg4, Arg5)
#define UT11_MOCK_VERIFY_7(mock, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) (mock).Verify(__LINE__, __FILE__, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)
#define UT11_MOCK_VERIFY_8(mock, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) (mock).Verify(__LINE__, __FILE__, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)
#define UT11_MOCK_VERIFY_9(mock, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) (mock).Verify(__LINE__, __FILE__, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)
#define UT11_MOCK_VERIFY_10(mock, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9) (mock).Verify(__LINE__, __FILE__, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)

#define UT11_MOCK_VERIFYTIMES_2(mock, count) (mock).VerifyTimes(__LINE__, __FILE__, count)
#define UT11_MOCK_VERIFYTIMES_3(mock, count, Arg1) (mock).VerifyTimes(__LINE__, __FILE__, count, Arg1)
#define UT11_MOCK_VERIFYTIMES_4(mock, count, Arg1, Arg2) (mock).VerifyTimes(__LINE__, __FILE__, count, Arg1, Arg2)
#define UT11_MOCK_VERIFYTIMES_5(mock, count, Arg1, Arg2, Arg3) (mock).VerifyTimes(__LINE__, __FILE__, count, Arg1, Arg2, Arg3)
#define UT11_MOCK_VERIFYTIMES_6(mock, count, Arg1, Arg2, Arg3, Arg4) (mock).VerifyTimes(__LINE__, __FILE__, count, Arg1, Arg2, Arg3, Arg4)
#define UT11_MOCK_VERIFYTIMES_7(mock, count, Arg1, Arg2, Arg3, Arg4, Arg5) (mock).VerifyTimes(__LINE__, __FILE__, count, Arg1, Arg2, Arg3, Arg4, Arg5)
#define UT11_MOCK_VERIFYTIMES_8(mock, count, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6) (mock).VerifyTimes(__LINE__, __FILE__, count, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)
#define UT11_MOCK_VERIFYTIMES_9(mock, count, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7) (mock).VerifyTimes(__LINE__, __FILE__, count, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)
#define UT11_MOCK_VERIFYTIMES_10(mock, count, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8) (mock).VerifyTimes(__LINE__, __FILE__, count, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)
#define UT11_MOCK_VERIFYTIMES_11(mock, count, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9) (mock).VerifyTimes(__LINE__, __FILE__, count, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)

#define UT11_DECLARE_FIXTURE_N(N, args...) UT11_MACRO_CONCAT(UT11_DECLARE_FIXTURE_, N)(args)

#define UT11_MOCK_ACTION_N(N, args...) UT11_MACRO_CONCAT(UT11_MOCK_ACTION_, N)(args)
#define UT11_MOCK_FUNCTION_N(N, args...) UT11_MACRO_CONCAT(UT11_MOCK_FUNCTION_, N)(args)
#define UT11_MOCK_VERIFY_N(N, args...) UT11_MACRO_CONCAT(UT11_MOCK_VERIFY_, N)(args)
#define UT11_MOCK_VERIFYTIMES_N(N, args...) UT11_MACRO_CONCAT(UT11_MOCK_VERIFYTIMES_, N)(args)

#define UT11_MOCK_ACTION_CONST_N(N, args...) UT11_MACRO_CONCAT(UT11_MOCK_ACTION_CONST_, N)(args)
#define UT11_MOCK_FUNCTION_CONST_N(N, args...) UT11_MACRO_CONCAT(UT11_MOCK_FUNCTION_CONST_, N)(args)

/*! \brief A mock action with no return values (Name, Arguments...) */
#define MockAction(args...) UT11_MOCK_ACTION_N(UT11_VA_NARGS(args), args)

/*! \brief A mock function with a return value (Return, Name, Arguments...) */
#define MockFunction(args...) UT11_MOCK_FUNCTION_N(UT11_VA_NARGS(args), args)

/*! \brief Verify a mock function was called with the passed predicates (mock, arguments) */
#define MockVerify(args...) UT11_MOCK_VERIFY_N(UT11_VA_NARGS(args), args)

/*! \brief Verify a mock function was called with the passed predicates the specified number of times (mock, count, arguments)  */
#define MockVerifyTimes(args...) UT11_MOCK_VERIFYTIMES_N(UT11_VA_NARGS(args), args)

/*! \brief Verify a mock was called more than once with any arguments */
#define MockVerifyAny(mock) (mock).VerifyAny(__LINE__, __FILE__)

/*! \brief A mock const action with no return values (Name, Arguments...) */
#define MockActionConst(args...) UT11_MOCK_ACTION_CONST_N(UT11_VA_NARGS(args), args)

/*! \brief A mock const function with a return value (Return, Name, Arguments...) */
#define MockFunctionConst(args...) UT11_MOCK_FUNCTION_CONST_N(UT11_VA_NARGS(args), args)

/*! \brief Declare a Test Fixture, adding it to the runner
 *
 * Adds a test fixture of type T to the runner.
 * Passes any arguments given on the right of the fixture name to that fixture's constructor.
 * Can not add the same fixture multiple times (compilation error).
 */
#define DeclareFixture(args...) UT11_DECLARE_FIXTURE_N(UT11_VA_NARGS(__LINE__, args), __LINE__, args)

/*! \brief Assert that for the given Actual, the Expectation is true */
#define AssertThat(Actual, Expectation) ut11::Assert::That(__LINE__, __FILE__, Actual, Expectation)

#endif // UNITTEST11_MACROS_HPP
