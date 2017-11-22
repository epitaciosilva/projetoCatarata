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


// void houghTransform(Image * image1, Image * image2) {
//   int x, y, a, b, r;
//   int rmin = 190, rmax = 210, theta;
//   double pi = 3.14159265;

//   int ***matrix = calloc(rmin, sizeof(int**));

//   for(x = 0; x < image1->height; x++) {
//       matrix[x] = calloc(image1->width, sizeof(int*));
//     for(y = 0; y < image1->width; y++) {
//       matrix[x][y] = calloc(rmax-rmin+1, sizeof(int));
//     }
//   }
//   printf("Matriz foi criada\n");
//   for (x = 0; x < image1->height; x++) {
//     for (y = 0; y < image1->width; y++) { 
//       if(image1->pixels[x][y].r == 255) {
//         for (r = rmin; r < rmax; r++) { 
//           for (theta = 0; theta <= 360; theta++) { 
//             a = (int) x - r*cos(theta*pi/180);
//             b = (int) y - r*sin(theta*pi/180);          
//             if(a > 0 && b > 0 && a-r >= 0 && b-r >= 0 && a+r < image1->height && b+r < image1->width) {
//               matrix[a][b][r-rmin] +=1;
//             } 
//           }
//         }
//       }
//     }
//   }
//   printf("Matriz foi preenchida\n");
//   Circulo c = {0,0,0, matrix[0][0][0]};

//   for (x = rmin; x < image1->height-rmin; x++) {
//     for (y = rmin; y < image1->width-rmin; y++) { 
//       for (r = rmin; r < rmax; r++) { 
//         if(matrix[x][y][r-rmin] > c.value) {
//           c.value = matrix[a][b][r-rmin];
//           c.x = x;
//           c.y = y;
//           c.r = r;
//           printf("%d %d %d %d\n", c.value, c.x, c.y, c.r);
//         }
//       }
//     }
//   }
//   printf("Matriz foi encotrado o valor maior %d %d %d\n", c.r, c.x, c.y);
//   for (x = rmin; x < image1->height-rmin; x++) {
//     for (y = rmax; y < image1->width-rmin; y++) { 
//       int dist = (int) sqrt(pow(x-c.x, 2) + pow(y-c.y,2));

//       if(dist != c.r) {
//         image2->pixels[x][y].r = 255;
//         image2->pixels[x][y].g = 255;
//         image2->pixels[x][y].b = 255;
//       }
//     }
//   }
//   printf("Meu deus berg\n");
// }

void houghTransform(Image *img, Image *img2) {
    int x, y, a, b;
    int r, rmin = 190, rmax = 210;
    int t;
    double PI = 3.14159265;
    int ***acumulador = calloc(img->height, sizeof(int **));
    for (x = 0; x < img->height; x++) {
        acumulador[x] = calloc(img->width, sizeof(int *));
        for (y = 0; y < img->width; y++) {
            acumulador[x][y] = calloc(rmax - rmin + 1, sizeof(int));
        }
    }
    for (x = rmin; x < img->height -rmin; x++) {
        for (y = rmin; y < img->width - rmin; y++) {
            if (img->pixels[x][y].r == 255) {
                for (r = rmin; r < rmax; r++) {
                    for (t = 0; t < 360; t++) {
                        a = x - r * cos(t * PI / 180);
                        b = y - r * sin(t * PI / 180);
                        if (a >= 0 && b >= 0 && a < img->height && b < img->width && a - r >= 0 && b - r >= 0 &&
                            a + r < img->height && b + r < img->width) {
                            acumulador[a][b][r - rmin]++;
                        }
                    }
                }
            }
        }
    }
    Circulo c = {0, 0, 0, acumulador[0][0][0]};
    Circulo c1 = {0, 0, 0, acumulador[0][0][0]};
    int soma = 0;
    for (x = rmin; x < img->height - rmin; x++) {
        for (y = rmin; y < img->width - rmin; y++) {
            for (r = rmin; r < rmax; r++) {
                if (acumulador[x][y][r - rmin] > c.valor) {
                    if(soma == 5) {
                      c1.valor = c.valor;
                      c1.x = c.x;
                      c1.y = c.y;
                      c1.r = c.r;
                      soma = -1;
                    }
                    c.valor = acumulador[x][y][r - rmin];
                    c.x = x;
                    c.y = y;
                    c.r = r;
                    soma++;
                }
            }
        }
    }

  for (x = rmin; x < img2->height-rmin; x++) {
    for (y = rmin; y < img2->width-rmin; y++) { 
      int dist = (int) sqrt(pow(x-c.x, 2) + pow(y-c.y,2));
      int dist1 = (int) sqrt(pow(x-c1.x, 2) + pow(y-c1.y,2));
      if(dist == c.r) {
        img2->pixels[x][y].r = 0;
        img2->pixels[x][y].g = 255;
        img2->pixels[x][y].b = 0;
      }
      if(dist1 == c1.r) {
        img2->pixels[x][y].r = 255;
        img2->pixels[x][y].g = 0;
        img2->pixels[x][y].b = 0;
      }
    }
  }
  printf("Meu deus berg\n");
}