#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <math.h>
#include <regex>
#include "bmplib.cpp"

using namespace std;

unsigned char image[SIZE][SIZE][RGB];
unsigned char new_image[SIZE][SIZE][RGB];
unsigned char secondImage[SIZE][SIZE][RGB];

// Defining the functions in the program so main function can recognize them.
void load_image(unsigned char image[][SIZE][RGB]);
void save_image(unsigned char saved_image[][SIZE][RGB]);
void blur();
void darkenlighten(string choice);
int& parse_valid_input(string str, int& dimension);
void shrink(int dimension);
void merge();
void enlarge_image1();
void enlarge_image2();
void enlarge_image3();
void enlarge_image4();
void enlarge_image();
void shuffle_image();
void rotate_image();
void invert_image();
void black_white_image();
void flip_vertically();
void flip_horizontally();
void flip_image_filter();
void edge_detection();
void mirror_upper_half();
void mirror_down_half();
void mirror_left_half();
void mirror_right_half();
void mirror_image();

int main()
{
  	string filter;

	int dimension = 0;
    string dimensionStr;

	cout << "Please, Choose a filter to perform it:\n1- Black & White Filter\n2- Invert Filter\n3- Merge two photos.\n4- Flip Image\n5- Darken and lighten\n6- Rotate.\n7- Detect Image Edges\n8- Enlarge Image\n9- Shrink the image\na- Mirror 1/2 Image\nb- Shuffle Image\nc- Blur Image.\n0- Exit\n>>";
	// Getting the input from the user
	getline(cin, filter);
	// Removing the spaces from the input string to the end of it, then returning a pointer to the beginning of the removed spaces then Erasing the content from if_remove returning pointer to the end of the string
	filter.erase(remove_if(filter.begin(), filter.end(), ::isspace), filter.end());
	cin.ignore(0);

	if (filter == "c" || filter == "C")
    {
        cout << "Enter the source image file name: ";
        load_image(image);
        blur();
        save_image(image);
        return 0;
	}
	else if (filter == "1")
    {
        cout << "Enter the source image file name: ";
        load_image(image);
        black_white_image();
        save_image(image);
        return 0;
    }
	else if (filter == "2")
    {
        cout << "Enter the source image file name: ";
        load_image(image);
        invert_image();
        save_image(new_image);
        return 0;
    }
	else if (filter == "3")
    {
        cout << "Enter the source image file name: ";
        load_image(image);
        cout << "Enter the source second image file name: ";
        load_image(secondImage);
        merge();
        save_image(image);
	}
	else if (filter == "4")
    {
        cout << "Enter the source image file name: ";
        load_image(image);
        flip_image_filter();
        save_image(new_image);
        return 0;
    }
	else if (filter == "5")
    {
        string answer;
        cout << "Enter the source image file name: ";
        load_image(image);
        cout << "(D)arken or (L)ighten the image: ";
        getline(cin, answer);
		cin.ignore(0);
		// Transforming the whole string to lowercase to accept any form of the char D and l.
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        if (answer == "d" || answer == "l")
        {
            darkenlighten(answer);
            save_image(image);
        }
        else
        {
            cout << "Sorry, unexpected input.";
            return 1;
        }
        return 0;
	}
	else if (filter == "6")
    {
        cout << "Enter the source image file name: ";
        load_image(image);
        rotate_image();
        save_image(new_image);
        return 0;
    }
    else if (filter == "7")
    {
        cout << "Enter the source image file name: ";
        load_image(image);
        edge_detection();
        save_image(new_image);
        return 0;
    }
	else if (filter == "8")
    {
        cout << "Enter the source image file name: ";
        load_image(image);
        enlarge_image();
        save_image(new_image);
        return 0;
    }
	else if (filter == "9")
    {
        cout << "Enter the source image file name: ";
        load_image(image);
        while (dimension == 0)
        {
            cout << "Shrink to (1/2), (1/3) or (1/4)?\nPlease, Enter the input on form a/b: ";
            getline(cin, dimensionStr);
            parse_valid_input(dimensionStr, dimension);
            cin.ignore(0);
        }
        shrink(dimension);
        save_image(image);
        return 0;
    }
    else if (filter == "a" || filter == "A")
    {
        cout << "Enter the source image file name: ";
        load_image(image);
        mirror_image();
        save_image(image);
        return 0;
    }
	else if (filter == "b" || filter == "B")
    {
        cout << "Enter the source image file name: ";
        load_image(image);
        shuffle_image();
        save_image(new_image);
        return 0;
    }
	else if (filter == "0")
    {
        return 0;
    }
	else
	{
		cout << "Wrong input, try again.";
		return 1;
	}

}
//_____________________________________________________
void load_image(unsigned char image[][SIZE][RGB])
{
	char imageFileName[100];

	// Get colored image file name
	cin >> imageFileName;
	cin.ignore();

	// Add to it .bmp extension and load image
	strcat(imageFileName, ".bmp");
	// Check if the bitmap image exist or not, If not Ask for another image
    if (readRGBBMP(imageFileName, image) == 1)
    {
        cout << "\nPlease, Try again: ";
        load_image(image);
    }
}
//_____________________________________________________
void save_image(unsigned char saved_image[][SIZE][RGB])
{
    char imageFileName[100];

    // Get colored image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, saved_image);
}
//_________________________________________
void shrink(int dimension)
{
	// Creating an RGB image for to store horizontally shrinked original image version
    unsigned char neww_image[SIZE][SIZE][RGB];
	// cursor for looping after every (dimension value) pixels each time
    int cursor = 0;

	// Variables for storing averages of colours
	double AVG_red = 0;
	double AVG_green = 0;
	double AVG_blue = 0;

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < (SIZE / dimension); ++j)
        {
			// Looping after every row to get every 2 pixels (for example (it can be 2 or 3 or 4 based on dimension value)) in it then shrink it into one pixel by taking the average of them horizontally
            for (int c = cursor; c < (cursor + dimension); ++c)
            {
				AVG_red += image[i][c][0];
				AVG_green += image[i][c][1];
				AVG_blue +=  image[i][c][2];
            }
			// Storing shrinked pixels in neww_image
            neww_image[i][j][0] = (AVG_red / dimension);
			neww_image[i][j][1] = (AVG_green / dimension);
			neww_image[i][j][2] = (AVG_blue / dimension);
			// Resetting the average to its primary value
			AVG_red = 0;
			AVG_green = 0;
			AVG_blue = 0;
			// Updating cursor to move to next 2 (for example) pixels in the row
            cursor += dimension;
        }
		// Resetting cursor to shrink next row
        cursor = 0;
    }

    for (int i = 0; i < SIZE / dimension; ++i)
    {
        for (int j = 0; j < SIZE / dimension; ++j)
        {
			// Looping after every column in shrinked neww_image to get every 2 pixels (it can be 2 or 3 or 4 based on dimension value) in it then shrink it into one pixel by taking the average of them vertically
            for (int c = cursor; c < (cursor + dimension); ++c)
            {
                AVG_red += neww_image[c][j][0];
				AVG_green += neww_image[c][j][1];
				AVG_blue +=  neww_image[c][j][2];
            }
			// Storing shrinked pixels in new_image
            new_image[i][j][0] = (AVG_red / dimension);
			new_image[i][j][1] = (AVG_green / dimension);
			new_image[i][j][2] = (AVG_blue / dimension);
			// Resetting the average to its primary value
			AVG_red = 0;
			AVG_green = 0;
			AVG_blue = 0;
        }
		// Updating cursor to move to next 2 (for example) pixels in the columns
        cursor += dimension;
    }

	// Updating the original image to the shrinked one (new_image) and every pixel not in shrinked photo will be white pixel
    for (int x = 0; x < SIZE; x++)
    {
        for (int y = 0; y < SIZE; y++)
        {
            if (x < (SIZE / dimension) && y < (SIZE / dimension))
            {
                image[x][y][0] = new_image[x][y][0];
				image[x][y][1] = new_image[x][y][1];
				image[x][y][2] = new_image[x][y][2];
            }
            else
            {
                image[x][y][0] = 255;
				image[x][y][1] = 255;
				image[x][y][2] = 255;
            }

        }
    }

}

