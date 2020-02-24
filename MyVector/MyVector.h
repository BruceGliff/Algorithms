#pragma once

#include <utility>
#include <stdexcept>

namespace My
{

    namespace Raw
    {
        template<typename T>
        class MyVectorBuf
        {
        protected:
            T * array_ = nullptr;
            int capacity_ = 0;
            int size_ = 0;

            T * GetArr()         noexcept { return array_; }
            int & GetCapacity()  noexcept { return capacity_; }
            int & GetSize()      noexcept { return size_; }

            void copy_construct(T * p, T const & value);
            void destroy(T * p) noexcept;
            void destroy(T * first, T * last) noexcept;

            MyVectorBuf(int cap = 0);
            virtual ~MyVectorBuf() noexcept;
        };

        #include "MyVectorBuf.hpp"
    }




template <typename T>
class Vector : public Raw::MyVectorBuf<T>
{
public:
    explicit Vector(int capacity =  0);
    Vector(Vector const & src);
    Vector(Vector && src);
    Vector<T> & operator=(Vector const & src);
    Vector<T> & operator=(Vector && src);

    ~Vector() noexcept;

    T & at(int idx);
    T const & at(int idx)           const;
    T & operator[](int idx);
    T const & operator[](int idx)   const;

    int size()      const noexcept { return Raw::MyVectorBuf<T>::size_; }
    int capacity()  const noexcept { return Raw::MyVectorBuf<T>::capacity_; }

    void swap(Vector & lf, Vector & rf) noexcept;
    void push_back(T const & el);
    void resize(int count);

    void pop() noexcept;
    T top();
};


#include "MyVector.hpp"

}