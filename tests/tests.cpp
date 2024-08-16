#include <cmath>
#include <fstream>
#include <iostream>

#include "../src/solver.h"
#include "../src/types.h"
#include "gtest/gtest.h"

TEST(type_tests, Vec3_indices_access) {
    Vec3 a;
    a[0] = 1;
    a[1] = 1;
    a[2] = 1;

}


TEST(type_tests, vec3_sum){
    Vec3 a;
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    Vec3 b;
    b[0] = 4;
    b[1] = 5;
    b[2] = 6;

    Vec3 res = a+b;

    EXPECT_EQ(res[0],5);
    EXPECT_EQ(res[1],7);
    EXPECT_EQ(res[2],9);
}

TEST(type_tests, vec3_substract){
    Vec3 a;
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    Vec3 b;
    b[0] = 4;
    b[1] = 5;
    b[2] = 6;

    Vec3 res = b-a;

    EXPECT_EQ(res[0],3);
    EXPECT_EQ(res[1],3);
    EXPECT_EQ(res[2],3);
}

TEST(type_tests, vec3_mult_double){
    Vec3 a;
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    double b = 2;

    Vec3 res = a*b;

    EXPECT_EQ(res[0],2);
    EXPECT_EQ(res[1],4);
    EXPECT_EQ(res[2],6);
}

TEST(type_tests, double_mult_vec3){
    Vec3 a;
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    double b = 2;

    Vec3 res = b*a;

    EXPECT_EQ(res[0],2);
    EXPECT_EQ(res[1],4);
    EXPECT_EQ(res[2],6);
}

TEST(type_tests, vec3_div_double){
    Vec3 a;
    a[0] = 10;
    a[1] = 12;
    a[2] = 14;

    double b = 2;

    Vec3 res = a/b;

    EXPECT_EQ(res[0],5);
    EXPECT_EQ(res[1],6);
    EXPECT_EQ(res[2],7);
}

TEST(type_tests, doublefield) {
    doublefield<10, 10> F;
    for (int i = 0; i < 100; i++) {
        F.f[i] = i;
    }

    EXPECT_EQ(F.f[0], 0);
    EXPECT_EQ(F.f[5], 5);
    EXPECT_EQ(F.f[70], 70);
}

TEST(type_tests, doublefield_sum) {
    doublefield<10, 10> A;
    for (int i = 0; i < 100; i++) {
        A.f[i] = i;
    }

    doublefield<10, 10> B;
    for (int i = 0; i < 100; i++) {
        B.f[i] = i;
    }

    doublefield<10, 10> F = A + B;

    EXPECT_EQ(F.f[0], 0);
    EXPECT_EQ(F.f[5], 10);
    EXPECT_EQ(F.f[70], 140);
}

TEST(type_tests, doublefield_mult_double) {
    doublefield<10, 10> A;
    for (int i = 0; i < 100; i++) {
        A.f[i] = i;
    }

    double f = 5;

    doublefield<10, 10> F = A * f;

    EXPECT_EQ(F.f[0], 0);
    EXPECT_EQ(F.f[5], 25);
    EXPECT_EQ(F.f[70], 350);
}

TEST(type_tests, Vec3field) {
    Vec3field<10, 10> F;
    for (int i = 0; i < 100; i++) {
        F.F[i].a[0] = i + 0;
        F.F[i].a[1] = i + 1;
        F.F[i].a[2] = i + 2;
    }

    EXPECT_EQ(F.F[0].a[0], 0);
    EXPECT_EQ(F.F[0].a[1], 1);
    EXPECT_EQ(F.F[0].a[2], 2);

    EXPECT_EQ(F.F[5].a[0], 5);
    EXPECT_EQ(F.F[5].a[1], 6);
    EXPECT_EQ(F.F[5].a[2], 7);
}

