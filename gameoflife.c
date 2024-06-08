/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				Wang Yanjie
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"
#include <stdbool.h>

int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dy[] = {1, 1, 1, 0, 0, -1, -1, -1};

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	bool isAliveR = false; 
	bool isAliveG = false; 
	bool isAliveB = false;
	int liveCountR = 0, liveCountG = 0, liveCountB = 0;

	if (image->image[row][col].R == 255) isAliveR = true;
	if (image->image[row][col].G == 255) isAliveG = true;
	if (image->image[row][col].B == 255) isAliveB = true;

	for (int i = 0; i < 8; i++) {
		int newRow = row + dy[i];
		int newCol = col + dx[i];
		if (newRow >= image->rows) newRow = 0;
		if (newRow < 0) newRow = image->rows - 1;
		if (newCol >= image->cols) newCol = 0;
		if (newCol < 0) newCol = image->cols - 1;

		if (image->image[newRow][newCol].R == 255) liveCountR++;
        if (image->image[newRow][newCol].G == 255) liveCountG++;
        if (image->image[newRow][newCol].B == 255) liveCountB++;	
	}

	struct Color* newColor = (struct Color*) malloc(sizeof(struct Color));

	// Process Red channel
    if (isAliveR) {
        newColor->R = (rule & (1 << (9 + liveCountR))) ? 255 : 0;
    } else {
        newColor->R = (rule & (1 << liveCountR)) ? 255 : 0;
    }

    // Process Green channel
    if (isAliveG) {
        newColor->G = (rule & (1 << (9 + liveCountG))) ? 255 : 0;
    } else {
        newColor->G = (rule & (1 << liveCountG)) ? 255 : 0;
    }

    // Process Blue channel
    if (isAliveB) {
        newColor->B = (rule & (1 << (9 + liveCountB))) ? 255 : 0;
    } else {
        newColor->B = (rule & (1 << liveCountB)) ? 255 : 0;
    }

	return newColor;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	struct Image *newImage = (struct Image*) malloc(sizeof(struct Image));
	newImage->cols = image->cols;
	newImage->rows = image->rows;
	newImage->image = (struct Color**) malloc(newImage->rows * sizeof(struct Color*));

	for (int i = 0; i < newImage->rows; i++) {
		newImage->image[i] = (struct Color*) malloc(newImage->cols * sizeof(struct Color));
		for (int j = 0; j < newImage->cols; j++) {
			Color *newColor = evaluateOneCell(image, i, j, rule);
			newImage->image[i][j] = *newColor;
			free(newColor);
		}
	}

	return newImage;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc != 3) return -1;

	char *endPtr;
	uint32_t rule = strtol(argv[2], &endPtr, 16);
	struct Image *tmp = readData(argv[1]);
	struct Image *image = life(tmp, rule);

	writeData(image);
	freeImage(image);
	freeImage(tmp);

	return 0;
}
