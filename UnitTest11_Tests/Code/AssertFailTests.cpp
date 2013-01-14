#include <UnitTest11.hpp>

#include <string>

class AssertFailTests : public ut11::TestFixture
{
private:
    ut11::TestFailedException m_exception;

    std::size_t line = 132;
    std::string file = "some file";
    std::string message = "some message";

public:
    virtual void Run()
    {
        When("calling Assert Fail", [&]()
        {
            try
            {
                ut11::Assert::Fail(line, file, message);
            }
            catch(const ut11::TestFailedException& ex)
            {
                m_exception = ex;
                return;
            }
        });

        Then("the expected exception is thrown", [&]()
        {
            AssertThat(line, ut11::Is::EqualTo(m_exception.getLine()));
            AssertThat(file, ut11::Is::EqualTo(m_exception.getFile()));
            AssertThat(message, ut11::Is::EqualTo(m_exception.getMessage()));
        });
    }
};
DeclareFixture(AssertFailTests);
