#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>
#include <regex> 
#include <string>
#include "bmplib.cpp"

using namespace std;

unsigned char image[SIZE][SIZE];
unsigned char secondImage[SIZE][SIZE];
unsigned char new_image[SIZE][SIZE];

// Defining the functions in the program so main function can recognize them.
void loadImage(unsigned char image[][SIZE]);
void saveImage();
void blur();
void darkenlighten(string choice);
void merge();
void shrink(int dimension);
int& parseValidInput(string str, int& dimension);
void enlarge_image1();
void enlarge_image2();
void enlarge_image3();
void enlarge_image4();
void enlarge_image();
void shuffle_image();
void rotate_image();
void invert_image();
void black_white();

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
        loadImage(image);
        black_white();
        saveImage();
        return 0;
    }
    else if (filter == "2")
    {
        cout << "Enter the source image file name: ";
        loadImage(image);
        invert_image();
        saveImage();
        return 0;
    }
    else if (filter == "3")
    {
        cout << "Enter the source image file name: ";
        loadImage(image);
        cout << "Enter the source second image file name: ";
        loadImage(secondImage);
        merge();
        saveImage();
        return 0;
    }
    else if (filter == "4")
    {
        cout << "Enter the source image file name: ";
        loadImage(image);
        // flip();
        saveImage();
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
    else if (filter == "6")
    {
        cout << "Enter the source image file name: ";
        loadImage(image);
        rotate_image();
        saveImage();
        return 0;
    }
    else if (filter == "7")
    {
        cout << "Enter the source image file name: ";
        loadImage(image);
        // edge();
        saveImage();
        return 0;
    }
    else if (filter == "8")
    {
        cout << "Enter the source image file name: ";
        loadImage(image);
        enlarge_image();
        saveImage();
        return 0;
    }
    else if (filter == "9")
    {
        cout << "Enter the source image file name: ";
        loadImage(image);
        cin.clear();
        cin.ignore();
        while (dimension == 0)
        {
            cout << "Shrink to (1/2), (1/3) or (1/4)?\nPlease, Enter the input on form a/b: ";
            getline(cin, dimensionStr);
            parseValidInput(dimensionStr, dimension);
            cin.ignore(0);
        }
        shrink(dimension);
        saveImage();
        return 0;
    }
    else if (filter == "a" || filter == "A")
    {
        cout << "Enter the source image file name: ";
        loadImage(image);
        // mirror ()
        saveImage();
        return 0;
    }
    else if (filter == "b" || filter == "B")
    {
        cout << "Enter the source image file name: ";
        loadImage(image);
        shuffle_image();
        saveImage();
        return 0;
    }
    else if (filter == "c" || filter == "C")
    {
        cout << "Enter the source image file name: ";
        loadImage(image);
        blur();
        saveImage();
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
void loadImage(unsigned char image[][SIZE])
{
    char imageFileName[100];

    // Get gray scale image file name
    cin >> imageFileName;
	cin.ignore();

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage()
{
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

void blur()
{
    float q;
    // the average of colour
    float avg = 0;

    for (int x = 0; x < SIZE; x++)
    {
        for (int y = 0; y < SIZE; y++)
        {
            avg = 0;
            //bluring the left corner
            if ((x == 0) && (y == 0))
            {
                q = 4.0;
                for (int n = x; n <= x + 1; n++)
                {
                    for (int m = y; m <= y + 1; m++)
                    {
                        avg += image[n][m];
                    }
                }
            }
            //bluring top pixel's edge
            if ((x == 0) && (y > 0) && (y < (SIZE - 1)))
            {
                q = 6.0;
                for (int n = x; n <= x + 1; n++)
                {
                    for (int m = y - 1; m <= y + 1; m++)
                    {
                        avg += image[n][m];

                    }
                }

            }
            //bluring the right corner
            if ((x == 0) && (y == SIZE - 1))
            {
                q = 4.0;
                for (int n = x; n <= x + 1; n++)
                {
                    for (int m = y - 1; m <= y; m++)
                    {
                        avg += image[n][m];
                    }
                }
            }
            //bluring left edges
            if ((x > 0) && (y == 0) && (x < SIZE - 1))
            {
                q = 6.0;
                for (int n = x - 1; n <= x + 1; n++)
                {
                    for (int m = y; m <= y + 1; m++)
                    {
                        avg += image[n][m];
                    }
                }
            }
            //bluring right edges
            if ((x > 0) && (y == SIZE - 1) && (x < SIZE - 1))
            {
                q = 6.0;
                for (int n = x - 1; n <= x + 1; n++)
                {
                    for (int m = y - 1; m <= y; m++)
                    {
                        avg += image[n][m];
                    }
                }
            }
            //bluring another left corner
            if ((x == (SIZE - 1)) && (y == 0))
            {
                q = 4.0;
                for (int n = x - 1; n <= x; n++)
                {
                    for (int m = y; m <= y + 1; m++)
                    {
                        avg += image[n][m];
                    }
                }
            }
            //bluring another right corner
            if ((x == (SIZE - 1)) && (y == (SIZE - 1)))
            {
                q = 4.0;
                for (int n = x - 1; n <= x; n++)
                {
                    for (int m = y - 1; m <= y; m++)
                    {
                        avg += image[n][m];
                    }
                }
            }
            //bluring middle pixels
            if (y > 0 && y < (SIZE - 1) && x > 0 && x < (SIZE - 1))
            {
                q = 9.0;
                for (int n = x - 1; n <= x + 1; n++)
                {
                    for (int m = y - 1; m <= y + 1; m++)
                    {
                        avg += image[n][m];
                    }
                }
            }
            //bluring bottom edges
            if (y > 0 && y < (SIZE - 1) && x == (SIZE - 1))
            {
                q = 6.0;
                for (int n = x - 1; n <= x; n++)
                {
                    for (int m = y - 1; m <= y + 1; m++)
                    {
                        avg += image[n][m];
                    }
                }
            }
            // Advantage RGB colours
            avg = round(avg / q);
            //storing the average value in new_image variable
            new_image[x][y] = avg;

        }

    }
    //converting the current pixels to blured ones
    for (int x = 0; x < SIZE; x++)
    {
        for (int y = 0; y < SIZE; y++)
        {
            image[x][y] = new_image[x][y];
        }
    }

}

void merge()
{
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
    if (choice == 'd')
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                image[i][j] -= image[i][j] * (0.5);
            }
        }
    }
    else if (choice == 'l')
    {
        float light = 0;
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                light = abs(image[i][j] - 255);
                image[i][j] += light / 2.0;
            }
        }
    }

}

