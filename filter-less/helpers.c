#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            int rounded_average = (int) round(average);
            image[i][j].rgbtBlue = rounded_average;
            image[i][j].rgbtGreen = rounded_average;
            image[i][j].rgbtRed = rounded_average;
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
            float sepia_blue = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;
            if (sepia_blue > 255.0)
            {
                sepia_blue = 255.0;
            }

            float sepia_green = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            if (sepia_green > 255.0)
            {
                sepia_green = 255.0;
            }

            float sepia_red = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            if (sepia_red > 255.0)
            {
                sepia_red = 255.0;
            }

            int rounded_sepia_blue = (int) round(sepia_blue);
            int rounded_sepia_green = (int) round(sepia_green);
            int rounded_sepia_red = (int) round(sepia_red);

            image[i][j].rgbtBlue = rounded_sepia_blue;
            image[i][j].rgbtGreen = rounded_sepia_green;
            image[i][j].rgbtRed = rounded_sepia_red;
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
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
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
            float blue_average = 0;
            float green_average = 0;
            float red_average = 0;
            int counter = 0;

            for (int box_row = -1; box_row <= 1; box_row++)
            {
                for (int box_column = -1; box_column <= 1; box_column++)
                {
                    int current_box_row = i + box_row;
                    int current_box_column = j + box_column;

                    if (current_box_row >= 0 && current_box_row < height && current_box_column >= 0 && current_box_column < width)
                    {
                        blue_average += image[current_box_row][current_box_column].rgbtBlue;
                        green_average += image[current_box_row][current_box_column].rgbtGreen;
                        red_average += image[current_box_row][current_box_column].rgbtRed;
                        counter++;
                    }
                }
            }

            temp[i][j].rgbtBlue = (int) round(blue_average / counter);
            temp[i][j].rgbtGreen = (int) round(green_average / counter);
            temp[i][j].rgbtRed = (int) round(red_average / counter);
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
