/*
 * StdOutput.cpp
 *
 *  Created on: 22 May 2013
 *      Author: Jason
 */

#include <UnitTest11/out/StdOutput.hpp>
#include <iostream>

ut11::out::StdOutput::~StdOutput()
{
}

void ut11::out::StdOutput::Begin()
{
}

void ut11::out::StdOutput::BeginFixture(std::string name)
{
    std::cout << "Fixture: " << name << std::endl;
    m_given = "";
    m_when = "";
    m_finally = "";
}

void ut11::out::StdOutput::EndFixture(std::string)
{
    if ( m_finally != "" )
        std::cout << "    Finally: " << m_finally << std::endl;
}


void ut11::out::StdOutput::BeginTest()
{
    m_testStartTime = std::chrono::system_clock::now();
    m_testRunTime = std::chrono::system_clock::duration(0);
}

void ut11::out::StdOutput::EndTest()
{
    std::cout << " [" << std::chrono::duration_cast<std::chrono::duration<float>>(m_testRunTime).count() << "s]" << std::endl;
}

void ut11::out::StdOutput::BeginGiven(std::string given)
{
    m_testStartTime = std::chrono::system_clock::now();

    if (m_given == given)
        return;

    if ( m_finally != "" )
        std::cout << "    Finally: " << m_finally << std::endl;

    m_given = given;
    m_when = "";
    std::cout << "    Given: " << given << std::endl;

    m_testStartTime = std::chrono::system_clock::now();
}

void ut11::out::StdOutput::EndGiven(std::string)
{
    m_testRunTime +=  std::chrono::system_clock::now() - m_testStartTime;
}

void ut11::out::StdOutput::BeginWhen(std::string when)
{
    m_testStartTime = std::chrono::system_clock::now();

    if (m_when == when)
        return;

    m_when = when;
    std::cout << "        When: " << when << std::endl;

    m_testStartTime = std::chrono::system_clock::now();
}

void ut11::out::StdOutput::EndWhen(std::string)
{
    m_testRunTime +=  std::chrono::system_clock::now() - m_testStartTime;
}

void ut11::out::StdOutput::BeginThen(std::string then)
{
    std::cout << "            Then: " << then;

    m_testStartTime = std::chrono::system_clock::now();
}

void ut11::out::StdOutput::EndThen(std::string)
{
    m_testRunTime +=  std::chrono::system_clock::now() - m_testStartTime;
}

void ut11::out::StdOutput::BeginFinally(std::string finally)
{
    m_finally = finally;

    m_testStartTime = std::chrono::system_clock::now();
}

void ut11::out::StdOutput::EndFinally(std::string)
{
    m_testRunTime +=  std::chrono::system_clock::now() - m_testStartTime;
}

void ut11::out::StdOutput::Finish(std::size_t ran, std::size_t succeeded)
{
    std::cout << "Finished!\nRan: " << ran
            << "\nSucceeded: " << succeeded
            << std::endl;
}

void ut11::out::StdOutput::OnError(const std::exception& exception)
{
    std::cout << "    Failed: std::exception was thrown [what(): "
            << exception.what() << "]" << std::endl;
}

void ut11::out::StdOutput::OnError(std::size_t line, std::string file, std::string message)
{
    std::cout << "    Failed: [" << line << ":" << file << "] " << message
              << std::endl;
}

void ut11::out::StdOutput::OnUnknownError()
{
    std::cout << "    Failed: Unknown Error" << std::endl;
}


