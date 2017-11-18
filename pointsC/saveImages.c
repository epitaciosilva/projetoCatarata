#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pointsH/primitive.h"
#include "../pointsH/saveImages.h"

void saveImage(Image *img) {
    int i, j;
    FILE *imageFile = fopen("images/finalImage.ppm", "w+");

    //Essas próximas três formam o cabeçalho da image. Tipo, dimensões e o valor máximo de um pixel
    fprintf(imageFile, "P3\n");
    fprintf(imageFile, "%d %d\n", img->width, img->height);
    fprintf(imageFile, "%d\n", img->maxPixel);

    for(i = 0; i<img->height; i++) {
      for(j = 0; j<img->width; j++) {
          //Aloco os pixels no arquivo
          fprintf(imageFile, "%d\n", img->pixels[i][j].r);
          fprintf(imageFile, "%d\n", img->pixels[i][j].g);
          fprintf(imageFile, "%d\n", img->pixels[i][j].b);
      }
    }

    fclose(imageFile);
}
