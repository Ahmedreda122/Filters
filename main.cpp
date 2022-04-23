#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>
#include <regex>
#include <algorithm>
#include <string>
#include "bmplib.cpp"

using namespace std;

unsigned char image[SIZE][SIZE];
unsigned char secondImage[SIZE][SIZE];
unsigned char new_image[SIZE][SIZE];

// Defining the functions in the program so main function can recognize them.
void load_image(unsigned char image[][SIZE]);
void save_image(unsigned char saved_image[][SIZE]);
void blur();
void darkenlighten(string choice);
void merge();
void shrink(int dimension);
int& parse_valid_input(string str, int& dimension);
void enlarge_image1();
void enlarge_image2();
void enlarge_image3();
void enlarge_image4();
void enlarge_image();
void shuffle_image();
void rotate_image();
void invert_image();
void black_white_filter();
void flip_vertically_filter();
void flip_horizontally_filter();
void flip_image_filter();
void edge_detection();
void mirror_left_half();
void mirror_right_half();
void mirror_upper_half();
void mirror_down_half();
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
    if (filter == "1")
    {
        cout << "Enter the source image file name: ";
        load_image(image);
        black_white_filter();
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
        return 0;
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
    else if (filter == "c" || filter == "C")
    {
        cout << "Enter the source image file name: ";
        load_image(image);
        blur();
        save_image(image);
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
//_________________________________________
void load_image(unsigned char image[][SIZE])
{
    char imageFileName[100];
    // Get gray scale image file name
    cin >> imageFileName;
	cin.ignore();
    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    // Check if the bitmap image exist or not, If not Ask for another image
    if (readGSBMP(imageFileName, image) == 1)
    {
        cout << "\nPlease, Try again: ";
        load_image(image);
    }
}
//________________________________________________
void save_image(unsigned char saved_image[][SIZE])
{
    char imageFileName[100];
    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, saved_image);
}

void blur()
{
    // The divisor
    float div;
    // The Average of colour
    float AVG = 0;

    // Loop for enhance the blur
    for (int i = 0; i < 7; ++i)
    {
        // Looping over the image pixels
        for (int x = 0; x < SIZE; x++)
        {
            for (int y = 0; y < SIZE; y++)
            {
                // Resetting average of colour to its primary value
                AVG = 0;
                // Bluring the top left corner
                if ((x == 0) && (y == 0))
                {
                    div = 4.0;
                    // Getting the 3 pixels that surround the first pixel + the first pixel itself then caculating the average colour of them to store it in the blurred first pixel
                    for (int n = x; n <= x + 1; n++)
                    {
                        for (int m = y; m <= y + 1; m++)
                        {
                            AVG += image[n][m];
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
                            AVG += image[n][m];
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
                            AVG += image[n][m];
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
                            AVG += image[n][m];
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
                        for (int m = y - 1; m <= y; m++)
                        {
                            AVG += image[n][m];
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
                            AVG += image[n][m];
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
                            AVG += image[n][m];
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
                        for (int m = y - 1; m <= y + 1; m++)
                        {
                            AVG += image[n][m];
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
                        for (int m = y - 1; m <= y + 1; m++)
                        {
                            AVG += image[n][m];
                        }
                    }
                }
                // Advantage colour
                AVG = round(AVG / div);
                // Storing the average value in new_image variable to blur the pixel.
                new_image[x][y] = AVG;
            }
        }
        //Converting the current pixels to blured ones
        for (int x = 0; x < SIZE; ++x)
        {
            for (int y = 0; y < SIZE; ++y)
            {
                image[x][y] = new_image[x][y];
            }
        }
    }
}

void merge()
{
	// Looping after every pixel then update it with average of the corresponding pixels in the two images to merge them
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            image[i][j] = (image[i][j] + secondImage[i][j]) / 2.0;
        }
    }
}

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
				// Decreasing light level by 50%
                image[i][j] -= image[i][j] * (0.5);
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
                /* Getting black level of colour by applying the formula "255 - light_level of pixel (pixel value) = black_level"
                'Cause if white pixel value = 255 so if we minus 255 by white pixel value(which is 255) it gives zero and this is what we want */
                black_level = 255 - image[i][j];
				// Dereasing black_level of gray colour by 50% by increasing light_level(pixel_value) by 50% of black_level
                image[i][j] += black_level / 2.0;
            }
        }
    }
}

