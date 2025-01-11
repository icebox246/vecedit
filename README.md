# VecEdit

Editor for vector graphics.

## Quick start (on Linux or MacOS)

Install:

- `cmake` >= 3.30
- `clang` or `gcc`

To setup build environment (manually):

```
mkdir build
cd build
cmake ..
```

To build and run (assuming current directory is already `build/`)

```
make -j8   # number relies on CPU count
./VecEdit
```

### Cross compilation for Windows 64-bit

This setup was prepared on Arch Linux, other distributions may require modifying `TC-mingw.cmake`.

Install:

```
- `mingw-w64-gcc`
```

To setup build environment and run compilation:

```
mkdir build_win
cd build_win
cmake .. -DCMAKE_TOOLCHAIN_FILE=../TC-mingw.cmake
make -j9
```

Such compilation results in `VecEdit.exe` which can be ran on Windows without additional dependencies.
