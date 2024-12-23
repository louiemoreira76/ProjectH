#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calcula a média dos valores RGB
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Define todos os valores RGB para a média calculada
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Troca os pixels à esquerda com os da direita
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // Copia a imagem original para um array temporário
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            int count = 0;

            // Itera sobre os pixels ao redor
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int newRow = i + di;
                    int newCol = j + dj;

                    // Verifica se o pixel está dentro dos limites da imagem
                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                    {
                        totalRed += image[newRow][newCol].rgbtRed;
                        totalGreen += image[newRow][newCol].rgbtGreen;
                        totalBlue += image[newRow][newCol].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calcula a média dos valores RGB
            temp[i][j].rgbtRed = round(totalRed / (float)count);
            temp[i][j].rgbtGreen = round(totalGreen / (float)count);
            temp[i][j].rgbtBlue = round(totalBlue / (float)count);
        }
    }

    // Copia os valores do array temporário de volta para a imagem original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // Matrizes de Sobel
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRedX = 0, sumGreenX = 0, sumBlueX = 0;
            int sumRedY = 0, sumGreenY = 0, sumBlueY = 0;

            // Itera sobre os pixels ao redor
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int newRow = i + di;
                    int newCol = j + dj;

                    // Verifica se o pixel está dentro dos limites da imagem
                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                    {
                        RGBTRIPLE pixel = image[newRow][newCol];
                        int weightX = Gx[di + 1][dj + 1];
                        int weightY = Gy[di + 1][dj + 1];

                        sumRedX += weightX * pixel.rgbtRed;
                        sumGreenX += weightX * pixel.rgbtGreen;
                        sumBlueX += weightX * pixel.rgbtBlue;

                        sumRedY += weightY * pixel.rgbtRed;
                        sumGreenY += weightY * pixel.rgbtGreen;
                        sumBlueY += weightY * pixel.rgbtBlue;
                    }
                }
            }

            // Calcula o valor final usando a magnitude
            temp[i][j].rgbtRed = fmin(round(sqrt(sumRedX * sumRedX + sumRedY * sumRedY)), 255);
            temp[i][j].rgbtGreen = fmin(round(sqrt(sumGreenX * sumGreenX + sumGreenY * sumGreenY)), 255);
            temp[i][j].rgbtBlue = fmin(round(sqrt(sumBlueX * sumBlueX + sumBlueY * sumBlueY)), 255);
        }
    }

    // Copia os valores do array temporário de volta para a imagem original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}