int& parse_valid_input(string str, int& dimension)
{
    // Making a form for input rational number using regular expressions
    regex isValidInput("(1/[2-4])");
    // Returning True if the input string was like the form we just make, False otherwise
    if (regex_match(str, isValidInput))
    {
		// Getting dimension denominator
        char d[1] = {str[2]};
		// Transfer it to integar
        dimension = atoi(d);
        return dimension;
    }
    else
    {
		// Return primary value of dimension which is ZERO
        return dimension;
    }

}
//_________________________________________
void darkenlighten(string choice)
{
	// If user choose to darken the image
    if (choice == "d")
    {
		// Looping after pixels
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
				// Looping after RGB colours
				for (int r = 0; r < 3; ++r)
				{
					// Decreasing light level by 50%
					image[i][j][r] -= image[i][j][r] * (0.5);
				}
            }
        }
    }
	// If user choose to lighten the image
    else if (choice == "l")
    {
		// Defining black_level that is equal to 255 - light_level(pixel value)
        float black_level = 0;
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
				for (int r = 0; r < 3; ++r)
				{
					/* Getting black level of each colour by applying the formula "255 - light_level of each colour(pixel value) = black_level"
					'Cause if white pixel value = 255 so if we minus 255 by white pixel value(which is 255) it give zero and this is what we want */
					black_level = 255 - image[i][j][r];
					// Dereasing black_level of each colour by 50% by increasing light_level(pixel_value) by 50% of black_level
                	image[i][j][r] += black_level / 2.0;
				}
            }
        }
    }
}
//_________________________________________
void merge()
{
	// Looping after every pixel then update it with average of the corresponding pixels in the two images to merge them
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
			for (int y = 0; y < 3; ++y)
			{
				image[i][j][y] = (image[i][j][y] + secondImage[i][j][y]) / 2.0;
			}
        }
    }
}
//_________________________________________
// Blur image
void blur()
{
	// The divisor
	float div;
	// The Average of colours
	int AVG_red;
	int AVG_green;
	int AVG_blue;

    // Loop for enhance the blur
    for (int i = 0; i < ; ++i)
    {
        // Looping over the image pixels
        for (int x = 0; x < SIZE; x++)
        {
            for (int y = 0; y < SIZE; y++)
            {
                // Resetting averages of colours to its primary value
                AVG_red = 0;
                AVG_green = 0;
                AVG_blue = 0;
                // Bluring the top left corner
                if ((x == 0) && (y == 0))
                {
                    div = 4.0;
                    // Getting the 3 pixels that surround the first pixel + the first pixel itself then calculating the average colours of them to store it in the blurred first pixel
                    for (int n = x; n <= x + 1; n++)
                    {
                        for (int m = y; m <= y + 1; m++)
                        {
                            AVG_red = AVG_red + image[n][m][0];
                            AVG_green = AVG_green + image[n][m][1];
                            AVG_blue = AVG_blue + image[n][m][2];
                        }
                    }
                }
                // Bluring top pixel's edge
                if ((x == 0) && (y > 0) && (y < (SIZE - 1)))
                {
                    div = 6.0;
                    // Looping after the top edge's pixels and get each pixel's surrounding pixels + the pixel itself then calculating  the average colours of them to store it in the new_image corresponding pixel(UPDATED pixel)
                    for (int n = x; n <= x + 1; n++)
                    {
                        for (int m = y - 1; m <= y + 1; m++)
                        {
                            AVG_red = AVG_red + image[n][m][0];
                            AVG_green = AVG_green + image[n][m][1];
                            AVG_blue = AVG_blue + image[n][m][2];
                        }
                    }
                }
                // Bluring the top right corner
                if ((x == 0) && (y == SIZE - 1))
                {
                    div = 4.0;
                    // Getting the 3 pixels that surround the top right corner pixel + the pixel itself then calculating  the average colours of them to store it in the new_image corresponding pixel
                    for (int n = x; n <= x + 1; n++)
                    {
                        for (int m = y - 1; m <= y; m++)
                        {
                            AVG_red = AVG_red + image[n][m][0];
                            AVG_green = AVG_green + image[n][m][1];
                            AVG_blue = AVG_blue + image[n][m][2];
                        }
                    }
                }
                // Bluring left edges
                if ((x > 0) && (y == 0) && (x < SIZE - 1))
                {
                    div = 6.0;
                    // Looping after the left edge's pixels except corners' pixels and get each pixel's surrounding pixels + the pixel itself then calculating  the average colours of them to store it in the new_image corresponding pixel(UPDATED pixel)
                    for (int n = x - 1; n <= x + 1; n++)
                    {
                        for (int m = y; m <= y + 1; m++)
                        {
                            AVG_red = AVG_red + image[n][m][0];
                            AVG_green = AVG_green + image[n][m][1];
                            AVG_blue = AVG_blue + image[n][m][2];
                        }
                    }
                }
                // Bluring right edges
                if ((x > 0) && (y == SIZE - 1) && (x < SIZE - 1))
                {
                    div = 6.0;
                    // Looping after the right edge's pixels except corners' pixels and get each pixel's surrounding pixels + the pixel itself then calculating  the average colours of them to store it in the new_image corresponding pixel(UPDATED pixel)
                    for (int n = x - 1; n <= x + 1; n++)
                    {
                        for (int m = y - 1; m <= y ; m++)
                        {
                            AVG_red = AVG_red + image[n][m][0];
                            AVG_green = AVG_green + image[n][m][1];
                            AVG_blue = AVG_blue + image[n][m][2];
                        }
                    }
                }
                // Bluring bottom left corner
                if ((x == (SIZE - 1)) && (y == 0))
                {
                    div = 4.0;
                    // Getting the 3 pixels that surround the bottom left corner pixel + the pixel itself then calculating  the average colours of them to store it in the new_image corresponding pixel
                    for (int n = x - 1; n <= x; n++)
                    {
                        for (int m = y; m <= y + 1; m++)
                        {
                            AVG_red = AVG_red + image[n][m][0];
                            AVG_green = AVG_green + image[n][m][1];
                            AVG_blue = AVG_blue + image[n][m][2];
                        }
                    }
                }
                // Bluring bottom right corner
                if ((x == (SIZE - 1)) && (y == (SIZE - 1)))
                {
                    div = 4.0;
                    // Getting the 3 pixels that surround the bottom right corner pixel + the pixel itself then calculating  the average colours of them to store it in the new_image corresponding pixel
                    for (int n = x - 1; n <= x; n++)
                    {
                        for (int m = y - 1; m <= y; m++)
                        {
                            AVG_red = AVG_red + image[n][m][0];
                            AVG_green = AVG_green + image[n][m][1];
                            AVG_blue = AVG_blue + image[n][m][2];
                        }
                    }
                }
                // Bluring middle pixels
                if (y > 0 && y < (SIZE - 1) && x > 0 && x < (SIZE - 1))
                {
                    div = 9.0;
                    // Looping after the pixels that are in the middle or (NOT in edges or corners pixels) then getting each pixel's surrounding pixels + the pixel itself then calculating  the average colours of them to store it in the new_image corresponding pixel(UPDATED pixel)
                    for (int n = x - 1; n <= x + 1; n++)
                    {
                        for (int  m = y - 1; m <= y + 1; m++)
                        {
                            AVG_red = AVG_red + image[n][m][0];
                            AVG_green = AVG_green + image[n][m][1];
                            AVG_blue = AVG_blue + image[n][m][2];
                        }
                    }
                }
                // Bluring bottom edges
                if (y > 0 && y < (SIZE - 1) && x == (SIZE - 1))
                {
                    div = 6.0;
                    // Looping after the bottom edge 's pixels and get each pixel's surrounding pixels + the pixel itself then calculating  the average colours of them to store it in the new_image corresponding pixel(UPDATED pixel)
                    for (int n = x - 1; n <= x; n++)
                    {
                        for (int  m = y - 1; m <= y + 1; m++)
                        {
                            AVG_red = AVG_red + image[n][m][0];
                            AVG_green = AVG_green + image[n][m][1];
                            AVG_blue = AVG_blue + image[n][m][2];
                        }
                    }
                }
                // Advantage RGB colours
                AVG_red = round(AVG_red / div);
                AVG_green = round(AVG_green / div);
                AVG_blue = round(AVG_blue / div);
                // Storing the average value in new_image variable to blur the pixel.
                new_image[x][y][0] = AVG_red;
                new_image[x][y][1] = AVG_green;
                new_image[x][y][2] = AVG_blue;
            }
        }
        // Converting the current pixels to blured ones
        for (int x = 0; x < SIZE; x++)
        {
            for (int y = 0; y < SIZE; y++)
            {
                image[x][y][0] = new_image[x][y][0];
                image[x][y][1] = new_image[x][y][1];
                image[x][y][2] = new_image[x][y][2];

            }
        }
    }
}
//____________________________________________________________________
// Enlarge first Part
void  enlarge_image1() {
    for (int i = 0; i <= 128; ++i) {
        for (int j = 0; j <= 128; ++j) {
			for (int k=0 ; k < RGB;++k){
			new_image[i * 2][j * 2][k] = image[i][j][k];
            new_image[(i * 2) + 1][j * 2][k] = image[i][j][k];
            new_image[i * 2][(j * 2) + 1][k] = image[i][j][k];
            new_image[(i * 2) + 1][(j * 2) + 1][k] = image[i][j][k];
			}
        }
    }
}

