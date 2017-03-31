
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "Movie.h"


unsigned int clip(unsigned int x) {
         if (x <= 0)
            return 0;
         else if (x >= 255) 
              return 255;
         return x;

}


/* allocate the memory space for the movie */
/* and the memory space for the frame list. */
/* return the pointer to the movie */
MOVIE *CreateMovie(unsigned int nFrames, unsigned int W, unsigned int H){

      MOVIE *movie = malloc(sizeof(MOVIE));
      ILIST *Frames_list = NewImageList();
      
      movie->Width = W;
      movie->Height = H;
      movie->NumFrames = nFrames;
      movie->Frames = Frames_list;
      

}


/*release the memory space for the frames and the frame list. */
/*release the memory space for the movie. */
void DeleteMovie(MOVIE *movie){
     
     assert(movie);
     DeleteImageList(movie->Frames);
     free(movie);
}


/* convert a YUV image into a RGB image */
void YUV2RGBImage(IMAGE *Image){
     assert(Image);
     int i, j;
     for (i = 0; i < Image->Width; i++){
         for (j = 0; j < Image->Height; j++) {
             unsigned int C = Image->Color.YUV.Y[i + j * Image->Width] - 16;
             unsigned int D = Image->Color.YUV.U[i + j * Image->Width] - 128;
             unsigned int E = Image->Color.YUV.V[i + j * Image->Width] - 128;
             
             Image->Color.RGB.R[i + j * Image->Width] = clip((298*C+409*E+128) >> 8);
             Image->Color.RGB.G[i + j * Image->Width] = clip((298*C-100*D-208*E+128) >> 8);
             Image->Color.RGB.B[i + j * Image->Width] = clip((298*C+516*D+128) >> 8);
         }
     }

}

/* convert a RGB image into a YUV image */
void RGB2YUVImage(IMAGE *Image){
     assert(Image);
     int i, j;
     for (i = 0; i < Image->Width; i++){
         for (j = 0; j < Image->Height; j++){
             unsigned char R = Image->Color.RGB.R[i + j * Image->Width];
             unsigned char G = Image->Color.RGB.G[i + j * Image->Width];
             unsigned char B = Image->Color.RGB.B[i + j * Image->Width];
             
             Image->Color.YUV.Y[i + j * Image->Width] = clip(((66*R+129*G+25*B+128) >> 8)+16);
             Image->Color.YUV.U[i + j * Image->Width] = clip(((-38*R-74*G+112*B+128) >> 8)+128);
             Image->Color.YUV.V[i + j * Image->Width] = clip(((112*R-94*G-18*B+128) >> 8)+128);
         }
     
     }

}













