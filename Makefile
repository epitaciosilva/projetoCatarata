all: executable

executable: imageTreatment.o filters.o saveImages.o
	gcc main.c imageTreatment.o filters.o saveImages.o -o executable -W -g -lm

imageTreatment.o: ./src/imageTreatment.c
	gcc -c ./src/imageTreatment.c -W -g -lm

filters.o: ./src/filters.c
	gcc -c ./src/filters.c -W -g -lm

saveImages.o: ./src/saveImages.c
	gcc -c ./src/saveImages.c -W -g 

clean: 
	rm -f ./images/*Image.ppm && rm -f ./images/*Final.ppm