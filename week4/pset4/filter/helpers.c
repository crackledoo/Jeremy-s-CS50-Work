#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            double gray = image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed;
            gray = gray / 3;
            image[h][w].rgbtBlue = round(gray);
            image[h][w].rgbtGreen = round(gray);
            image[h][w].rgbtRed = round(gray);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    double reflectionwidth = (width) / 2;
    int wideness = round(reflectionwidth);
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < reflectionwidth; w++)
        {
            RGBTRIPLE tmp = image[h][w];
            image[h][w] = image[h][(width-1)-w];
            image[h][(width-1)-w] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagecopy[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int c = 0;
            int sumrgbtBlue = 0;
            int sumrgbtGreen = 0;
            int sumrgbtRed = 0;
            //top lane of blur box
            if (h < height - 1)
            {

                //top left of blur box
                if (w > 0)
                {
                    sumrgbtBlue += image[h+1][w-1].rgbtBlue;
                    sumrgbtGreen += image[h+1][w-1].rgbtGreen;
                    sumrgbtRed += image[h+1][w-1].rgbtRed;
                    c++;
                }

                //top middle of blur box
                sumrgbtBlue += image[h+1][w].rgbtBlue;
                sumrgbtGreen += image[h+1][w].rgbtGreen;
                sumrgbtRed += image[h+1][w].rgbtRed;
                c++;

                //top right of blur box
                if (w < width - 1)
                {
                    sumrgbtBlue += image[h+1][w+1].rgbtBlue;
                    sumrgbtGreen += image[h+1][w+1].rgbtGreen;
                    sumrgbtRed += image[h+1][w+1].rgbtRed;
                    c++;
                }
            }
            //middle lane of blur box

            //middle left of blur box
            if (w > 0)
            {
                sumrgbtBlue += image[h][w-1].rgbtBlue;
                sumrgbtGreen += image[h][w-1].rgbtGreen;
                sumrgbtRed += image[h][w-1].rgbtRed;
                c++;
            }

            //middle middle of blur box
            sumrgbtBlue += image[h][w].rgbtBlue;
            sumrgbtGreen += image[h][w].rgbtGreen;
            sumrgbtRed += image[h][w].rgbtRed;
            c++;

            //midde right of blur box
            if (w < width - 1)
            {
                sumrgbtBlue += image[h][w+1].rgbtBlue;
                sumrgbtGreen += image[h][w+1].rgbtGreen;
                sumrgbtRed += image[h][w+1].rgbtRed;
                c++;
            }

            //bottom lane of blur box
            if (h > 0)
            {
                //bottom left of blur box

                if (w > 0)
                {
                    sumrgbtBlue += image[h-1][w-1].rgbtBlue;
                    sumrgbtGreen += image[h-1][w-1].rgbtGreen;
                    sumrgbtRed += image[h-1][w-1].rgbtRed;
                    c++;
                }



                //bottom middle of blur box
                sumrgbtBlue += image[h-1][w].rgbtBlue;
                sumrgbtGreen += image[h-1][w].rgbtGreen;
                sumrgbtRed += image[h-1][w].rgbtRed;
                c++;

                //bottom right of blur box
                if (w < width - 1)
                {
                    sumrgbtBlue += image[h-1][w+1].rgbtBlue;
                    sumrgbtGreen += image[h-1][w+1].rgbtGreen;
                    sumrgbtRed += image[h-1][w+1].rgbtRed;
                    c++;
                }
            }
            //calculate average
            double Blue = (double) sumrgbtBlue / c;
            double Green = (double) sumrgbtGreen / c;
            double Red = (double) sumrgbtRed / c;

            imagecopy[h][w].rgbtBlue = round(Blue);
            imagecopy[h][w].rgbtGreen = round(Green);
            imagecopy[h][w].rgbtRed = round(Red);
        }
    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = imagecopy[h][w];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imagecopy[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int sumGxBlue = 0;
            int sumGxGreen = 0;
            int sumGxRed = 0;

            int sumGyBlue = 0;
            int sumGyGreen = 0;
            int sumGyRed = 0;

            //G x

            //Left side of Gx
            if (w > 0)
            {
                //top left of Gx
                if (h > 0)
                {
                    sumGxBlue += (image[h-1][w-1].rgbtBlue * -1);
                    sumGxGreen += (image[h-1][w-1].rgbtGreen * -1);
                    sumGxRed += (image[h-1][w-1].rgbtRed * -1);
                }

                //middle left of Gx
                sumGxBlue += (image[h][w-1].rgbtBlue * -2);
                sumGxGreen += (image[h][w-1].rgbtGreen * -2);
                sumGxRed += (image[h][w-1].rgbtRed * -2);

                //bottom left of Gx
                if (h < height - 1)
                {
                    sumGxBlue += (image[h+1][w-1].rgbtBlue * -1);
                    sumGxGreen += (image[h+1][w-1].rgbtGreen * -1);
                    sumGxRed += (image[h+1][w-1].rgbtRed * -1);
                }
            }

            //right side of Gx
            if (w < width- 1)
            {
                //top right of Gx
                if (h > 0)
                {
                    sumGxBlue += (image[h-1][w+1].rgbtBlue);
                    sumGxGreen += (image[h-1][w+1].rgbtGreen);
                    sumGxRed += (image[h-1][w+1].rgbtRed);
                }

                //middle right of Gx
                sumGxBlue += (image[h][w+1].rgbtBlue * 2);
                sumGxGreen += (image[h][w+1].rgbtGreen * 2);
                sumGxRed += (image[h][w+1].rgbtRed * 2);

                //bottom right of Gx
                if (h < height - 1)
                {
                    sumGxBlue += (image[h+1][w+1].rgbtBlue);
                    sumGxGreen += (image[h+1][w+1].rgbtGreen);
                    sumGxRed += (image[h+1][w+1].rgbtRed);
                }
            }

            // G y

            //top side of Gy
            if (h > 0)
            {
                //top left of Gy
                if (w > 0)
                {
                    sumGyBlue += (image[h-1][w-1].rgbtBlue * -1);
                    sumGyGreen += (image[h-1][w-1].rgbtGreen * -1);
                    sumGyRed += (image[h-1][w-1].rgbtRed * -1);
                }

                //top middle of Gy
                sumGyBlue += (image[h-1][w].rgbtBlue * -2);
                sumGyGreen += (image[h-1][w].rgbtGreen * -2);
                sumGyRed += (image[h-1][w].rgbtRed * -2);

                //top right of Gx
                if (w < width - 1)
                {
                    sumGyBlue += (image[h-1][w+1].rgbtBlue * -1);
                    sumGyGreen += (image[h-1][w+1].rgbtGreen * -1);
                    sumGyRed += (image[h-1][w+1].rgbtRed * -1);
                }
            }

            //bottom side of Gy
            if (h < height - 1)
            {
                //bottom left of Gy
                if (w > 0)
                {
                    sumGyBlue += (image[h+1][w-1].rgbtBlue);
                    sumGyGreen += (image[h+1][w-1].rgbtGreen);
                    sumGyRed += (image[h+1][w-1].rgbtRed);
                }

                //bottom middle of Gy
                sumGyBlue += (image[h+1][w].rgbtBlue * 2);
                sumGyGreen += (image[h+1][w].rgbtGreen * 2);
                sumGyRed += (image[h+1][w].rgbtRed * 2);

                //bottom right of Gx
                if (w < width - 1)
                {
                    sumGyBlue += (image[h+1][w+1].rgbtBlue);
                    sumGyGreen += (image[h+1][w+1].rgbtGreen);
                    sumGyRed += (image[h+1][w+1].rgbtRed);
                }
            }
            sumGxBlue *= sumGxBlue;
            sumGxGreen *= sumGxGreen;
            sumGxRed *= sumGxRed;

            sumGyBlue *= sumGyBlue;
            sumGyGreen *= sumGyGreen;
            sumGyRed *= sumGyRed;

            double Blue = sqrt(sumGxBlue + sumGyBlue);
            double Green = sqrt(sumGxGreen + sumGyGreen);
            double Red = sqrt(sumGxRed + sumGyRed);

            if (Blue > 255)
                Blue = 255;
            if (Blue < 0)
                Blue *= -1;
            if (Green > 255)
                Green = 255;
            if (Green < 0)
                Green *= -1;
            if (Red > 255)
                Red = 255;
            if (Red < 0)
                Red *= -1;




            imagecopy[h][w].rgbtBlue = round(Blue);
            imagecopy[h][w].rgbtGreen = round(Green);
            imagecopy[h][w].rgbtRed = round(Red);
        }
    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = imagecopy[h][w];
        }
    }
    return;
}
