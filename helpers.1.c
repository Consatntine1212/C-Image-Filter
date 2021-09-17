#include "helpers.h"
#include <math.h>//delete

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int a = 0 ; a < height ; a++)
    {
        for (int b = 0 ; b < width ; b++)
        {
            int temp = image[a][b].rgbtRed +  image[a][b].rgbtGreen +  image[a][b].rgbtBlue;
            temp = temp / 3;
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
    int tempr[width];
    int tempg[width];
    int tempb[width];
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            tempr[j] = image[i][j].rgbtRed;
            tempg[j] = image[i][j].rgbtGreen;
            tempb[j] = image[i][j].rgbtBlue;
        }
        for (int j = 0 ; j < width ; j++)
        {
            image[i][j].rgbtRed = tempr[width - j];
            image[i][j].rgbtGreen = tempg[width - j];
            image[i][j].rgbtBlue = tempb[width - j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int temp = 0 ;
    int tempR[height][width];
    int tempG[height][width];
    int tempB[height][width];
    for (int i = 0 ; i < height ; i ++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            // upper left corner
            if (( i == 0 ) && ( j == 0))
            {
                tempR[i][j] = image[i][j].rgbtRed + image[i+1][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j+1].rgbtRed;
                tempG[i][j] = image[i][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j+1].rgbtGreen;
                tempB[i][j] = image[i][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j+1].rgbtBlue;
                tempR[i][j] = tempR[i][j] / 4;
                tempG[i][j] = tempG[i][j] / 4;
                tempB[i][j] = tempB[i][j] / 4;
            }
            // upper right corner
            else if (( i == 0 ) && ( j == width ))
            {
                tempR[i][j] = image[i][j].rgbtRed + image[i+1][j].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed;
                tempG[i][j] = image[i][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen;
                tempB[i][j] = image[i][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue;
                tempR[i][j] = tempR[i][j] / 4;
                tempG[i][j] = tempG[i][j] / 4;
                tempB[i][j] = tempB[i][j] / 4;
            }
            // down left corner
            else if (( i == height ) && ( j == 0 ))
            {
                tempR[i][j] = image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j+1].rgbtRed;
                tempG[i][j] = image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i-1][j+1].rgbtGreen;
                tempB[i][j] = image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j+1].rgbtBlue;
                tempR[i][j] = tempR[i][j] / 4;
                tempG[i][j] = tempG[i][j] / 4;
                tempB[i][j] = tempB[i][j] / 4;
            }
            // down right corner
            else if (( i == height ) && ( j == width ))
            {
                tempR[i][j] = image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j-1].rgbtRed;
                tempG[i][j] = image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j-1].rgbtGreen;
                tempB[i][j] = image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j-1].rgbtBlue;
                tempR[i][j] = tempR[i][j] / 4;
                tempG[i][j] = tempG[i][j] / 4;
                tempB[i][j] = tempB[i][j] / 4;
            }
            // ferst row
            else if ( i == 0  &&  j != 0  &&  j != width)
            {
                tempR[i][j] = image[i][j].rgbtRed + image[i+1][j].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j+1].rgbtRed;
                tempG[i][j] = image[i][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j+1].rgbtGreen;
                tempB[i][j] = image[i][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j+1].rgbtBlue;
                tempR[i][j] = tempR[i][j] / 6;
                tempG[i][j] = tempG[i][j] / 6;
                tempB[i][j] = tempB[i][j] / 6;
            }
            // last row
            else if ( i == height  &&  j != 0  &&  j != width)
            {
                tempR[i][j] = image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j-1].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j+1].rgbtRed;
                tempG[i][j] = image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i][j+1].rgbtGreen + image[i-1][j+1].rgbtGreen;
                tempB[i][j] = image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j+1].rgbtBlue;
                tempR[i][j] = tempR[i][j] / 6;
                tempG[i][j] = tempG[i][j] / 6;
                tempB[i][j] = tempB[i][j] / 6;
            }
            // ferst Colume
            else if ( j == 0  &&  i != 0  &&  i != height)
            {
                tempR[i][j] = image[i][j].rgbtRed + image[i+1][j].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j+1].rgbtRed + image[i-1][j].rgbtRed + image[i+1][j+1].rgbtRed;
                tempG[i][j] = image[i][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i-1][j].rgbtGreen + image[i+1][j+1].rgbtGreen;
                tempB[i][j] = image[i][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i-1][j].rgbtBlue + image[i+1][j+1].rgbtBlue;
                tempR[i][j] = tempR[i][j] / 6;
                tempG[i][j] = tempG[i][j] / 6;
                tempB[i][j] = tempB[i][j] / 6;
            }
            //Last colume
            else if ( j == width  &&  i != 0  &&  i != height)
            {
                tempR[i][j] = image[i][j].rgbtRed + image[i+1][j].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i+1][j-1].rgbtRed;
                tempG[i][j] = image[i][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i+1][j-1].rgbtGreen;
                tempB[i][j] = image[i][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i+1][j-1].rgbtBlue;
                tempR[i][j] = tempR[i][j] / 6;
                tempG[i][j] = tempG[i][j] / 6;
                tempB[i][j] = tempB[i][j] / 6;
            }
            // Rest
            else if ( i != 0  &&  i != height &&  j != 0  &&  j != width)
            {
                tempR[i][j] = image[i][j].rgbtRed + image[i+1][j].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j+1].rgbtRed + image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed;
                tempG[i][j] = image[i][j].rgbtGreen + image[i+1][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen;
                tempB[i][j] = image[i][j].rgbtBlue + image[i+1][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue;
                tempR[i][j] = tempR[i][j] / 9;
                tempG[i][j] = tempG[i][j] / 9;
                tempB[i][j] = tempB[i][j] / 9;
            }
        }
    }
    for (int i = 0 ; i < height ; i ++)
    {
        for (int j = 0 ; j < width ; j ++)
        {
            image[i][j].rgbtRed = tempR[i][j];
            image[i][j].rgbtGreen = tempG[i][j];
            image[i][j].rgbtBlue = tempB[i][j];
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

for ( int i = 0; i < height ; i ++ )
{
    for ( int j = 0 ; j < width; j++)
    {
        float Gx_red = 0;
        float Gx_blue = 0;
        float Gx_green = 0;
        float Gy_red = 0;
        float Gy_blue = 0;
        float Gy_green = 0;

        for ( int a = -1; a < 2 ; a++)
        {
            for ( int b = -1; b < 2 ; b++)
            {
                if ( i + a < 0 || i + a >= height)
                {
                    continue;
                }
                if ( j+ 1 < 0 || j + b >= width)
                {
                    continue;
                }
                Gx_red += temp[i+a][j+b].rgbtRed*Gx[a+1][b+1];
                Gx_green += temp[i+a][j+b].rgbtGreen*Gx[a+1][b+1];
                Gx_blue += temp[i+a][j+b].rgbtBlue*Gx[a+1][b+1];
                Gy_red += temp[i+a][j+b].rgbtRed*Gy[a+1][b+1];
                Gy_green += temp[i+a][j+b].rgbtGreen*Gy[a+1][b+1];
                Gy_blue += temp[i+a][j+b].rgbtBlue*Gy[a+1][b+1];
            }
        }


        //
        int red = round(sqrt(Gx_red * Gx_red + Gy_red *Gy_red));
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

        image[i][j].rgbtRed = red ;
        image[i][j].rgbtGreen = green ;
        image[i][j].rgbtBlue = blue;
    }
}

    return;
}
