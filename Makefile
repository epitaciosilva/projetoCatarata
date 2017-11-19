all:
	gcc main.c ./pointsC/imageTreatment.c ./pointsC/filters.c ./pointsC/saveImages.c -o exec -lm
