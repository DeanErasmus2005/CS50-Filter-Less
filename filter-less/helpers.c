#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float Red = image[i][j].rgbtRed;
            printf("Red: %f", Red);
            float Green = image[i][j].rgbtGreen;
            printf("Green: %f ", Green);
            float Blue = image[i][j].rgbtBlue;
            printf("Blue: %f ", Blue);

            int average = round((Red + Green + Blue) / 3.0);
            printf("Average: %d", average);
            image[i][j].rgbtRed = average;
            printf("rgbtred: %hhu ", image[i][j].rgbtRed);
            image[i][j].rgbtGreen = average;
            printf("rgbtgreen: %hhu ", image[i][j].rgbtGreen);
            image[i][j].rgbtBlue = average;
            printf("rgbtblue: %hhu\n", image[i][j].rgbtBlue);
        }
    }

    return;
}
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float Red = image[i][j].rgbtRed;
            float Green = image[i][j].rgbtGreen;
            float Blue = image[i][j].rgbtBlue;

            float sepiaRed = 0.393 * Red + 0.769 * Green + 0.189 * Blue;
            float sepiaGreen = 0.349 * Red + 0.686 * Green + 0.168 * Blue;
            float sepiaBlue = 0.272 * Red + 0.534 * Green + 0.131 * Blue;

            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : (int) round(sepiaRed);
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : (int) round(sepiaGreen);
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : (int) round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        { // laat chris hierso begin verduidelik
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalRed = 0;
            int totalGreen = 0;
            int totalBlue = 0;
            float counter = 0.00;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentX = i + x;
                    int currentY = j + y;

                    if (currentX < 0 || currentX > (height - 1) || currentY < 0 ||
                        currentY > (height - 1))
                    {
                        continue;
                    }

                    totalRed += image[currentX][currentY].rgbtRed;
                    totalGreen += image[currentX][currentY].rgbtGreen;
                    totalBlue += image[currentX][currentY].rgbtBlue;

                    counter++;
                }
            }
            temp[i][j].rgbtRed = round(totalRed / counter);
            temp[i][j].rgbtGreen = round(totalGreen / counter);
            temp[i][j].rgbtBlue = round(totalBlue / counter);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
