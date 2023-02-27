#ifndef STRUCT_H
#define STRUCT_H

#include <string>

const int n = 5;

struct data
{
    int a[n];
};

void scan_data( data &d );
void print_data( const data &d );
bool save_data( std::string filename, const data &d );
bool read_data( const std::string &filename, const data &d );
bool is_equal( const data &d, const data &e );
void sort_data( data &d );




#endif