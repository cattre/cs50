#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float shade;
    // Iterate through rows
    for (int i = 0; i < height; i++)
    {
        // Iterate through columns
        for (int j = 0; j < width; j++)
        {
            // Get average of pixel colours
            shade = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtRed = round(shade);
            image[i][j].rgbtGreen = round(shade);
            image[i][j].rgbtBlue = round(shade);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    // Iterate through rows
    for (int i = 0; i < height; i++)
    {
        // Iterate through columns until middle of image
        for (int j = 0; j < width/2; j++)
        {
            // Swap pixels with opposite position
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempImage[height][width];

    // Iterate through rows
    for (int i = 0; i < height; i++)
    {
        // Iterate through columns
        for (int j = 0; j < width; j++)
        {
            float blurRed = 0;
            float blurGreen = 0;
            float blurBlue = 0;
            int pixelCount = 0;

            // Iterate through rows above and below current pixel
            for (int k = i - 1; k <= i + 1; k++)
            {
                // Iterate through columns to left and right of current pixel
                for (int l = j - 1; l <= j + 1; l++)
                {
                    // Check if pixel within range
                    if (k >= 0 && k < height && l >= 0 && l < width)
                    {
                        // Sum colour values
                        blurRed = blurRed + image[k][l].rgbtRed;
                        blurGreen = blurGreen + image[k][l].rgbtGreen;
                        blurBlue = blurBlue + image[k][l].rgbtBlue;
                        pixelCount++;
                    }
                }
            }
            // Get average for colour values and store in temp image
            tempImage[i][j].rgbtRed = round(blurRed / pixelCount);
            tempImage[i][j].rgbtGreen = round(blurGreen / pixelCount);
            tempImage[i][j].rgbtBlue = round(blurBlue / pixelCount);
        }
    }

    // Copy temp image back to main one

    // Iterate through rows
    for (int i = 0; i < height; i++)
    {
        // Iterate through columns
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tempImage[i][j].rgbtRed;
            image[i][j].rgbtGreen = tempImage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tempImage[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int GxKernel[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}}; // Gx kernel array
    int GyKernel[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}}; // Gy kernel array

    RGBTRIPLE tempImage[height][width];

    // Iterate through rows
    for (int i = 0; i < height; i++)
    {
        // Iterate through columns
        for (int j = 0; j < width; j++)
        {
            float GxRed = 0;
            float GxGreen = 0;
            float GxBlue = 0;
            float GyRed = 0;
            float GyGreen = 0;
            float GyBlue = 0;
            
            // Iterate through rows above and below current pixel
            for (int k = i - 1; k <= i + 1; k++)
            {
                // Iterate through columns to left and right of current pixel
                for (int l = j - 1; l <= j + 1; l++)
                {
                    int x = k - i + 1; // horizontal kernel array location
                    int y = l - j + 1; // vertical kernel array location

                    // Check if pixel within range
                    if (k >= 0 && k < height && l >= 0 && l < width)
                    {
                        // Sum Gx values
                        GxRed = GxRed + image[k][l].rgbtRed * GxKernel[x][y];
                        GxGreen = GxGreen + image[k][l].rgbtGreen * GxKernel[x][y];
                        GxBlue = GxBlue + image[k][l].rgbtBlue * GxKernel[x][y];

                        // Sum Gy values
                        GyRed = GyRed + image[k][l].rgbtRed * GyKernel[x][y];
                        GyGreen = GyGreen + image[k][l].rgbtGreen * GyKernel[x][y];
                        GyBlue = GyBlue + image[k][l].rgbtBlue * GyKernel[x][y];
                    }
                }
            }
            // Get average for colour values and store in temp image
            tempImage[i][j].rgbtRed = fminf(round(sqrt(pow(GxRed,2) + pow(GyRed,2))),255);
            tempImage[i][j].rgbtGreen = fminf(round(sqrt(pow(GxGreen,2) + pow(GyGreen,2))),255);
            tempImage[i][j].rgbtBlue = fminf(round(sqrt(pow(GxBlue,2) + pow(GyBlue,2))),255);
        }
    }

    // Copy temp image back to main one

    // Iterate through rows
    for (int i = 0; i < height; i++)
    {
        // Iterate through columns
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tempImage[i][j].rgbtRed;
            image[i][j].rgbtGreen = tempImage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tempImage[i][j].rgbtBlue;
        }
    }

    return;
}
