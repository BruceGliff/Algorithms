template<typename T>
Vector<T>::Vector(int size) :
    Raw::MyVectorBuf<T>{size}
{}

template<typename T>
Vector<T>::~Vector() noexcept
{}

template<typename T>
Vector<T>::Vector(Vector const & src) :
    Raw::MyVectorBuf<T>{src.size_}
{
    // array_ = safe_copy(src.array_, src.size_);
    // size_ = src.size_;
    // current_ = src.current_;

    for (int i = 0; i < src.size_; ++i)
        copy_construct(array_ + i, src[i]);

}


template<typename T>
T * Vector<T>::safe_copy(T const * source, int srsize)
{
    T * dest = new T[srsize];
    try
    {
        for(int i = 0; i < srsize; ++i)
            dest[i] = source[i];
    }
    catch(...)
    {
        delete[] dest;
        throw;
    }

    return dest;   
}

template<typename T>
void Vector<T>::swap(T const & lf, T const & rf) noexcept
{
    std::swap(lf.array_, rf.array_);
    std::swap(lf.size_, rf.size_);
    std::swap(lf.current_, rf.current_);
}

template<typename T>
Vector<T> & Vector<T>::operator=(T const & src)
{
    Vector<T> tmp{src};
    swap(tmp, src);
    return *this;
}

template<typename T>
T Vector<T>::top()
{
    if (!current_)
        throw std::out_of_range();

    return array_[current_ - 1];
}

template<typename T>
void Vector<T>::pop()
{
    if (!current_)
        throw std::out_of_range();

    current_ -= 1;
}