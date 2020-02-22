template<typename T>
void MyVectorBuf<T>::copy_construct(T * p, T const & value)
{
    new (p) T (value);
}

template<typename T>
void MyVectorBuf<T>::destroy(T * p) noexcept
{
    p->~T();
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
MyVectorBuf<T>::MyVectorBuf(int size)
{
    if (size)
    {
        array_ = static_cast<T *>(::operator new(sizeof(T) * size));
        size_ = size;
    }
}

template<typename T>
MyVectorBuf<T>::~MyVectorBuf() noexcept
{
    destroy(array_, array_ + curr_);
    ::operator delete(array_);
}