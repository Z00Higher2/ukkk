#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX_H = 512;  // Maximum height of the image
const int MAX_W = 512;  // Maximum width of the image

// Function to read an image from a file
void readImage(int image[MAX_H][MAX_W], int &height, int &width) {
    char c;
    int x;
    ifstream instr;
    instr.open("inImage.pgm");  // Open the input image file

    instr >> c;  // Read magic number
    assert(c == 'P');  // Ensure it's a PGM file
    instr >> c;
    assert(c == '2');  // Ensure it's a plain PGM file

    // Skip the comments (if any)
    while ((instr>>ws).peek() == '#') {
        instr.ignore(4096, '\n');
    }

    // Read width, height, and maximum value for a pixel
    instr >> width;
    instr >> height;

    assert(width <= MAX_W);  // Ensure width is within the maximum limit
    assert(height <= MAX_H);  // Ensure height is within the maximum limit
    int max;
    instr >> max;
    assert(max == 255);  // Ensure maximum pixel value is 255

    // Read pixel values into the image array
    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++)
            instr >> image[row][col];
    instr.close();
    return;
}

// Function to write an image to a file
void writeImage(int image[MAX_H][MAX_W], int height, int width) {
    ofstream ostr;
    ostr.open("outImage.pgm");  // Open the output image file
    if (ostr.fail()) {
        cout << "Unable to write file\n";
        exit(1);
    };

    // Write PGM header
    ostr << "P2" << endl;
    ostr << width << ' ';
    ostr << height << endl;
    ostr << 255 << endl;

    // Write pixel values to the file
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            assert(image[row][col] < 256);  // Ensure pixel value is within 0-255
            assert(image[row][col] >= 0);  // Ensure pixel value is non-negative
            ostr << image[row][col] << ' ';
            ostr << endl;
        }
    }
    ostr.close();
    return;
}

int main() {

    int img[MAX_H][MAX_W];  // Array to store input image
    int H, W;  // Height and width of the image

    readImage(img, H, W);  // Read the input image
    int out[MAX_H][MAX_W];  // Array to store output image

    // Creating a temporary array for image processing with a border of 1 pixel
    int temp[MAX_H+2][MAX_W+2];
    memset(temp,0,sizeof(temp));  // Initialize the temporary array to 0

    // Copying the input image to the temporary array
    for(int row = 0; row < H; row++) {
        for(int col = 0; col < W; col++) {
            temp[row+1][col+1] = img[row][col]; 
        }
    }

    int a,b,c,d,e,f,g,h,i;  // Variables to store pixel values
    int func;  // Variable to store the result of the filter operation

    // Applying the filter operation to each pixel in the temporary array
    for(int row = 1; row < H+1; row++) {
        for(int col = 1; col < W+1; col++) {
            // Neighboring pixel values for the current pixel
            a = temp[row-1][col-1];
            b = temp[row-1][col];
            c = temp[row-1][col+1];
            d = temp[row][col-1];
            e = temp[row][col];
            f = temp[row][col+1];
            g = temp[row+1][col-1];
            h = temp[row+1][col];
            i = temp[row+1][col+1];

            // Sobel edge detection filter operation
            func = (g + 2*h + i) - (a + 2*b + c);

            // Ensure the result is within the range 0-255
            if(func < 0) {
                func = 0;
            } 
            if(func > 255) {
                func = 255;
            }

            // Store the result in the output image array
            out[row-1][col-1] = func;
        }
    }

    // Write the output image to a file
    writeImage(out, H, W);
}
