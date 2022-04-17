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
void blur();


int main()
{
<<<<<<< HEAD
  	string filter;
=======
	string filter;
>>>>>>> origin
	cout << "Please, Choose a filter to perform it:\n1- Black & White Filter\n2- Invert Filter\n3- Merge two photos.\n4- Flip Image\n5- Darken and lighten\n6- Rotate.\n7- Detect Image Edges\n8- Enlarge Image\n9- Shrink the image\na- Mirror 1/2 Image\nb- Shuffle Image\nc- Blur Image.\n0- Exit\n>>";

	getline(cin, filter);
	cin.ignore(0);

	if (filter == "c")
<<<<<<< HEAD
    {
        cout << "Enter the source image file name: ";
        loadImage(image);
        blur();
        saveImage(new_image);
        return 0;
	}
=======
	{
		cout << "Enter the source image file name: ";
		loadImage(image);
		blur();
		saveImage(new_image);
		return 0;
	}
	else
	{
		cout << "Wrong input, try again.";
		return 1;
	}
>>>>>>> origin

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

// Blur image
void blur()
{
	// The divisor
	float div;
	// The Average of colours
	int Avred;
	int Avgreen;
	int Avblue;

	for (int x = 0; x < SIZE; x++)
	{
		for (int y = 0; y < SIZE; y++)
		{
			Avred = 0;
			Avgreen = 0;
			Avblue = 0;
			// Bluring the left corner
			if ((x == 0) && (y == 0))
			{
				div = 4.0;
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
			// Bluring the right corner
			if ((x == 0) && (y == SIZE - 1))
			{
				div = 4.0;
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
			// Bluring another left corner
			if ((x == (SIZE - 1)) && (y == 0))
			{
				div = 4.0;
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
			// Bluring another right corner
			if ((x == (SIZE - 1)) && (y == (SIZE - 1)))
			{
				div = 4.0;
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
			//storing the average value in new_image variable
			new_image[x][y][0] = Avred;
			new_image[x][y][1] = Avgreen;
			new_image[x][y][2] = Avblue;
		}

	}
<<<<<<< HEAD
}
=======
}
>>>>>>> origin
