/*
 * StdOutput.cpp
 *
 *  Created on: 22 May 2013
 *      Author: Jason
 */

#include <UnitTest11/StdOutput.hpp>
#include <iostream>

ut11::StdOutput::~StdOutput()
{
}

void ut11::StdOutput::Begin()
{
}

void ut11::StdOutput::BeginFixture(std::string name)
{
	std::cout << "Fixture: " << name << std::endl;
	m_given = "";
	m_when = "";
	m_finally = "";
}

void ut11::StdOutput::EndFixture(std::string)
{
	if ( m_finally != "" )
		std::cout << "    Finally: " << m_finally << std::endl;
}


void ut11::StdOutput::BeginTest()
{
	m_testStartTime = std::chrono::system_clock::now();
	m_testRunTime = std::chrono::system_clock::duration(0);
}

void ut11::StdOutput::EndTest()
{
	std::cout << " [" << std::chrono::duration_cast<std::chrono::duration<float>>(m_testRunTime).count() << "s]" << std::endl;
}

void ut11::StdOutput::BeginGiven(std::string given)
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

void ut11::StdOutput::EndGiven(std::string)
{
	m_testRunTime +=  std::chrono::system_clock::now() - m_testStartTime;
}

void ut11::StdOutput::BeginWhen(std::string when)
{
	m_testStartTime = std::chrono::system_clock::now();

	if (m_when == when)
		return;

	m_when = when;
	std::cout << "        When: " << when << std::endl;

	m_testStartTime = std::chrono::system_clock::now();
}

void ut11::StdOutput::EndWhen(std::string)
{
	m_testRunTime +=  std::chrono::system_clock::now() - m_testStartTime;
}

void ut11::StdOutput::BeginThen(std::string then)
{
	std::cout << "            Then: " << then;

	m_testStartTime = std::chrono::system_clock::now();
}

void ut11::StdOutput::EndThen(std::string)
{
	m_testRunTime +=  std::chrono::system_clock::now() - m_testStartTime;
}

void ut11::StdOutput::BeginFinally(std::string finally)
{
	m_finally = finally;

	m_testStartTime = std::chrono::system_clock::now();
}

void ut11::StdOutput::EndFinally(std::string)
{
	m_testRunTime +=  std::chrono::system_clock::now() - m_testStartTime;
}

void ut11::StdOutput::Finish(std::size_t ran, std::size_t succeeded)
{
	std::cout << "Finished!\nRan: " << ran
			<< "\nSucceeded: " << succeeded
			<< std::endl;
}

void ut11::StdOutput::OnError(const std::exception& exception)
{
	std::cout << "    Failed: std::exception was thrown [what(): "
			<< exception.what() << "]" << std::endl;
}

void ut11::StdOutput::OnError(std::size_t line, std::string file, std::string message)
{
	std::cout << "    Failed: [" << line << ":" << file << "] " << message
			  << std::endl;
}

void ut11::StdOutput::OnUnknownError()
{
	std::cout << "    Failed: Unknown Error" << std::endl;
}


