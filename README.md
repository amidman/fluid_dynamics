# Fluid dynamics
Some simulation

### Build and run
```bash
cmake -S . -B build
cmake --build build
./build/fluid_dynamics
```

### Build and run tests:
```bash
cmake -S . -B build
cmake --build build
cd build && ctest
```

### To format source code:
You need install [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
```bash
clang-format -style=file:.clang-format -i src/*.cpp src/*.h
```
