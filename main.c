#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./include/primitive.h"
#include "./include/imageTreatment.h"
#include "./include/saveImages.h"
#include "./include/filters.h"
#include "./include/finalProcess.h"

int main(int argc, char *argv[]) {
  Image img, imgSobelBinary, imgColorful;
  
  if(argc != 7) {
    printf("Erro nos valores de entrada. Verifique os parâmetros.\n");
    exit(1);
  }

  //Contruindo imagens.
  //Recebe como parâmetro a variável Image e o nome do arquivo da imagem a ser diagnósticada.
  //A imgSobelBinary e a imgColorful é necessária para implementação do filtro de sobel e 
  //para dectectação da iris e da catarata respectivamente.
  buildImage(&img, argv[2]);
  buildImage(&imgSobelBinary, argv[2]);
  buildImage(&imgColorful, argv[2]);

  //Filtro cinza.
  grayFilter(&img);
  saveImage(&img, "GrayImage.ppm");

  //Filtro gaussiano
  gaussianoFilter(&img);
  saveImage(&img, "GaussianoImage.ppm");

  //Filtro de sobelimgSobelBinary
  sobelFilter(&img, &imgSobelBinary);
  saveImage(&imgSobelBinary, "SobelImage.ppm");

  //Binarização
  binaryFilter(&imgSobelBinary);
  saveImage(&imgSobelBinary, "BinaryImage.ppm");

  //Transformação de Hough
  Circle circle = houghTransform(&imgSobelBinary, &imgColorful);
  classification(&imgColorful, &circle, argv[6]);
  saveImage(&imgColorful, "Final.ppm");

  printf("Acesse o arquivo %s para saber do resultado.\n", argv[6]);
  printf("Para visualizar as imagens geradas acesse a pasta images.\n");

  fclose(img.file);
  fclose(imgSobelBinary.file);
  fclose(imgColorful.file);
  return 0;
}
