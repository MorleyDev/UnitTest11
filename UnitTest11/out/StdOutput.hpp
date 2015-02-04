#ifndef UNITTEST11_STDOUTPUT_HPP
#define UNITTEST11_STDOUTPUT_HPP

#include "Output.hpp"
#include <chrono>
#include <ostream>

namespace ut11
{
	namespace out
	{
		class StdOutput : public Output
		{
		public:
			StdOutput();
			StdOutput(std::ostream&);
			virtual ~StdOutput();

			virtual void Begin();
			virtual void Finish(std::size_t ran, std::size_t succeeded);

			virtual void BeginFixture(std::string name);
			virtual void BeginTest();
			virtual void BeginGiven(std::string given);
			virtual void BeginWhen(std::string when);
			virtual void BeginThen(std::string then);
			virtual void BeginFinally(std::string finally);

			virtual void EndFixture(std::string);
			virtual void EndTest();
			virtual void EndGiven(std::string);
			virtual void EndWhen(std::string);
			virtual void EndThen(std::string);
			virtual void EndFinally(std::string);

			virtual void OnError(std::size_t line, std::string file, std::string message);
			virtual void OnError(const std::exception& exception);

			virtual void OnUnknownError();

		private:
			std::ostream& m_out;
			std::string m_given, m_when, m_finally;
			std::chrono::system_clock::duration m_testRunTime;
			std::chrono::system_clock::time_point m_testStartTime;
		};
	}
}

#endif // UNITTEST11_STDOUTPUT_HPP
