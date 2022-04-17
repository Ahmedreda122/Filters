#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <math.h>
#include <regex>
#include <string>
#include "bmplib.cpp"

using namespace std;

unsigned char image[SIZE][SIZE][RGB];
unsigned char new_image[SIZE][SIZE][RGB];
void loadImage(unsigned char image[][SIZE][RGB]);
void saveImage(unsigned char saved_image[][SIZE][RGB]);



int main()
{
    string filter; 
	cout << "Please, Choose a filter to perform it:\n1- Black & White Filter\n2- Invert Filter\n3- Merge two photos.\n4- Flip Image\n5- Darken and lighten\n6- Rotate.\n7- Detect Image Edges\n8- Enlarge Image\n9- Shrink the image\na- Mirror 1/2 Image\nb- Shuffle Image\nc- Blur Image.\n0- Exit\n>>";

	getline(cin,filter);
	cin.clear();
	cin.ignore();


}

void loadImage(unsigned char image[][SIZE][RGB])
{
    char imageFileName[100];

    // Get colored image file name
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}

void saveImage(unsigned char saved_image[][SIZE][RGB])
{
    char imageFileName[100];

    // Get colored image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, saved_image);
}