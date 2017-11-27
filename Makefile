all: catarata

catarata: imageTreatment.o filters.o saveImages.o finalProcess.o
	gcc main.c imageTreatment.o filters.o saveImages.o finalProcess.o -o catarata -W -g -lm

imageTreatment.o: ./src/imageTreatment.c
	gcc -c ./src/imageTreatment.c -W -g

filters.o: ./src/filters.c
	gcc -c ./src/filters.c -W -g -lm

saveImages.o: ./src/saveImages.c
	gcc -c ./src/saveImages.c -W -g 

finalProcess.o: 
	gcc -c ./src/finalProcess.c -W -g -lm

clean: 
	rm -f ./images/*Image.ppm ./images/*Final.ppm *.o *.txt catarata