#include <cstdio>
#include <iostream>
#include <fstream>
#include "struct.h"

void swap( int &a, int &b)
{
  int x;
  x=a;
  a=b;
  b=x;
}

void sort_data(data &d)
{
  for (int i=0; i<n-1; i++)
    for (int j=i; j>=0; j--)
      if (d.a[j]>d.a[j+1]) swap( d.a[j],d.a[j+1]);
}

void print_data(const data &d)
{
  std::cout << "Data:" << std::endl;
  for (int i=0; i<n; i++) std::cout << d.a[i] << " ";
  std::cout << std::endl;
}

void scan_data( data &d )
{
  std::cout << "Zadej " << n << " cisel:" << std::endl;

  for (int i=0; i<n; i++)
  {
    std::cin >> d.a[i];
  }
}

bool is_equal(const data& d, const data& e)
{
  bool equal = true;
  
  for (int i=0; i<n; i++)
  {
    if (d.a[i] != e.a[i] ) 
    {
      equal = false;
      break;
    }
  }
  return equal;
}

bool read_data(const std::string &filename, data &d)
{
  bool ok = true;
  std::ifstream in_file;
  
  in_file.open( filename, std::ios::in | std::ios::binary);

  if (in_file.is_open())
  {
      in_file.read((char*)&d, sizeof(d));
      
      if (!in_file.good())
      {
        std::cout << "cannot read from file" << std::endl;
        ok = false;
      }
      
      in_file.close();
  } 
  else
  {
    std::cout << "cannot open file" << std::endl;
    ok = false;
  }

  return ok;
}

bool save_data(const std::string &filename, const data &d)
{
  bool ok = true;
  std::ofstream out_file;

  out_file.open( filename, std::ios::out | std::ios::binary );
  
  if (out_file.is_open())
  {
    out_file.write((char*)&d, sizeof(d));
    
    if (!out_file.good()) 
    {
      std::cout << "cannot write to file " << std::endl;
      ok = false;
    }
    
    out_file.close();
  } 
  else
  {
    std::cout << "cannot create file" << std::endl;
    ok = false;
  }

  return ok;
}