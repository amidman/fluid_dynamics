#pragma once

struct Vec3 {
    double a[3] = {0};

    double &operator[](int idx) { return a[idx]; }
    double operator[](int idx) const { return a[idx]; }
};

Vec3 operator+(const Vec3 &a, const Vec3 &b) {
    Vec3 res;
    for (int i = 0; i < 3; ++i) {
        res[i] = a[i] + b[i];
    }
    return res;
}

Vec3 operator-(const Vec3 &a, const Vec3 &b) {
    Vec3 res;
    for (int i = 0; i < 3; ++i) {
        res[i] = a[i] - b[i];
    }
    return res;
}

Vec3 operator*(const Vec3 &a, double b) {
    Vec3 res;
    for (int i = 0; i < 3; ++i) {
        res[i] = a[i] * b;
    }
    return res;
}

Vec3 operator*(double b, const Vec3 &a) {
    Vec3 res;
    for (int i = 0; i < 3; ++i) {
        res[i] = a[i] * b;
    }
    return res;
}

Vec3 operator/(const Vec3 &a, double b) {
    Vec3 res;
    for (int i = 0; i < 3; ++i) {
        res[i] = a[i] / b;
    }
    return res;
}

template <int N, int M> struct Vec3field {
    Vec3 F[N * M];

    Vec3 &operator[](int idx) { return F[idx]; }
    Vec3 operator[](int idx) const { return F[idx]; }
};

template <int N, int M> struct floatfield {
    float f[N * M];

    float &operator[](int idx) { return f[idx]; }
    float operator[](int idx) const { return f[idx]; }
};

template <int N, int M> floatfield<N, M> operator*(float f, const floatfield<N, M> &a) {
    floatfield<N, M> res;

    for (int i = 0; i < N * M; ++i) {
        res[i] = a[i] * f;
    }

    return res;
}

template <int N, int M> floatfield<N, M> operator*(const floatfield<N, M> &a, float f) {
    floatfield<N, M> res;

    for (int i = 0; i < N * M; ++i) {
        res[i] = a[i] * f;
    }

    return res;
}

template <int N, int M> floatfield<N, M> operator+(const floatfield<N, M> &a, const floatfield<N, M> &b) {
    floatfield<N, M> res;

    for (int i = 0; i < N * M; ++i) {
        res[i] = a[i] + b[i];
    }

    return res;
}

template <int N, int M> Vec3field<N, M> operator*(const Vec3field<N, M> &A, const Vec3field<N, M> &B) {
    Vec3field<N, M> res;

    for (int i = 0; i < N*M; ++i) {
            res[i][0] = A[i][0] * B[i][0];
            res[i][1] = A[i][1] * B[i][1];
            res[i][2] = A[i][2] * B[i][2];
    }
    return res;
}

template <int N, int M> Vec3field<N, M> operator*(float f, const Vec3field<N, M> &a) {
    Vec3field<N, M> res;

    for (int i = 0; i < N * M; ++i) {
        res[i] = a[i] * f;
    }

    return res;
}

template <int N, int M> Vec3field<N, M> operator*(const Vec3field<N, M> &a, float f) {
    Vec3field<N, M> res;

    for (int i = 0; i < N * M; ++i) {
        res[i] = a[i] * f;
    }

    return res;
}

template <int N, int M> Vec3field<N, M> operator+(const Vec3field<N, M> &a, const Vec3field<N, M> &b) {
    Vec3field<N, M> res;

    for (int i = 0; i < N * M; ++i) {
        res[i] = a[i] + b[i];
    }

    return res;
}

template <int d = 2> struct Nabla {};

struct Laplassian {};

template <int N, int M> Vec3field<N, M> operator*(Nabla<2> n, const floatfield<N, M> &f) {
    Vec3field<N, M> res;

    for (int i = 1; i < N - 1; ++i) {
        for (int j = 1; j < M - 1; ++j) {
            res[i + j * N][0] = (f[i + 1 + j * N] - f[i - 1 + j * N]) / 2;
            res[i + j * N][1] = (f[i + (j + 1) * N] - f[i + (j - 1) * N]) / 2;
            res[i + j * N][2] = 0;
        }
    }
    return res;
}

template <int N, int M> floatfield<N, M> operator*(Nabla<2> n, const Vec3field<N, M> &f) {
    floatfield<N, M> res;

    for (int i = 1; i < N - 1; ++i) {
        for (int j = 1; j < M - 1; ++j) {
            res[i + j * N] = (f[i + 1 + j * N][0] - f[i - 1 + j * N][0]) / 2 + (f[i + (j + 1) * N][1] - f[i + (j - 1) * N][1]) / 2;
        }
    }
    return res;
}

template <int N, int M> Vec3field<N, M> operator*(Laplassian n, const Vec3field<N, M> &F) {
    Vec3field<N, M> res;

    for (int i = 1; i < N - 1; ++i) {
        for (int j = 1; j < M - 1; ++j) {
            res[i + j * N][0] = (F[i + 1 + j * N][0] + F[i - 1 + j * N][0] - 2 * F[i + j * N][0]) + (F[i + (j + 1) * N][0] + F[i + (j - 1) * N][0] - 2 * F[i + j * N][0]);
            res[i + j * N][1] = (F[i + 1 + j * N][1] + F[i - 1 + j * N][1] - 2 * F[i + j * N][1]) + (F[i + (j + 1) * N][1] + F[i + (j - 1) * N][1] - 2 * F[i + j * N][1]);
            res[i + j * N][2] = 0;
        }
    }
    return res;
}

template <int d = 2> struct x_Nabla_x {};

template <int N, int M> Vec3field<N, M> operator*(x_Nabla_x<2> n, const Vec3field<N, M> &F) {
    Vec3field<N, M> res;

    for (int i = 1; i < N - 1; ++i) {
        for (int j = 1; j < M - 1; ++j) {
            res[i + j * N][0] = F[i + j * N][0] * (F[i + 1 + j * N][0] - F[i - 1 + j * N][0]) / 2 + F[i + j * N][1] * (F[i + (j + 1) * N][0] - F[i + (j - 1) * N][0]) / 2;
            res[i + j * N][1] = F[i + j * N][0] * (F[i + 1 + j * N][1] - F[i - 1 + j * N][1]) / 2 + F[i + j * N][1] * (F[i + (j + 1) * N][1] - F[i + (j - 1) * N][1]) / 2;
            res[i + j * N][2] = 0;
        }
    }
    return res;
}

struct config_fluid {
    float nu;
    float eta;
};