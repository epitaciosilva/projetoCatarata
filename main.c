#include <stdio.h>
#include "primitive.h"
#include "readImage.h"
#include "saveImages.h"

int main() {
  Image img;
  buildImage(&img);
  //Salvar a imagem normalmente, ou seja, lê e salva em outro arquivo.
  saveImageNormal(&img);
  //Aplica o algoritmo para deixar toda imagem cinza.
  saveImageColorToGray(&img);

//Fecha o arquivo.	
  fclose(img.file);
  return 0;
}