// Enlarge second Part
void  enlarge_image2() {
    for (int i = 0; i <= 128; ++i) {
        for (int j = 128; j <= 255; ++j) {
			for (int k=0 ; k < RGB;++k){
				new_image[i * 2][((j - 128) * 2)][k] = image[i][j][k];
				new_image[i * 2][((j - 128) * 2) + 1][k] = image[i][j][k];
				new_image[(i * 2) + 1][((j - 128) * 2)][k] = image[i][j][k];
				new_image[(i * 2) + 1][(((j - 128) * 2)) + 1][k] = image[i][j][k];
			}
        }
    }
}

// Enlarge third Part
void  enlarge_image3() {
    for (int i = 128; i <= 255; ++i) {
        for (int j = 0; j <= 128; ++j) {
			for (int k=0 ; k < RGB;++k){
				new_image[((i - 128) * 2)][j * 2][k] = image[i][j][k];
				new_image[((i - 128) * 2) + 1][j * 2][k] = image[i][j][k];
				new_image[((i - 128) * 2)][(j * 2) + 1][k] = image[i][j][k];
				new_image[(((i - 128) * 2)) + 1][(j * 2) + 1][k] = image[i][j][k];
			}
        }
    }
}

// Enlarge forth Part
void  enlarge_image4() {
    for (int i = 128; i <= 255; ++i) {
        for (int j = 128; j <= 255; ++j) {
			for (int k=0 ; k < RGB;++k){
				new_image[((i - 128) * 2)][((j - 128) * 2)][k] = image[i][j][k];
				new_image[((i - 128) * 2)][((j - 128) * 2) + 1][k] = image[i][j][k];
				new_image[((i - 128) * 2) + 1][((j - 128) * 2)][k] = image[i][j][k];
				new_image[((i - 128) * 2) + 1][((j - 128) * 2) + 1][k] = image[i][j][k];
			}
        }
    }
}

