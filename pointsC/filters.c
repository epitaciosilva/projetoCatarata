#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../pointsH/primitive.h"
#include "../pointsH/filters.h"
#include "../pointsH/imageTreatment.h"

void grayFilter(Image *img) {
    int i, j;
    for(i = 0; i < img->height; i++) {
      for(j = 0; j < img->width; j++) {

        //Aplicando o cálculo do píxel cinza.
        int colorGray = img->pixels[i][j].r*0.3  + img->pixels[i][j].g*0.59 + img->pixels[i][j].b*0.11;

        //Salvando os três valores, vermelho, verde e vermelho ao arquivo.
        img->pixels[i][j].r = colorGray;
        img->pixels[i][j].g = colorGray;
        img->pixels[i][j].b = colorGray;
      }
    }
}

void gaussianoFilter(Image *img) {
  int x, y, m, n, newPixel = 0;
  int sumPixels, sumFilter;
  Pixel *pixel;

  int filter[5][5] = {{ 2,  4,  5,  4, 2 },
                      { 4,  9, 12,  9, 4 },
                      { 5, 12, 15, 12, 5 },
                      { 4,  9, 12,  9, 4 },
                      { 2, 4, 5, 4, 2 }};

  for(x = 0; x < img->height; x++) {
    for(y = 0; y < img->width; y++) {
      sumPixels = 0;
      sumFilter = 0;
      for (m = -2; m <= 2; m++) {
        for (n = -2; n <= 2; n++) {
          pixel = pixelReturn(img, x + m, y  + n);

          sumPixels += (pixel->r * filter[m + 2][n + 2]);
          sumFilter += filter[m + 2][n + 2];
        }
      }
      newPixel = sumPixels/sumFilter;

      img->pixels[x][y].r = newPixel;
      img->pixels[x][y].g = newPixel;
      img->pixels[x][y].b = newPixel;
    }
  }
}

void sobelFilter(Image *img, Image *image) {
  int x, y, m, n, newPixel = 0;
  int valueX, valueY;
  Pixel *pixel;
  img->maxPixel = 0;
  int sobelX[3][3] = {{-1, 0, 1},
                      {-2, 0, 2},
                      {-1, 0, 1}};

  int sobelY[3][3] = {{1,  2, 1},
                      {0,  0, 0},
                      {-1,-2,-1}};

  for(x = 0; x < img->height; x++) {
    for(y = 0; y < img->width; y++) {
      valueX = 0;
      valueY = 0;
      for (m = -1; m <= 1; m++) {
        for (n = -1; n <= 1; n++) {
          pixel = pixelReturn(img, x + m, y  + n);

          valueX += (pixel->r * sobelX[m + 1][n + 1]);
          valueY += (pixel->r * sobelY[m + 1][n + 1]);
        }
      }
      newPixel = (int) sqrt(pow(valueX, 2) + pow(valueY, 2));

      image->pixels[x][y].r = newPixel;
      image->pixels[x][y].g = newPixel;
      image->pixels[x][y].b = newPixel;
      image->maxPixel += newPixel;
    }
  }
}

void binaryFilter(Image *img) {
  int i, j;
  int averageSumPixels= img->maxPixel/(img->width*img->height);
  for (i = 0; i < img->height; i++) {
    for (j = 0; j < img->width; j++) {
      if(img->pixels[i][j].r > averageSumPixels) {
        img->pixels[i][j].r = 255;
        img->pixels[i][j].g = 255;
        img->pixels[i][j].b = 255;
      }else {
        img->pixels[i][j].r = 0;
        img->pixels[i][j].g = 0;
        img->pixels[i][j].b = 0;
      }
    }
  }
}
