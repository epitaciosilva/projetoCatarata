#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "primitive.h"
#include "readImage.h"
#include "saveImages.h"

void saveImageNormal(Image *img) {
    int i, j;
    FILE *imageFile = fopen("images/normalImageSaved.ppm", "w+");
    //Essas próximas três forma o cabeçalho da image. Tipo, dimensões e o valor máximo de um pixel
    fprintf(imageFile, "P3\n");
    fprintf(imageFile, "%d %d\n", img->width, img->height);
    fprintf(imageFile, "%d\n", img->maxPixel);

    for(i = 0; i<img->height-1; i++) {
      for(j = 0; j<img->width; j++) {
          //Aloco os pixels no arquivo
          fprintf(imageFile, "%d\n", img->pixels[i][j].r);
          fprintf(imageFile, "%d\n", img->pixels[i][j].g);
          fprintf(imageFile, "%d\n", img->pixels[i][j].b);
      }
    }

    fclose(imageFile);
}

void saveImageColorToGray(Image *img) {
    int i, j;
    FILE *file = fopen("images/savedImageWithGrayColor", "w+");
    
    //Essas próximas três forma o cabeçalho da image. Tipo, dimensões e o valor máximo de um pixel
    fprintf(file, "P3\n");
    fprintf(file, "%d %d\n", img->width, img->height);
    fprintf(file, "%d\n", img->maxPixel);
    
    for(i = 0; i<img->height; i++) {
      for(j = 0; j<img->width; j++) {
        //Aplico o cálculo paa deixar o pixel cinza. 
        int colorGray = img->pixels[i][j].r*0.3  + img->pixels[i][j].g*0.59 + img->pixels[i][j].b*0.11;
        
        //Aloca os três valores, vermelho, verde e vermelho ao arquivo.
        fprintf(file, "%d\n", colorGray);
        fprintf(file, "%d\n", colorGray);
        fprintf(file, "%d\n", colorGray);
      }
    }

    fclose(file);
}
