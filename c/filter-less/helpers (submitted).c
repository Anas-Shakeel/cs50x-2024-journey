#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
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
    RGBTRIPLE pixel;
    // Iterate over the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            pixel = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = pixel;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
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

    // Positions of neighbors (relative to current pixel)
    int dx[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    int new_x, new_y;

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
                    sumRed += copy[new_x][new_y].rgbtRed;     // Red
                    sumGreen += copy[new_x][new_y].rgbtGreen; // Green
                    sumBlue += copy[new_x][new_y].rgbtBlue;   // Blue

                    // Increment neighbor's count
                    n_len++;
                }
            }

            // Calculate averages and set to pixel's values
            image[i][j].rgbtRed = (int) round(sumRed / (float) n_len);     // Red
            image[i][j].rgbtGreen = (int) round(sumGreen / (float) n_len); // Green
            image[i][j].rgbtBlue = (int) round(sumBlue / (float) n_len);   // Blue
        }
    }

    return;
}
