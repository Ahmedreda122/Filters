#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <math.h>
#include <regex>
#include <string>
#include "bmplib.cpp"

using namespace std;

unsigned char image[SIZE][SIZE][RGB];
unsigned char new_image[SIZE][SIZE][RGB];
void loadImage(unsigned char image[][SIZE][RGB]);
void saveImage(unsigned char saved_image[][SIZE][RGB]);
void blur();
void darkenlighten(string choice);


int main()
{
  	string filter;
	cout << "Please, Choose a filter to perform it:\n1- Black & White Filter\n2- Invert Filter\n3- Merge two photos.\n4- Flip Image\n5- Darken and lighten\n6- Rotate.\n7- Detect Image Edges\n8- Enlarge Image\n9- Shrink the image\na- Mirror 1/2 Image\nb- Shuffle Image\nc- Blur Image.\n0- Exit\n>>";

	getline(cin, filter);
	cin.ignore(0);

	if (filter == "c")
    {
        cout << "Enter the source image file name: ";
        loadImage(image);
        blur();
        saveImage(new_image);
        return 0;
	}
	else if (filter == "5")
    {
        string answer;
        cout << "Enter the source image file name: ";
        loadImage(image);
        cout << "(D)arken or (L)ighten the image: ";
        getline(cin, answer);
		cin.ignore(0);
		// Transforming the whole string to lowercase to accept any form of the char D and l.
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        if (answer == "d" || answer == "l")
        {
            darkenlighten(answer);
            saveImage(image);
        }
        else
        {
            cout << "Sorry, unexpected input.";
            return 1;
        }
        return 0;
	}
	else
	{
		cout << "Wrong input, try again.";
		return 1;
	}

}

void loadImage(unsigned char image[][SIZE][RGB])
{
	char imageFileName[100];

	// Get colored image file name
	cin >> imageFileName;
	cin.ignore();

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

void darkenlighten(string choice)
{
    if (choice == "d")
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
				for (int r = 0; r < 3; ++r)
				{
					image[i][j][r] -= image[i][j][r] * (0.5);
				}
            }
        }
    }
    else if (choice == "l")
    {
        float light = 0;
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
				for (int r = 0; r < 3; ++r)
				{
					light = abs(image[i][j][r] - 255);
                	image[i][j][r] += light / 2.0;
				}
            }
        }
    }
}

