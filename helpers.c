#include "helpers.h"
#include <math.h>

// Convert image to grayscale
//The function grayscale should take an image and turn it into a black-and-white version of the same image
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            //luu tam vao 1 bien roi gan lai bien do cho ca 3 red green blue
            double gray = round(((float)image[i][j].rgbtRed + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = gray;
        }
    }
    return;
}
// Convert image to sepia
//The function sepia should take an image and turn it into a sepia version of the same image.
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen +
                                 0.189 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            int sepiaGreen = round(0.349  * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen +
                                   0.168 * image[i][j].rgbtBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            int sepiaBlue = round(0.272  * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen +
                                  0.131 * image[i][j].rgbtBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
//The reflect function should take an image and reect it horizontally.
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int a[3] ;
    for (int i = 0; i < height; i ++)
    {
        // chi lap 1 nua thoi
        for (int j = 0; j < width / 2; j ++)
        {
            //gan anh ben trai cho a
            a[0] = image[i][j].rgbtRed ;
            //gan anh ben phai cho ben trai
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed ;
            // gan anh ben trai cho ben phai thong qua a
            image[i][width - j - 1].rgbtRed = a[0] ;
            a[1] = image[i][j].rgbtGreen ;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen ;
            image[i][width - j - 1].rgbtGreen = a[1] ;
            a[2] = image[i][j].rgbtBlue ;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue ;
            image[i][width - j - 1].rgbtBlue = a[2] ;
        }
    }
    return;
}

// Blur image
//the blur function should take an image and turn it into a box-blurred version of  the same image.
int getBlur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_position)
{
    float counter = 0;
    int sum = 0;

    /** Start from 1 row before it and end at 1 row after it- total of 3rows */
    for (int k = i - 1; k < (i + 2); k++)
    {
        /** Start from 1 block before it and end at 1 block after it- total of 3blocks */
        for (int l = j - 1; l < (j + 2); l ++)
        {
            if (k < 0 || l < 0 || k >= height || l >= width)
            {
                continue;
            }
            if (color_position == 0)
            {
                sum += image[k][l].rgbtRed;
            }
            else if (color_position == 1)
            {
                sum += image[k][l].rgbtGreen;
            }
            else
            {
                sum += image[k][l].rgbtBlue;
            }
            counter++;

        }
    }
    return round(sum / counter);
}
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // for (int i = 0; i < height; i ++)
    // {
    //     for (int j = 0; j < height; j ++)
    //     {
    //         if (i < (height - 1) && j < (height - 1) && i > 0 && j > 0)
    //         {
    //             //truong hop 1
    //             double Blur1Red = round(((float)image[i - 1][j - 1].rgbtRed + (float)image[i - 1][j].rgbtRed +
    //                                      (float)image[i - 1][j + 1].rgbtRed + (float)image[i][j + 1].rgbtRed + (float)image[i + 1][j + 1].rgbtRed +
    //                                      (float)image[i + 1][j].rgbtRed + (float)image[i + 1][j - 1].rgbtRed + (float)image[i][j - 1].rgbtRed) / 8.0);
    //             double Blur1Green = round(((float)image[i - 1][j - 1].rgbtGreen + (float)image[i - 1][j].rgbtGreen +
    //                                        (float)image[i - 1][j + 1].rgbtGreen + (float)image[i][j + 1].rgbtGreen + (float)image[i + 1][j + 1].rgbtGreen +
    //                                        (float)image[i + 1][j].rgbtGreen + (float)image[i + 1][j - 1].rgbtGreen + (float)image[i][j - 1].rgbtGreen) / 8.0);
    //             double Blur1Blue = round(((float)image[i - 1][j - 1].rgbtBlue + (float)image[i - 1][j].rgbtBlue +
    //                                       (float)image[i - 1][j + 1].rgbtBlue + (float)image[i][j + 1].rgbtBlue + (float)image[i + 1][j + 1].rgbtBlue +
    //                                       (float)image[i + 1][j].rgbtBlue + (float)image[i + 1][j - 1].rgbtBlue + (float)image[i][j - 1].rgbtBlue) / 8.0);
    //             image[i][j].rgbtRed = Blur1Red;
    //             image[i][j].rgbtGreen = Blur1Green;
    //             image[i][j].rgbtBlue = Blur1Blue;
    //         }
    //         else if (i == 0 && j == 0)
    //         {
    //             //truong hop 2
    //             double Blur2Red = round(((float)image[i][j + 1].rgbtRed + (float)image[i + 1][j + 1].rgbtRed +
    //                                      (float)image[i + 1][j].rgbtRed) / 3.0);
    //             double Blur2Green = round(((float)image[i][j + 1].rgbtGreen + (float)image[i + 1][j + 1].rgbtGreen +
    //                                        (float)image[i + 1][j].rgbtGreen) / 3.0);
    //             double Blur2Blue = round(((float)image[i][j + 1].rgbtBlue + (float)image[i + 1][j + 1].rgbtBlue +
    //                                       (float)image[i + 1][j].rgbtBlue) / 3.0);
    //             image[i][j].rgbtRed = Blur2Red;
    //             image[i][j].rgbtGreen = Blur2Green;
    //             image[i][j].rgbtBlue = Blur2Blue;
    //         }
    //         else if (i == 0 && j == height - 1)
    //         {
    //             //truong hop 3
    //             double Blur3Red = round(((float)image[i][j - 1].rgbtRed + (float)image[i + 1][j - 1].rgbtRed +
    //                                      (float)image[i + 1][j].rgbtRed) / 3.0);
    //             double Blur3Green = round(((float)image[i][j - 1].rgbtGreen + (float)image[i + 1][j - 1].rgbtGreen +
    //                                        (float)image[i + 1][j].rgbtGreen) / 3.0);
    //             double Blur3Blue = round(((float)image[i][j - 1].rgbtBlue + (float)image[i + 1][j - 1].rgbtBlue +
    //                                       (float)image[i + 1][j].rgbtBlue) / 3.0);
    //             image[i][j].rgbtRed = Blur3Red;
    //             image[i][j].rgbtGreen = Blur3Green;
    //             image[i][j].rgbtBlue = Blur3Blue;
    //         }
    //         else if (i == height - 1 && j == 0)
    //         {
    //             //truong hop 4
    //             double Blur4Red = round(((float)image[i - 1][j].rgbtRed + (float)image[i - 1][j + 1].rgbtRed +
    //                                      (float)image[i][j + 1].rgbtRed) / 3.0);
    //             double Blur4Green = round(((float)image[i - 1][j].rgbtGreen + (float)image[i - 1][j + 1].rgbtGreen +
    //                                        (float)image[i][j + 1].rgbtGreen) / 3.0);
    //             double Blur4Blue = round(((float)image[i - 1][j].rgbtBlue + (float)image[i - 1][j + 1].rgbtBlue +
    //                                       (float)image[i][j + 1].rgbtBlue) / 3.0);
    //             image[i][j].rgbtRed = Blur4Red;
    //             image[i][j].rgbtGreen = Blur4Green;
    //             image[i][j].rgbtBlue = Blur4Blue;
    //         }
    //         else if (i == height - 1 && j == height - 1)
    //         {
    //             //truong hop 5
    //             double Blur5Red = round(((float)image[i - 1][j].rgbtRed + (float)image[i - 1][j - 1].rgbtRed +
    //                                      (float)image[i][j - 1].rgbtRed) / 3.0);
    //             double Blur5Green = round(((float)image[i - 1][j].rgbtGreen + (float)image[i - 1][j - 1].rgbtGreen +
    //                                        (float)image[i][j - 1].rgbtGreen) / 3.0);
    //             double Blur5Blue = round(((float)image[i - 1][j].rgbtBlue + (float)image[i - 1][j - 1].rgbtBlue +
    //                                       (float)image[i][j - 1].rgbtBlue) / 3.0);
    //             image[i][j].rgbtRed = Blur5Red;
    //             image[i][j].rgbtGreen = Blur5Green;
    //             image[i][j].rgbtBlue = Blur5Blue;
    //         }
    //         else if (i == 0 && j < height - 1 &&  j > 0)
    //         {
    //             //truong hop 6
    //             double Blur6Red = round(((float)image[i][j - 1].rgbtRed + (float)image[i + 1][j - 1].rgbtRed +
    //                                      (float)image[i + 1][j].rgbtRed + (float)image[i + 1][j + 1].rgbtRed + (float)image[i][j + 1].rgbtRed) / 5.0);
    //             double Blur6Green = round(((float)image[i][j - 1].rgbtGreen + (float)image[i + 1][j - 1].rgbtGreen +
    //                                        (float)image[i + 1][j].rgbtGreen + (float)image[i + 1][j + 1].rgbtGreen + (float)image[i][j + 1].rgbtGreen) / 5.0);
    //             double Blur6Blue = round(((float)image[i][j - 1].rgbtBlue + (float)image[i + 1][j - 1].rgbtBlue +
    //                                       (float)image[i + 1][j].rgbtBlue + (float)image[i + 1][j + 1].rgbtBlue + (float)image[i][j + 1].rgbtBlue) / 5.0);
    //             image[i][j].rgbtRed = Blur6Red;
    //             image[i][j].rgbtGreen = Blur6Green;
    //             image[i][j].rgbtBlue = Blur6Blue;
    //         }
    //         else if (i == height - 1 && j < height - 1 &&  j > 0)
    //         {
    //             //truong hop 7
    //             double Blur7Red = round(((float)image[i][j - 1].rgbtRed + (float)image[i - 1][j - 1].rgbtRed +
    //                                      (float)image[i - 1][j].rgbtRed + (float)image[i - 1][j + 1].rgbtRed + (float)image[i][j + 1].rgbtRed) / 5.0);
    //             double Blur7Green = round(((float)image[i][j - 1].rgbtGreen + (float)image[i - 1][j - 1].rgbtGreen +
    //                                        (float)image[i - 1][j].rgbtGreen + (float)image[i - 1][j + 1].rgbtGreen + (float)image[i][j + 1].rgbtGreen) / 5.0);
    //             double Blur7Blue = round(((float)image[i][j - 1].rgbtBlue + (float)image[i - 1][j - 1].rgbtBlue +
    //                                       (float)image[i - 1][j].rgbtBlue + (float)image[i - 1][j + 1].rgbtBlue + (float)image[i][j + 1].rgbtBlue) / 5.0);
    //             image[i][j].rgbtRed = Blur7Red;
    //             image[i][j].rgbtGreen = Blur7Green;
    //             image[i][j].rgbtBlue = Blur7Blue;
    //         }
    //         else if (j == 0 && i < height - 1 &&  i > 0)
    //         {
    //             //truong hop 8
    //             double Blur8Red = round(((float)image[i - 1][j].rgbtRed + (float)image[i - 1][j + 1].rgbtRed +
    //                                      (float)image[i][j + 1].rgbtRed + (float)image[i + 1][j + 1].rgbtRed + (float)image[i + 1][j].rgbtRed) / 5.0);
    //             double Blur8Green = round(((float)image[i - 1][j].rgbtGreen + (float)image[i - 1][j + 1].rgbtGreen +
    //                                        (float)image[i][j + 1].rgbtGreen + (float)image[i + 1][j + 1].rgbtGreen + (float)image[i + 1][j].rgbtGreen) / 5.0);
    //             double Blur8Blue = round(((float)image[i - 1][j].rgbtBlue + (float)image[i - 1][j + 1].rgbtBlue +
    //                                       (float)image[i][j + 1].rgbtBlue + (float)image[i + 1][j + 1].rgbtBlue + (float)image[i + 1][j].rgbtBlue) / 5.0);
    //             image[i][j].rgbtRed = Blur8Red;
    //             image[i][j].rgbtGreen = Blur8Green;
    //             image[i][j].rgbtBlue = Blur8Blue;
    //         }
    //         else if (j == height - 1 && i < height - 1 &&  i > 0)
    //         {
    //             //truong hop 9
    //             double Blur9Red = round(((float)image[i - 1][j].rgbtRed + (float)image[i - 1][j - 1].rgbtRed +
    //                                      (float)image[i][j - 1].rgbtRed + (float)image[i + 1][j - 1].rgbtRed + (float)image[i + 1][j].rgbtRed) / 5.0);
    //             double Blur9Green = round(((float)image[i - 1][j].rgbtGreen + (float)image[i - 1][j - 1].rgbtGreen +
    //                                        (float)image[i][j - 1].rgbtGreen + (float)image[i + 1][j - 1].rgbtGreen + (float)image[i + 1][j].rgbtGreen) / 5.0);
    //             double Blur9Blue = round(((float)image[i - 1][j].rgbtBlue + (float)image[i - 1][j - 1].rgbtBlue +
    //                                       (float)image[i][j - 1].rgbtBlue + (float)image[i + 1][j - 1].rgbtBlue + (float)image[i + 1][j].rgbtBlue) / 5.0);
    //             image[i][j].rgbtRed = Blur9Red;
    //             image[i][j].rgbtGreen = Blur9Green;
    //             image[i][j].rgbtBlue = Blur9Blue;
    //         }
    //     }
    // }
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
            image[i][j].rgbtRed = getBlur(i, j, height, width, copy, 0);
            image[i][j].rgbtGreen = getBlur(i, j, height, width, copy, 1);
            image[i][j].rgbtBlue = getBlur(i, j, height, width, copy, 2);
        }
    }
    return;
}
