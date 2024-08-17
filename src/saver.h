#pragma once

#include "types.h"
#include <fstream>
#include <string>

template <int N, int M> void save_vec3field(Vec3field<N, M> V, std::string file_name) {
    std::ofstream outputFileStream("foo.bin", std::ios::out | std::ios::binary);

    outputFileStream.write((char *)N, sizeof(int));
    outputFileStream.write((char *)M, sizeof(int));

    for (int i = 0; i < M * N; i++) {
        outputFileStream.write((char *)&V[i][0], sizeof(float));
        outputFileStream.write((char *)&V[i][1], sizeof(float));
        outputFileStream.write((char *)&V[i][2], sizeof(float));
    }

    outputFileStream.close();
}

template <int N, int M> void save_doublefield(doublefield<N, M> f, std::string file_name) {
    std::ofstream outputFileStream("foo.bin", std::ios::out | std::ios::binary);
    int N_ = N;
    int M_ = M;

    outputFileStream.write((char *)&N_, sizeof(int));
    outputFileStream.write((char *)&M_, sizeof(int));

    for (int i = 0; i < M * N; i++) {
        outputFileStream.write((char *)&f[i], sizeof(double));
    }

    outputFileStream.close();
}