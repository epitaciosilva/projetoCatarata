void saveImageNormal(Image *img) {
    int i, j;
    FILE *imageFile = fopen("images/normalImageSaved.ppm", "w+");

    fprintf(imageFile, "P3\n");
    fprintf(imageFile, "%d %d\n", img->width, img->height);
    fprintf(imageFile, "%d\n", img->maxPixel);

    for(i = 0; i<img->height-1; i++) {
      for(j = 0; j<img->width; j++) {
          fscanf(img->file, "%d", &img->pixels[i][j].r);
          fscanf(img->file, "%d", &img->pixels[i][j].g);
          fscanf(img->file, "%d", &img->pixels[i][j].b);
          fprintf(imageFile, "%d\n", img->pixels[i][j].r);
          fprintf(imageFile, "%d\n", img->pixels[i][j].g);
          fprintf(imageFile, "%d\n", img->pixels[i][j].b);
      }
    }

    fclose(imageFile);
}

void saveImageColorToGray(Image *img) {
    int i, j;
    FILE *file = fopen("images/savedImageWithGrayColor", "w+");

    fprintf(file, "P3\n");
    fprintf(file, "%d %d\n", img->width, img->height);
    fprintf(file, "%d\n", img->maxPixel);

    for(i = 0; i<img->height-1; i++) {
      for(j = 0; j<img->width; j++) {
        fscanf(img->file, "%d", &img->pixels[i][j].r);
        fscanf(img->file, "%d", &img->pixels[i][j].g);
        fscanf(img->file, "%d", &img->pixels[i][j].b);
        int colorGray = img->pixels[i][j].r*0.3  + img->pixels[i][j].g*0.59 + img->pixels[i][j].b*0.11;
        fprintf(file, "%d\n", colorGray);
        fprintf(file, "%d\n", colorGray);
        fprintf(file, "%d\n", colorGray);
      }
    }

    fclose(file);
}
