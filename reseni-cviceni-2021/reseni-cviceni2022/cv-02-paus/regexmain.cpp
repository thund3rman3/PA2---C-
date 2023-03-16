#include <iostream>
#include <cassert>
#include "simpleregex.h"

int main()
{
    assert(SimpleRegex::getCounter()==0);

    string p1 = "abc..fgh";
    SimpleRegex r1;
    r1.setPattern(p1);
    assert(r1.matchText("abcdefgh"));
    assert(r1.matchText("abcXXfgh"));
    assert(!r1.matchText("abcefgh"));

    assert(SimpleRegex::getCounter()==3);

    SimpleRegex r2;
    r2.setPattern("Mam rad ...");
    assert(r2.matchText("Mam rad PA2"));
    assert(!r2.matchText("mam rad LIN"));
    assert(!r2.matchText("Mam rad ZMA!"));

    assert(r2.getCounter()==6);

    return 0;
}
