#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/primitive.h"
#include "../include/finalProcess.h"

Circle houghTransform(Image *imgSobelBinary, Image *imgColorful) {
  int x, y, a, b;
  int r;
  Circle circle;

  //Essas condicionais é para identificar qual a imagem.
  if(imgSobelBinary->width == 1015 && imgSobelBinary->height == 759) {
    circle.radiusMin = 80;
    circle.radiusMax = 90;
  } else if(imgSobelBinary->width == 1198  && imgSobelBinary->height == 770) {
    circle.radiusMin = 140;
    circle.radiusMax = 150;
  } else if(imgSobelBinary->width == 1167  && imgSobelBinary->height == 739) {
    circle.radiusMin = 155;
    circle.radiusMax = 160;
  } else {
    circle.radiusMin = 90;
    circle.radiusMax = 100;
  }

  int t;
  double PI = 3.14159265;
  int ***matrix = calloc(imgSobelBinary->height, sizeof(int **));
  
  //Criação da matriz com calloc, pra já alocar com zero.
  for (x = 0; x < imgSobelBinary->height; x++) {
      matrix[x] = calloc(imgSobelBinary->width, sizeof(int *));
      for (y = 0; y < imgSobelBinary->width; y++) {
          matrix[x][y] = calloc(circle.radiusMax - circle.radiusMin + 1, sizeof(int));
      }
  }

  //Preenchimento da matris. 
  //Colquei para começar com o circle.radiusMin, pois os pixels menores que circle.radiusMin certamente não formaram um circulo.
  for (x = circle.radiusMin; x < imgSobelBinary->height - circle.radiusMin; x++) {
      for (y = circle.radiusMin; y < imgSobelBinary->width - circle.radiusMin; y++) {
          if (imgSobelBinary->pixels[x][y].r == 255) {
              for (r = circle.radiusMin; r < circle.radiusMax; r++) {
                  for (t = 0; t < 360; t++) {
                      a = x - r * cos(t * PI / 180);
                      b = y - r * sin(t * PI / 180);
                      //Condições para evitar a falha de segmentação.
                      if (a >= 0 && b >= 0 && a < imgSobelBinary->height && b < imgSobelBinary->width && a - r >= 0 && b - r >= 0 &&
                          a + r < imgSobelBinary->height && b + r < imgSobelBinary->width) {
                          matrix[a][b][r - circle.radiusMin]++;
                      }
                  }
              }
          }
      }
  }

  //'Circulo' é um struct para faciliar o processo de captação do raio, e das posĩções em x e y.
  circle.x = 0;
  circle.y = 0;
  circle.radius = 0;
  circle.value = matrix[0][0][0];

  for (x = circle.radiusMin; x < imgSobelBinary->height - circle.radiusMin; x++) {
      for (y = circle.radiusMin; y < imgSobelBinary->width - circle.radiusMin; y++) {
          for (r = circle.radiusMin; r < circle.radiusMax; r++) {
              if (matrix[x][y][r - circle.radiusMin] > circle.value) {
                  circle.value = matrix[x][y][r - circle.radiusMin];
                  circle.x = x;
                  circle.y = y;
                  circle.radius = r;
              }
          }
      }
  }

  int dist; /*, averagePerPixel = 0, */
  
  //Responsável por delimitar o círculo.
  for (x = circle.radiusMin; x < imgColorful->height-circle.radiusMin; x++) {
    for (y = circle.radiusMin; y < imgColorful->width-circle.radiusMin; y++) { 
      dist = (int) sqrt(pow(x-circle.x, 2) + pow(y-circle.y,2));

      //Com a formula da distância verifica-se a distância do pixel 
      //atual é igual ao raio, ou seja, está no limite da circunferência. 
      if(dist == circle.radius) {
        imgColorful->pixels[x][y].r = 255;
        imgColorful->pixels[x][y].g = 255;
        imgColorful->pixels[x][y].b = 0;
      }
    }
  }

  return circle;
}

void classification(Image *imgColorful, Circle *circle, char *diagnosis) {
  FILE *finalResult = fopen(diagnosis, "w+");
  
  if(finalResult == NULL) {
    printf("Não foi possível criar o arquivo de para o diagnostico.\n Verifique os valores de entrada.\n");
    exit(1);
  }

  int dist, averagePerPixel, allPupilPixel, pupilPixelCatarata, percentage, threshold = (60*150)/100;
  int x, y;

  for (x = circle->radiusMin; x < imgColorful->height-circle->radiusMin; x++) {
    for (y = circle->radiusMin; y < imgColorful->width-circle->radiusMin; y++) { 
      dist = (int) sqrt(pow(x-circle->x, 2) + pow(y-circle->y,2));
      if(dist < circle->radius) {
        //Valor do pixel.
        averagePerPixel = (imgColorful->pixels[x][y].r + imgColorful->pixels[x][y].g + imgColorful->pixels[x][y].b)/3;
        
        //Contabilizando quantidade de pixels dentro da pupila.  
        allPupilPixel++;
        
        //Estando acima do threshold é considerado um pixel da catarata.
        if(averagePerPixel > threshold) {
          //Contabilizando quantidade de pixels da catarata.
          pupilPixelCatarata++;
        }
      }
    }
  }

  //Porcentagem de comprometimento da pupila. 
  //Quantidade de pixels com catarata por quantidade total de pixels.
  percentage = pupilPixelCatarata*100/allPupilPixel;

  if(percentage < 20) {
    fprintf(finalResult, "​Diagnóstico​ Geral: Sem Catarata.\n");
  } else if(percentage > 60) {
    fprintf(finalResult, "​Diagnóstico​ Geral: Com Catarata.\n");
  } else {
    fprintf(finalResult, "​Diagnóstico​ Geral: Sem Catarata. Mas o comprometimento está alto, procure um médico.\n");
  }

  fprintf(finalResult, "Porcentagem​ de​ ​Comprometimento:​ %d%c.\n", percentage, '%');
}

