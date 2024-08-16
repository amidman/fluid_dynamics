#pragma once


struct Vec3{
    double a[3] = {0};
};


Vec3 operator+(const Vec3& a, const Vec3& b){
    Vec3 res;
    for(int i=0;i<3;++i){
        res.a[i] = a.a[i]+b.a[i];
    }
    return res;
}

Vec3 operator-(const Vec3& a, const Vec3& b){
    Vec3 res;
    for(int i=0;i<3;++i){
        res.a[i] = a.a[i]-b.a[i];
    }
    return res;
}

Vec3 operator*(const Vec3& a, double b){
    Vec3 res;
    for(int i=0;i<3;++i){
        res.a[i] = a.a[i]*b;
    }
    return res;
}

Vec3 operator*(double b, const Vec3& a){
    Vec3 res;
    for(int i=0;i<3;++i){
        res.a[i] = a.a[i]*b;
    }
    return res;
}

template<int N, int M>
struct Vec3field{
    Vec3 F[N*M];
};

template<int N, int M>
struct floatfield{
    float f[N*M];
};

template<int N, int M>
floatfield<N,M> operator*(float f, const floatfield<N,M>& a){
    floatfield<N,M> res;

    for(int i=0;i<N*M;++i){
        res.f[i] = a.f[i]*f;
    }

    return res;
}

template<int N, int M>
floatfield<N,M> operator*(const floatfield<N,M>& a, float f){
    floatfield<N,M> res;

    for(int i=0;i<N*M;++i){
        res.f[i] = a.f[i]*f;
    }

    return res;
}

template<int N, int M>
floatfield<N,M> operator+(const floatfield<N,M>& a, const floatfield<N,M>& b){
    floatfield<N,M> res;

    for(int i=0;i<N*M;++i){
        res.f[i] = a.f[i] + b.f[i];
    }

    return res;
}

template<int N, int M>
Vec3field<N,M> operator*(float f, const Vec3field<N,M>& a){
    Vec3field<N,M> res;

    for(int i=0;i<N*M;++i){
        res.f[i] = a.f[i]*f;
    }

    return res;
}

template<int N, int M>
Vec3field<N,M> operator*(const Vec3field<N,M>& a, float f){
    Vec3field<N,M> res;

    for(int i=0;i<N*M;++i){
        res.F[i] = a.F[i]*f;
    }

    return res;
}

template<int N, int M>
Vec3field<N,M> operator+(const Vec3field<N,M>& a, const Vec3field<N,M>& b){
    Vec3field<N,M> res;

    for(int i=0;i<N*M;++i){
        res.F[i] = a.F[i] + b.F[i];
    }

    return res;
}

template<int d = 2>
struct Nabla{};

struct Laplassian{};

template<int N, int M>
Vec3field<N,M> operator*(Nabla<2> n, const floatfield<N,M>& f){
    Vec3field<N,M> res;

    for(int i=1;i<N-1;++i){
        for(int j=1;j<M-1;++j){
            res.F[i+j*N].a[0] = (f.f[i+1+j*N]-f.f[i-1+j*N])/2;
            res.F[i+j*N].a[1] = (f.f[i+(j+1)*N]-f.f[i+(j-1)*N])/2;
            res.F[i+j*N].a[2] = 0;
        }
    }
    return res;
}

template<int N, int M>
floatfield<N,M> operator*(Nabla<2> n, const Vec3field<N,M>& f){
    floatfield<N,M> res;

    for(int i=1;i<N-1;++i){
        for(int j=1;j<M-1;++j){
            res.F[i+j*N] = (f.f[i+1+j*N].a[0]-f.f[i-1+j*N].a[0])+(f.f[i+(j+1)*N].a[1]-f.f[i+(j-1)*N].a[1]);
        }
    }
    return res;
}

template<int N, int M>
Vec3field<N,M> operator*(Laplassian n, const Vec3field<N,M>& F){
    Vec3field<N,M> res;

    for(int i=1;i<N-1;++i){
        for(int j=1;j<M-1;++j){
            res.F[i+j*N].a[0] = (F.F[i+1+j*N].a[0]+F.F[i-1+j*N].a[0]-2*F.F[i+j*N].a[0]) + (F.F[i+(j+1)*N].a[0]+F.F[i+(j-1)*N].a[0]-2*F.F[i+j*N].a[0]);
            res.F[i+j*N].a[1] = (F.F[i+1+j*N].a[1]+F.F[i-1+j*N].a[1]-2*F.F[i+j*N].a[1]) + (F.F[i+(j+1)*N].a[1]+F.F[i+(j-1)*N].a[1]-2*F.F[i+j*N].a[1]);
            res.F[i+j*N].a[2] = 0;
        }
    }
    return res;
}

struct config_fluid{
    float nu;
    float eta;
};