void shrink(int dimension)
{
	// Creating an grayscale image for to store horizontally shrinked original image version
    unsigned char neww_image[SIZE][SIZE];
    // Counter for looping after every (dimension value) pixels each time
    int counter = 0;
    // Variable for storing average of colour
    double AVG = 0;
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < (SIZE / dimension); ++j)
        {
			// Looping after every row to get every 2 pixels (for example (it can be 2 or 3 or 4 based on dimension value)) in it then shrink it into one pixel by taking the average of them horizontally
            for (int c = counter; c < (counter + dimension); ++c)
            {
                AVG += image[i][c];
            }
			// Storing shrinked pixels in neww_image
            neww_image[i][j] = (AVG / dimension);
			// Resetting the average to its primary value
            AVG = 0;
			// Updating counter to move to next 2 (for example) pixels in the row
            counter += dimension;
        }
        // Resetting counter to shrink next row
        counter = 0;
    }
    for (int i = 0; i < SIZE / dimension; ++i)
    {
        for (int j = 0; j < SIZE / dimension; ++j)
        {
			// Looping after every column in shrinked neww_image to get every 2 pixels (it can be 2 or 3 or 4 based on dimension value) in it then shrink it into one pixel by taking the average of them vertically
            for (int c = counter; c < (counter + dimension); ++c)
            {
                AVG += neww_image[c][j];
            }
            new_image[i][j] = (AVG / dimension);
            AVG = 0;
        }
		// Updating counter to move to next 2 (for example) pixels in the columns
        counter += dimension;
    }
	// Updating the original image to the shrinked one (new_image) and every pixel not in shrinked photo will be white pixel
    for (int x = 0; x < SIZE; x++)
    {
        for (int y = 0; y < SIZE; y++)
        {
            if (x < (SIZE / dimension) && y < (SIZE / dimension))
            {
                image[x][y] = new_image[x][y];
            }
            else
            {
                image[x][y] = 255;
            }
        }
    }
}

int& parse_valid_input(string str, int& dimension)
{
    // Making a form for input rational number using regular expressions
    regex is_valid_input("(1/[2-4])");
    //Returning True if the input string was like the form we just make, False otherwise
    if (regex_match(str, is_valid_input))
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
//__________________________________________________________________
// Enlarge first Part
void  enlarge_image1() {
    for (int i = 0; i <= 128; ++i) {
        for (int j = 0; j <= 128; ++j) {
            new_image[i * 2][j * 2] = image[i][j];
            new_image[(i * 2) + 1][j * 2] = image[i][j];
            new_image[i * 2][(j * 2) + 1] = image[i][j];
            new_image[(i * 2) + 1][(j * 2) + 1] = image[i][j];
        }
    }
}
// Enlarge second Part
void  enlarge_image2() {
    for (int i = 0; i <= 128; ++i) {
        for (int j = 128; j <= 255; ++j) {
            new_image[i * 2][((j - 128) * 2)] = image[i][j];
            new_image[i * 2][((j - 128) * 2) + 1] = image[i][j];
            new_image[(i * 2) + 1][((j - 128) * 2)] = image[i][j];
            new_image[(i * 2) + 1][(((j - 128) * 2)) + 1] = image[i][j];
        }
    }
}
// Enlarge third Part
void  enlarge_image3() {
    for (int i = 128; i <= 255; ++i) {
        for (int j = 0; j <= 128; ++j) {
            new_image[((i - 128) * 2)][j * 2] = image[i][j];
            new_image[((i - 128) * 2) + 1][j * 2] = image[i][j];
            new_image[((i - 128) * 2)][(j * 2) + 1] = image[i][j];
            new_image[(((i - 128) * 2)) + 1][(j * 2) + 1] = image[i][j];
        }
    }
}
// Enlarge forth Part
void  enlarge_image4() {
    for (int i = 128; i <= 255; ++i) {
        for (int j = 128; j <= 255; ++j) {
            new_image[((i - 128) * 2)][((j - 128) * 2)] = image[i][j];
            new_image[((i - 128) * 2)][(((j - 128) * 2)) + 1] = image[i][j];
            new_image[(((i - 128) * 2)) + 1][((j - 128) * 2)] = image[i][j];
            new_image[(((i - 128) * 2)) + 1][(((j - 128) * 2)) + 1] = image[i][j];
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
            new_image[x][y] = image[i][j];
        }
    }
    //copy secound quarter in new possition
    for (int i = 0; i <= 128; ++i) {
        for (int j = 128; j <= 255; ++j) {
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
            new_image[x][y] = image[i][j];
        }
    }
    //copy third quarter in new possition
    for (int i = 128; i <= 255; ++i) {
        for (int j = 0; j <= 128; ++j) {
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
            new_image[x][y] = image[i][j];
        }
    }
    //copy forth quarter in new possition
    for (int i = 128; i <= 255; ++i) {
        for (int j = 128; j <= 255; ++j) {
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
            new_image[x][y] = image[i][j];
        }
    }
}
//___________________________________________________________________________________________
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
                    new_image[i][j] = image[255 - j][i];
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
                    new_image[i][j] = image[j][255 - i];
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
                    new_image[i][j] = image[255 - i][255 - j];
                }
            }
            break;
        }
    }
}
//________________________________________________________
// invert color
void invert_image()
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            new_image[i][j] = 255 - image[i][j];
        }
    }
}

