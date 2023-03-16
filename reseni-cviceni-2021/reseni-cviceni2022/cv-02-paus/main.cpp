#include <iostream>
#include <cassert>
#include "simpleregex.h"

int main()
{
    SimpleRegex r1;
    r1.setPattern("abc..fgh");
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


    SimpleRegex r3;
    r3.setPattern("a.c*xyz");
    assert(r3.matchText2("abcdefghijklmnopqrstuvwxyz"));
    assert(r3.matchText2("abcxyz"));
    assert(r3.matchText2("aXc512xyz"));
    assert(r3.matchText2("abcxyzxyz"));

    SimpleRegex r4;
    r4.setPattern("a.c*x*z");
    assert(r4.matchText2("abcdefghijklmnopqrstuvwxyz"));
    assert(r4.matchText2("abcxyz"));
    assert(r4.matchText2("abcxz"));
    assert(r4.matchText2("abcxyzxyz"));
    assert(r4.matchText2("abcxxxxxxxxxyzxyzzzzz"));

    SimpleRegex r5;
    r5.setPattern("a.c*x.x*z.z");
    assert(!r5.matchText2("abcdefghijklmnopqrstuvwxyz"));
    assert(!r5.matchText2("abcxyz"));
    assert(!r5.matchText2("abcxz"));
    assert(!r5.matchText2("abcxyzxyz"));
    assert(r5.matchText2("abcxxxxxxxxxyzxyzzzzz"));

    return 0;
}
