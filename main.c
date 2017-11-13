#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "primitive.h"
#include "readImage.h"
#include "saveImages.h"

int main() {
  Image img;
  buildImage(&img);
  saveImageColorToGray(&img);
  fclose(img.file);
  return 0;
}
