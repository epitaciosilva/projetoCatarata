#include <stdio.h>
#include <string.h>
#include "./pointsH/primitive.h"
#include "./pointsH/imageTreatment.h"
#include "./pointsH/saveImages.h"
#include "./pointsH/filters.h"

int main() {
  Image img, image;
  char nameFileImage[20];
  char nameFinalFileImage[20];
  fgets(nameFileImage, 20, stdin);

  //Contruindo imagem.
  //Recebe como parâmetro a variável Image e o nome do arquivo da imagem a ser diagnósticada.
  buildImage(&img, nameFileImage);
  buildImage(&image, nameFileImage);

  //Filtro cinza.
  grayFilter(&img);
  strcpy(nameFinalFileImage, "grayImage.ppm");
  saveImage(&img, nameFinalFileImage);

  //Filtro gaussiano
  gaussianoFilter(&img);
  strcpy(nameFinalFileImage, "gaussianoImage.ppm");
  saveImage(&img, nameFinalFileImage);

  sobelFilter(&img, &image);
  strcpy(nameFinalFileImage, "sobelImage.ppm");
  saveImage(&image, nameFinalFileImage);

  fclose(img.file);
  fclose(image.file);
  return 0;
}
