#ifndef UNITTEST11_STDOUTPUT_HPP
#define UNITTEST11_STDOUTPUT_HPP

#include "IOutput.hpp"
#include <iostream>

namespace ut11
{
    class StdOutput : public IOutput
    {
    public:
        virtual void Begin() { }

        virtual void BeginFixture(std::string name)
        {
        	std::cout << "Fixture: " << name << std::endl;
        	m_given = "";
        	m_when = "";
        }

        virtual void BeginGiven(std::string given)
        {
        	if ( m_given == given )
        		return;

        	m_given = given;
        	std::cout << "    Given: " << given << std::endl;
        }

        virtual void BeginWhen(std::string when)
        {
        	if ( m_when == when )
        		return;

        	m_when = when;
        	std::cout << "        When: " << when << std::endl;
        }

        virtual void BeginThen(std::string then)
        {
        	std::cout << "            Then: " << then << std::endl;
        }

        virtual void BeginFinally(std::string finally)
        {
        	std::cout << "    Finally: " << finally << std::endl;
        	m_given = "";
        	m_when = "";
        }

        virtual void EndFixture(std::string) { }
        virtual void EndGiven(std::string) { }
        virtual void EndWhen(std::string) { }
        virtual void EndThen(std::string) { }
        virtual void EndFinally(std::string) { }

        virtual void Finish(std::size_t ran, std::size_t succeeded)
        {
        	std::cout << "Finished!\nRan: " << ran << "\nSucceeded: " << succeeded << std::endl;
        }

        virtual void OnError(std::size_t line, std::string file, std::string message)
        {
        	std::cout << "    Failed: [" << line << ":" << file << "] " << message << std::endl;
        }

        virtual void OnError(const std::exception& exception)
        {
        	std::cout << "    Failed: std::exception was thrown [what(): " << exception.what() << "]" << std::endl;
        }

        virtual void OnUnknownError()
        {
        	std::cout << "    Failed: Unknown Error" << std::endl;
        }

    private:
        std::string m_given, m_when;
    };
}

#endif // UNITTEST11_STDOUTPUT_HPP