// Choice any part user need Enlarge
void enlarge_image() {
    int option = 0;
    cout << "Ahlan ya Am El-User...Which Part U Need zoom it?!...\n";
    cout << " 1 | 2 \n 3 | 4 \n";
    cin >> option;

    if (option == 1) {
        enlarge_image1();
    }
    else if (option == 2) {
        enlarge_image2();
    }
    else if (option == 3) {
        enlarge_image3();
    }
    else if (option == 4) {
        enlarge_image4();
    }
    else {
        cout << "Wrong choice!.." << " Try Again.." << endl;
    }
}
//____________________________________________________________________
// sort the quarters in new file
void shuffle_image() {

    int a = 0, b = 0, c = 0, d = 0, x = 0, y = 0;
    cout << "Ahlan ya Am El-User...\n";
    cout << "How u sort the quarters?...\n";
    cout << " 1 | 2 \n 3 | 4 \n";
    cin >> a >> b >> c >> d;

    //copy first quarter in new possition
    for (int i = 0; i <= 128; ++i) {
        for (int j = 0; j <= 128; ++j) {
			for (int k=0 ; k < RGB;++k){
				if (a == 1) {
					x = i;
					y = j;
				}
				else if (b == 1) {
					x = i;
					y = j + 128;
				}
				else if (c == 1) {
					x = i + 128;
					y = j;
				}
				else if (d == 1) {
					x = i + 128;
					y = j + 128;
				}
				new_image[x][y][k] = image[i][j][k] ;
			}
        }
    }
    //copy secound quarter in new possition
    for (int i = 0; i <= 128; ++i) {
        for (int j = 128; j <= 255; ++j) {
			for (int k=0 ; k < RGB;++k){
				if (a == 2) {
					x = i;
					y = j - 128;
				}
				else if (b == 2) {
					x = i;
					y = j;
				}
				else if (c == 2) {
					x = i + 128;
					y = j - 128;
				}
				else if (d == 2) {
					x = i + 128;
					y = j;
				}
				new_image[x][y][k] = image[i][j][k] ;
			}
        }
    }
    //copy third quarter in new possition
    for (int i = 128; i <= 255; ++i) {
        for (int j = 0; j <= 128; ++j) {
			for (int k=0 ; k < RGB;++k){

				if (a == 3) {
					x = i - 128;
					y = j;
				}
				else if (b == 3) {
					x = i - 128;
					y = j + 128;
				}
				else if (c == 3) {
					x = i;
					y = j;
				}
				else if (d == 3) {
					x = i;
					y = j + 128;
				}
				new_image[x][y][k] = image[i][j][k] ;
			}
        }
    }
    //copy forth quarter in new possition
    for (int i = 128; i <= 255; ++i) {
        for (int j = 128; j <= 255; ++j) {
			for (int k=0 ; k < RGB;++k){
                if (a == 4) {
                    x = i - 128;
                    y = j - 128;
                }
                else if (b == 4) {
                    x = i - 128;
                    y = j;
                }
                else if (c == 4) {
                    x = i;
                    y = j - 128;
                }
                else if (d == 4) {
                    x = i;
                    y = j;
                }
				new_image[x][y][k] = image[i][j][k] ;
			}
        }
    }
}
//____________________________________________________________________
// to rotate image (90 / 180 / 270) deg
void rotate_image()
{
    while (true)
	{
		string degree;
		cout << "Ahlan ya Am El-User...\n";
		cout << "Rotate image:(1 | 2 | 3) \n";
		cout << " 1- 90 deg Right \n 2- 90 deg Left \n 3- 180 deg \n>>> ";

		getline(cin, degree);
		degree.erase(remove_if(degree.begin(), degree.end(), ::isspace), degree.end());
		cin.ignore(0);

		// rotate image 90 deg Right
		if (degree == "1")
		{
			for (int i = 0; i < SIZE; ++i)
			{
				for (int j = 0; j < SIZE; ++j)
				{
					for (int k=0 ; k < RGB;++k){
						new_image[i][j][k] = image[255 - j][i][k];
					}
				}
			}
			break;
		}
		// rotate image 90 deg Left
		else if (degree == "2")
		{
			for (int i = 0; i < SIZE; ++i)
			{
				for (int j = 0; j < SIZE; ++j)
				{
					for (int k=0 ; k < RGB;++k){
						new_image[i][j][k] = image[j][255 - i][k];
					}
				}
			}
			break;
		}
		// rotate image 180 deg
		else if (degree == "3")
		{
			for (int i = 0; i < SIZE; ++i)
			{
				for (int j = 0; j < SIZE; ++j)
				{
					for (int k=0 ; k < RGB;++k){
						new_image[i][j][k] = image[255 - i][255 - j][k];
					}
				}
			}
			break;
		}
	}
}
//_________________________________________
// invert color
void invert_image()
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
			for (int k=0 ; k < RGB;++k){
          		new_image[i][j][k] = 255 - image[i][j][k];
			}
        }
    }
}

