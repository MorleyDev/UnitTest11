#ifndef UNITTEST11_COPIEDPTR_HPP
#define UNITTEST11_COPIEDPTR_HPP

#include <memory>

namespace ut11
{
    template<typename T> class CopiedPtr
    {
    private:
        static void DefaultDestructor(T* pointer)
        {
            if ( pointer != nullptr )
                delete pointer;
        }

        static T* DefaultCopy(T* pointer)
        {
            if ( pointer != nullptr )
                return new T(*pointer);
            return nullptr;
        }

    public:
        typedef T type;
        typedef T* pointer;
        typedef T& reference;

        typedef const T const_type;
        typedef T const* const_pointer;
        typedef const T& const_reference;

        typedef std::function<void (pointer)> destructor;
        typedef std::function<pointer (pointer)> copy_operator;

        inline CopiedPtr()
            : m_pointer(nullptr), m_copy(DefaultCopy), m_destructor(DefaultDestructor)
        {
        }

        inline CopiedPtr(pointer ptr)
            : m_pointer(ptr), m_copy(DefaultCopy), m_destructor(DefaultDestructor)
        {
        }

        inline CopiedPtr(pointer ptr, destructor destroy)
            : m_pointer(ptr), m_copy(DefaultCopy), m_destructor(destroy)
        {
        }

        inline CopiedPtr(pointer ptr, copy_operator copy)
            : m_pointer(ptr), m_copy(copy), m_destructor(DefaultDestructor)
        {
        }

        inline CopiedPtr(pointer ptr, copy_operator copy, destructor destroy)
            : m_pointer(ptr), m_copy(copy), m_destructor(destroy)
        {
        }

        template<typename D>
        inline CopiedPtr(std::unique_ptr<T,D> ptr)
            : m_pointer(ptr.get()), m_copy(DefaultCopy), m_destructor(ptr.get_deleter())
        {
            ptr.release();
        }

        template<typename D>
        inline CopiedPtr(std::unique_ptr<T,D> ptr, copy_operator copy)
            : m_pointer(ptr.get()), m_copy(copy), m_destructor(ptr.get_deleter())
        {
            ptr.release();
        }

        inline CopiedPtr(const CopiedPtr& orig)
            : m_pointer(orig.m_copy(orig.get())),
              m_copy(orig.m_copy),
              m_destructor(orig.m_destructor)
        {
        }

        inline CopiedPtr(CopiedPtr&& orig)
            : m_pointer(orig.m_pointer),
              m_copy(std::move(orig.m_copy)),
              m_destructor(std::move(orig.m_destructor))
        {
            orig.m_pointer = nullptr;
        }

        inline ~CopiedPtr()
        {
            m_destructor( m_pointer );
        }

        inline CopiedPtr& operator=(const CopiedPtr& orig)
        {
            m_pointer = orig.m_copy(orig.get());
            m_destructor = orig.m_destructor;
            m_copy = orig.m_copy;

            return *this;
        }

        inline CopiedPtr& operator=(CopiedPtr&& orig)
        {
            m_pointer = orig.m_pointer;
            orig.m_pointer = nullptr;

            m_destructor = std::move(orig.m_destructor);
            m_copy = std::move(orig.m_copy);

            return *this;
        }

        inline pointer operator->() { return m_pointer; }
        inline const_pointer operator->() const { return m_pointer; }

        inline pointer get() { return m_pointer; }
        inline const_pointer get() const { return m_pointer; }

        inline reference operator*() { return *m_pointer; }
        inline const_reference operator*() const { return *m_pointer; }

        inline copy_operator get_copy_operator() { return m_copy; }
        inline copy_operator get_copy_operator() const { return m_copy; }

        inline destructor get_destructor() { return m_destructor; }
        inline destructor get_destructor() const { return m_destructor; }

    private:
        pointer m_pointer;
        copy_operator m_copy;
        destructor m_destructor;
    };
}

#endif // UNITTEST11_COPIEDPTR_HPP
