#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE *ptr;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            ptr = &image[i][j];
            int sum = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;

            int avg = round((float)sum/3);
            ptr->rgbtRed = avg;
            ptr->rgbtGreen = avg;
            ptr->rgbtBlue = avg;
        }
    }

    return;

}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE *ptr, tmp[height][width];

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            tmp[i][j].rgbtRed = image[i][j].rgbtRed;
            tmp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            tmp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            ptr = &image[i][j];

            ptr->rgbtRed = tmp[i][width-j-1].rgbtRed;
            ptr->rgbtGreen = tmp[i][width-j-1].rgbtGreen;
            ptr->rgbtBlue = tmp[i][width-j-1].rgbtBlue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{


    RGBTRIPLE *ptr, tmp[height][width];
    int rSum, gSum, bSum, counter;
    //int rTest, gTest, bTest;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            tmp[i][j].rgbtRed = image[i][j].rgbtRed;
            tmp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            tmp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            ptr = &image[i][j];
            rSum = gSum = bSum = 0;

            //adds the center pixel
            rSum += image[i][j].rgbtRed;
            gSum += image[i][j].rgbtGreen;
            bSum += image[i][j].rgbtBlue;
            counter = 1;

            //EVERYTHING ABOVE WORKS
            /*
            order of the summing
            [3, 8, 4]
            [7, 0, 5]
            [2, 6, 1]
            */

            //checks if the corners are values in the array and adds that corner to the sum
            if(i + 1 <= height && j + 1 <= width){
                if(i != width - 1 && j != width - 1){
                    rSum += tmp[i+1][j+1].rgbtRed;
                    gSum += tmp[i+1][j+1].rgbtGreen;
                    bSum += tmp[i+1][j+1].rgbtBlue;
                    counter += 1;
                }
            }
            if(i + 1 <= height && j - 1 >= 0){
                if(i != height - 1){
                    rSum += tmp[i+1][j-1].rgbtRed;
                    gSum += tmp[i+1][j-1].rgbtGreen;
                    bSum += tmp[i+1][j-1].rgbtBlue;
                    counter += 1;
                }
            }
            if(i - 1 >= 0 && j - 1 >= 0){
                rSum += tmp[i-1][j-1].rgbtRed;
                gSum += tmp[i-1][j-1].rgbtGreen;
                bSum += tmp[i-1][j-1].rgbtBlue;
                counter += 1;
            }
            if(i - 1 >= 0 && j + 1 <= width){
                if(j != width - 1){
                    rSum += tmp[i-1][j+1].rgbtRed;
                    gSum += tmp[i-1][j+1].rgbtGreen;
                    bSum += tmp[i-1][j+1].rgbtBlue;
                    counter += 1;
                }
            }
            //checks if the edges are values in the array and adds that edge to the sum
            //Right
            if(j + 1 <= width){
                if(j != width - 1){
                    rSum += tmp[i][j+1].rgbtRed;
                    gSum += tmp[i][j+1].rgbtGreen;
                    bSum += tmp[i][j+1].rgbtBlue;
                    counter += 1;
                }
            }
            //Bottom
            if(i + 1 <= height){
                if(i != height - 1){
                    rSum += tmp[i+1][j].rgbtRed;
                    gSum += tmp[i+1][j].rgbtGreen;
                    bSum += tmp[i+1][j].rgbtBlue;
                    counter += 1;
                }
            }
            //Left
            if(j - 1 >= 0){
                rSum += tmp[i][j-1].rgbtRed;
                gSum += tmp[i][j-1].rgbtGreen;
                bSum += tmp[i][j-1].rgbtBlue;
                counter += 1;
            }
            //Top
            if(i - 1 >= 0){
                rSum += tmp[i-1][j].rgbtRed;
                gSum += tmp[i-1][j].rgbtGreen;
                bSum += tmp[i-1][j].rgbtBlue;
                counter += 1;
            }
            ptr->rgbtRed = round(rSum/(float)counter);
            ptr->rgbtGreen = round(gSum/(float)counter);
            ptr->rgbtBlue = round(bSum/(float)counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //TO DO LIST
    //Multiply a 3x3 box around the pixel by the kernels
    //Multiply all null pixels by 0

    //defining kernels
    int MatrixGx[3][3] = {{ 1, 0,-1}, { 2, 0,-2}, { 1, 0,-1}};
    int MatrixGy[3][3] = {{ 1, 2, 1}, { 0, 0, 0}, {-1,-2,-1}};
    RGBTRIPLE *ptr, tmp[height][width];

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            tmp[i][j] = image[i][j];
        }
    }

    for(int h = 0; h < height; h++){
        for(int w = 0; w < width; w++){
            //MAKE SURE YOU ARE ACCESSING VALUES FROM THE TMP NOT THE POINTER
            ptr = &image[h][w];
            //RGB matrix
            int Gx[3] = {0,0,0};
            int Gy[3] = {0,0,0};
            int G[3] = {0,0,0};

            for(int i = -1; i < 2; i++){
                for(int j = -1; j < 2; j++){
                    if(h + i >= 0 && h + i < height && w + j >= 0 && w + j < width){
                        //int r = tmp[h+i][w+j].rgbtRed;
                        Gx[0] += tmp[h+i][w+j].rgbtRed * MatrixGx[i+1][j+1];
                        Gy[0] += tmp[h+i][w+j].rgbtRed * MatrixGy[i+1][j+1];
                        Gx[1] += tmp[h+i][w+j].rgbtGreen * MatrixGx[i+1][j+1];
                        Gy[1] += tmp[h+i][w+j].rgbtGreen * MatrixGy[i+1][j+1];
                        Gx[2] += tmp[h+i][w+j].rgbtBlue * MatrixGx[i+1][j+1];
                        Gy[2] += tmp[h+i][w+j].rgbtBlue * MatrixGy[i+1][j+1];
                    }
                }
            }

            G[0] = round(sqrt(Gx[0] * Gx[0] + Gy[0] * Gy[0]));
            G[1] = round(sqrt(Gx[1] * Gx[1] + Gy[1] * Gy[1]));
            G[2] = round(sqrt(Gx[2] * Gx[2] + Gy[2] * Gy[2]));


            if(G[0] > 255){
                G[0] = 255;
            }
            if(G[1] > 255){
                G[1] = 255;
            }
            if(G[2] > 255){
                G[2] = 255;
            }

            ptr->rgbtRed = (int)G[0];
            ptr->rgbtGreen = (int)G[1];
            ptr->rgbtBlue = (int)G[2];

            // ptr->rgbtRed = red;
            // ptr->rgbtGreen = green;
            // ptr->rgbtBlue = blue;
        }
    }
    return;
}

