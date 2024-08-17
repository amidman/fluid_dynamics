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
    Vec3 *F;

    Vec3field() { F = new Vec3[N * M]; }
    ~Vec3field() { delete[] F; }

    // Конструктор копирования
    Vec3field(const Vec3field &other) {
        F = new Vec3[N * M];
        for (int i = 0; i < N * M; ++i) {
            F[i] = other.F[i];
        }
    }

    // Конструктор перемещения, noexcept - для оптимизации при использовании стандартных контейнеров
    Vec3field(Vec3field &&other) noexcept {
        F = other.F;
        other.F = nullptr;
    }

    // Оператор присваивания копированием (copy assignment)
    Vec3field &operator=(const Vec3field &other) {
        if (this == &other)
            return *this;

        Vec3 *tmp_vec3 = new Vec3[N * M];

        for (int i = 0; i < N * M; ++i) {
            tmp_vec3[i] = other.F[i];
        }
        delete[] F;
        F = tmp_vec3;
        return *this;
    }

    // Оператор присваивания перемещением (move assignment)
    Vec3field &operator=(Vec3field &&other) noexcept {
        if (this == &other)
            return *this;

        delete[] F;
        F = other.F;
        other.F = nullptr;
        return *this;
    }

    Vec3 &operator[](int idx) { return F[idx]; }
    Vec3 operator[](int idx) const { return F[idx]; }
};

template <int N, int M> struct doublefield {
    double *f;

    doublefield() { f = new double[N * M]; }
    ~doublefield() { delete[] f; }

// Конструктор копирования
    doublefield(const doublefield &other) {
        f = new double[N * M];
        for (int i = 0; i < N * M; ++i) {
            f[i] = other.f[i];
        }
    }

    // Конструктор перемещения, noexcept - для оптимизации при использовании стандартных контейнеров
    doublefield(doublefield &&other) noexcept {
        f = other.f;
        other.f = nullptr;
    }

    // Оператор присваивания копированием (copy assignment)
    doublefield &operator=(const doublefield &other) {
        if (this == &other)
            return *this;

        double *tmp_double = new double[N * M];
        
        for (int i = 0; i < N * M; ++i) {
            tmp_double[i] = other.f[i];
        }
        delete[] f;
        f = tmp_double;
        return *this;
    }

    // Оператор присваивания перемещением (move assignment)
    doublefield &operator=(doublefield &&other) noexcept {
        if (this == &other)
            return *this;

        delete[] f;
        f = other.f;
        other.f = nullptr;
        return *this;
    }

    double &operator[](int idx) { return f[idx]; }
    double operator[](int idx) const { return f[idx]; }
};

template <int N, int M> doublefield<N, M> operator*(double f, const doublefield<N, M> &a) {
    doublefield<N, M> res;

    for (int i = 0; i < N * M; ++i) {
        res[i] = a[i] * f;
    }

    return res;
}

template <int N, int M> doublefield<N, M> operator*(const doublefield<N, M> &a, double f) {
    doublefield<N, M> res;

    for (int i = 0; i < N * M; ++i) {
        res[i] = a[i] * f;
    }

    return res;
}

template <int N, int M> doublefield<N, M> operator+(const doublefield<N, M> &a, const doublefield<N, M> &b) {
    doublefield<N, M> res;

    for (int i = 0; i < N * M; ++i) {
        res[i] = a[i] + b[i];
    }

    return res;
}

template <int N, int M> doublefield<N, M> operator-(const doublefield<N, M> &a, const doublefield<N, M> &b) {
    doublefield<N, M> res;

    for (int i = 0; i < N * M; ++i) {
        res[i] = a[i] - b[i];
    }

    return res;
}

template <int N, int M> Vec3field<N, M> operator*(const Vec3field<N, M> &A, const Vec3field<N, M> &B) {
    Vec3field<N, M> res;

    for (int i = 0; i < N * M; ++i) {
        res[i][0] = A[i][0] * B[i][0];
        res[i][1] = A[i][1] * B[i][1];
        res[i][2] = A[i][2] * B[i][2];
    }
    return res;
}

template <int N, int M> Vec3field<N, M> operator*(const doublefield<N, M> &A, const Vec3field<N, M> &B) {
    Vec3field<N, M> res;

    for (int i = 0; i < N * M; ++i) {
        res[i][0] = A[i] * B[i][0];
        res[i][1] = A[i] * B[i][1];
        res[i][2] = A[i] * B[i][2];
    }
    return res;
}

template <int N, int M> Vec3field<N, M> operator*(double f, const Vec3field<N, M> &a) {
    Vec3field<N, M> res;

    for (int i = 0; i < N * M; ++i) {
        res[i] = a[i] * f;
    }

    return res;
}

template <int N, int M> Vec3field<N, M> operator*(const Vec3field<N, M> &a, double f) {
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

template <int N, int M> Vec3field<N, M> operator-(const Vec3field<N, M> &a, const Vec3field<N, M> &b) {
    Vec3field<N, M> res;

    for (int i = 0; i < N * M; ++i) {
        res[i] = a[i] - b[i];
    }

    return res;
}

template <int d = 2> struct Nabla {};

struct Laplassian {};

template <int N, int M> Vec3field<N, M> operator*(Nabla<2> n, const doublefield<N, M> &f) {
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

template <int N, int M> doublefield<N, M> operator*(Nabla<2> n, const Vec3field<N, M> &f) {
    doublefield<N, M> res;

    for (int i = 1; i < N - 1; ++i) {
        for (int j = 1; j < M - 1; ++j) {
            res[i + j * N] = (f[i + 1 + j * N][0] - f[i - 1 + j * N][0]) / 2 + (f[i + (j + 1) * N][1] - f[i + (j - 1) * N][1]) / 2;
        }
    }
    return res;
}

template <int N, int M> Vec3field<N, M> operator*(Laplassian n, const Vec3field<N, M> &F) {
    Vec3field<N, M> res;

    for (long int i = 1; i < N - 1; ++i) {
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
    double nu;
    double eta;
};