#include <stdio.h>
#include <string.h>
#include "./pointsH/primitive.h"
#include "./pointsH/readImage.h"
#include "./pointsH/saveImages.h"
#include "./pointsH/filters.h"

int main() {
  Image img;
  char nameFileImage[20];
  fgets(nameFileImage, 20, stdin);

  //Contruindo imagem.
  //Recebe como parâmetro a variável Image e o nome do arquivo da imagem a ser diagnósticada.
  buildImage(&img, nameFileImage);

  //Chamando filtro cinza.
  grayFilter(&img);

  // //Salvando imagem
  saveImage(&img);

  fclose(img.file);
  return 0;
}
