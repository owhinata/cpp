# host2ip
Resolve hostname to ip address.

## requirement
```
-std=c++17
asio (installed in build directory automatically)
```

## build
```bash
mkdir build && cd build
cmake ..
make
```

## usage
```bash
./host2ip <hostname>
```

## test
To run tests,
```bash
ctest
```
Tested Platform
* Linux (Ubuntu 16.04 Xenial) using g++ 5.4

