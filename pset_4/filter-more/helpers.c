#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average, blue, green, red;
    int rounded;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blue = image[i][j].rgbtBlue;
            green = image[i][j].rgbtGreen;
            red = image[i][j].rgbtRed;

            average = (blue + green + red) / 3;
            rounded = round(average);

            image[i][j].rgbtBlue = rounded;
            image[i][j].rgbtGreen = rounded;
            image[i][j].rgbtRed = rounded;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temporary[height][width];

    // Write in temporary image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temporary[i][j].rgbtBlue = image[i][j].rgbtBlue;
            temporary[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temporary[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    // Invert image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width; j < width; j++)
        {
            k--;
            image[i][j].rgbtBlue = temporary[i][k].rgbtBlue;
            image[i][j].rgbtGreen = temporary[i][k].rgbtGreen;
            image[i][j].rgbtRed = temporary[i][k].rgbtRed;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temporary[height][width];

    // Write in temporary image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temporary[i][j].rgbtBlue = image[i][j].rgbtBlue;
            temporary[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temporary[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    float BLUE = 0;
    float GREEN = 0;
    float RED = 0;

    float bCounter = 0;
    float gCounter = 0;
    float rCounter = 0;

    int averageBlue;
    int averageGreen;
    int averageRed;

    float aBlue, aGreen, aRed;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // Blue Start

            // Upper row; left center and right
            if (i > 0)
            {
                if (j > 0)
                {
                    BLUE = BLUE + temporary[i - 1][j - 1].rgbtBlue;
                    bCounter++;
                }

                BLUE = BLUE + temporary[i - 1][j].rgbtBlue;
                bCounter++;

                if (j < width - 1)
                {
                    BLUE = BLUE + temporary[i - 1][j + 1].rgbtBlue;
                    bCounter++;
                }
            }

            // Current row; left, center(current pixel), and right
            if (j > 0)
            {
                BLUE = BLUE + temporary[i][j - 1].rgbtBlue;
                bCounter++;
            }

            // Current pixel
            BLUE = BLUE + temporary[i][j].rgbtBlue;
            bCounter++;

            if (j < width - 1)
            {
                BLUE = BLUE + temporary[i][j + 1].rgbtBlue;
                bCounter++;
            }

            // Lower Row; left, center and right
            if (i < height - 1)
            {
                if (j > 0)
                {
                    BLUE = BLUE + temporary[i + 1][j - 1].rgbtBlue;
                    bCounter++;
                }

                BLUE = BLUE + temporary[i + 1][j].rgbtBlue;
                bCounter++;

                if (j < width - 1)
                {
                    BLUE = BLUE + temporary[i + 1][j + 1].rgbtBlue;
                    bCounter++;
                }
            }
            // Blue End

            // Green Start

            // Upper row; left center and right
            if (i > 0)
            {
                if (j > 0)
                {
                    GREEN = GREEN + temporary[i - 1][j - 1].rgbtGreen;
                    gCounter++;
                }

                GREEN = GREEN + temporary[i - 1][j].rgbtGreen;
                gCounter++;

                if (j < width - 1)
                {
                    GREEN = GREEN + temporary[i - 1][j + 1].rgbtGreen;
                    gCounter++;
                }
            }

            // Current row; left, center(current pixel), and right
            if (j > 0)
            {
                GREEN = GREEN + temporary[i][j - 1].rgbtGreen;
                gCounter++;
            }

            // Current pixel
            GREEN = GREEN + temporary[i][j].rgbtGreen;
            gCounter++;

            if (j < width - 1)
            {
                GREEN = GREEN + temporary[i][j + 1].rgbtGreen;
                gCounter++;
            }

            // Lower Row; left, center and right
            if (i < height - 1)
            {
                if (j > 0)
                {
                    GREEN = GREEN + temporary[i + 1][j - 1].rgbtGreen;
                    gCounter++;
                }

                GREEN = GREEN + temporary[i + 1][j].rgbtGreen;
                gCounter++;

                if (j < width - 1)
                {
                    GREEN = GREEN + temporary[i + 1][j + 1].rgbtGreen;
                    gCounter++;
                }
            }
            // Green End

            // Red Start

            // Upper row; left center and right
            if (i > 0)
            {
                if (j > 0)
                {
                    RED = RED + temporary[i - 1][j - 1].rgbtRed;
                    rCounter++;
                }

                RED = RED + temporary[i - 1][j].rgbtRed;
                rCounter++;

                if (j < width - 1)
                {
                    RED = RED + temporary[i - 1][j + 1].rgbtRed;
                    rCounter++;
                }
            }

            // Current row; left, center(current pixel), and right
            if (j > 0)
            {
                RED = RED + temporary[i][j - 1].rgbtRed;
                rCounter++;
            }

            // Current pixel
            RED = RED + temporary[i][j].rgbtRed;
            rCounter++;

            if (j < width - 1)
            {
                RED = RED + temporary[i][j + 1].rgbtRed;
                rCounter++;
            }

            // Lower Row; left, center and right
            if (i < height - 1)
            {
                if (j > 0)
                {
                    RED = RED + temporary[i + 1][j - 1].rgbtRed;
                    rCounter++;
                }

                RED = RED + temporary[i + 1][j].rgbtRed;
                rCounter++;

                if (j < width - 1)
                {
                    RED = RED + temporary[i + 1][j + 1].rgbtRed;
                    rCounter++;
                }
            }
            // Red End

            aBlue = (BLUE / bCounter);
            aGreen = (GREEN / gCounter);
            aRed = (RED / rCounter);

            // Round the average per color
            averageBlue = round(aBlue);
            averageGreen = round(aGreen);
            averageRed = round(aRed);

            // Write new mix of colors to current pixel
            image[i][j].rgbtBlue = averageBlue;
            image[i][j].rgbtGreen = averageGreen;
            image[i][j].rgbtRed = averageRed;

            // Reset Variables
            BLUE = 0;
            GREEN = 0;
            RED = 0;

            bCounter = 0;
            gCounter = 0;
            rCounter = 0;

            aBlue = 0;
            aGreen = 0;
            aRed = 0;

            averageBlue = 0;
            averageGreen = 0;
            averageRed = 0;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temporary[height][width];

    // Write in temporary image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temporary[i][j].rgbtBlue = image[i][j].rgbtBlue;
            temporary[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temporary[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    float gxBLUE = 0, gxGREEN = 0, gxRED = 0;
    float gyBLUE = 0, gyGREEN = 0, gyRED = 0;
    float BLUE, GREEN, RED;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // BLUE***********************************************************************************************************************************************

            // Blue Gx
            // Start--------------------------------------------------------------------------------------------------------------------------
            // If Upper Row Exists
            if (i > 0)
            {
                // Upper Left Pixel
                if (j > 0)
                {
                    gxBLUE = gxBLUE + ((temporary[i - 1][j - 1].rgbtBlue) * (-1));
                }

                // Upper Center Pixel
                gxBLUE = gxBLUE + ((temporary[i - 1][j].rgbtBlue) * (0));

                // Upper Right Pixel
                if (j < width - 1)
                {
                    gxBLUE = gxBLUE + ((temporary[i - 1][j + 1].rgbtBlue) * (1));
                }
            }

            // Current row; left, center(current pixel), and right
            if (j > 0)
            {
                gxBLUE = gxBLUE + ((temporary[i][j - 1].rgbtBlue) * (-2));
            }

            // Current pixel
            gxBLUE = gxBLUE + ((temporary[i][j].rgbtBlue) * (0));

            if (j < width - 1)
            {
                gxBLUE = gxBLUE + ((temporary[i][j + 1].rgbtBlue) * (2));
            }

            // Lower Row; left, center and right
            if (i < height - 1)
            {
                if (j > 0)
                {
                    gxBLUE = gxBLUE + ((temporary[i + 1][j - 1].rgbtBlue) * (-1));
                }

                gxBLUE = gxBLUE + ((temporary[i + 1][j].rgbtBlue) * (0));

                if (j < width - 1)
                {
                    gxBLUE = gxBLUE + ((temporary[i + 1][j + 1].rgbtBlue) * (1));
                }
            }
            // Blue Gx
            // End--------------------------------------------------------------------------------------------------------------------

            // Blue Gy
            // Start__________________________________________________________________________________________________________________
            // If Upper Row Exists
            if (i > 0)
            {
                // Upper Left Pixel
                if (j > 0)
                {
                    gyBLUE = gyBLUE + ((temporary[i - 1][j - 1].rgbtBlue) * (-1));
                }

                // Upper Center Pixel
                gyBLUE = gyBLUE + ((temporary[i - 1][j].rgbtBlue) * (-2));

                // Upper Right Pixel
                if (j < width - 1)
                {
                    gyBLUE = gyBLUE + ((temporary[i - 1][j + 1].rgbtBlue) * (-1));
                }
            }

            // Current row; left, center(current pixel), and right
            if (j > 0)
            {
                gyBLUE = gyBLUE + ((temporary[i][j - 1].rgbtBlue) * (0));
            }

            // Current pixel
            gyBLUE = gyBLUE + ((temporary[i][j].rgbtBlue) * (0));

            if (j < width - 1)
            {
                gyBLUE = gyBLUE + ((temporary[i][j + 1].rgbtBlue) * (0));
            }

            // Lower Row; left, center and right
            if (i < height - 1)
            {
                if (j > 0)
                {
                    gyBLUE = gyBLUE + ((temporary[i + 1][j - 1].rgbtBlue) * (1));
                }

                gyBLUE = gyBLUE + ((temporary[i + 1][j].rgbtBlue) * (2));

                if (j < width - 1)
                {
                    gyBLUE = gyBLUE + ((temporary[i + 1][j + 1].rgbtBlue) * (1));
                }
            }
            // Blue Gy
            // End___________________________________________________________________________________________________________________________

            // BLUE***********************************************************************************************************************************************

            // GREEN***********************************************************************************************************************************************

            // GREEN Gx
            // Start--------------------------------------------------------------------------------------------------------------------------
            // If Upper Row Exists
            if (i > 0)
            {
                // Upper Left Pixel
                if (j > 0)
                {
                    gxGREEN = gxGREEN + ((temporary[i - 1][j - 1].rgbtGreen) * (-1));
                }

                // Upper Center Pixel
                gxGREEN = gxGREEN + ((temporary[i - 1][j].rgbtGreen) * (0));

                // Upper Right Pixel
                if (j < width - 1)
                {
                    gxGREEN = gxGREEN + ((temporary[i - 1][j + 1].rgbtGreen) * (1));
                }
            }

            // Current row; left, center(current pixel), and right
            if (j > 0)
            {
                gxGREEN = gxGREEN + ((temporary[i][j - 1].rgbtGreen) * (-2));
            }

            // Current pixel
            gxGREEN = gxGREEN + ((temporary[i][j].rgbtGreen) * (0));

            if (j < width - 1)
            {
                gxGREEN = gxGREEN + ((temporary[i][j + 1].rgbtGreen) * (2));
            }

            // Lower Row; left, center and right
            if (i < height - 1)
            {
                if (j > 0)
                {
                    gxGREEN = gxGREEN + ((temporary[i + 1][j - 1].rgbtGreen) * (-1));
                }

                gxGREEN = gxGREEN + ((temporary[i + 1][j].rgbtGreen) * (0));

                if (j < width - 1)
                {
                    gxGREEN = gxGREEN + ((temporary[i + 1][j + 1].rgbtGreen) * (1));
                }
            }
            // GREEN Gx
            // End--------------------------------------------------------------------------------------------------------------------

            // GREEN Gy
            // Start__________________________________________________________________________________________________________________
            // If Upper Row Exists
            if (i > 0)
            {
                // Upper Left Pixel
                if (j > 0)
                {
                    gyGREEN = gyGREEN + ((temporary[i - 1][j - 1].rgbtGreen) * (-1));
                }

                // Upper Center Pixel
                gyGREEN = gyGREEN + ((temporary[i - 1][j].rgbtGreen) * (-2));

                // Upper Right Pixel
                if (j < width - 1)
                {
                    gyGREEN = gyGREEN + ((temporary[i - 1][j + 1].rgbtGreen) * (-1));
                }
            }

            // Current row; left, center(current pixel), and right
            if (j > 0)
            {
                gyGREEN = gyGREEN + ((temporary[i][j - 1].rgbtGreen) * (0));
            }

            // Current pixel
            gyGREEN = gyGREEN + ((temporary[i][j].rgbtGreen) * (0));

            if (j < width - 1)
            {
                gyGREEN = gyGREEN + ((temporary[i][j + 1].rgbtGreen) * (0));
            }

            // Lower Row; left, center and right
            if (i < height - 1)
            {
                if (j > 0)
                {
                    gyGREEN = gyGREEN + ((temporary[i + 1][j - 1].rgbtGreen) * (1));
                }

                gyGREEN = gyGREEN + ((temporary[i + 1][j].rgbtGreen) * (2));

                if (j < width - 1)
                {
                    gyGREEN = gyGREEN + ((temporary[i + 1][j + 1].rgbtGreen) * (1));
                }
            }
            // GREEN Gy
            // End___________________________________________________________________________________________________________________________

            // GREEN***********************************************************************************************************************************************

            // RED*************************************************************************************************************************************************

            // RED Gx
            // Start--------------------------------------------------------------------------------------------------------------------------
            // If Upper Row Exists
            if (i > 0)
            {
                // Upper Left Pixel
                if (j > 0)
                {
                    gxRED = gxRED + ((temporary[i - 1][j - 1].rgbtRed) * (-1));
                }

                // Upper Center Pixel
                gxRED = gxRED + ((temporary[i - 1][j].rgbtRed) * (0));

                // Upper Right Pixel
                if (j < width - 1)
                {
                    gxRED = gxRED + ((temporary[i - 1][j + 1].rgbtRed) * (1));
                }
            }

            // Current row; left, center(current pixel), and right
            if (j > 0)
            {
                gxRED = gxRED + ((temporary[i][j - 1].rgbtRed) * (-2));
            }

            // Current pixel
            gxRED = gxRED + ((temporary[i][j].rgbtRed) * (0));

            if (j < width - 1)
            {
                gxRED = gxRED + ((temporary[i][j + 1].rgbtRed) * (2));
            }

            // Lower Row; left, center and right
            if (i < height - 1)
            {
                if (j > 0)
                {
                    gxRED = gxRED + ((temporary[i + 1][j - 1].rgbtRed) * (-1));
                }

                gxRED = gxRED + ((temporary[i + 1][j].rgbtRed) * (0));

                if (j < width - 1)
                {
                    gxRED = gxRED + ((temporary[i + 1][j + 1].rgbtRed) * (1));
                }
            }
            // RED Gx
            // End--------------------------------------------------------------------------------------------------------------------

            // RED Gy
            // Start__________________________________________________________________________________________________________________
            // If Upper Row Exists
            if (i > 0)
            {
                // Upper Left Pixel
                if (j > 0)
                {
                    gyRED = gyRED + ((temporary[i - 1][j - 1].rgbtRed) * (-1));
                }

                // Upper Center Pixel
                gyRED = gyRED + ((temporary[i - 1][j].rgbtRed) * (-2));

                // Upper Right Pixel
                if (j < width - 1)
                {
                    gyRED = gyRED + ((temporary[i - 1][j + 1].rgbtRed) * (-1));
                }
            }

            // Current row; left, center(current pixel), and right
            if (j > 0)
            {
                gyRED = gyRED + ((temporary[i][j - 1].rgbtRed) * (0));
            }

            // Current pixel
            gyRED = gyRED + ((temporary[i][j].rgbtRed) * (0));

            if (j < width - 1)
            {
                gyRED = gyRED + ((temporary[i][j + 1].rgbtRed) * (0));
            }

            // Lower Row; left, center and right
            if (i < height - 1)
            {
                if (j > 0)
                {
                    gyRED = gyRED + ((temporary[i + 1][j - 1].rgbtRed) * (1));
                }

                gyRED = gyRED + ((temporary[i + 1][j].rgbtRed) * (2));

                if (j < width - 1)
                {
                    gyRED = gyRED + ((temporary[i + 1][j + 1].rgbtRed) * (1));
                }
            }
            // RED Gy
            // End___________________________________________________________________________________________________________________________

            // RED***********************************************************************************************************************************************

            BLUE = sqrt(pow(gxBLUE, 2) + pow(gyBLUE, 2));
            GREEN = sqrt(pow(gxGREEN, 2) + pow(gyGREEN, 2));
            RED = sqrt(pow(gxRED, 2) + pow(gyRED, 2));

            BLUE = round(BLUE);
            GREEN = round(GREEN);
            RED = round(RED);

            // Cap values at 255
            if (BLUE > 255)
            {
                BLUE = 255;
            }

            if (GREEN > 255)
            {
                GREEN = 255;
            }

            if (RED > 255)
            {
                RED = 255;
            }

            // Write new mix of colors to current pixel
            image[i][j].rgbtBlue = BLUE;
            image[i][j].rgbtGreen = GREEN;
            image[i][j].rgbtRed = RED;

            // Reset values
            BLUE = 0;
            GREEN = 0;
            RED = 0;

            gxBLUE = 0;
            gyBLUE = 0;

            gxGREEN = 0;
            gyGREEN = 0;

            gxRED = 0;
            gyRED = 0;
        }
    }

    return;
}
