#include "simpleregex.h"

int SimpleRegex::m_counter = 0;

void SimpleRegex::setPattern(const string & pattern) {
    m_pattern = pattern;
}

bool SimpleRegex::matchText(const string & text) {
    m_counter++;
    return matchTextR(text, 0, 0);
}

bool SimpleRegex::matchTextR(const string &text, int i, int j) const {
    if (i == m_pattern.length() && j == text.length()) {
        return true;
    }

    if ((i == m_pattern.length() && j != text.length()) ||
         i != m_pattern.length() && j == text.length()) {
        return false;
    }

    if (m_pattern[i] == '.' || m_pattern[i] == text[j]) {
        return matchTextR(text, i + 1, j + 1);
    }

    if (m_pattern[i] == '*') {
        return matchTextR(text, i + 1, j)
            || matchTextR(text, i + 1, j + 1)
            || matchTextR(text, i, j + 1);
    }
    return false;
}

int SimpleRegex::getCounter() {
    return m_counter;
}


