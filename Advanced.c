#include <stdio.h>
#include <time.h>
#include "Advanced.h"
#include "Image.h"

unsigned char pow(unsigned char a, unsigned char b){
	unsigned char i;
	unsigned char temp = 1;
	for (i = 0; i < b; i++){
		temp *= a;
	}
	return temp;
}



IMAGE *Posterize( IMAGE *image){
  unsigned int pbits = 6;
	int i, j;
	for (i = 0; i < image->Width; i++){
		for (j = 0; j < image->Height; j++){
			char temp = pow(2, pbits - 1) - 1;
			
      SetPixelR(image, i, j, GetPixelR(image, i, j) & ~(1 << pbits - 1));
      SetPixelR(image, i, j, GetPixelR(image, i, j) | temp);
			
      SetPixelG(image, i, j, GetPixelG(image, i, j) & ~(1 << pbits - 1));
      SetPixelG(image, i, j, GetPixelG(image, i, j) | temp);
			
      SetPixelB(image, i, j, GetPixelB(image, i, j) & ~(1 << pbits - 1));
      SetPixelB(image, i, j, GetPixelB(image, i, j) | temp);
		}
	}
 return image;
}
 






/* Resize */
IMAGE *Resize( unsigned int percentage, IMAGE *image){
   /*   int i, j;
      if (percentage == 100)
         return image;
         
      else {
           double p_divide = percentage/100.00; 
           double new_width  = (image->Width) * (percentage/100.00);
           double new_height = (image->Height) * (percentage/100.00);
           IMAGE* new_image = CreateImage((int)new_width, (int)new_height);

           if (percentage > 100) {
              for (i = 0; i < new_image->Width; i++){
                  for (j = 0; j < new_image->Height; j++){
                      SetPixelR(new_image, i, j, GetPixelR(image, (100*i)/(percentage), (100*j)/(percentage)));
                      SetPixelG(new_image, i, j, GetPixelG(image, (100*i)/(percentage), (100*j)/(percentage)));
                      SetPixelB(new_image, i, j, GetPixelB(image, (100*i)/(percentage), (100*j)/(percentage)));
                  }
              }
           }
           else if (percentage < 100){
                int k, l;
                for (i = 0; i < new_image->Width; i++){
                    for (j = 0; j < new_image->Height; j++){
                        int sum_r = 0;
                        int sum_g = 0;
                        int sum_b = 0;
                        int x1 = (int) (i/p_divide);
                        int y1 = (int) (j/p_divide);
                        int x2 = (int) ((i+1)/p_divide);
                        int y2 = (int) ((j+1)/p_divide);
                        int to_divide = ((x2 - x1)) * ((y2 - y1));
                        
                        for (k = x1; k < x2; k++){
                            for (l  = y1; l < y2; l++){
                                sum_r += GetPixelR(image, k, l);
                                sum_g += GetPixelG(image, k, l); 
                                sum_b += GetPixelB(image, k, l); 
                            }
                        }
                        SetPixelR(new_image, i, j, sum_r/to_divide);
                        SetPixelG(new_image, i, j, sum_g/to_divide);
                        SetPixelB(new_image, i, j, sum_b/to_divide);
                    }
                }
           
           } 
                     
           DeleteImage(image);
           image = NULL;
           return new_image;
      } */
      
	unsigned int    x, y, x1, y1, x2, y2, i, j, tmpR, tmpG, tmpB;
	unsigned int 	NEW_WIDTH, NEW_HEIGHT;
	unsigned int WIDTH;
	unsigned int HEIGHT;
	IMAGE *image_tmp;

	assert(image);
	WIDTH 	= image->Width;
	HEIGHT = image->Height;

	if(percentage <= 0 || percentage > 500){
		printf("Resizing percentage %d%% is out of the range, Sorry! \n", percentage);
		return image;
	}

	NEW_WIDTH = WIDTH * percentage / 100;
	NEW_HEIGHT = HEIGHT * percentage / 100;
	image_tmp = CreateImage(NEW_WIDTH, NEW_HEIGHT);
	
	for(x = 0; x < NEW_WIDTH; x ++){
		for(y = 0; y < NEW_HEIGHT; y++){
			x1 = (unsigned int)(x / (percentage / 100.00));
			y1 = (unsigned int)(y / (percentage / 100.00));
			x2 = (unsigned int)((x + 1) / (percentage / 100.00));
			y2 = (unsigned int)((y + 1) / (percentage / 100.00));
			tmpR = tmpB = tmpG = 0;
			
			if(percentage < 100){
				for(i = x1; i < x2; i ++){
					for(j = y1; j < y2; j ++){
						tmpR += GetPixelR(image, i, j);
						tmpG += GetPixelG(image, i, j);
						tmpB += GetPixelB(image, i, j);
					}
				}
				SetPixelR(image_tmp, x, y, tmpR / ((x2 - x1) * (y2 - y1)));
				SetPixelG(image_tmp, x, y, tmpG / ((x2 - x1) * (y2 - y1)));
				SetPixelB(image_tmp, x, y, tmpB / ((x2 - x1) * (y2 - y1)));

			}
			else{
				SetPixelR(image_tmp, x, y, GetPixelR(image, x1, y1));
				SetPixelG(image_tmp, x, y, GetPixelG(image, x1, y1));
				SetPixelB(image_tmp, x, y, GetPixelB(image, x1, y1));
			}
		}
	}

	DeleteImage(image);
	image = NULL;
	return image_tmp;

}




/* Mandelbrot */
IMAGE *Mandelbrot(unsigned int W, unsigned int H, unsigned int max_iteration){

      IMAGE *image = CreateImage(W, H);
      const unsigned char palette[MAX_COLOR][3] = {
      /* r g b*/
      { 0, 0, 0 }, /* 0, black */
      { 127, 0, 0 }, /* 1, brown */
      { 255, 0, 0 }, /* 2, red */
      { 255, 127, 0 }, /* 3, orange */
      { 255, 255, 0 }, /* 4, yellow */
      { 127, 255, 0 }, /* 5, light green */
      { 0, 255, 0 }, /* 6, green */
      { 0, 255, 127 }, /* 7, blue green */
      { 0, 255, 255 }, /* 8, turquoise */
      { 127, 255, 255 }, /* 9, light blue */
      { 255, 255, 255 }, /* 10, white */
      { 255, 127, 255 }, /* 11, pink */
      { 255, 0, 255 }, /* 12, light pink */
      { 127, 0, 255 }, /* 13, purple */
      { 0, 0, 255 }, /* 14, blue */
      { 0, 0, 127 } /* 15, dark blue */
      };

      int i, j;
      for (i = 0; i < W; i++){
          for (j = 0; j < H; j++){
              double x0 = (i - W/2.0)*4.0/W;
              double y0 = (j - H/2.0)*4.0/H;
                 
              double x = 0.0;
              double y = 0.0;
              
              int iteration = 0;
              
              while (((x*x + y*y) < 2*2) && (iteration < max_iteration)){
                    double xtemp = x*x - y*y + x0;
                    y = 2*x*y + y0;
                    x = xtemp;
                    iteration++;
              }
              
              int color = iteration % 16;
              
              SetPixelR(image, i, j, palette[color][0]);
              SetPixelG(image, i, j, palette[color][1]);
              SetPixelB(image, i, j, palette[color][2]);
          }
      }
      return image;

}












