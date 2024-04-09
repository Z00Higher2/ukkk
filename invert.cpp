// Author: Zuhayer Tashin
// Course: CSCI-135
// Instructor: Tong Yi
// Assignment: Lab 8A
// Write a new program invert.cpp that inverts all colors, so white shades become black, and black become white:
// Since black = 0, and white = 255, you should do the following transformation for each pixel color:

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX_H = 512;
const int MAX_W = 512;


void readImage(int image[MAX_H][MAX_W], int &height, int &width) {
	char c;
	int x;
	ifstream instr;
	instr.open("inImage.pgm");

	
	instr >> c;
	assert(c == 'P');
	instr >> c;
	assert(c == '2');

	// skip the comments (if any)
	while ((instr>>ws).peek() == '#') {
		instr.ignore(4096, '\n');
	}

	instr >> width;
	instr >> height;

	assert(width <= MAX_W);
	assert(height <= MAX_H);
	int max;
	instr >> max;
	assert(max == 255);

	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
			instr >> image[row][col];
	instr.close();
	return;
}



void writeImage(int image[MAX_H][MAX_W], int height, int width) {
	ofstream ostr;
	ostr.open("outImage.pgm");
	if (ostr.fail()) {
		cout << "Unable to write file\n";
		exit(1);
	};

	ostr << "P2" << endl;
	ostr << width << ' ';
	ostr << height << endl;
	ostr << 255 << endl;

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			assert(image[row][col] < 256);
			assert(image[row][col] >= 0);
			ostr << image[row][col] << ' ';
			ostr << endl;
		}
	}
	ostr.close();
	return;
}

int main() {

    int img[MAX_H][MAX_W];
    int H, W;

    readImage(img, H, W); 
    int out[MAX_H][MAX_W];

   
    int temp[MAX_H+2][MAX_W+2];
    memset(temp,0,sizeof(temp));    
    for(int row = 0; row < H; row++) {
        for(int col = 0; col < W; col++) {
                temp[row+1][col+1] = img[row][col]; 
        }
    }

    int a,b,c,d,e,f,g,h,i;
    int func;

    for(int row =1; row<H+1; row++) {
        for(int col=1; col<W+1; col++) {
            a = temp[row-1][col-1];
            b = temp[row-1][col];
            c = temp[row-1][col+1];

            g = temp[row+1][col-1];
            h = temp[row+1][col];
            i = temp[row+1][col+1];

            func = (g+2*h+i)-(a+2*b+c);

            if(func<0) {
                func=0;
            } 

            if(func>255) {
                func=255;
            }


            out[row-1][col-1] = func;
        }
    }

    writeImage(out, H, W);
}