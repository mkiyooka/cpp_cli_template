# ビルド方法

``` sh
clone https://github.com/mkiyooka/cpp_cli_template
cd cpp_cli_template
mkdir build && cd build
cmake ..
make -j
```

コンパイラをclangにする場合

``` sh
clone https://github.com/mkiyooka/cpp_cli_template
cd cpp_cli_template
mkdir build && cd build
cmake -C ../clang-cmakeinit.cmake ../
make -j
```
