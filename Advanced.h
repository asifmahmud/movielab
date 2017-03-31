#ifndef Advanced
#define Advanced
#include "Image.h"
#define MAX_COLOR 16
#define SLEN 80


/* Posterize the image */
IMAGE *Posterize( IMAGE *image);


/* Resize */
IMAGE *Resize( unsigned int percentage, IMAGE *image);

/* Mandelbrot */
IMAGE *Mandelbrot(unsigned int W, unsigned int H, unsigned int max_iteration);

#endif