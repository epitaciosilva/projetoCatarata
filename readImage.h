void buildImage(Image *img) {
  img->file = fopen("images/Catarata.ppm", "rw");

  verifyImageType(img);
  deleteComments(img->file);
  allocateDimensions(img);
  buildPixelsMatrix(img);
}

void buildPixelsMatrix(Image *img) {
  int i, j;
  img->pixels = (Pixel**)malloc(img->height * sizeof(Pixel*));

  for(i = 0;  i < img->height; i++) {
    img->pixels[i] = (Pixel*)malloc(img->width * sizeof(Pixel*));
  }
}

void deleteComments(FILE *file_img) {
    char buffer = fgetc(file_img);
    do {
        if (buffer == '#') {
            while (buffer != '\n') {
              buffer = fgetc(file_img);
            }
        } else {
          ungetc(buffer, file_img);
        }
        buffer = fgetc(file_img);
    } while (buffer == '#');
    ungetc(buffer, file_img);
}

void allocateDimensions(Image *img) {
  fscanf(img->file, "%d %d", &img->width, &img->height);
  fscanf(img->file, "%d", &img->maxPixel);
}

void verifyImageType(Image *img) {
  if(img->file == NULL) {
    printf("Nao foi possivel abrir o arquivo.\n");
    exit(1);
  }

  char header[3];
  fscanf(img->file, "%s ", header);

  if(header[0] != 'P' || header[1] != '3') {
    printf("Formato da imagem deve ser P3.\n");
    exit(1);
  }
}
