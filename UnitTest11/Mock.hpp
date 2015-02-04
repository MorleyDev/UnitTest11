#ifndef UNITTEST11_MOCK_HPP
#define UNITTEST11_MOCK_HPP

#include "detail/MockArgumentHandler.hpp"
#include "detail/MockReturnHandler.hpp"
#include "Assert/Fail.hpp"

#include <sstream>
#include <functional>

namespace ut11
{
	/*! \brief A Mock functor object that can be used to mock out injected an std::function or to build up a Mock class */
	template<typename T> class Mock;
	template<typename R, typename... ARGS> class Mock<R (ARGS...)>
	{
	public:
		Mock()
			: m_callbackHandler(),
			  m_argumentHandler(),
			  m_returnHandler()
		{
		}

		~Mock()
		{
		}

		R operator()(ARGS... args)
		{
			if ( m_callbackHandler )
				m_callbackHandler(args...);

			m_argumentHandler.AddCall(args...);
			return m_returnHandler(args...);
		}

		void SetCallback(std::function<void (const ARGS&...)> callback)
		{
			m_callbackHandler = callback;
		}

		template<typename V> void SetReturn(V value) { m_returnHandler.SetReturn(value); }

		void VerifyAny(std::size_t line, std::string file) const
		{
			if ( m_argumentHandler.TotalCount() == 0 )
				Assert::Fail(line, file, GetVerifyFailMessage());
		}

		template<typename... Expectations> void Verify(std::size_t line, std::string file, const Expectations&... expectations) const
		{
			if ( m_argumentHandler.CountCalls(expectations...) == 0 )
				Assert::Fail(line, file, GetVerifyFailMessage());
		}

		template<typename Operand, typename... Expectations> void VerifyTimes(std::size_t line, std::string file, const Operand& count, const Expectations&... expectations) const
		{
			VerifyTimes(typename std::is_integral<Operand>::type(), line, file, count, expectations...);
		}

	private:
		template<typename Operand, typename... Expectations> void VerifyTimes(std::false_type isNotOperand, std::size_t line, std::string file, const Operand& operand, const Expectations&... expectations) const
		{
			auto actual = m_argumentHandler.CountCalls(expectations...);
			if ( !operand(actual) )
				Assert::Fail(line, file, GetVerifyFailTimesMessageForOperand(operand, actual));
		}

		template<typename Count, typename... Expectations> void VerifyTimes(std::true_type isOperand, std::size_t line, std::string file, const Count& count, const Expectations&... expectations) const
		{
			auto actual = m_argumentHandler.CountCalls(expectations...);
			if ( actual != count )
				Assert::Fail(line, file, GetVerifyFailTimesMessageForCount(count, actual));
		}

		std::string GetVerifyFailMessage() const
		{
			return "Expected function call was not found";
		}

		std::string GetVerifyFailTimesMessageForCount(std::size_t expected, std::size_t actual) const
		{
			std::stringstream output;
			output << "Expected function to be called " << expected << " times was actually called " << actual << " times";
			return output.str();
		}

		template<typename Operand> std::string GetVerifyFailTimesMessageForOperand(Operand& operand, std::size_t actual) const
		{
			std::stringstream output;
			output << "Expected function call count was not found." << operand.GetErrorMessage(actual) << "\nWas actually called " << actual << " times";
			return output.str();
		}

		std::function<void (const ARGS&...)> m_callbackHandler;
		detail::MockArgumentHandler<ARGS...> m_argumentHandler;
		detail::MockReturnHandler<R, ARGS...> m_returnHandler;
	};
}


#endif // UNITTEST11_MOCK_HPP
