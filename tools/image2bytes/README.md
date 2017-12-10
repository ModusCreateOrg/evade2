# Tool for converting images to byte arrays

### Installation

Compile using provided Make file `cd tools/image2bytes/ && make`

### Usage

```
Usage: image2bytes [-voh] [file...]
Convert image(s) to byte array

  -o DIR    Write output to DIR
  -v        Write byte array to stdout
  -vv       Write byte array and ASCII image to stdout
  -h        Show usage
```

Verbosity level can be increased with `-vv`. Doing so will display the resulting byte array as an ASCII image

### Examples

Convert example image to byte array and write to stdout

`./image2bytes image-example.png`

Convert all png images in current directory and write output to an existing directory

`./image2bytes *png -o exports/`

As above, but also raise the verbosity level to see an ASCII representation of the converted image

`./image2bytes image-example.png -o exports/ -vv`

Convert example image to byte array and pipe output to a different command

`./image2bytes image-example.png | tee raw_bytes.txt`

### Output

By default The output will be written to stdout,
by specifying a directory to write to with the `-o` option
you can generate a `.h` file with the same name as the input image

First 2 bytes are the width and height of the image

Next are bytes (little-endian) read vertically from top left moving right until end of image

```c
#ifndef MY_IMAGE
#define MY_IMAGE

const PROGMEM uint8_t my_image[] = {
    // width, height
    0x61, 0x15,

    // data
    0x70, 0x5f, 0xf2, 0xe6, 0x2c, 0x80, 0xe8, ...
};

#endif
```
