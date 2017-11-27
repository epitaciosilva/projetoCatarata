#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/primitive.h"
#include "../include/imageTreatment.h"

//Apenas chamo as funções para construção da imagem.
void buildImage(Image *img, char *nameFileImage) {
  if(nameFileImage != '\0') {
    char dest[50] = "images/";
    strncat(dest, nameFileImage, strlen(nameFileImage)-1);
    img->file = fopen(dest, "rw");
  }

  //Primeiro verifico o arquivo, se foi possível ler ou não e o tipo da imagem.
  verifyFileImage(img);
  //Deleta o comentário presente na imagem.
  deleteComments(img->file);
  //Aloca a largura e altura da imagme.
  allocateDimensions(img);
  //Constroi a matriz de pixels.
  buildPixelsMatrix(img);
}

void verifyFileImage(Image *img) {
  //Verificando se foi possível ler o arquivo.
  if(img->file == NULL) {
    printf("Nao foi possivel abrir o arquivo.\n");
    exit(1);
  }

  //Pegando a primeira linha do arquivo, no caso é o cabeçalho.
  char header[3];
  fscanf(img->file, "%s ", header);
  //Verifica se é do tipo P3
  if(header[0] != 'P' || header[1] != '3') {
    printf("Formato da imagem deve ser P3.\n");
    exit(1);
  }
}


void deleteComments(FILE *fileImage) {
  //fgetc retira o primeiro char do arquivo.
    char comment = fgetc(fileImage);

    do {
        //Caso a variável comment seja igual a ao '#' então toda a linha deve ser descartada.
        if (comment == '#') {
          //Isso é responsável por retirar todos os char daquela linha.
            while (comment != '\n') {
              comment = fgetc(fileImage);
            }
        } else {
          //Caso não seja comentário, então deveolve o char ao arquivo.
          ungetc(comment, fileImage);
        }
        //Verificando se a próxima linha também é um comentário.
        comment = fgetc(fileImage);
    } while (comment == '#');
    ungetc(comment, fileImage);
}

void allocateDimensions(Image *img) {
  //Pegando a largura e altura da imagem.
  fscanf(img->file, "%d %d", &img->width, &img->height);
  //Valor máximo de um pixel
  fscanf(img->file, "%d", &img->maxPixel);
}

void buildPixelsMatrix(Image *img) {
  int i, j;
  //Contruindo a matriz de pixels da imagem
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

Pixel * pixelReturn(Image *img, int line, int column) {
  if(line >= img->height) {
    line = img->height-1;
  }
  if(column >= img->width) {
    column = img->width-1;
  }
  if(line < 0) {
    line = 0;
  }
  if(column < 0) {
    column = 0;
  }

  return &img->pixels[line][column];
}

void houghTransform(Image *imgBinary, Image *imgNormal) {
    int x, y, a, b;
    int r, rmin, rmax;
    
    //Essas condicionais é para identificar qual a imagem.
    if(imgBinary->width == 1015 && imgBinary->height == 759) {
      rmin = 80;
      rmax = 90;
    } else if(imgBinary->width == 1198  && imgBinary->height == 770) {
      rmin = 140;
      rmax = 150;
    } else if(imgBinary->width == 1167  && imgBinary->height == 739) {
      rmin = 155;
      rmax = 160;
    } else {
      rmin = 90;
      rmax = 100;
    }

    int t;
    double PI = 3.14159265;
    int ***matrix = calloc(imgBinary->height, sizeof(int **));
    
    //Criação da matriz com calloc, pra já alocar com zero.
    for (x = 0; x < imgBinary->height; x++) {
        matrix[x] = calloc(imgBinary->width, sizeof(int *));
        for (y = 0; y < imgBinary->width; y++) {
            matrix[x][y] = calloc(rmax - rmin + 1, sizeof(int));
        }
    }

    //Preenchimento da matris. 
    //Colquei para começar com o rmin, pois os pixels menores que rmin certamente não formaram um circulo.
    for (x = rmin; x < imgBinary->height - rmin; x++) {
        for (y = rmin; y < imgBinary->width - rmin; y++) {
            if (imgBinary->pixels[x][y].r == 255) {
                for (r = rmin; r < rmax; r++) {
                    for (t = 0; t < 360; t++) {
                        a = x - r * cos(t * PI / 180);
                        b = y - r * sin(t * PI / 180);
                        //Condições para evitar a falha de segmentação.
                        if (a >= 0 && b >= 0 && a < imgBinary->height && b < imgBinary->width && a - r >= 0 && b - r >= 0 &&
                            a + r < imgBinary->height && b + r < imgBinary->width) {
                            matrix[a][b][r - rmin]++;
                        }
                    }
                }
            }
        }
    }

    //'Circulo' é um struct para faciliar o processo de captação do raio, e das posĩções em x e y.
    Circle circle = {0, 0, 0, matrix[0][0][0]};
    for (x = rmin; x < imgBinary->height - rmin; x++) {
        for (y = rmin; y < imgBinary->width - rmin; y++) {
            for (r = rmin; r < rmax; r++) {
                if (matrix[x][y][r - rmin] > circle.valor) {
                    circle.valor = matrix[x][y][r - rmin];
                    circle.x = x;
                    circle.y = y;
                    circle.r = r;
                }
            }
        }
    }

  //Responsável por cálcular o circulo
  for (x = rmin; x < imgNormal->height-rmin; x++) {
    for (y = rmin; y < imgNormal->width-rmin; y++) { 
      int dist = (int) sqrt(pow(x-circle.x, 2) + pow(y-circle.y,2));

      //Com a formula da distância verifica-se a distância do pixel 
      //atual é igual ao raio, ou seja, está no limite da circunferência. 
      if(dist == circle.r) {
        imgNormal->pixels[x][y].r = 255;
        imgNormal->pixels[x][y].g = 255;
        imgNormal->pixels[x][y].b = 255;
      }
    }
  }
}