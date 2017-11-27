//Cria o tipo Pixel. 
typedef struct pixel {
  int r, g, b;
} Pixel;

//Cria o tipo imagem com o tipo pixel dentro.
typedef struct image{
  FILE *file;
  int height, width, maxPixel;
  Pixel **pixels;
} Image;

typedef struct circle { 
	int x, y, r, valor;
} Circle;
