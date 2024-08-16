#include "types.h"

template <int N, int M> class Solver {
  public:
    Vec3field<N, M> V_old;
    floatfield<N, M> P_old;
    floatfield<N, M> ro_old;

    Vec3field<N, M> V_new;
    floatfield<N, M> P_new;
    floatfield<N, M> ro_new;

    Solver() {}

    void solve_step() {
        Nabla nabla;
        Laplassian lap;
        x_Nabla_x x_n_x;

        float tau = 1e-6;
        float nu = 1e-6;
        float eta = 1e-9;

        V_new = V_old + (lap * V_old * nu + nabla * (nabla * V_old) * (eta + nu / 3) - nabla * P_old - x_n_x * V_old) * tau;
    }
};