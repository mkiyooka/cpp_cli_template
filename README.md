# ビルド方法

``` sh
clone https://github.com/mkiyooka/cpp_cli_template --recursive
cd cpp_cli_template
```

``` sh
mkdir build && cd build
cmake ..
make -j
```

コンパイラをclangにする場合

``` sh
mkdir build && cd build
cmake -C ../clang-cmakeinit.cmake ../
make -j
```

``` sh
# solve $2x - 3 = 0$ with bisection method
./cmd bisection linear 15 --coefs=2.0 --coefs=-3.0
# solve $2x - 3 = 0$ with newton method
./cmd newton linear 15 --coefs=2.0 --coefs=-3.0

# solve $2x^2 - 3 = 0$ with bisection method
./cmd bisection quadratic 15 --coefs=2.0 --coefs=-3.0
# solve $2x^2 - 3 = 0$ with newton method
./cmd newton quadratic 15 --coefs=2.0 --coefs=-3.0

# vector型の変数への取り込みは以下の2種類の指定が可能
./cmd newton quadratic 15 --coefs=2.0 --coefs=-3.0
./cmd newton quadratic 15 --coefs=[2.0,-3.0]
```
