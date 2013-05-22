#ifndef UNITTEST11_STDOUTPUT_HPP
#define UNITTEST11_STDOUTPUT_HPP

#include "Output.hpp"

namespace ut11
{
    class StdOutput : public Output
    {
    public:
    	virtual ~StdOutput();

    	virtual void Begin();
        virtual void Finish(std::size_t ran, std::size_t succeeded);

        virtual void BeginFixture(std::string name);
        virtual void BeginGiven(std::string given);
        virtual void BeginWhen(std::string when);
        virtual void BeginThen(std::string then);
        virtual void BeginFinally(std::string finally);

        virtual void EndFixture(std::string);
        virtual void EndGiven(std::string);
        virtual void EndWhen(std::string);
        virtual void EndThen(std::string);
        virtual void EndFinally(std::string);

        virtual void OnError(std::size_t line, std::string file, std::string message);
        virtual void OnError(const std::exception& exception);

        virtual void OnUnknownError();

    private:
        std::string m_given, m_when;
    };
}

#endif // UNITTEST11_STDOUTPUT_HPP
