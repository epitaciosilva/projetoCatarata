#include <stdio.h>
#include <string.h>
#include "../pointsH/primitive.h"
#include "../pointsH/filters.h"

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
