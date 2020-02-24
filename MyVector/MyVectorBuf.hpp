#include <cstdio>
template<typename T>
void MyVectorBuf<T>::copy_construct(T * p, T const & value)
{
    new (p) T (value);
    ++size_;
}

template<typename T>
void MyVectorBuf<T>::destroy(T * p) noexcept
{
    p->~T();
    --size_;
}

template<typename T>
void MyVectorBuf<T>::destroy(T * first, T * last) noexcept
{
    while(first != last)
    {
        destroy(first);
        ++first;        
    }
}
template<typename T>
MyVectorBuf<T>::MyVectorBuf(int cap)
{
    if (cap)
    {
        array_ = static_cast<T *>(::operator new(sizeof(T) * cap));
        capacity_ = cap;
    }
}

template<typename T>
MyVectorBuf<T>::~MyVectorBuf() noexcept
{
    destroy(array_, array_ + size_);
    ::operator delete(array_);
}