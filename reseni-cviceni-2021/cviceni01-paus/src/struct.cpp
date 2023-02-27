#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "struct.h"

// Implementace fci pracujicich se strukturou data

void scan_data(data &d)
{
    std::cout << "Zadej " << n << " cisel: " << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cin >> d.a[i];
    }
}

void print_data(const data &d)
{
    std::cout << "Data: ";
    for (int i = 0; i < n; i++ )
        std::cout << d.a[i] << " ";
    
    std::cout << std::endl;
}

bool save_data(std::string filename, const data &d)
{
    bool ok = true;
    std::ofstream ofs;

    ofs.open( filename, std::ios::out | std::ios::binary );
    if (ofs.is_open())
    {
        ofs.write( (char*) &d, sizeof(d));

        if (!ofs.good())
        {
            std::cout << "Nelze zapisovat do souboru!" << std::endl;
            ok = false;
        }
        ofs.close();
    }
    else
    {
        std::cout << "Nelze vytvorit soubor!" << std::endl;
        ok = false;
    }

    return ok;
}

bool read_data(const std::string &filename, const data &d)
{
    bool ok = true;

    std::ifstream ifs;

    ifs.open( filename, std::ios::in | std::ios::binary );

    if (ifs.is_open())
    {
        ifs.read( (char*) &d, sizeof(d) );
        if (!ifs.good())
        {
            std::cout << "Nelze cist!" << std::endl;
            ok = false;
        }

        ifs.close();
    }
    else
    {
        std::cout << "Nelze otevrit!" << std::endl;
        ok = false;       
    }

    return ok;
}

bool is_equal(const data &d, const data &e)
{
    bool equal = true;

    for (int i=0; i<n; i++)
    {
        if ( d.a[i] != e.a[i] )
        {
            equal = false;
            break;
        }
    }
    return equal;
}

void sort_data(data &d)
{
    std::sort( d.a, d.a + n );
}