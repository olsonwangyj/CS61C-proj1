/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				Wang Yanjie
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	struct Color *color = (struct Color*) malloc(sizeof(struct Color));
	*color = image->image[row][col];
	return color;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	struct Image *ans = (struct Image*) malloc(sizeof(struct Image));
	ans->cols = image->cols;
	ans->rows = image->rows;
	ans->image = (struct Color**) malloc(ans->rows * sizeof(struct Color*));
	
	for (int i = 0; i < ans->rows; i++) {
		ans->image[i] = (struct Color*) malloc(ans->cols * sizeof(struct Color));
		for (int j = 0; j < ans->cols; j++) {
			ans->image[i][j].B = (image->image[i][j].B & 1);
		}
	}

	return ans;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	struct Image *tmp;
	tmp = readData(argv[1]);
	struct Image *image = steganography(tmp);

	for (int i = 0; i < image->rows; i++) {
		for (int j = 0; j < image->cols; j++) {
			if (image->image[i][j].B) {
				image->image[i][j].R = 255;
				image->image[i][j].G = 255;
				image->image[i][j].B = 255;
			} else {
				image->image[i][j].R = 0;
				image->image[i][j].G = 0;
				image->image[i][j].B = 0;
			}
		}
	}

	writeData(image);
	freeImage(image);
	freeImage(tmp);
	return 0;
}
