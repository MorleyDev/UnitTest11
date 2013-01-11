#include <UnitTest11/CopiedPtr.hpp>

#include <UnitTest++/UnitTest++.h>

#include <list>
#include <algorithm>

TEST(CopiedPtrTest)
{
    auto data = new int(6);

    ut11::CopiedPtr<int> copiedPtr(data);

    ut11::CopiedPtr<int> copyConstrutorPtr(copiedPtr);

    ut11::CopiedPtr<int> operatorEqualsPtr;
    operatorEqualsPtr = copiedPtr;

    CHECK_EQUAL(copiedPtr.get(), data);
    CHECK_EQUAL(*copiedPtr, *data);
    CHECK_EQUAL(copiedPtr.operator->(), data);

    CHECK(copyConstrutorPtr.get() != data);
    CHECK_EQUAL(*copyConstrutorPtr, *data);

    CHECK(operatorEqualsPtr.get() != data);
    CHECK_EQUAL(*operatorEqualsPtr, *data);
}

TEST(CopiedPtrUniquePtrTest)
{
    std::unique_ptr<int> ptr(new int(6));
    auto data = ptr.get();

    ut11::CopiedPtr<int> copiedPtr(std::move(ptr));

    ut11::CopiedPtr<int> copyConstrutorPtr(copiedPtr);

    ut11::CopiedPtr<int> operatorEqualsPtr;
    operatorEqualsPtr = copiedPtr;

    CHECK_EQUAL(copiedPtr.get(), data);
    CHECK_EQUAL(*copiedPtr, *data);

    CHECK(copyConstrutorPtr.get() != data);
    CHECK_EQUAL(*copyConstrutorPtr, *data);

    CHECK(operatorEqualsPtr.get() != data);
    CHECK_EQUAL(*operatorEqualsPtr, *data);
}

TEST(CopiedPtrDestructorTest)
{
    int* expectedPointer[3];
    expectedPointer[0] = new int(6);

    std::list<int*> destructorPointers;
    auto destructor0 = [&](int* ptr) { destructorPointers.push_back(ptr); delete ptr; };

    {
        ut11::CopiedPtr<int> copiedPtr(expectedPointer[0], std::function<void (int*)>(destructor0));
        ut11::CopiedPtr<int> copyConstrutorPtr(copiedPtr);
        ut11::CopiedPtr<int> operatorEqualsPtr;
        operatorEqualsPtr = copiedPtr;

        expectedPointer[1] = copyConstrutorPtr.get();
        expectedPointer[2] = operatorEqualsPtr.get();
    }

    CHECK(destructorPointers.end() != std::find(destructorPointers.begin(), destructorPointers.end(), expectedPointer[0]) );
    CHECK(destructorPointers.end() != std::find(destructorPointers.begin(), destructorPointers.end(), expectedPointer[1]) );
    CHECK(destructorPointers.end() != std::find(destructorPointers.begin(), destructorPointers.end(), expectedPointer[2]) );
}

TEST(CopiedPtrDestructorUniquePtrTest)
{
    std::list<int*> destructorPointers;
    auto destructor0 = [&](int* ptr) { destructorPointers.push_back(ptr); delete ptr; };
    std::unique_ptr< int, std::function<void (int*)> > rootPtr(new int(6), destructor0) ;

    int* expectedPointer[3];
    expectedPointer[0] = rootPtr.get();

    {
        ut11::CopiedPtr<int> copiedPtr(std::move(rootPtr));
        ut11::CopiedPtr<int> copyConstrutorPtr(copiedPtr);
        ut11::CopiedPtr<int> operatorEqualsPtr;
        operatorEqualsPtr = copiedPtr;

        expectedPointer[1] = copyConstrutorPtr.get();
        expectedPointer[2] = operatorEqualsPtr.get();
    }

    CHECK(destructorPointers.end() != find(destructorPointers.begin(), destructorPointers.end(), expectedPointer[0]) );
    CHECK(destructorPointers.end() != find(destructorPointers.begin(), destructorPointers.end(), expectedPointer[1]) );
    CHECK(destructorPointers.end() != find(destructorPointers.begin(), destructorPointers.end(), expectedPointer[2]) );
}

TEST(CopiedPtrCustomCopyTest)
{
    std::list<int*> pointers;
    pointers.push_back(new int(2));
    pointers.push_back(new int(3));

    auto rootPtr = new int(6);

    std::list<int*> expectedPointers;
    expectedPointers.push_back(pointers.front());
    expectedPointers.push_back(pointers.back());

    ut11::CopiedPtr<int> copiedPtr(rootPtr, std::function<int* (int*)>([&](int* ptr) -> int*
    {
        CHECK(ptr == rootPtr);

        int* data = pointers.back();
        pointers.pop_back();
        return data;
    }));

    ut11::CopiedPtr<int> copyConstrutorPtr(copiedPtr);

    ut11::CopiedPtr<int> operatorEqualsPtr;
    operatorEqualsPtr = copiedPtr;

    CHECK(copyConstrutorPtr.get() == expectedPointers.back());
    CHECK(operatorEqualsPtr.get() == expectedPointers.front());
}
