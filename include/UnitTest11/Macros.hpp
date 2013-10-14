#ifndef UNITTEST11_MACROS_HPP
#define UNITTEST11_MACROS_HPP

#ifdef __COUNTER__
#define UT11_UNIQUE_NUMBER __COUNTER__
#else
#define UT11_UNIQUE_NUMBER __LINE__
#endif


// Work around for Visual Studio compiler bug where variadic macros are not correctly expanded
#ifdef _MSC_VER
#define UT11_VA_NUM_ARGS_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...)	N
#define UT11_VA_NUM_ARGS_REVERSE_SEQUENCE 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
#define UT11_LEFT_PARENTHESIS (
#define UT11_RIGHT_PARENTHESIS )
#define UT11_VA_NARGS(...)						UT11_VA_NUM_ARGS_HELPER UT11_LEFT_PARENTHESIS __VA_ARGS__, UT11_VA_NUM_ARGS_REVERSE_SEQUENCE UT11_RIGHT_PARENTHESIS

#else
#define UT11_VA_NARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, N, ...) N
#define UT11_VA_NARGS(...) UT11_VA_NARGS_IMPL(__VA_ARGS__, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#endif

#define UT11_MACRO_CONCAT_IMPL(func, suffix) func##suffix
#define UT11_MACRO_CONCAT(func, suffix) UT11_MACRO_CONCAT_IMPL(func, suffix)

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

#ifdef _MSC_VER
#define UT11_MOCK_ACTION_N(N, ...) UT11_MACRO_CONCAT(UT11_MOCK_ACTION_, N) UT11_LEFT_PARENTHESIS __VA_ARGS__ UT11_RIGHT_PARENTHESIS
#define UT11_MOCK_FUNCTION_N(N, ...) UT11_MACRO_CONCAT(UT11_MOCK_FUNCTION_, N) UT11_LEFT_PARENTHESIS __VA_ARGS__ UT11_RIGHT_PARENTHESIS

#define UT11_MOCK_ACTION_CONST_N(N, ...) UT11_MACRO_CONCAT(UT11_MOCK_ACTION_CONST_, N) UT11_LEFT_PARENTHESIS __VA_ARGS__ UT11_RIGHT_PARENTHESIS
#define UT11_MOCK_FUNCTION_CONST_N(N, ...) UT11_MACRO_CONCAT(UT11_MOCK_FUNCTION_CONST_, N) UT11_LEFT_PARENTHESIS __VA_ARGS__ UT11_RIGHT_PARENTHESIS

#else
#define UT11_MOCK_ACTION_N(N, ...) UT11_MACRO_CONCAT(UT11_MOCK_ACTION_, N)(__VA_ARGS__)
#define UT11_MOCK_FUNCTION_N(N, ...) UT11_MACRO_CONCAT(UT11_MOCK_FUNCTION_, N)(__VA_ARGS__)

#define UT11_MOCK_ACTION_CONST_N(N, ...) UT11_MACRO_CONCAT(UT11_MOCK_ACTION_CONST_, N)(__VA_ARGS__)
#define UT11_MOCK_FUNCTION_CONST_N(N, ...) UT11_MACRO_CONCAT(UT11_MOCK_FUNCTION_CONST_, N)(__VA_ARGS__)
#endif

/*! \brief A mock action with no return values (Name, Arguments...) */
#define MockAction(...) UT11_MOCK_ACTION_N(UT11_VA_NARGS(__VA_ARGS__), __VA_ARGS__)

/*! \brief A mock function with a return value (Return, Name, Arguments...) */
#define MockFunction(...) UT11_MOCK_FUNCTION_N(UT11_VA_NARGS(__VA_ARGS__), __VA_ARGS__)

/*! \brief A mock const action with no return values (Name, Arguments...) */
#define MockActionConst(...) UT11_MOCK_ACTION_CONST_N(UT11_VA_NARGS(__VA_ARGS__), __VA_ARGS__)

/*! \brief A mock const function with a return value (Return, Name, Arguments...) */
#define MockFunctionConst(...) UT11_MOCK_FUNCTION_CONST_N(UT11_VA_NARGS(__VA_ARGS__), __VA_ARGS__)

/*! \brief Verify a mock function was called with the passed predicates (mock, arguments) */
#define MockVerify(...) ::ut11::detail::MockVerifyer<decltype(__VA_ARGS__)>(__VA_ARGS__, __LINE__, __FILE__)

/*! \brief Verify a mock function was called with the passed predicates the specified number of times (mock, count, arguments)  */
#define MockVerifyTimes(times, ...) ::ut11::detail::MockTimesVerifyer<decltype(times), decltype(__VA_ARGS__)>(__VA_ARGS__, times, __LINE__, __FILE__)

/*! \brief Declare a Test Fixture, adding it to the runner
*
* Adds a test fixture of type T to the runner.
* Passes any arguments given on the right of the fixture name to that fixture's constructor.
*/
#define DeclareFixture(...) static const int UT11_MACRO_CONCAT(ut11Fixture, UT11_UNIQUE_NUMBER) = ut11::detail::DeclareFixtureObj<__VA_ARGS__>(#__VA_ARGS__)

/*! \brief Assert that for the given Actual, the Expectation is true */
#define AssertThat(...) ut11::Assert::That(__LINE__, __FILE__, __VA_ARGS__)

#endif // UNITTEST11_MACROS_HPP
