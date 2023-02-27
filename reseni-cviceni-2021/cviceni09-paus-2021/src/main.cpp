#include <iostream>
#include <sstream>
#include "Array.hpp"
#include "Point.hpp"


#define LEVEL1  // Implementace Array< T, size>
#define LEVEL2  // Implementace fce max(Array<T, size>)
#define LEVEL3  // Vyuziti pro vlastni tridu Point
#define LEVEL4  // Specializace pro char pri vypisu


// TODO: Naimplementovat sablonovou fci max() podle zadani
template< class T, size_t size>
size_t max( const Array<T, size>& arr )
{
    size_t m = 0;
    for (size_t i = 1; i<size; i++)
    {
        if (arr[i]>arr[m]) m = i;
    }
    return m;
}

// Testovaci main(), splnit beze zmeny
int main()
{
#ifdef LEVEL1
    Array<int, 3> a1;
    Array<double, 3> a2;
    Array<char, 3> a3;
    Array<std::string, 3> a4;

    a1[0] = 8;
    a1[1] = 9;
    a1[2] = 7;

    a2[0] = 1.5;
    a2[1] = 1.6;
    a2[2] = 1.7;

    a3[0] = 'X';
    a3[1] = 'B';
    a3[2] = 'C';

    a4[0] = "koza";
    a4[1] = "divocak";
    a4[2] = "lev";

    std::cout << a1 << std::endl;
    std::cout << a2 << std::endl;
    std::cout << a3 << std::endl;
    std::cout << a4 << std::endl;

    std::stringstream s;
    s << a1;
    assert(s.str() == std::string("8 9 7 "));

#ifdef LEVEL2

    std::cout << "max = " << a1[max(a1)] << std::endl;
    std::cout << "max = " << a2[max(a2)] << std::endl;
    std::cout << "max = " << a3[max(a3)] << std::endl;
    std::cout << "max = " << a4[max(a4)] << std::endl;

    assert(a3[max(a3)] == 'X');

#ifdef LEVEL3
    Array<Point, 3> a5;
    a5[0] = Point(3, 4);
    a5[1] = Point{1, 1};
    a5[2] = Point({-10, -10});

    std::cout << a5 << std::endl;
    std::cout << "max = " << a5[max(a5)] << std::endl;

#ifdef LEVEL4
    std::stringstream s1;
    s1 << a3;
    assert(s1.str() == "XBC");

    std::cout << a3 << std::endl;
#endif // L4
#endif // L3
#endif // L2
#endif // L1

    return 0;
}