//________________________________________________________
void black_white_filter()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // 127 is the avg of pixels value
            if (image[i][j] > 127)
            {
                image[i][j] = 255;
            }
            else
            {
                image[i][j] = 0;
            }
        }
    }
}
//________________________________________________________
void flip_vertically_filter(){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            new_image[i][j] = image[SIZE - i - 1][j];
        }
    }
}
//________________________________________________________
void flip_horizontally_filter(){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            new_image[i][j] = image[i][SIZE - j - 1];
        }
    }
}
//_________________________________________________________
// make the user any direction to flip
void flip_image_filter(){
    string v_or_h;
    cout << "\nDo you want to flip vertically or horizontally?\n";
    cin >> v_or_h;
    if(v_or_h == "vertically" || v_or_h == "v" || v_or_h == "V") {
        flip_vertically_filter();
    }
    else if(v_or_h == "horizontally" || v_or_h == "h" || v_or_h == "H") {
        flip_horizontally_filter();
    }
}
//______________________________________________________________________
void edge_detection(){
    // convert picture into black and white to ease detection
    black_white_filter();
    int x, y;
    int image_copy[SIZE][SIZE] = {0};
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(i - 1 > 0 && i + 1  < 256 && j - 1 > 0 && j + 1 < 256 ){
                // calculate change in x axis
                x = image[i - 1][j] + image[i + 1][j] - 2*image[i][j];
                // calculate change in y axis
                y = image[i][j - 1] + image[i][j + 1] - 2*image[i][j];
                // collect change in both axises
                // subtract from 255 to convert edges from white to black
                new_image[i][j] = 255 - (x + y);
            }
            // make the remaining pixels from black to white
            else {
                new_image[i][j] = 255;
            }

        }
    }

}
//_________________________________________
void mirror_down_half(){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            image[i][j] = image[SIZE - i][j];
        }
    }
}
//_________________________________________
void mirror_right_half(){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            image[i][j] = image[i][SIZE - j];
        }
    }
}
//_________________________________________
void mirror_upper_half(){
    for(int i = SIZE; i >= 0; i--){
        for(int j = 0; j < SIZE; j++){
            image[i][j] = image[SIZE - i][j];
        }
    }
}
//_________________________________________
void mirror_left_half(){
    for(int i = 0; i < SIZE; i++){
        for(int j = SIZE; j >= 0; j--){
            image[i][j] = image[i][SIZE - j];
        }
    }
}
//_______________________________________________________________________________
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
