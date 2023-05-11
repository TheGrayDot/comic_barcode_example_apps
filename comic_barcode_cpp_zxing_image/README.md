# comic_barcode_cpp_zxing_image

A simple POC C++ application using zxing-cpp to extract a comic book barcode from an image

## Overview

This project is a very simple implementation and example of using the [zxing-cpp library](https://github.com/zxing-cpp/zxing-cpp) to extract a comic book barcode. This was written as a first test to see if zxing-cpp could handle the "supplementary barcode" on modern comic books - commonly called UPC or EAN extensions, EAN-2 or EAN-5 depending on length, and known in the barcode-world as addenda codes. This code is heavily based on the [ZXingReader.cpp](https://github.com/zxing-cpp/zxing-cpp/blob/master/example/ZXingReader.cpp) example provided in the zxing-cpp project.

## Requirements

- cmake
- C++17 compliant compiler (e.g., gcc 7)

## QuickStart

Install requirements:

```
sudo apt install cmake libstb-dev
```

The `libstd-dev` is a package to install the [`stb` header files](https://github.com/nothings/stb). For reference, they are installed to the following path:

```
/usr/include/stb/
```

Download the repo:

```
git clone https://github.com/TheGrayDot/comic_barcode_example_apps.git
cd comic_barcode_example_apps/comic_barcode_cpp_zxing_image
```

Download and compile the zxing-cpp project:

```
git clone https://github.com/zxing-cpp/zxing-cpp.git --single-branch --depth 1
cmake -S zxing-cpp -B zxing-cpp.release -DCMAKE_BUILD_TYPE=Release
cmake --build zxing-cpp.release -j8
# The line below is not required
# It installs zxing-cpp system wide
sudo cmake --install zxing-cpp.release/
```

Compile the project:

```
g++ -std=c++17 -o comic_barcode_cpp_zxing_image comic_barcode_cpp_zxing_image.cpp -I/usr/include/stb/ -Izxing-cpp/core/src/ -lZXing 
```

Run the tool with a provided image:

```
./comic_barcode_cpp_zxing_image ../test/upc5.jpg
```
