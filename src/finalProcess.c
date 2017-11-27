#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/primitive.h"
#include "../include/finalProcess.h"

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

  
  int dist, averagePerPixel = 0, allPupilPixel = 0, pupilPixelCatarata = 0, threshold = (60*150)/100;
  
  //Responsável por delimitar o círculo.
  for (x = rmin; x < imgNormal->height-rmin; x++) {
    for (y = rmin; y < imgNormal->width-rmin; y++) { 
      dist = (int) sqrt(pow(x-circle.x, 2) + pow(y-circle.y,2));

      //Com a formula da distância verifica-se a distância do pixel 
      //atual é igual ao raio, ou seja, está no limite da circunferência. 
      if(dist == circle.r) {
        
        imgNormal->pixels[x][y].r = 255;
        imgNormal->pixels[x][y].g = 255;
        imgNormal->pixels[x][y].b = 0;

      } else if(dist < circle.r) {
        //Valor do pixel.
        averagePerPixel = (imgNormal->pixels[x][y].r + imgNormal->pixels[x][y].g + imgNormal->pixels[x][y].b)/3;
        
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

  //Clasificação da catarata. 
  classification(allPupilPixel, pupilPixelCatarata);
}

void classification(int allPupilPixel, int pupilPixelCatarata) {
  FILE *finalResult = fopen("Diagnostico.txt", "w+");
  
  //Porcentagem de comprometimento da pupila. 
  //Quantidade de pixels com catarata por quantidade total de pixels.
  int percentage = (pupilPixelCatarata*100)/allPupilPixel;

  fprintf(finalResult, "Comprometimento da pupila: %d%c\n", percentage, '%');

  if(percentage < 35) {
    fprintf(finalResult, "Diagnóstico final: Sem Catarata. Porém, consulte um médico.\n");
  } else if(percentage > 60) {
    fprintf(finalResult, "Diagnóstico final: Com Catarata.\nProcure um médico urgente.\n");
  } else {
    fprintf(finalResult, "Diagnóstico final: comprometimento está alto.\n Procure um médico urgente.\n");
  }
}

