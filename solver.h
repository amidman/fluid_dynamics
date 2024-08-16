#include"types.h"

class Solver{
    public:

    Vec3field* V_old;
    floatfield* P_old;
    floatfield* ro_old;

    Vec3field* V_new;
    floatfield* P_new;
    floatfield* ro_new;

    int N;
    int M;

    Solver(int N, int M){
        this.N = N;
        this.M = M;

        V_old = new Vec3field(N,M);
        V_new = new Vec3field(N,M);

        P_old = new floatfield(N,M);
        P_new = new floatfield(N,M);

        ro_old = new floatfield(N,M);
        ro_new = new floatfield(N,M);
    }

    
};