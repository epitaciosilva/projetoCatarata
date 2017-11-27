#include <stdio.h>
#include <string.h>
#include "./include/primitive.h"
#include "./include/imageTreatment.h"
#include "./include/saveImages.h"
#include "./include/filters.h"

//Gerando nome do arquivo final das imagens.
void concatenateFileName(char nameFile[15], char *nameFinalFileImage, char nameFileImage[20]) {
  //Apenas para inicializar a variável.
  strcpy(nameFinalFileImage, "");
  //Concatena com o nome inicial da image.
  strncat(nameFinalFileImage, nameFileImage, strlen(nameFileImage)-5);
  //Concatena com nome passado por parâmetro.
  strncat(nameFinalFileImage, nameFile, strlen(nameFile));
  //Coloca a extensão do arquivo '.ppm'.
  strncat(nameFinalFileImage, ".ppm", 4);
}

int main() {
  Image img, image, imgFinal;
  char nameFileImage[20];
  char nameFinalFileImage[50];

  printf("Nome das imagens: Catarata.ppm, Catarata2.ppm, Normal.ppm e Normal2.ppm\n");
  printf("Insira o nome de alguma dessas imagens:\n");
  fgets(nameFileImage, 20, stdin);

  //Contruindo imagens.
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

  //Filtro de sobel
  sobelFilter(&img, &image);
  concatenateFileName("SobelImage", nameFinalFileImage, nameFileImage);
  saveImage(&image, nameFinalFileImage);

  //Binarização
  binaryFilter(&image);
  concatenateFileName("BinaryImage", nameFinalFileImage, nameFileImage);
  saveImage(&image, nameFinalFileImage);

  //Transformação de Hough
  houghTransform(&image, &imgFinal);
  concatenateFileName("Final", nameFinalFileImage, nameFileImage);
  saveImage(&imgFinal, nameFinalFileImage);

  fclose(img.file);
  fclose(image.file);
  fclose(imgFinal.file);
  return 0;
}
