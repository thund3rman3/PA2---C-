#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cassert>

#define UKOL0   // Definice typu vektoru intu
#define UKOL1   // Hashovani
#define UKOL2   // Filtrovani vektoru
#define UKOL3   // Razeni podle zadani
#define UKOL4   // Komprese vektoru

#define PRINTRESULTS 1

#ifdef UKOL0
typedef std::vector<int> int_vect;
#endif

// stream operator pro vektor intu
std::ostream& operator<< ( std::ostream& os, const int_vect& v)
{
    for ( int x : v ) os << x << " ";
    return os;
}

// TODO: hash functor
class HashString 
{
public:
    int operator()( const std::string& s) const
    {
        int result = 0;

        for ( char c : s ) result += c;
        //for (int i=0;i<s.length(); i++) result += s[i];

        return result;
    }
};


// TODO: funkce pro filtrovani duplikatu ve vektoru, ktera vraci take vektor
 int_vect filter_duplicates( const int_vect& v )
 {
      /* Verze 1
      std::set<int> s;
      int_vect result;

      for (int i=0; i<v.size(); i++) s.insert(v[i]);

     // for (std::set<int>::const_iterator i=s.begin(); i!=s.end(); i++)
      for (auto i = s.begin(); i != s.end(); i++)
          result.push_back(*i);

      return result;

      */

     /* verze 2 */
      std::set<int> s( v.begin(), v.end() );
      return int_vect( s.begin(), s.end() ); 
 }

class MyCompare
{
public:
    bool operator()( const std::pair<int, int>& a, const std::pair<int, int>& b ) const
    {
        if ( a.second > b.second ) return true;

        if ( a.second == b.second && a.first <= b.first ) return true;

        return false;
    }
};

// TODO: funkce pro nase specialni razeni
 int_vect sort_data( const int_vect& v )
{
    std::map<int, int> m;
    int_vect result;

    for ( int x : v ) m[x]++;

    std::set< std::pair<int,int>, MyCompare > s(m.begin(), m.end());

    for ( auto x : s ) for (int i=0; i<x.second; i++) result.push_back(x.first);

    return result;
}
        
// TODO: funktor pro kompresi rozsahu vektoru
class CompressVector
{
    int start;
public:
    CompressVector(int s = 1 ):start(s) {}

    int_vect operator()( const int_vect& v )
    {
        std::map<int, int> m;
        int_vect result;

        for ( int x : v ) m[x] = 0;

        int i = start;
        //for ( std::pair<int, int> x : m ) m[ x.first ] = i++;     // verze 1
        for ( auto& x : m) x.second = i++;                          // verze 2

        for ( int x : v ) result.push_back( m[x] );

        return result;
    }
};

int main()
{
#ifdef UKOL0
    int_vect data = {1, 4, 1, 7, 4, 5, 7, 7};

    if (PRINTRESULTS) std::cout << "Input data:       " << data << std::endl;
    std::cout << "UKOL0: OK" << std::endl;
#endif

#ifdef UKOL1    // hash functor
    HashString hash;
    
    std::string s1 = "AA";
    std::string s2 = "    ";
    
    assert( hash(s1) == 130);
    assert( hash(s2) == 128);

    if (PRINTRESULTS) std::cout << "String hash: "  << hash(s1) << std::endl;
    if (PRINTRESULTS) std::cout << "String hash: "  << hash(s2) << std::endl;
        
    std::cout << "UKOL1: OK" << std::endl;
#endif
        

#ifdef UKOL2    // filtrovani pole pomoci funkce
    int_vect  filtered = filter_duplicates(data);
    assert( filtered == int_vect({1, 4, 5, 7}) );
        
    int_vect  filtered2 = filter_duplicates({3, 2, 1, 1, 2, 3, 3, 2, 3});
    assert( filtered2 == int_vect({1, 2, 3}) );
    
    if (PRINTRESULTS) std::cout << "Filtered data:    " << filtered << std::endl;
    if (PRINTRESULTS) std::cout << "Filtered data:    " << filtered2 << std::endl;
        
    std::cout << "UKOL2: OK" << std::endl;
#endif

#ifdef UKOL3    // serazeni dat podle zadani pomoci funkce
    int_vect sorted = sort_data(data);
    assert( sorted == int_vect({7, 7, 7, 1, 1, 4, 4, 5}) );
           
    if (PRINTRESULTS) std::cout << "Sorted data:      " << sorted << std::endl;
        
    std::cout << "UKOL3: OK" << std::endl;
#endif
    
#ifdef UKOL4    // komprese vektoru podle zadani s volitelnym zacatkem
    CompressVector c1;
    CompressVector c2(10);
        
    int_vect  compressed1 = c1(data);
    int_vect  compressed2 = c2(data);
           
    assert( compressed1 == int_vect({1, 2, 1, 4, 2, 3, 4, 4}) );
    assert( compressed2 == int_vect({10, 11, 10, 13, 11, 12, 13, 13}) );

    if (PRINTRESULTS) std::cout << "Compressed data1: " << compressed1 << std::endl;
    if (PRINTRESULTS) std::cout << "Compressed data2: " << compressed2 << std::endl;
        
    std::cout << "UKOL4: OK" << std::endl;
#endif
    
    return 0;
}


