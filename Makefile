all:
	gcc main.c ./pointsC/readImage.c ./pointsC/filters.c ./pointsC/saveImages.c -o exec
