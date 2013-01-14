#ifndef UNITTEST11_GLOBAL_HPP
#define UNITTEST11_GLOBAL_HPP

#include "TestFixture.hpp"
#include "IOutput.hpp"

namespace ut11
{
    void PushFixture(std::unique_ptr<ITestFixture>);
    int Run();
    int Run(IOutput&);

    template<typename T>
    struct DeclareFixtureObj
    {
        DeclareFixtureObj(std::string name)
        {
            std::unique_ptr<T> fixture(new T());
            fixture->setName(name);
            PushFixture(std::move(fixture));
        }
    };
}

#endif // UNITTEST11_GLOBAL_HPP
