#include <stdio.h>
#include <string.h>
#include "./include/primitive.h"
#include "./include/imageTreatment.h"
#include "./include/saveImages.h"
#include "./include/filters.h"

void concatenateFileName(char nameFile[15], char *nameFinalFileImage, char nameFileImage[20]) {
  strcpy(nameFinalFileImage, "");

  strncat(nameFinalFileImage, nameFileImage, strlen(nameFileImage)-5);
  strncat(nameFinalFileImage, nameFile, strlen(nameFile));
  strncat(nameFinalFileImage, ".ppm", 4);
}

int main() {
  Image img, image, imgFinal;
  char nameFileImage[20];
  char nameFinalFileImage[50];

  printf("Insira o nome do arquivo:\n");
  fgets(nameFileImage, 20, stdin);

  //Contruindo imagem.
  //Recebe como parâmetro a variável Image e o nome do arquivo da imagem a ser diagnósticada.
  buildImage(&img, nameFileImage);
  buildImage(&image, nameFileImage);
  buildImage(&imgFinal, nameFileImage);


  //Filtro cinza.
  grayFilter(&img);
  concatenateFileName("GrayImage", nameFinalFileImage, nameFileImage);
  saveImage(&img, nameFinalFileImage);

  //Filtro gaussiano
  gaussianoFilter(&img);
  concatenateFileName("GaussianoImage", nameFinalFileImage, nameFileImage);
  saveImage(&img, nameFinalFileImage);

  sobelFilter(&img, &image);
  concatenateFileName("SobelImage", nameFinalFileImage, nameFileImage);
  saveImage(&image, nameFinalFileImage);

  binaryFilter(&image);
  concatenateFileName("BinaryImage", nameFinalFileImage, nameFileImage);
  saveImage(&image, nameFinalFileImage);

  houghTransform(&image, &imgFinal);
  concatenateFileName("FINAL", nameFinalFileImage, nameFileImage);
  saveImage(&imgFinal, nameFinalFileImage);

  fclose(img.file);
  fclose(image.file);
  return 0;
}
