#ifndef UNITTEST11_TESTFAILEDEXCEPTION_HPP
#define UNITTEST11_TESTFAILEDEXCEPTION_HPP

#include <string>

namespace ut11
{
    class TestFailedException
    {
    public:
        TestFailedException()
            : m_line(0),
              m_file(),
              m_message()
        {

        }

        TestFailedException(std::size_t line, std::string file, std::string message)
            : m_line(line),
              m_file(file),
              m_message(message)
        {
        }

        std::size_t GetLine() const { return m_line; }
        std::string GetFile() const { return m_file; }
        std::string GetMessage() const { return m_message; }

    private:
        std::size_t m_line;
        std::string m_file;
        std::string m_message;
    };
}

#endif // UNITTEST11_TESTFAILEDEXCEPTION_HPP
