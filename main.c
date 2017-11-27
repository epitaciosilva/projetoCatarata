#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./include/primitive.h"
#include "./include/imageTreatment.h"
#include "./include/saveImages.h"
#include "./include/filters.h"
#include "./include/finalProcess.h"

int main(int argc, char *argv[]) {
  Image img, image, imgFinal;
  
  if(argc != 7) {
    printf("Erro nos valores de entrada. Verifique os parâmetros de entrada.\n");
    exit(1);
  }
  //Contruindo imagens.
  //Recebe como parâmetro a variável Image e o nome do arquivo da imagem a ser diagnósticada.
  buildImage(&img, argv[2]);
  buildImage(&image, argv[2]);
  buildImage(&imgFinal, argv[2]);

  //Filtro cinza.
  grayFilter(&img);
  saveImage(&img, "GrayImage.ppm");

  //Filtro gaussiano
  gaussianoFilter(&img);
  saveImage(&img, "GaussianoImage.ppm");

  //Filtro de sobel
  sobelFilter(&img, &image);
  saveImage(&image, "SobelImage.ppm");

  //Binarização
  binaryFilter(&image);
  saveImage(&image, "BinaryImage.ppm");

  //Transformação de Hough
  houghTransform(&image, &imgFinal, argv[6]);
  saveImage(&imgFinal, "Final.ppm");

  printf("Acesse o arquivo %s para saber do resultado.\n", argv[6]);
  printf("Acesse a pasta images para visualizar as imagens geradas.\n");

  fclose(img.file);
  fclose(image.file);
  fclose(imgFinal.file);
  return 0;
}
