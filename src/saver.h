#pragma once

#include "types.h"
#include <fstream>
#include <string>

template <int N, int M> void save_vec3field(Vec3field<N, M> V, std::string file_name) {
    std::ofstream outputFileStream(file_name, std::ios::out | std::ios::binary);
    int N_ = N;
    int M_ = M;

    outputFileStream.write((char *)&N_, sizeof(int));
    outputFileStream.write((char *)&M_, sizeof(int));

    for (int i = 0; i < M * N; i++) {
        outputFileStream.write((char *)&V[i][0], sizeof(double));
        outputFileStream.write((char *)&V[i][1], sizeof(double));
    }

    outputFileStream.close();
}

template <int N, int M> void save_doublefield(doublefield<N, M> f, std::string file_name) {
    std::ofstream outputFileStream(file_name, std::ios::out | std::ios::binary);
    int N_ = N;
    int M_ = M;

    outputFileStream.write((char *)&N_, sizeof(int));
    outputFileStream.write((char *)&M_, sizeof(int));

    for (int i = 0; i < M * N; i++) {
        outputFileStream.write((char *)&f[i], sizeof(double));
    }

    outputFileStream.close();
}

template <int N, int M> void save_P_ro_V(doublefield<N, M> P, doublefield<N, M> ro, Vec3field<N, M> V, std::string file_name) {
    std::ofstream outputFileStream(file_name, std::ios::out | std::ios::binary);
    int N_ = N;
    int M_ = M;

    outputFileStream.write((char *)&N_, sizeof(int));
    outputFileStream.write((char *)&M_, sizeof(int));

    for (int i = 0; i < M * N; i++) {
        outputFileStream.write((char *)&P[i], sizeof(double));
        outputFileStream.write((char *)&ro[i], sizeof(double));
        outputFileStream.write((char *)&V[i][0], sizeof(double));
        outputFileStream.write((char *)&V[i][1], sizeof(double));
    }

    outputFileStream.close();
}