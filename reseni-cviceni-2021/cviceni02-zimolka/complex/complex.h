#ifndef CV2_TEST_COMPLEX_H
#define CV2_TEST_COMPLEX_H

using namespace std;

class Complex {
    double m_re;
    double m_im;
public:
    double getRe();
    double getIm();
    void setRe(double re);
    void setIm(double im);
    void print();
};


#endif //CV2_TEST_COMPLEX_H