//_________________________________________
void black_white_image(){
    //converting image into gray
    int pixel_value = 0;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++){
                pixel_value += image[i][j][k]; // calculate the avg of RGB
            }

            for(int Z = 0; Z < RGB; Z++){
                image[i][j][Z] = pixel_value / 3;
            }
            pixel_value = 0;

        }
    }
    //converting gray image into black and white
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++){
            }if (image[i][j][0] > 127){
                for(int z = 0; z < RGB; z++){
                    image[i][j][z] = 255;
                }


                }else{
                    for(int z = 0; z < RGB; z++){
                        image[i][j][z] = 0;
                    }

                }
        }
    }
}
//_________________________________________
void flip_vertically(){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++){
                new_image[i][j][k] = image[SIZE - i - 1][j][k];
            }
        }
    }
}
//_________________________________________
void flip_horizontally(){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++){
                new_image[i][j][k] = image[i][SIZE - j - 1][k];
            }
        }
    }
}
//_________________________________________
void flip_image_filter(){
    string v_or_h;
    cout << "\nDo you want to flip vertically or horizontally?\n";
    cin >> v_or_h;
    if(v_or_h == "vertically" || v_or_h == "v" || v_or_h == "V") {
        flip_vertically();
    }
    else if(v_or_h == "horizontally" || v_or_h == "h" || v_or_h == "H") {
        flip_horizontally();
    }
}
//_________________________________________
void edge_detection(){
    // convert picture into black and white too ease detection
    black_white_image();
    int x, y;
    for(int i = 0; i < SIZE; i++){
        for(int j= 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++){
                if (i - 1 > 0 && i + 1  < 256 && j - 1 > 0 && j + 1 < 256 ){
                    // calculate changes in x axis
                    x = image[i - 1][j][k] + image[i + 1][j][k] - 2*image[i][j][k];
                    // calculate changes in y axis
                    y = image[i][j - 1][k] + image[i][j + 1][k] - 2*image[i][j][k];
                    // collect changes in both axises
                    // subtract from 255 to convert edges color from white to black
                    new_image[i][j][k] = 255 - (x + y);
                }
                else
                {
                    // make the remaining pixels white
                    new_image[i][j][k] = 255;
                }
            }
        }
    }
}
//_________________________________________
// mirror down side 1/2
void mirror_down_half(){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++){
                image[i][j][k] = image[SIZE - i][j][k];
            }
        }
    }
}
//_________________________________________
// mirror right 1/2
void mirror_right_half(){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++){
                image[i][j][k] = image[i][SIZE - j][k];
            }
        }
    }

}
//_________________________________________
// mirror upper 1/2
void mirror_upper_half(){
    for(int i = SIZE; i >= 0; i--){
        for(int j = 0; j < SIZE; j++){
            for(int k = 0; k < RGB; k++){
                image[i][j][k] = image[SIZE - i][j][k];
            }
        }
    }

}
//_________________________________________
// mirror left 1/2
void mirror_left_half(){
    for(int i = 0; i < SIZE; i++){
        for(int j = SIZE; j >= 0; j--){
            for(int k = 0; k < RGB; k++){
                image[i][j][k] = image[i][SIZE - j][k];
            }
        }
    }
}
//_________________________________________
// make the user choose any half he wants
void mirror_image(){
    string wanted_half;
    cout << "\nmirror (l)eft, (r)ight, (u)pper, (d)own ?\n ";
    cin >> wanted_half;
    if(wanted_half == "left" || wanted_half == "l" || wanted_half == "L"){
        mirror_left_half();
    }
    else if(wanted_half == "right" || wanted_half == "r" || wanted_half == "R"){
        mirror_right_half();
    }
    else if(wanted_half == "upper" || wanted_half == "u" || wanted_half == "U"){
        mirror_upper_half();
    }
    else if(wanted_half == "down" || wanted_half == "d" || wanted_half == "D"){
        mirror_down_half();
    }
}
