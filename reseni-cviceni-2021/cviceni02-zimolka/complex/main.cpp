#include <iostream>
#include "complex.h"

int main() {

    Complex a;
    a.setRe(5);
    a.setIm(3);

    cout << a.getIm() << endl;
    a.print();


    return 0;
}
