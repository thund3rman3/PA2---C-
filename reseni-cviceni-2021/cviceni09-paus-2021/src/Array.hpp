#ifndef ARRAY_H
#define ARRAY_H

#include <cstdio>
#include <exception>

// TODO: naimplementovat tridu Array podle zadani

template< typename T, size_t size >
class ArrayBase
{
protected:
    T data[size];

public:
    T& operator[](size_t i)
    {
        if (i<size)
        {
            return data[i];
        }
        else 
        {
            throw std::out_of_range("Error");
        }
    }

    const T& operator[](size_t i) const
    {
        if (i < size)
        {
            return data[i];
        }
        else
        {
            throw std::out_of_range("Error");
        }
    }

    std::ostream& print(std::ostream& os) const
    {
        for (const T& x : data )
        {
            os << x << ' ';
        }
        return os;
    }
};

template< typename T, size_t size>
class Array : public ArrayBase<T, size>
{

};

template<size_t size>
class Array<char, size> : public ArrayBase<char, size>
{
public:
    std::ostream &print(std::ostream &os) const
    {
        //for (const char &x : ArrayBase<char, size>::data)
        for (const char &x : this->data)
        {
            os << x;
        }
        return os;
    }
};

// template <size_t size>
// class Array<char, size>
// {
// private:
//     char data[size];

// public:
//     char &operator[](size_t i)
//     {
//         if (i < size)
//         {
//             return data[i];
//         }
//         else
//         {
//             throw std::out_of_range("Error");
//         }
//     }

//     const char &operator[](size_t i) const
//     {
//         if (i < size)
//         {
//             return data[i];
//         }
//         else
//         {
//             throw std::out_of_range("Error");
//         }
//     }

//     std::ostream &print(std::ostream &os) const
//     {
//         for (const char &x : data)
//         {
//             os << x;
//         }
//         return os;
//     }
// };

template<typename T, size_t size>
std::ostream& operator<<(std::ostream& os, const Array<T, size>& arr)
{
    return arr.print(os);
}

#endif