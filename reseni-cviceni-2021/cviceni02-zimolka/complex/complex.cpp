#include "complex.h"
#include <iostream>

double Complex::getRe() {
    return m_re;
}

double Complex::getIm() {
    return m_im;
}

void Complex::setRe(double re) {
    m_re = re;
}

void Complex::setIm(double im) {
    m_im = im;
}

void Complex::print() {
    cout << m_re << (m_im < 0 ? " - " : " + ") << abs(m_im) << endl;
}