void shrink(int dimension)
{
    unsigned char new_image[SIZE][SIZE];
    unsigned char neww_image[SIZE][SIZE];
    int counter = 0;
    double avg = 0;

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < (SIZE / dimension); ++j)
        {
            for (int c = counter; c < (counter + dimension); ++c)
            {
                avg += image[i][c];
            }
            neww_image[i][j] = (avg / dimension);
            avg = 0;
            counter += dimension;
        }
        counter = 0;
    }

    counter = 0;
    avg = 0;

    for (int i = 0; i < SIZE / dimension; ++i)
    {
        for (int j = 0; j < SIZE / dimension; ++j)
        {
            for (int c = counter; c < (counter + dimension); ++c)
            {
                avg += neww_image[c][j];
            }
            new_image[i][j] = (avg / dimension);
            avg = 0;
        }
        counter += dimension;
    }


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

int& parseValidInput(string str, int& dimension)
{
    // Making a form for input rational number using regular expressions 
    regex isValidInput("(1/[2-4])");
    //Returning True if the input string was like the form we just make, False otherwise
    if (regex_match(str, isValidInput))
    {
        char d[1] = { str[2] };
        dimension = atoi(d);
        return dimension;
    }
    else
    {
        return dimension;
    }

}


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

void  enlarge_image2() {
    for (int i = 0; i <= 128; ++i) {
        for (int j = 129; j <= 256; ++j) {

            new_image[i * 2][((j - 129) * 2)] = image[i][j];
            new_image[i * 2][((j - 129) * 2) + 1] = image[i][j];
            new_image[(i * 2) + 1][((j - 129) * 2)] = image[i][j];
            new_image[(i * 2) + 1][(((j - 129) * 2)) + 1] = image[i][j];
        }
    }
}

