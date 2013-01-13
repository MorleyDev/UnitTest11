#ifndef UNITTEST11_ASSERT_FAIL_HPP
#define UNITTEST11_ASSERT_FAIL_HPP

#include "../TestFailedException.hpp"
#include <string>

namespace ut11
{
    namespace Assert
    {
        inline void Fail(std::size_t line, std::string file, std::string message)
        {
            throw ut11::TestFailedException(line, file, message);
        }
    }
}

#endif // UNITTEST11_ASSERT_FAIL_HPP
