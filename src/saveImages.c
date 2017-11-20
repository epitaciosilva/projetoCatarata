#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/primitive.h"
#include "../include/saveImages.h"

void saveImage(Image *img, char *nameFileImage) {
    int i, j;
    char dest[100] = "images/";
    strncat(dest, nameFileImage, strlen(nameFileImage));
    FILE *imageFile = fopen(dest, "w+");

    //Essas próximas três linhas formam o cabeçalho da imagem.
    //Tipo, dimensões e o valor máximo de um pixel respectivamente.
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
