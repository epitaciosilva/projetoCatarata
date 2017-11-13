typedef struct pixel {
  int r, g, b;
} Pixel;

typedef struct imagem{
  FILE *file;
  int height, width, maxPixel;
  Pixel **pixels;
} Image;
