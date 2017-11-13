#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "primitive.h"
#include "readImage.h"
#include "saveImages.h"

//Apenas chamo as funções para construção da imagem.
void buildImage(Image *img) {
  img->file = fopen("images/Normal2.ppm", "rw");
  //Primeiro verifico o arquivo, se foi possível ler ou não e o tipo da imagem.  
  verifyFileImage(img);
  //Deleta o comentário presente na imagem.
  deleteComments(img->file);
  //Aloca a largura e altura da imagme.
  allocateDimensions(img);
  //Constroi a matriz de pixels.
  buildPixelsMatrix(img);
}

void buildPixelsMatrix(Image *img) {
  int i, j;
  //Controi a matriz de pixels da imagem
  img->pixels = malloc(img->height * sizeof(Pixel*));

  for(i = 0;  i < img->height; i++) {
    img->pixels[i] = malloc(img->width * sizeof(Pixel));
  }

  //Lê todos os valores do arquivo e e preenche toda a matriz de pixel
  for(i = 0; i < img->height; i++) {
    for(j = 0; j < img->width; j++) {
      fscanf(img->file, "%d", &img->pixels[i][j].r);
      fscanf(img->file, "%d", &img->pixels[i][j].g);
      fscanf(img->file, "%d", &img->pixels[i][j].b);
    }
  } 
}

void deleteComments(FILE *fileImage) {
  //fgetc retira o primeiro char do arquivo.
    char comment = fgetc(fileImage);

    do {
        //Caso o comment seja igual a ao '#' então toda a linha deve ser descartada.
        if (comment == '#') {
          //Isso é responsável por retirar todos os char daquela linha.
            while (comment != '\n') {
              comment = fgetc(fileImage);
            }
        } else {
          //Caso não seja comentário, então deveolve o char ao arquivo.
          ungetc(comment, fileImage);
        }
        //Verifica se a próxima linha também é um comentário.
        comment = fgetc(fileImage);
    } while (comment == '#');
    ungetc(comment, fileImage);
}

void allocateDimensions(Image *img) {
  //Pega a largura e altura da imagem.
  fscanf(img->file, "%d %d", &img->width, &img->height);
  //Valor máximo de um pixel
  fscanf(img->file, "%d", &img->maxPixel);
}

void verifyFileImage(Image *img) {
  //Verificar se foi possível ler o arquivo.
  if(img->file == NULL) {
    printf("Nao foi possivel abrir o arquivo.\n");
    exit(1);
  }

  //Pega a primeira linha do arquivo, no caso é o cabeçalho.
  char header[3];
  fscanf(img->file, "%s ", header);
  //Verifica se é do tipo P3
  if(header[0] != 'P' || header[1] != '3') {
    printf("Formato da imagem deve ser P3.\n");
    exit(1);
  }
}