void  enlarge_image3() {
    for (int i = 129; i <= 256; ++i) {
        for (int j = 0; j <= 128; ++j) {

            new_image[((i - 129) * 2)][j * 2] = image[i][j];
            new_image[((i - 129) * 2) + 1][j * 2] = image[i][j];
            new_image[((i - 129) * 2)][(j * 2) + 1] = image[i][j];
            new_image[(((i - 129) * 2)) + 1][(j * 2) + 1] = image[i][j];

        }
    }
}

void  enlarge_image4() {
    for (int i = 129; i <= 256; ++i) {
        for (int j = 129; j <= 256; ++j) {

            new_image[((i - 129) * 2)][((j - 129) * 2)] = image[i][j];
            new_image[((i - 129) * 2) + 1][((j - 129) * 2) + 1] = image[i][j];
            new_image[((i - 129) * 2)][((j - 129) * 2)] = image[i][j];
            new_image[(((i - 129) * 2)) + 1][(((j - 129) * 2)) + 1] = image[i][j];

        }
    }
}

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


//_________________________________________

void shuffle_image() {

    int a = 0, b = 0, c = 0, d = 0, x = 0, y = 0;
    cout << "Ahlan ya Am El-User...\n";
    cout << "How u sort the quarters?...\n";
    cout << " 1 | 2 \n 3 | 4 \n";
    cin >> a >> b >> c >> d;

    //first
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
    //second
    for (int i = 0; i <= 128; ++i) {
        for (int j = 129; j <= 256; ++j) {

            if (a == 2) {
                x = i;
                y = j - 129;
            }
            else if (b == 2) {
                x = i;
                y = j;
            }
            else if (c == 2) {
                x = i + 128;
                y = j - 129;
            }
            else if (d == 2) {
                x = i + 128;
                y = j;
            }

            new_image[x][y] = image[i][j];
        }
    }
    //third
    for (int i = 129; i <= 256; ++i) {
        for (int j = 0; j <= 128; ++j) {
            if (a == 3) {
                x = i - 129;
                y = j;
            }
            else if (b == 3) {
                x = i - 129;
                y = j + 128;
            }
            else if (c == 3) {
                x = i;
                y = j;
            }
            else if (d == 4) {
                x = i;
                y = j + 128;
            }
            new_image[x][y] = image[i][j];
        }
    }
    //forth
    for (int i = 129; i <= 256; ++i) {
        for (int j = 129; j <= 256; ++j) {
            if (a == 4) {
                x = i - 129;
                y = j - 129;
            }
            else if (b == 4) {
                x = i - 129;
                y = j;
            }
            else if (c == 4) {
                x = i;
                y = j - 129;
            }
            else if (d == 4) {
                x = i;
                y = j;
            }

            new_image[x][y] = image[i][j];
        }
    }
}

//_________________________________________

void rotate_image()
{
    int degree;
    cout << "Ahlan ya Am El-User...\n";
    cout << "Rotate image:(1 | 2 | 3) \n";
    cout << " 1- 90 deg Right \n 2- 90 deg Left \n 3- 180 deg \n>>> ";
    cin >> degree;

    if (degree == 1)
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                new_image[i][j] = image[255 - j][i];
            }
        }
    }
    else if (degree == 2)
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                new_image[i][j] = image[j][255 - i];
            }
        }
    }
    else if (degree == 3)
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                new_image[i][j] = image[255 - i][255 - j];
            }
        }
    }
}


void invert_image()
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            image[i][j] = 255 - image[i][j];
        }
    }
}

void black_white() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {

            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}