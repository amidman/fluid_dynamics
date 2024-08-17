#include "types.h"

template <int N, int M> class Solver {
  public:
    Vec3field<N, M> V[2];
    doublefield<N, M> P[2];
    doublefield<N, M> ro[2];

    double T = 273;
    int step_count = 1;

    Solver() {}

    void set_all_P(double P_) {
        for (int i = 0; i < N * M; ++i) {
            P[0][i] = P_;
            P[1][i] = P_;
        }
    }

    void set_all_ro(double ro_) {
        for (int i = 0; i < N * M; ++i) {
            ro[0][i] = ro_;
            ro[1][i] = ro_;
        }
    }

    void set_all_V(Vec3 V_) {
        for (int i = 0; i < N * M; ++i) {
            V[0][i] = V_;
            V[1][i] = V_;
        }
    }

    doublefield<N, M> calc_P(doublefield<N, M> ro_) {
        doublefield<N, M> res;
        res = 1e5 * ro_;
        return res;
    }

    void solve_step() {
        Nabla nabla;
        Laplassian lap;
        x_Nabla_x x_n_x;

        double tau = 1e-6;
        double nu = 1e-6;
        double eta = 1e-9;

        int idxn = step_count % 2;
        int idxp = (step_count - 1) % 2;

        V[idxn] = V[idxp] + (lap * V[idxp] * nu + nabla * (nabla * V[idxp]) * (eta + nu / 3) - nabla * P[idxp] - x_n_x * V[idxp]) * tau;
        ro[idxn] = ro[idxp] - (nabla * (ro[idxp] * V[idxp])) * tau;
        P[idxn] = calc_P(ro[idxn]);

        step_count++;
    }
};