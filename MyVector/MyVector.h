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
            int size_ = 0;
            int curr_ = 0;

            void copy_construct(T * p, T const & value);
            void destroy(T * p) noexcept;
            void destroy(T * first, T * last) noexcept;

        public:
            MyVectorBuf(int size = 0);
            ~MyVectorBuf() noexcept;
        };

        #include "MyVectorRaw.hpp"
    }




template <typename T>
class Vector : public Raw::MyVectorBuf<T>
{
    // T * array_ = nullptr;
    // int size_ = 0;
    // int current_ = 0;

    T * safe_copy(T const * source, int srsize);


public:
    explicit Vector(int size);
    Vector(Vector const & src);
    ~Vector() noexcept;
    Vector<T> & operator=(T const & src);

    void swap(T const & lf, T const & rf) noexcept;
    //void push_back(T const & el);

    void pop();
    T top();
};


#include "MyVector.hpp"

}