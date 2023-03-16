#ifndef SIMPLEREGEX_H
#define SIMPLEREGEX_H

#include <string>

using namespace std;

class SimpleRegex
{
   string m_pattern;
   static int m_counter;
   bool matchTextR(const string& t_text, int i, int j) const;
public:
   bool matchText(const string& t_text);
   void setPattern(const string& t_pattern);
   static int getCounter();
   bool matchText2(const string& t_text);
};

#endif
