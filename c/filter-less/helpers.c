#include "helpers.h"
#include <math.h>
#include <stdio.h>

int get_average(int array[], int length);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    /*
    How to convert a color image into black-and-white image?
    Well,
        you just have to convert each pixel of an image into black-and-white.
        How to convert a pixel into black-and-white?
            Iterate over an image's pixels:
                    Take an average of Red, green and blue in that pixel

    How to take an average of a value?
        values = [5, 2, 4]

        Mathematical Algorithm for finding the average:
            take a list of items (numbers)
            find the sum of the numbers
            find the count of the numbers
            divide the sum by count
            DONE!
    */

    int sum = 0;

    // Iterate over the image's pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Caldulate the sum [R+G+B]
            sum = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;

            // Calculate the average
            int average = (int) round(sum / 3.0);

            // Update the pixel values
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    /*
    How to apply sepia filter to an image?
        for each pixel in image:
            apply sepia algorithm to the pixel
            if result > 255:
                sepia_value should capped at 255
            update pixel's value to sepia_value

    Sepia Algorithm:
        sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
        sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
        sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue

        Round each of em' to nearest integer
        if value greater than 255:
            Cap at 255
    */

    int sepiaRed, sepiaGreen, sepiaBlue;
    int originalRed, originalGreen, originalBlue;

    // Iterate over the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get the values from pixel
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            // Calculate the sepia values
            sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // Cap at 255, if greater
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Update the pixel's values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    /*
    Reflection Filter? (Horizontally!)
    - Pixels on left side of image should end up in the right side of the image & vice versa

    for each row in image:
        for each pixel in row:
            // swap the pixel

    How to swap?
    - store the current value
    - swap:
        0 with n-1
        1 with n-2
        2 with n-3
        3 with n-4

    */

    // Iterate over an image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            RGBTRIPLE pixel = image[i][j]; // store the current pixel
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = pixel;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    /*
    Applying blur filter?
    there are number of ways to apply a blur effect on an image,
    for this problem, we'll use the box-blur method.
    Box-Blur: ??
        box-blur works by taking each pixel and, for each color value, giving
        it a new value by averaging the color values of neighboring pixels.
    Explanation:
        for example, consider this image (rather a grid of pixels),
        where each pixel is represented by a value:

        1  | 2  | 3  | 4
        5  | 6  | 7  | 8
        9  | 10 | 11 | 12
        13 | 14 | 15 | 16

        The new value for 'pixel 6' would be the average of [1,2,3,5,6,7,9,10,11]
            NOTE: the pixel(6) itself is included in the average too.

        For pixels along the edge or corner, like pixel 15, we would still
        look for all pixels within 1 row 1 column 3x3 box.
            in this case, average of [10,11,12,14,15,16]

    But blurring one pixel might affect the blur of other pixels
    like for example, blurring 6 will affect the blur of all surrounding
    pixels in 3x3 grid, because their initial values will already be blurred!

    Its best to take a copy of an image and then blur the image,
    this solves the problem above as you'll be taking the values from a copy.
        Then you can:
            Read from image.copy
            Write to image

    Algorithm:
        for each pixel in image:
            find neighbors of this pixel
            find the average of neighbors(including pixel)
            set pixel's value to average

    Finding the neighbors:?
        void findNeighbors(int array[][3], int rows, int cols, int x, int y) {
            // Define relative positions of neighbors
            int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
            int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

            printf("Neighbors of array[%d][%d]:\n", x, y);

            // Iterate through all neighbors
            for (int i = 0; i < 8; ++i) {
                int newX = x + dx[i];
                int newY = y + dy[i];

                // Check if the new position is within the array bounds
                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
                    printf("%d ", array[newX][newY]);
                }
            }
        }

    Finding neighbors:
    at any [i][j]:
    all neighbors would be:
        i-1,j-1 | i-1,j | i-1,j+1
        i,j-1   | i,j   | i,j+1
        i+1,j-1 | i+1,j | i+1,j+1
    check for boundaries to avoid out of range issues

    */

    // First make a copy of the image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // copy pixels from image to copy
            copy[i][j] = image[i][j];
        }
    }

    // RGBTRIPLE neighbor; // Will hold a single neighbor
    int new_x, new_y;

    // Positions of neighbors (relative to current pixel)
    int dx[] = {0, -1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {0, -1, 0, 1, -1, 1, -1, 0, 1};
    int averages[3]; // will hold the average values (RGB)

    // Iterate over each pixel in image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int n_len = 0; // length of neighbors
            int sumRed = 0, sumGreen = 0, sumBlue = 0;

            // Find the neighboring pixels
            for (int k = 0; k < 9; k++)
            {
                new_x = i + dx[k]; // find x index of neighbor
                new_y = j + dy[k]; // find y index of neighbor

                // Check if the new position is within the image bounds
                if ((new_x >= 0 && new_x < height) && (new_y >= 0 && new_y < width))
                {
                    // Sum the values
                    sumRed += copy[new_x][new_y].rgbtRed;     // red
                    sumGreen += copy[new_x][new_y].rgbtGreen; // geen
                    sumBlue += copy[new_x][new_y].rgbtBlue;   // blue

                    // Increment neighbor's count
                    n_len++;
                }
            }

            // Calculate the averages
            averages[0] = (int) round(sumRed / (float) n_len);   // Red avg.
            averages[1] = (int) round(sumGreen / (float) n_len); // Green avg.
            averages[2] = (int) round(sumBlue / (float) n_len);  // Blue avg.

            // Set averages to current pixel
            image[i][j].rgbtRed = averages[0];   // Red
            image[i][j].rgbtGreen = averages[1]; // Green
            image[i][j].rgbtBlue = averages[2];  // Blue
        }
    }

    return;
}

// Custom function to find the average in an array of integers
int get_average(int array[], int length)
{
    int sum = 0;
    // Iterate through the list
    for (int i = 0; i < length; i++)
    {
        // Add to sum
        sum += array[i];
    }

    // Divide Sum by total numbers in the list (length)
    float average = round(sum / (float) length);
    // Return the result (INTEGER!!!!!!)
    return (int) average;
}
