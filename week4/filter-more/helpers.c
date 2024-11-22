#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
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
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
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
        {
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
            int redSum = 0;
            int greenSum = 0;
            int blueSum = 0;
            int count = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k < 0 || i + k > height - 1 || j + l < 0 || j + l > width - 1)
                    {
                        continue;
                    }
                    redSum += image[i + k][j + l].rgbtRed;
                    greenSum += image[i + k][j + l].rgbtGreen;
                    blueSum += image[i + k][j + l].rgbtBlue;
                    count++;
                }
            }
            temp[i][j].rgbtRed = round((float) redSum / count);
            temp[i][j].rgbtGreen = round((float) greenSum / count);
            temp[i][j].rgbtBlue = round((float) blueSum / count);
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
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float GxRed = 0, GxGreen = 0, GxBlue = 0;
            float GyRed = 0, GyGreen = 0, GyBlue = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k < 0 || i + k > height - 1 || j + l < 0 || j + l > width - 1)
                    {
                        continue;
                    }
                    GxRed += image[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                    GxGreen += image[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                    GxBlue += image[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];

                    GyRed += image[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                    GyGreen += image[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    GyBlue += image[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                }
            }

            int finalRed = round(sqrt(GxRed * GxRed + GyRed * GyRed));
            int finalGreen = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
            int finalBlue = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));

            temp[i][j].rgbtRed = (finalRed > 255) ? 255 : finalRed;
            temp[i][j].rgbtGreen = (finalGreen > 255) ? 255 : finalGreen;
            temp[i][j].rgbtBlue = (finalBlue > 255) ? 255 : finalBlue;
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