// Blur image
void blur()
{
	// The divisor
	float div;
	// The Average of colours
	int Avred;
	int Avgreen;
	int Avblue;

	// Looping over the image pixels
	for (int x = 0; x < SIZE; x++)
	{
		for (int y = 0; y < SIZE; y++)
		{
			// Variables for storing averages of colours
			Avred = 0;
			Avgreen = 0;
			Avblue = 0;
			// Bluring the top left corner
			if ((x == 0) && (y == 0))
			{
				div = 4.0;
				// Getting the 3 pixels that surround the first pixel + the first pixel itself then caculating the average colours of them to store it in the blurred first pixel 
				for (int n = x; n <= x + 1; n++)
				{
					for (int m = y; m <= y + 1; m++)
					{
						Avred = Avred + image[n][m][0];
						Avgreen = Avgreen + image[n][m][1];
						Avblue = Avblue + image[n][m][2];
					}
				}
			}
			// Bluring top pixel's edge
			if ((x == 0) && (y > 0) && (y < (SIZE - 1)))
			{
				div = 6.0;
				// Looping after the top edge's pixels and get each pixel's surrounding pixels + the pixel itself then caculating the average colours of them to store it in the new_image corresponding pixel(UPDATED pixel) 
				for (int n = x; n <= x + 1; n++)
				{
					for (int m = y - 1; m <= y + 1; m++)
					{
						Avred = Avred + image[n][m][0];
						Avgreen = Avgreen + image[n][m][1];
						Avblue = Avblue + image[n][m][2];
					}
				}

			}
			// Bluring the top right corner
			if ((x == 0) && (y == SIZE - 1))
			{
				div = 4.0;
				// Getting the 3 pixels that surround the top right corner pixel + the pixel itself then caculating the average colours of them to store it in the new_image corresponding pixel 
				for (int n = x; n <= x + 1; n++)
				{
					for (int m = y - 1; m <= y; m++)
					{
						Avred = Avred + image[n][m][0];
						Avgreen = Avgreen + image[n][m][1];
						Avblue = Avblue + image[n][m][2];
					}
				}
			}
			// Bluring left edges
			if ((x > 0) && (y == 0) && (x < SIZE - 1))
			{
				div = 6.0;
				// Looping after the left edge's pixels except corners' pixels and get each pixel's surrounding pixels + the pixel itself then caculating the average colours of them to store it in the new_image corresponding pixel(UPDATED pixel) 
				for (int n = x - 1; n <= x + 1; n++)
				{
					for (int m = y; m <= y + 1; m++)
					{
						Avred = Avred + image[n][m][0];
						Avgreen = Avgreen + image[n][m][1];
						Avblue = Avblue + image[n][m][2];
					}
				}
			}
			// Bluring right edges
			if ((x > 0) && (y == SIZE - 1) && (x < SIZE - 1))
			{
				div = 6.0;
				// Looping after the right edge's pixels except corners' pixels and get each pixel's surrounding pixels + the pixel itself then caculating the average colours of them to store it in the new_image corresponding pixel(UPDATED pixel) 
				for (int n = x - 1; n <= x + 1; n++)
				{
					for (int m = y - 1; m <= y ; m++)
					{
						Avred = Avred + image[n][m][0];
						Avgreen = Avgreen + image[n][m][1];
						Avblue = Avblue + image[n][m][2];
					}
				}
			}
			// Bluring bottom left corner
			if ((x == (SIZE - 1)) && (y == 0))
			{
				div = 4.0;
				// Getting the 3 pixels that surround the bottom left corner pixel + the pixel itself then caculating the average colours of them to store it in the new_image corresponding pixel 
				for (int n = x - 1; n <= x; n++)
				{
					for (int m = y; m <= y + 1; m++)
					{
						Avred = Avred + image[n][m][0];
						Avgreen = Avgreen + image[n][m][1];
						Avblue = Avblue + image[n][m][2];
					}
				}
			}
			// Bluring bottom right corner
			if ((x == (SIZE - 1)) && (y == (SIZE - 1)))
			{
				div = 4.0;
				// Getting the 3 pixels that surround the bottom right corner pixel + the pixel itself then caculating the average colours of them to store it in the new_image corresponding pixel 
				for (int n = x - 1; n <= x; n++)
				{
					for (int m = y - 1; m <= y; m++)
					{
						Avred = Avred + image[n][m][0];
						Avgreen = Avgreen + image[n][m][1];
						Avblue = Avblue + image[n][m][2];
					}
				}
			}
			// Bluring middle pixels
			if (y > 0 && y < (SIZE - 1) && x > 0 && x < (SIZE - 1))
			{
				div = 9.0;
				// Looping after the pixels that are in the middle or (NOT in edges or corners pixels) then getting each pixel's surrounding pixels + the pixel itself then caculating the average colours of them to store it in the new_image corresponding pixel(UPDATED pixel)
				for (int n = x - 1; n <= x + 1; n++)
				{
					for (int  m = y - 1; m <= y + 1; m++)
					{
						Avred = Avred + image[n][m][0];
						Avgreen = Avgreen + image[n][m][1];
						Avblue = Avblue + image[n][m][2];

					}
				}
			}
			// Bluring bottom edges
			if (y > 0 && y < (SIZE - 1) && x == (SIZE - 1))
			{
				div = 6.0;
				// Looping after the bottom edge 's pixels and get each pixel's surrounding pixels + the pixel itself then caculating the average colours of them to store it in the new_image corresponding pixel(UPDATED pixel) 
				for (int n = x - 1; n <= x; n++)
				{
					for (int  m = y - 1; m <= y + 1; m++)
					{
						Avred = Avred + image[n][m][0];
						Avgreen = Avgreen + image[n][m][1];
						Avblue = Avblue + image[n][m][2];

					}
				}
			}
			// Advantage RGB colours
			Avred = round(Avred / div);
			Avgreen = round(Avgreen / div);
			Avblue = round(Avblue / div);
			// Storing the average value in new_image variable to blur the pixel.
			new_image[x][y][0] = Avred;
			new_image[x][y][1] = Avgreen;
			new_image[x][y][2] = Avblue;
		}

	}
}
