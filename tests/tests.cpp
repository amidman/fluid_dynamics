#include <cmath>
#include <fstream>
#include <iostream>

#include "../src/saver.h"
#include "../src/solver.h"
#include "../src/types.h"
#include "gtest/gtest.h"
#include <string>

TEST(type_tests, Vec3_indices_access) {
    Vec3 a;
    a[0] = 1;
    a[1] = 1;
    a[2] = 1;
}

TEST(type_tests, vec3_sum) {
    Vec3 a;
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    Vec3 b;
    b[0] = 4;
    b[1] = 5;
    b[2] = 6;

    Vec3 res = a + b;

    EXPECT_EQ(res[0], 5);
    EXPECT_EQ(res[1], 7);
    EXPECT_EQ(res[2], 9);
}

TEST(type_tests, vec3_substract) {
    Vec3 a;
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    Vec3 b;
    b[0] = 4;
    b[1] = 5;
    b[2] = 6;

    Vec3 res = b - a;

    EXPECT_EQ(res[0], 3);
    EXPECT_EQ(res[1], 3);
    EXPECT_EQ(res[2], 3);
}

TEST(type_tests, vec3_mult_double) {
    Vec3 a;
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    double b = 2;

    Vec3 res = a * b;

    EXPECT_EQ(res[0], 2);
    EXPECT_EQ(res[1], 4);
    EXPECT_EQ(res[2], 6);
}

TEST(type_tests, double_mult_vec3) {
    Vec3 a;
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    double b = 2;

    Vec3 res = b * a;

    EXPECT_EQ(res[0], 2);
    EXPECT_EQ(res[1], 4);
    EXPECT_EQ(res[2], 6);
}

TEST(type_tests, vec3_div_double) {
    Vec3 a;
    a[0] = 10;
    a[1] = 12;
    a[2] = 14;

    double b = 2;

    Vec3 res = a / b;

    EXPECT_EQ(res[0], 5);
    EXPECT_EQ(res[1], 6);
    EXPECT_EQ(res[2], 7);
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

    Vec3field<10, 10> F;
    F = A + B;

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

TEST(Laplassian_tests, x_N_x) {
    Vec3field<10, 10> F;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            F.F[i + j * 10].a[0] = i + j;
            F.F[i + j * 10].a[1] = i + j;
            F.F[i + j * 10].a[2] = i + j;
        }
    }

    x_Nabla_x x_n_x;

    Vec3field lap = x_n_x * F;

    EXPECT_EQ(lap.F[11].a[0], 4);
    EXPECT_EQ(lap.F[11].a[1], 4);

    EXPECT_EQ(lap.F[55].a[0], 20);
    EXPECT_EQ(lap.F[55].a[1], 20);
}

TEST(saver, save_doublefield) {
    doublefield<10, 10> f;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            f.f[i + j * 10] = i + j;
        }
    }

    save_doublefield(f, "test");
}

TEST(Nabla_tests, gradient_save) {
    doublefield<10, 10> f;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            f.f[i + j * 10] = i;
        }
    }

    Nabla n;

    Vec3field grad = n * f;

    save_P_ro_V(f, f, grad, "grad.bin");
}

TEST(solver, solver) {
    Solver<100, 100> solver = Solver<100, 100>();

    solver.set_all_P(1e5);
    solver.set_all_ro(1);
    Vec3 v = {0, 0, 0};
    solver.set_all_V(v);
    Vec3 g = {0, 9.810, 0};
    solver.add_gravity(g);

    for (int i = 0; i < 100; ++i) {
        for (int j = 100 / 2; j < 100 - 1; ++j) {
            solver.ro[0][i + j * 100] = 0.1;
            solver.ro[1][i + j * 100] = 0.1;
        }
    }

    // save_doublefield(solver.P[0], "0.bin");
    save_P_ro_V(solver.P[0], solver.ro[0], solver.V[0], "0.bin");

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            solver.solve_step();
        }
        save_P_ro_V(solver.P[0], solver.ro[0], solver.V[0], std::to_string(i + 1) + ".bin");
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}