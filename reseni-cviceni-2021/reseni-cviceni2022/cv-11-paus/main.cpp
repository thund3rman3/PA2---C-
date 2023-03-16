#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define C11INIT
#define AUTO1
#define AUTO2
#define AUTO3
#define LAMBDA1
#define LAMBDA2
#define OVERRIDE_FINAL_DELETE

#define ___
#ifdef  ___
//functor pro zjisteni, zda je pismeno velke
class IsUpperFunc
{
public:
    bool operator()(char c) { return isupper(c); }
};

// funkce pro zjisteni, zda je pismeno velke
bool isU(char c)
{
    return isupper(c);
}

// funkce pro pocitani nejakych vlastnosti stringu
// 4 druhy fci s parametrem funkce

// pomoci template
template<typename Func>
int countOccurences(const string s, Func f)
{
    int n=0;
    for (char c: s) if (f(c)) n++;
    return n;
}

// bezna fce jako parametr
int countOccurences2(const string s, bool f(char))
{
    int n=0;
    for (char c: s) if (f(c)) n++;
    return n;
}

// pomoci std::function
int countOccurences3(const string s, function<bool(char)> f)
{
    int n=0;
    for (char c: s) if (f(c)) n++;
    return n;
}

// pomoci functoru
int countOccurences4(const string s, IsUpperFunc f)
{
    int n = 0;
    for (char c : s)
        if (f(c))
            n++;
    return n;
}
#endif

// ukazkove tridy pro klicova slova override, delete, final
#ifdef OVERRIDE_FINAL_DELETE
// DELETE, FINAL, OVERRIDE
class A 
{
public:
    char virtual operator()() const  { return 'A'; }  // budeme chtit pretezovat operator ()
    A& operator= (const A& ) = delete; 
    string virtual f1() { return "A1"; }
    string f2() { return "A2"; }
    virtual string f3() { return "A3"; }
};

class B : public A 
{
    char virtual operator()() const override { return 'B'; } // chceme pretizit
    string f1() override { return "B1"; }  // chceme pretizit
    string f2() { return "B2"; }  
    string f3() override final { return "B3"; }  // chceme pretizit, ale zakazat dalsi pretezovani

};

class C : public B
{
    char virtual operator()() const override { return 'C'; }     // chceme pretizit
    string f1() override { return "C1"; };  // chceme pretizit
    //string f3() override { return "C3";  }  // chceme pretizit, ale...
};
#endif

#ifdef AUTO1
// zde chceme vytvorit operator << pro vypis libovoneho vectoru
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    //for ( auto& it : v ) os << it << ' ';
    for ( const T &it : v)
        os << it << ' ';
    return os;
}

// zde chceme vytvorit operator << pro vypis libovone mapy
template<typename T1, typename T2>
ostream &operator<<(ostream &os, map<T1, T2> m)
{
    //for (typename map<T1, T2>::const_iterator it = m.begin(); it != m.end(); it++)
    //for (const pair<T1, T2> &it : m)
    
    for ( auto& it : m  )
        os << it.first << ": " << it.second << endl;
    return os;
}
#endif

#ifdef AUTO3
// zde chceme operator nasobeni pro prenasobeni vektoru cislem (vector int, double, atd...)

template<typename T>
auto operator*( const vector<T>& v, T m )
{
    auto result(v);
    for ( auto& x : result ) x *= m; 
    return result;
}
#endif

int main(int argc, const char * argv[])
{
#ifdef C11INIT
    vector<char> vect = {
        'A',
        'B',
        'c',
        'd',
        'e',
        'F',
        'G'
    };
    vector<double> vdouble = { 1.1, 2.3, 3.5};
    map<string, int> platy = { { "Michal Valenta", 45450 }, {"Andrej Babis ", 454000}, { "Uklizecka", 15000} } ;
#endif

#ifdef AUTO1
    cout << vect << endl;
    cout << vdouble << endl;
    cout << platy;
#endif
    
#ifdef AUTO2
    // zde chceme prekonvertovat vektor charu do uppercase
    cout << "Original: " << vect << endl;
    
    for ( auto &x : vect ) x = toupper(x);

    cout << vect << endl;
    cout << endl;
#endif

#ifdef AUTO3
    // pouziti operatoru * na vector cisel
    vector<int> v1 = {0, 1, 2, 3, 4};
    vector<double> v2 = {1.2, 2.2, 3.2, 4.2, 5.2, 6.2};

    auto v1result = v1 * 2;
    auto v2result = v2 * 0.5;

    cout << v1 << endl << v1result << endl << endl;
    cout << v2 << endl << v2result << endl << endl;

#endif

#ifdef LAMBDA1
    // FUNCTOR
    IsUpperFunc f;    
    cout << "template(Functor):       " << countOccurences ("AbCdE", f) << endl;
    //cout << "function(Functor):       " << countOccurences2("AbcdE", f) << endl; 
    cout << "std::function(Functor):  " << countOccurences3("AbCdE", f) << endl;
    cout << "Functor(Functor):        " << countOccurences4("AbCdE", f) << endl;
    cout << endl;

    // FUNCTION
    cout << "template(function):      " << countOccurences ("AbCdE", isU) << endl;
    cout << "function(function):      " << countOccurences2("AbCdE", isU) << endl;
    cout << "std::function(function): " << countOccurences3("AbCdE", isU) << endl;
    //cout << "Functor(function):       " << countOccurences4("AbCdE", isU) << endl;
    cout << endl;

    // LAMBDA
    cout << "template(lambda):        " << countOccurences ("AbCdE", [](char c)->bool { return isupper(c); } ) << endl;
    cout << "function(lambda):        " << countOccurences2("AbCdE", [](char c)->bool { return isupper(c); } ) << endl;
    cout << "std::function(lambda):   " << countOccurences3("AbCdE", [](char c)->bool { return isupper(c); } ) << endl;
    //cout << "Functor(lambda):         " << countOccurences4("AbCdE", [](char c)->bool { return isupper(c); } ) << endl;
    cout << endl;
#endif

#ifdef LAMBDA2
    // pocitani velkych pismen ve stringu
    string s("AbCdE");
    int n = 0, m = 0, o = 0;

    for_each(s.begin(), s.end(), [&] (char c) mutable { if (isupper(c)) m++; o++; } );
    cout << "&: " << m << endl;
    cout << "o: " << o << endl;

    for_each(s.begin(), s.end(), [&n, &o](char c) { if (isupper(c)) n++; o++; });
    cout << "&n: " << n << endl;
    cout << "o: " << o << endl;

    for_each(s.begin(), s.end(), [=](char c) mutable { if (isupper(c)) m++; o++; });
    cout << "= : " << o << endl;
#endif

#ifdef OVERRIDE_FINAL_DELETE
    A a,b;
    //b = a;
    cout << a() << endl;

    A* aptr = new C;
    //cout << *aptr() << endl;
    cout << (*aptr)() << endl;
    cout << aptr->operator()() << endl;

    cout << aptr->f1() << endl;
#endif

    return 0;
}
