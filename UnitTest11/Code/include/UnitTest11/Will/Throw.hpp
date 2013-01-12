#ifndef UNITTEST11_WILL_THROW_HPP
#define UNITTEST11_WILL_THROW_HPP

#include "../Utility/BaseOperand.hpp"

#include <exception>
#include <string>
#include <sstream>
#include <functional>

namespace ut11
{
    namespace Operands
    {
        template<typename Exception> struct WillThrow : public Utility::BaseOperand
        {
            WillThrow(std::string exceptionName = typeid(Exception).name())
                : m_exceptionName(exceptionName),
                  m_errorMessage("Expected " + exceptionName + " to be thrown, but no exception was thrown")
            {
            }

            inline std::string GetErrorMessage(std::function<void (void)>) const { return m_errorMessage; }

            inline bool operator()(std::function<void (void)> function)
            {
                try
                {
                    function();
                }
                catch(const Exception&)
                {
                    return true;
                }
                catch(const std::exception& ex)
                {
                    std::stringstream stream;
                    stream << "Expected " << m_exceptionName << " to be thrown, but std::exception was thrown instead (what: " << ex.what() << ")";
                    m_errorMessage = stream.str();
                }
                catch(...)
                {
                    std::stringstream stream;
                    stream << "Expected " << m_exceptionName << " to be thrown, but an unknown exception was thrown instead";
                    m_errorMessage = stream.str();
                }
                return false;
            }

        private:
            std::string m_exceptionName;
            std::string m_errorMessage;
        };
    }

    namespace Will
    {
        template<typename Exception> Operands::WillThrow<Exception> Throw()
        {
            return Operands::WillThrow<Exception>();
        }
    }
}

#endif // UNITTEST11_WILL_THROW_HPP
