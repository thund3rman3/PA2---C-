#include <iostream>
#include <cassert>

#define LEVEL1
#define LEVEL2
#define LEVEL3
#define LEVEL4

class Stack
{
    // TODO: definovat a implementovat Stack, vizte zadani
};


int main()
{
#ifdef LEVEL1 
    Stack s;
    s.push_back(1);
    s.push_back(2);
    s.push_back(3);

    assert(s.at(0)==1);
    assert(s.at(2)==3);
#ifdef LEVEL2
    std::cout << s << std::endl;

#ifdef LEVEL3
    s.at(1) = 5;
    assert(s.at(1) == 5);

    std::cout << s << std::endl;

    s.pop_back();
    std::cout << s << std::endl;

    s.push_back(10);
    s.push_back(11);
    s.push_back(12);

    std::cout << s << std::endl;

#ifdef LEVEL4

    const Stack& s1 = s;

    assert(s1.at(1)==5);
    //s1.at(0) = 2;  // nelze na const

    Stack s2;
    // s2 = s; //nelze, pokud zrusime operator prirazeni
#endif // level 4
#endif // level 3
#endif // level 2
#endif // level 1

}