TEST(type_tests, Vec3field_sum) {
    Vec3field<10, 10> A;
    for (int i = 0; i < 100; i++) {
        A.F[i].a[0] = i + 0;
        A.F[i].a[1] = i + 1;
        A.F[i].a[2] = i + 2;
    }

    Vec3field<10, 10> B;
    for (int i = 0; i < 100; i++) {
        B.F[i].a[0] = i + 0;
        B.F[i].a[1] = i + 1;
        B.F[i].a[2] = i + 2;
    }

    Vec3field<10, 10> F = A + B;

    EXPECT_EQ(F.F[0].a[0], 0);
    EXPECT_EQ(F.F[0].a[1], 2);
    EXPECT_EQ(F.F[0].a[2], 4);

    EXPECT_EQ(F.F[5].a[0], 10);
    EXPECT_EQ(F.F[5].a[1], 12);
    EXPECT_EQ(F.F[5].a[2], 14);
}

TEST(type_tests, Vec3field_mult_Vec3field) {
    Vec3field<10, 10> A;
    for (int i = 0; i < 100; i++) {
        A.F[i].a[0] = i + 0;
        A.F[i].a[1] = i + 1;
        A.F[i].a[2] = i + 2;
    }

    Vec3field<10, 10> B;
    for (int i = 0; i < 100; i++) {
        B.F[i].a[0] = i + 0;
        B.F[i].a[1] = i + 1;
        B.F[i].a[2] = i + 2;
    }

    Vec3field<10, 10> F = A * B;

    EXPECT_EQ(F.F[0].a[0], 0);
    EXPECT_EQ(F.F[0].a[1], 1);
    EXPECT_EQ(F.F[0].a[2], 4);

    EXPECT_EQ(F.F[5].a[0], 25);
    EXPECT_EQ(F.F[5].a[1], 36);
    EXPECT_EQ(F.F[5].a[2], 49);
}


TEST(type_tests, Vec3field_mult_double) {
    Vec3field<10, 10> A;
    for (int i = 0; i < 100; i++) {
        A.F[i].a[0] = i + 0;
        A.F[i].a[1] = i + 1;
        A.F[i].a[2] = i + 2;
    }

    double f = 5;

    Vec3field<10, 10> F = A * f;

    EXPECT_EQ(F.F[0].a[0], 0);
    EXPECT_EQ(F.F[0].a[1], 5);
    EXPECT_EQ(F.F[0].a[2], 10);

    EXPECT_EQ(F.F[5].a[0], 25);
    EXPECT_EQ(F.F[5].a[1], 30);
    EXPECT_EQ(F.F[5].a[2], 35);
}

TEST(Nabla_tests, gradient) {
    doublefield<10, 10> f;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            f.f[i + j * 10] = i;
        }
    }

    Nabla n;

    Vec3field grad = n * f;

    EXPECT_EQ(grad.F[11].a[0], 1);
    EXPECT_EQ(grad.F[11].a[1], 0);

    EXPECT_EQ(grad.F[55].a[0], 1);
    EXPECT_EQ(grad.F[94].a[1], 0);
}

TEST(Nabla_tests, div) {
    Vec3field<10, 10> F;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            F.F[i + j * 10].a[0] = i + j;
            F.F[i + j * 10].a[1] = i + j;
            F.F[i + j * 10].a[2] = i + j;
        }
    }

    Nabla n;

    doublefield grad = n * F;

    EXPECT_EQ(grad.f[11], 2);
    EXPECT_EQ(grad.f[55], 2);
}

TEST(Laplassian_tests, laplassian) {
    Vec3field<10, 10> F;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            F.F[i + j * 10].a[0] = i + j;
            F.F[i + j * 10].a[1] = i + j;
            F.F[i + j * 10].a[2] = i + j;
        }
    }

    Laplassian L;

    Vec3field lap = L * F;

    EXPECT_EQ(lap.F[11].a[0], 0);
    EXPECT_EQ(lap.F[11].a[1], 0);

    EXPECT_EQ(lap.F[55].a[0], 0);
    EXPECT_EQ(lap.F[55].a[1], 0);
}

TEST(solver, solver){
    Solver<50,50> solver = Solver<50, 50>();
    
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
