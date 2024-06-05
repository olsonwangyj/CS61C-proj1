/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				Wang Yanjie
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE *fp = fopen(filename, "r");
	
	struct Image *data = (struct Image*) malloc(sizeof(struct Image));
	char format[3];
	uint32_t col;
	uint32_t row;
	int scale;
	
	fscanf(fp, "%s %d %d %d", format, &col, &row, &scale);
	
	struct Color **color = (struct Color**) malloc(row * sizeof(struct Color*));
	for (int i = 0; i < row; i++) {
		color[i] = (struct Color*) malloc(col * sizeof(struct Color));
	}
	
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			fscanf(fp, "%hhu %hhu %hhu", &color[i][j].R, &color[i][j].G, &color[i][j].B);
		}
	}

	fclose(fp);
	data->cols = col;
	data->rows = row;
	data->image = color;

	return data;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	printf("P3\n");
	printf("%d %d\n", image->cols, image->rows);
	printf("255\n");
	
	int j;
	for (int i = 0; i < image->rows; i++) {
		for (j = 0; j < image->cols - 1; j++) {
			printf("%3hhu %3hhu %3hhu   ", image->image[i][j].R, image->image[i][j].G, image->image[i][j].B);
		}
		printf("%3hhu %3hhu %3hhu\n", image->image[i][j].R, image->image[i][j].G, image->image[i][j].B);
	}
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	for (int i = 0; i < image->rows; i++) {
		free(image->image[i]);
	}
	free(image->image);
	free(image);
}