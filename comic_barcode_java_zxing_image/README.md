# comic_barcode_java_zxing_image

A simple POC Java application using zxing to extract a comic book barcode from an image

## Overview

This project is a very simple implementation and example of using the [zxing library](https://github.com/zxing/zxing) to extract a comic book barcode. This was written as a first test to see if zxing could handle the "supplementary barcode" on modern comic books - commonly called UPC or EAN extensions, EAN-2 or EAN-5 depending on length, and known in the barcode-world as addenda codes.

## Requirements

- JDK
- Maven

## QuickStart

Install requirements:

```
sudo apt install default-jdk maven
```

Download the repo:

```
git clone https://github.com/TheGrayDot/comic_barcode_example_apps.git
```

Compile the project

```
cd comic_barcode_example_apps/comic_barcode_java_zxing_image
mvn package
```

Run the tool with a provided image:


```
java -jar target/comic_barcode_java_zxing_image-1.0-shaded.jar <some-image>
java -jar target/comic_barcode_java_zxing_image-1.0-shaded.jar ../test/upc5.jpg
```
