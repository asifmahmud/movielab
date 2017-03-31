#ifndef DIPs
#define DIPs
#include "Image.h"



/* change color image to black & white */
IMAGE *BlackNWhite(IMAGE *image);

/* flip image vertically */
IMAGE *VFlip(IMAGE *image);

/* mirror image horizontally */
IMAGE *HMirror(IMAGE *image);

/* color filter */
IMAGE *ColorFilter(IMAGE *image, int target_r, int target_g, int target_b,
int threshold, int replace_r, int replace_g, int replace_b);

/* sharpen the image */
IMAGE *Shuffle(IMAGE *image);

/* edge detection */
IMAGE *Edge(IMAGE *image);





#endif