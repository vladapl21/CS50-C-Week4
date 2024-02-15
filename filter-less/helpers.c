#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int avg = round(((float) image[i][j].rgbtRed + (float) image[i][j].rgbtGreen + (float) image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int ogred = image[i][j].rgbtRed;
            int oggreen = image[i][j].rgbtGreen;
            int ogblue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = fmin(round((0.393 * ogred) + (0.769 * oggreen) + (0.189 * ogblue)), 255);
            image[i][j].rgbtGreen = fmin(round((0.349 * ogred) + (0.686 * oggreen) + (0.168 * ogblue)), 255);
            image[i][j].rgbtBlue = fmin(round((0.272 * ogred) + (0.534 * oggreen) + (0.131 * ogblue)), 255);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2.0); j++)
        {
            int tempred = image[i][j].rgbtRed;
            int tempgreen = image[i][j].rgbtGreen;
            int tempblue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;

            image[i][width - 1 - j].rgbtRed = tempred;
            image[i][width - 1 - j].rgbtGreen = tempgreen;
            image[i][width - 1 - j].rgbtBlue = tempblue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // loop around each pixel in a 9x9
            int totred = 0;
            int totgreen = 0;
            int totblue = 0;
            int divisor = 9;
            for (int row = i - 1; row < i + 2; row++)
            {
                for (int column = j - 1; column < j + 2; column++)
                {
                    if (row < height && row >= 0 && column >= 0 && column < width)
                    {
                        totred += copy[row][column].rgbtRed;
                        totgreen += copy[row][column].rgbtGreen;
                        totblue += copy[row][column].rgbtBlue;
                    }
                    else
                    {
                        divisor -= 1;
                    }
                }
            }
            image[i][j].rgbtRed = round((float) totred / (float) divisor);
            image[i][j].rgbtGreen = round((float) totgreen / (float) divisor);
            image[i][j].rgbtBlue = round((float) totblue / (float) divisor);
        }
    }
    return;
}
