#include "types.h"
#include <iostream>

int main() {
    Vec3 a;
    a[0] = 1.;
    a[1] = 1.;
    a[2] = 1.;

    Vec3 b;
    b[0] = 1.;
    b[1] = 1.;
    b[2] = 1.;

    Vec3 c = a + b;
    std::cout << "[" << c[0] << "," << c[1] << "," << c[2] << "]" << std::endl;
    std::cout << "Hello world!" << std::endl;
    return 0;
}
