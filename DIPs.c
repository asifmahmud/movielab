#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "DIPs.h"
#include "Image.h"

int Range(int value, int from, int to){
	if (value < from || value > to)
		return 0;

	else
		return 1;

}

int in(int array[16], int value){
	int i;

	for (i = 0; i < 16; i++){
		if (array[i] == value)
			return 1;
	}
	return 0;
}

void append(int array[16], int value_1, int value_2){

	int i;
	for (i = 0; i < 16; i++){
		if (array[i] == 99)
			array[i] = value_1;
		array[i + 1] = value_2;
		break;
	}

}



IMAGE *BlackNWhite(IMAGE *image){
	int             x, y;
	unsigned int WIDTH;
	unsigned int HEIGHT;
	unsigned int tmp;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			tmp = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
			SetPixelR(image, x, y, tmp);
			SetPixelG(image, x, y, tmp);
			SetPixelB(image, x, y, tmp);
		}

	return image;

}


IMAGE *VFlip(IMAGE *image){
	unsigned int i, j;
  unsigned int r_temp, b_temp, g_temp;
  /*IMAGE *image_tmp = CreateImage(image->Width, image->Height); */
/*
	for (i = 0; i < (image->Width); i++){
		for (j = 0; j < (image->Height) / 2; j++){
			unsigned int r_temp = GetPixelR(image, i, j);
			unsigned int g_temp = GetPixelG(image, i, j);
			unsigned int b_temp = GetPixelB(image, i, j);
      
      SetPixelR(image, i, j, GetPixelR(image, i, image->Height - j));
      SetPixelR(image, i, image->Height - j, r_temp);
      SetPixelG(image, i, j, GetPixelG(image, i, image->Height - j));
      SetPixelG(image, i, image->Height - j, g_temp);
      SetPixelB(image, i, j, GetPixelB(image, i, image->Height - j));
      SetPixelB(image, i, image->Height - j, b_temp);
		}
	}
  /*DeleteImage(image);
  image = NULL; */
  
	for (i = 0; i < (image->Width); i++){
		for (j = 0; j < (image->Height) / 2; j++){
        r_temp = GetPixelR(image, i, image->Height - 1 - j);
        g_temp = GetPixelG(image, i, image->Height - 1 - j);
        b_temp = GetPixelB(image, i, image->Height - 1 - j);
        
        SetPixelR(image, i, image->Height - 1 - j, GetPixelR(image, i, j));
        SetPixelG(image, i, image->Height - 1 - j, GetPixelG(image, i, j));
        SetPixelB(image, i, image->Height - 1 - j, GetPixelB(image, i, j));
        
        SetPixelR(image, i, j, r_temp);
        SetPixelG(image, i, j, g_temp);
        SetPixelB(image, i, j, b_temp);
    }
  }
  
  return image;
}


IMAGE *HMirror(IMAGE *image){
	int             x, y;
	unsigned int WIDTH;
	unsigned int HEIGHT;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH / 2; x++) {
			SetPixelR(image, x, y, GetPixelR(image, WIDTH - 1 - x, y));
			SetPixelG(image, x, y, GetPixelG(image, WIDTH - 1 - x, y));
			SetPixelB(image, x, y, GetPixelB(image, WIDTH - 1 - x, y));
		}
	}

	return image;

}





IMAGE *Edge(IMAGE *image) {
	int i, j = 0;
	unsigned char *temp_r = (unsigned char*)malloc(sizeof(unsigned char) * (image->Width * image->Height));
  unsigned char *temp_g = (unsigned char*)malloc(sizeof(unsigned char) * (image->Width * image->Height));
  unsigned char *temp_b = (unsigned char*)malloc(sizeof(unsigned char) * (image->Width * image->Height));

	/* Creating temporary image */

	for (i = 0; i < image->Width; i++){
		for (j = 0; j < image->Height; j++){
      *(temp_r + (i + j * image->Width)) = GetPixelR(image, i, j);      
			*(temp_g + (i + j * image->Width)) = GetPixelG(image, i, j);
			*(temp_b + (i + j * image->Width)) = GetPixelB(image, i, j);
		}
	}


	for (i = 1; i < image->Width - 1; i++){
		for (j = 1; j < image->Height - 1; j++){
			int r_sum = GetPixelR(image, i, j+1) +
				GetPixelR(image, i, j-1) +
				GetPixelR(image, i+1, j) +
				GetPixelR(image, i-1, j) +
				GetPixelR(image, i+1, j-1) +
				GetPixelR(image, i+1, j+1) +
				GetPixelR(image, i-1, j+1) +
				GetPixelR(image, i-1, j-1);

			int g_sum = GetPixelG(image, i, j+1) +
				GetPixelG(image, i, j-1) +
				GetPixelG(image, i+1, j) +
				GetPixelG(image, i-1, j) +
				GetPixelG(image, i+1, j-1) +
				GetPixelG(image, i+1, j+1) +
				GetPixelG(image, i-1, j+1) +
				GetPixelG(image, i-1, j-1);

			int b_sum = GetPixelB(image, i, j+1) +
				GetPixelB(image, i, j-1) +
				GetPixelB(image, i+1, j) +
				GetPixelB(image, i-1, j) +
				GetPixelB(image, i+1, j-1) +
				GetPixelB(image, i+1, j+1) +
				GetPixelB(image, i-1, j+1) +
				GetPixelB(image, i-1, j-1);

			int replace_r = 8 * GetPixelR(image, i, j) - (r_sum);
			int replace_g = 8 * GetPixelG(image, i, j) - (g_sum);
			int replace_b = 8 * GetPixelB(image, i, j) - (b_sum);

			if (replace_r < 0)
				replace_r = 0;
			else if (replace_r > 255)
				replace_r = 255;

			if (replace_g < 0)
				replace_g = 0;
			else if (replace_g > 255)
				replace_g = 255;

			if (replace_b < 0)
				replace_b = 0;
			else if (replace_b > 255)
				replace_b = 255;

			*(temp_r + (i + j * image->Width)) = replace_r;
			*(temp_g + (i + j * image->Width)) = replace_g;
			*(temp_b + (i + j * image->Width)) = replace_b;

		}
	}

	for (i = 1; i < image->Width - 1; i++){
		for (j = 1; j < image->Height - 1; j++){
      SetPixelR(image, i, j, *(temp_r + (i + j * image->Width)));
			SetPixelG(image, i, j, *(temp_g + (i + j * image->Width)));
			SetPixelB(image, i, j, *(temp_b + (i + j * image->Width)));

		}

	}
  free(temp_r);
  temp_r = NULL;
  free(temp_g);
  temp_g = NULL;
  free(temp_b);
  temp_b = NULL;
 return image;
}


