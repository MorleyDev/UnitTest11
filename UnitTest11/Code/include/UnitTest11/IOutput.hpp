#ifndef UNITTEST11_IOUTPUT_HPP
#define UNITTEST11_IOUTPUT_HPP

#include <string>
#include <exception>

namespace ut11
{
    class IOutput
    {
    public:
        virtual ~IOutput() { }

        virtual void Begin() = 0;
        virtual void Finish(std::size_t ran, std::size_t succeeded) = 0;

        virtual void BeginFixture(std::string) = 0;
        virtual void EndFixture(std::string) = 0;

        virtual void BeginGiven(std::string) = 0;
        virtual void EndGiven(std::string) = 0;

        virtual void BeginWhen(std::string) = 0;
        virtual void EndWhen(std::string) = 0;

        virtual void BeginThen(std::string) = 0;
        virtual void EndThen(std::string) = 0;

        virtual void BeginFinally(std::string) = 0;
        virtual void EndFinally(std::string) = 0;

        virtual void OnError(std::size_t line, std::string file, std::string message) = 0;
        virtual void OnError(const std::exception& exception) = 0;
        virtual void OnUnknownError() = 0;
    };
}

#endif // UNITTEST11_IOUTPUT_HPP
