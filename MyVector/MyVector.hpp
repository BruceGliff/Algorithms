#include <cstdio>
template<typename T>
using R = Raw::MyVectorBuf<T>;


template<typename T>
Vector<T>::Vector(int cap) :
    Raw::MyVectorBuf<T>{cap}
{}

template<typename T>
Vector<T>::Vector(Vector const & src) :
    Raw::MyVectorBuf<T>{src.capacity_}
{
    for (int i = 0; i < src.size_; ++i)
        R<T>::copy_construct(R<T>::array_ + i, src[i]);
}

template<typename T>
Vector<T> & Vector<T>::operator=(Vector const & src)
{
    Vector<T> tmp{src};
    swap(tmp, *this);
    return *this;
}

template<typename T>
Vector<T>::~Vector() noexcept
{}

template<typename T>
T & Vector<T>::at(int idx)
{
    if(idx == R<T>::size_ || idx < 0)
        throw std::out_of_range("Out of range");

    return R<T>::array_[idx];
}

template<typename T>
T const & Vector<T>::at(int idx) const
{
    if(idx == R<T>::size_ || idx < 0)
        throw std::out_of_range("Out of range");

    return R<T>::array_[idx];
}

template<typename T>
T & Vector<T>::operator[](int idx)
{
    return at(idx);
}

template<typename T>
T const & Vector<T>::operator[](int idx) const
{
    return at(idx);
}

template<typename T>
void Vector<T>::swap(Vector & lf, Vector & rf) noexcept
{
    std::swap(lf.array_, rf.array_);
    std::swap(lf.size_, rf.size_);
    std::swap(lf.capacity_, rf.capacity_);
}

template<typename T>
T Vector<T>::top()
{
    if (!R<T>::size_)
        throw std::out_of_range("Vector is empty");

    return R<T>::array_[R<T>::capacity_ - 1];
}

template<typename T>
void Vector<T>::pop() noexcept
{
    if (!R<T>::size_)
        return;

    --R<T>::size_;
}

template<typename T>
void Vector<T>::push_back(T const & el)
{
    if (R<T>::capacity_ == R<T>::size_)
        resize(R<T>::capacity_ * 2);

    R<T>::copy_construct(R<T>::array_ + R<T>::size_, el);
}

template<typename T>
void Vector<T>::resize(int count)
{
    Vector<T> tmp{count};
    int const curr = std::min(count, R<T>::size_);
    for(int i = 0; i < curr; ++i)
        tmp.copy_construct(tmp.array_ + i, at(i));
    swap(*this, tmp);
}