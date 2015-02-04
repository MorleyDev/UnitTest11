/*
 * StdOutput.cpp
 *
 *  Created on: 22 May 2013
 *	  Author: Jason
 */

#include <UnitTest11/out/StdOutput.hpp>
#include <iostream>

ut11::out::StdOutput::StdOutput()
	: m_out(std::cout)
{
}

ut11::out::StdOutput::StdOutput(std::ostream& out)
	: m_out(out)
{
}

ut11::out::StdOutput::~StdOutput()
{
}

void ut11::out::StdOutput::Begin()
{
}

void ut11::out::StdOutput::BeginFixture(std::string name)
{
	m_out << "Fixture: " << name;
	m_given = "";
	m_when = "";
	m_finally = "";
}

void ut11::out::StdOutput::EndFixture(std::string)
{
	if (m_finally != "")
		m_out << "\n\tFinally: " << m_finally;
	m_out << std::endl;
}

void ut11::out::StdOutput::BeginTest()
{
	m_testStartTime = std::chrono::system_clock::now();
	m_testRunTime = std::chrono::system_clock::duration(0);
}

void ut11::out::StdOutput::EndTest()
{
	m_out << " [" << std::chrono::duration_cast<std::chrono::duration<long double>>(m_testRunTime).count() << "s]";
}

void ut11::out::StdOutput::BeginGiven(std::string given)
{
	m_testStartTime = std::chrono::system_clock::now();

	if (m_given == given)
		return;

	if ( m_finally != "" )
		m_out << "\n\tFinally: " << m_finally;

	m_given = given;
	m_when = "";
	m_out << "\n\tGiven: " << given;

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
	m_out << "\n\t\tWhen: " << when;

	m_testStartTime = std::chrono::system_clock::now();
}

void ut11::out::StdOutput::EndWhen(std::string)
{
	m_testRunTime +=  std::chrono::system_clock::now() - m_testStartTime;
}

void ut11::out::StdOutput::BeginThen(std::string then)
{
	m_out << "\n\t\t\tThen: " << then;

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
	m_out << "\nFinished!\nRan: " << ran
		  << "\nSucceeded: " << succeeded
		  << std::endl;
}

void ut11::out::StdOutput::OnError(const std::exception& exception)
{
	m_out << "\n\tFailed: std::exception was thrown [what(): " << exception.what() << "]";
}

void ut11::out::StdOutput::OnError(std::size_t line, std::string file, std::string message)
{
	if (m_finally != "")
	{
		m_out << "\n\tFinally: " << m_finally;
		m_finally = "";
	}

	m_out << "\n\tFailed: [" << line << ":" << file << "] " << message;
}

void ut11::out::StdOutput::OnUnknownError()
{
	m_out << "\n\tFailed: Unknown Error";
}
