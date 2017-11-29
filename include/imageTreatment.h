void buildImage(Image *img, char *nameFileImage);

Bool verifyFileImage(Image *img);

void deleteComments(FILE *fileImage, char comment);

void allocateDimensions(Image *img);

void buildPixelsMatrix(Image *img);

Pixel * pixelReturn(Image *img, int line, int column);

  