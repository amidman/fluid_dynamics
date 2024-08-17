#include "types.h"
#include <iostream>

template <int N, int M> class Solver {
  public:
    Vec3field<N, M> V[2];
    doublefield<N, M> P[2];
    doublefield<N, M> ro[2];
    Vec3field<N, M> F;

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

    void add_gravity(Vec3 g) {
        for (int i = 0; i < N * M; ++i) {
            F[i] = g;
        }
    }

    void boundary_conditions(int idx) {
        Vec3 zero = {0, 0, 0};
        for (int i = 0; i < N; ++i) {
            P[idx][i] = P[idx][i + N];
            ro[idx][i] = ro[idx][i + N];
            V[idx][i] = zero;
            // P[idx][i] = 0;
            //  ro[idx][i] = 0;
        }

        for (int i = 1; i < N - 1; ++i) {
            // P[idx][i + N * (M - 1)] = P[idx][i + N * (M - 2)];
            // ro[idx][i + N * (M - 1)] = ro[idx][i + N * (M - 2)];
            // V[idx][i + N * (M - 1)] = zero;
            P[idx][i + N * (M - 1)] = 1e4;
            ro[idx][i + N * (M - 1)] = 0.1;
            ;
        }

        for (int j = 1; j < M - 1; ++j) {
            P[idx][j * N] = P[idx][1 + j * N];
            ro[idx][j * N] = ro[idx][1 + j * N];
            V[idx][j * N] = zero;
        }

        for (int j = 1; j < M - 1; ++j) {
            P[idx][j * N + M - 1] = P[idx][j * N + M - 2];
            ro[idx][j * N + M - 1] = ro[idx][j * N + M - 2];
            V[idx][j * N + M - 1] = zero;
        }
        P[idx][0] = (P[idx][1] + P[idx][N]) / 2;
        ro[idx][0] = (ro[idx][1] + ro[idx][N]) / 2;
        V[idx][0] = zero;

        P[idx][N - 1] = (P[idx][N - 2] + P[idx][N - 1 + N]) / 2;
        ro[idx][N - 1] = (ro[idx][N - 2] + ro[idx][N - 1 + N]) / 2;
        V[idx][N - 1] = zero;

        P[idx][(M - 1) * N] = (P[idx][(M - 1) * N + 1] + P[idx][(M - 2) * N]) / 2;
        ro[idx][(M - 1) * N] = (ro[idx][(M - 1) * N + 1] + ro[idx][(M - 2) * N]) / 2;
        V[idx][(M - 1) * N] = zero;

        P[idx][M * N - 1] = (P[idx][M * N - 2] + P[idx][(M - 1) * N - 1]) / 2;
        ro[idx][M * N - 1] = (ro[idx][M * N - 2] + ro[idx][(M - 1) * N - 1]) / 2;
        V[idx][M * N - 1] = zero;

        for (int i = 0; i < N; ++i) {
            for (int j = M / 2; j < M - 1; ++j) {
                // P[idx][i + j * N] = 1e5 + (50-j) * 2000;
            }
        }
    }

    doublefield<N, M> calc_P(doublefield<N, M> ro_) {
        doublefield<N, M> res;
        res = 1e5 * ro_;
        return res;
    }

    void solve_step() {
        Nabla<1> nabla;
        Laplassian lap;
        x_Nabla_x x_n_x;

        double tau = 1e-9;
        double nu = 18e-6;
        double eta = 1e-12;
        double h = 1e-3;

        int idxn = step_count % 2;
        int idxp = (step_count - 1) % 2;

        boundary_conditions(idxp);

        // V[idxn] = V[idxp] + (lap * V[idxp] * nu / (h * h) + nabla * (nabla * V[idxp]) * (eta + nu / 3) / (h * h) - nabla * P[idxp] / h - x_n_x * V[idxp] / (h * h)) * tau;
        // ro[idxn] = ro[idxp] - (nabla * (ro[idxp] * V[idxp])) * tau / h;
        // P[idxn] = calc_P(ro[idxn]);

        V[idxn] = V[idxp] - (F - nabla * P[idxp] / h / ro[idxp]) * tau;
        ro[idxn] = ro[idxp] - (nabla * (ro[idxp] * V[idxn])) * tau / h;
        P[idxn] = calc_P(ro[idxn]);

        boundary_conditions(idxn);

        step_count++;
    }
};