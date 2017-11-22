void buildImage(Image *img, char *nameFileImage);

void buildPixelsMatrix(Image *img);

void deleteComments(FILE *fileImage);

void allocateDimensions(Image *img);

void verifyFileImage(Image *img);

Pixel * pixelReturn(Image *img, int line, int column);

void houghTransform(Image *image1, Image *image);
  