#include <cstdio>
#include <iostream>
#include "simpleregex.h"

int SimpleRegex::m_counter = 0;

void SimpleRegex::setPattern(const string& t_pattern)
{
    m_pattern = t_pattern;
}

bool SimpleRegex::matchText(const string& t_text)
{
    size_t plen = m_pattern.size();
    size_t tlen = t_text.size();

    m_counter++;

    //cout << plen << " " << tlen << endl;

    if (tlen!=plen) return false;

    for (int i = 0; i<plen; i++)
    {
        //cout << m_pattern[i] << " " << t_text[i] << endl;
        if ( (m_pattern[i]!=t_text[i]) && (m_pattern[i]!='.') )
           return false;
    }
    return true;
}

bool SimpleRegex::matchText2(const string& t_text)
{
    m_counter++;
    return matchTextR(t_text,0,0);
}

bool SimpleRegex::matchTextR(const string& t_text, int i, int j) const
{
    if (i == m_pattern.length() && j == t_text.length())
	return true;

    if ((i == m_pattern.length() && j != t_text.length()) || (i != m_pattern.length() && j == t_text.length()))
        return false;

    if (m_pattern[i] == '.' || m_pattern[i] == t_text[j])
        return matchTextR(t_text, i + 1, j + 1);

    if (m_pattern[i] == '*')
       return matchTextR(t_text, i + 1, j) || matchTextR(t_text, i, j + 1) || matchTextR(t_text, i + 1, j + 1);

    return false;
}

int SimpleRegex::getCounter()
{
  return m_counter;
}
