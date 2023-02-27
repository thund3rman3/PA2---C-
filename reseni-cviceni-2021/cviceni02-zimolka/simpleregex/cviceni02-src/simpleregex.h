#ifndef CVICENI02_SIMPLEREGEX_H
#define CVICENI02_SIMPLEREGEX_H

#include <string>

using namespace std;

class SimpleRegex {
    string m_pattern;
    static int m_counter;
    bool matchTextR(const string & text, int i, int j) const;
public:
    void setPattern(const string & pattern);
    bool matchText(const string & text);
    static int getCounter();
};


#endif //CVICENI02_SIMPLEREGEX_H
