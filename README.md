# c3po - C++ Palette Obtainer

A C++ implementation of k-means++ for extracting prominent colors from PNG images.

## Compilation
Using g++ on Unix/Linux, enter the following command:

`g++ -std=c++11 c3po.cpp Centroid.cpp KMeans.cpp Pixel.cpp lodepng.cpp -o c3po`

## Usage
Using c3po is pretty straight forward. The command format for using c3po is as follows:

`c3po [name of image file] [number of colors to generate]`

For example, in order to extract 5 prominent colors from an image called `example.png`, you can just issue the following command:

`c3po example.png 5`

This will print out the colors to standard output and also generate a file called `quantized_example.png` which is the original image restricted to the generated color palette.

__NOTE__: It is suggested that you use PNG files with small dimensions (i.e. 100x100). The reason for this is that k-means++ can get really slow very quickly. Execution time is noticeably slower even with dimensions of 256x256.

## Credits
[@lvandeve](https://github.com/lvandeve) for [LodePNG](https://github.com/lvandeve/lodepng)
