all:
	gcc main.c ./src/imageTreatment.c ./src/filters.c ./src/saveImages.c -o exec -lm
