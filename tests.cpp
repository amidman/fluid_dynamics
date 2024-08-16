#include<iostream>
#include<fstream>
#include<cmath>

#include"gtest/gtest.h"
#include"types.h"

TEST(type_tests,floatfield){
    floatfield<10,10> F;
    for(int i=0;i<100;i++){
        F.f[i] = i;
    }

    EXPECT_EQ(F.f[0],0);
    EXPECT_EQ(F.f[5],5);
    EXPECT_EQ(F.f[70],70);
}

TEST(type_tests,floatfield_sum){
    floatfield<10,10> A;
    for(int i=0;i<100;i++){
        A.f[i] = i;
    }

    floatfield<10,10> B;
    for(int i=0;i<100;i++){
        B.f[i] = i;
    }

    floatfield<10,10> F = A+B;

    EXPECT_EQ(F.f[0],0);
    EXPECT_EQ(F.f[5],10);
    EXPECT_EQ(F.f[70],140);
}

TEST(type_tests,floatfield_mult_float){
    floatfield<10,10> A;
    for(int i=0;i<100;i++){
        A.f[i] = i;
    }

    float f = 5;

    floatfield<10,10> F = A*f;

    EXPECT_EQ(F.f[0],0);
    EXPECT_EQ(F.f[5],25);
    EXPECT_EQ(F.f[70],350);
}


TEST(type_tests,Vec3field){
    Vec3field<10,10> F;
    for(int i=0;i<100;i++){
        F.F[i].a[0] = i+0;
        F.F[i].a[1] = i+1;
        F.F[i].a[2] = i+2;
    }

    EXPECT_EQ(F.F[0].a[0],0);
    EXPECT_EQ(F.F[0].a[1],1);
    EXPECT_EQ(F.F[0].a[2],2);

    EXPECT_EQ(F.F[5].a[0],5);
    EXPECT_EQ(F.F[5].a[1],6);
    EXPECT_EQ(F.F[5].a[2],7);
}

TEST(type_tests,Vec3field_sum){
    Vec3field<10,10> A;
    for(int i=0;i<100;i++){
        A.F[i].a[0] = i+0;
        A.F[i].a[1] = i+1;
        A.F[i].a[2] = i+2;
    }

    Vec3field<10,10> B;
    for(int i=0;i<100;i++){
        B.F[i].a[0] = i+0;
        B.F[i].a[1] = i+1;
        B.F[i].a[2] = i+2;
    }

    Vec3field<10,10> F = A+B;

    EXPECT_EQ(F.F[0].a[0],0);
    EXPECT_EQ(F.F[0].a[1],2);
    EXPECT_EQ(F.F[0].a[2],4);

    EXPECT_EQ(F.F[5].a[0],10);
    EXPECT_EQ(F.F[5].a[1],12);
    EXPECT_EQ(F.F[5].a[2],14);
}

TEST(type_tests,Vec3field_mult_float){
    Vec3field<10,10> A;
    for(int i=0;i<100;i++){
        A.F[i].a[0] = i+0;
        A.F[i].a[1] = i+1;
        A.F[i].a[2] = i+2;
    }

    float f = 5;

    Vec3field<10,10> F = A*f;

    EXPECT_EQ(F.F[0].a[0],0);
    EXPECT_EQ(F.F[0].a[1],5);
    EXPECT_EQ(F.F[0].a[2],10);

    EXPECT_EQ(F.F[5].a[0],25);
    EXPECT_EQ(F.F[5].a[1],30);
    EXPECT_EQ(F.F[5].a[2],35);
}

TEST(Nabla_tests, gradient){
    floatfield<10,10> f;

    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            f.f[i+j*10] = i;
        }
    }

    Nabla n;

    Vec3field grad = n*f;

    EXPECT_EQ(grad.F[11].a[0],1);
    EXPECT_EQ(grad.F[11].a[1],0);

    EXPECT_EQ(grad.F[55].a[0],1);
    EXPECT_EQ(grad.F[94].a[1],0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}