#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int a = 0 ; a < height ; a++)
    {
        for (int b = 0 ; b < width ; b++)
        {
            float temp = image[a][b].rgbtRed +  image[a][b].rgbtGreen +  image[a][b].rgbtBlue;
            temp = temp / 3;
            temp = round(temp);
            image[a][b].rgbtRed = temp;
            image[a][b].rgbtGreen = temp;
            image[a][b].rgbtBlue = temp;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
             image[i][j] = temp[i][width-j-1];// fix
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // making a copy
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    // Going throu evry pixel
    float n = 0 ;
    float Green = 0;
    float Red = 0;
    float Blue = 0;
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            n = 0 ;
            Green = 0;
            Red = 0;
            Blue = 0;
            // oing throu all 9 pixels
            for (int k = 0 ; k < 3 ; k++)
            {
                for (int l = 0 ; l < 3 ; l++)
                {
                    if ( i + k - 1  < 0 || i + k - 1 >= height)
                    {
                        continue;
                    }
                    if ( j + l -1 < 0 || j + l - 1 >= width )
                    {
                        continue;
                    }
                    Red = Red + (float)temp[i + k - 1][j + l - 1].rgbtRed;
                    Blue = Blue + (float)temp[i + k - 1][j + l - 1].rgbtBlue;
                    Green = Green + (float)temp[i + k - 1][j + l - 1].rgbtGreen;
                    n++;
                }
            }
            Red = round(Red / n);
            Green = round(Green / n);
            Blue = round(Blue / n);
            image[i][j].rgbtRed = Red;
            image[i][j].rgbtGreen = Green;
            image[i][j].rgbtBlue = Blue;
            }
        }
    return;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
for (int i = 0 ; i < height ; i++ )
{
    for ( int j = 0 ; j < width ; j++)
    {
        temp[i][j] = image [i][j];
    }
}
//initializing gx gy arrays
int Gx[3][3] = {{-1 , 0 , 1 } , { -2 , 0 , -2 } ,{ -1 , 0 , 1 }};
int Gy[3][3] = {{-1 , -2 , -1 } , { 0 , 0 , 0 } ,{ 1 , 2 , 1 }};

for (int i = 0; i < height ; i++)
{
    for (int j = 0; j < width ; j++)
        {
        float Gx_red = 0;
        float Gx_blue = 0;
        float Gx_green = 0;
        float Gy_red = 0;
        float Gy_blue = 0;
        float Gy_green = 0;


        for (int k = 0 ; k < 3 ; k++)
        {
            for (int l = 0 ; l < 3 ; l++)
            {
                if ( i + k - 1  < 0 || i + k - 1 >= height)
                {
                    continue;
                }
                if ( j + l - 1  < 0 || j + l - 1 >= width )
                {
                    continue;
                }
                Gx_red += temp[i+k-1][j+l-1].rgbtRed*Gx[k][l];
                Gx_green += temp[i+k-1][j+l-1].rgbtGreen*Gx[k][l];
                Gx_blue += temp[i+k-1][j+l-1].rgbtBlue*Gx[k][l];
                Gy_red += temp[i+k-1][j+l-1].rgbtRed*Gx[k][l];
                Gy_green += temp[i+k-1][j+l-1].rgbtGreen*Gx[k][l];
                Gy_blue += temp[i+k-1][j+l-1].rgbtBlue*Gx[k][l];
            }
        }
        int red = round(sqrt(Gx_red * Gx_red + Gy_red *Gy_red)); // Here is the mistake !!
        int green = round(sqrt(Gx_green * Gx_green + Gy_green *Gy_green));
        int blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue *Gy_blue));

        if (red > 255)
        {
            red = 255;
        }
        if (green > 255)
        {
            green = 255;
        }
        if (blue > 255)
        {
            blue = 255;
        }
        // Sobel operator

        image[i][j].rgbtRed = red ;
        image[i][j].rgbtGreen = green ;
        image[i][j].rgbtBlue = blue;
    }
}

    return;
}
