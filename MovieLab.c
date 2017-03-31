/*********************************************************************/
/* MovieLab.c: homework assignment #5 Fall 2014			             */
/* Asif Mahmud, 70556749											 */
/*********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Image.h"
#include "ImageList.h"
#include "DIPs.h"
#include "Advanced.h"
#include "Movie.h"

/*save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie);

/*read one frame from the movie */
IMAGE* ReadOneFrame(const char* fname, int nFrame, unsigned int W, unsigned H);

/*read the movie frames from the input file */
int ReadMovie(const char *fname, int nFrame, unsigned int W, unsigned H, MOVIE *movie);

/* Print the command line parameter usage of the program*/
void PrintUsage();

/* type define the function pointer to the DIP function	*/
typedef IMAGE* MOP_F(IMAGE *image);

/* the function for perform DIP operations on the movie*/
void Movie_DIP_Operation(MOVIE *movie, MOP_F *MovieOP){

     IENTRY *Frame = movie->Frames->First;
     while (Frame) {
           Frame->Image = (*MovieOP)(Frame->Image);
           Frame = Frame->Next;
     }
     free(Frame);
}


int main(int argc, char *argv[]){
	int x = 0;
	char *fname = NULL, *out_name = NULL;
  char *no_frames = NULL;
  int is_i = 0, is_o = 0, is_f = 0, is_s = 0, is_h = 0;
  int is_bw = 0, is_vflip = 0, is_hmirror = 0, is_edge = 0, is_poster = 0;
  int is_fast = 0, is_cut = 0, is_resize = 0, is_rvs = 0;
  unsigned int W, H;
  unsigned int from_cut, to_cut;
  unsigned int ff_factor;
  unsigned int percentage;
  unsigned int nFrames;
  IENTRY *Frame = NULL;
  MOVIE *movie = NULL;

 /*entering while loop to check options entered*/
	while(x < argc){
		/*specify input video*/
		if(0 == strcmp(&argv[x][0], "-i")) {
      is_i = 1;
			if(x < argc - 1){
				fname = (char *)malloc(sizeof(char) * (strlen(&argv[x + 1][0]) + strlen(".yuv") + 1));
				strcpy(fname, argv[x + 1]);
				strcat( fname, ".yuv");
        
			}
			else{
				printf("Missing argument for input name!");
				free(fname);
				free(out_name);
        free(no_frames);
				return 5;
			}
			x += 2;
			continue;
		}

		/*specify output video*/
		if(0 == strcmp(&argv[x][0], "-o")) {
       is_o = 1;
			if(x < argc - 1){
				out_name = (char *)malloc(sizeof(char) * (strlen(&argv[x + 1][0]) + strlen(".yuv") + 1));
				strcpy(out_name, argv[x + 1]);
				strcat( out_name, ".yuv");
			}
			else{
				printf("Missing argument for output name!");
				free(fname);
				free(out_name);
        free(no_frames);
				return 5;
			}
			x += 2;
			continue;
		}
   
   /* Number of frames */
   if (0 == strcmp(&argv[x][0], "-f")) {
      is_f = 1;
			if(x < argc - 1){
				no_frames = (char *)malloc(sizeof(char) * (strlen(&argv[x + 1][0]) + 1));
				strcpy(no_frames, argv[x + 1]);
			}
			else{
				printf("Missing argument for number of frames!");
				free(fname);
				free(out_name);
        free(no_frames);
				return 5;
			}
      nFrames = atoi(no_frames);
			x += 2;
			continue;      
   }
   
   /* WidthxHeight */
   if (0 == strcmp(&argv[x][0], "-s")) {
      is_s = 1;
			if(x < argc - 1){
				if (sscanf(argv[x+1], "%dx%d", &W, &H) == 2) {/* */}
				else {
             printf("Width Height Input Format Error\n");
             return 5;
        }
			}
			else{
				printf("Missing argument for number of frames!");
				free(fname);
				free(out_name);
        free(no_frames);
				return 5;
			}
      movie = CreateMovie(nFrames, W, H);
      ReadMovie(fname, nFrames, W, H, movie);
			x += 2;
			continue;      
   }


   /* BlackNWhite */
   if (0 == strcmp(&argv[x][0], "-bw")) {
      
      is_bw = 1;
			x++;
			continue;      
   }
   
   /* VFlip */
   if (0 == strcmp(&argv[x][0], "-vflip")) {
   
      is_vflip = 1;
			x++;
			continue;      
   }
   
   /* HMirror */
   if (0 == strcmp(&argv[x][0], "-hmirror")) {
      is_hmirror = 1;
			x++;
			continue;      
   }
   
   /* Edge */
   if (0 == strcmp(&argv[x][0], "-edge")) {
      is_edge = 1;
			x++;
			continue;      
   }
   

   
   /* Poster */
   if (0 == strcmp(&argv[x][0], "-poster")) {
      is_poster = 1;
			x++;
			continue;      
   }
   
   /* Resize */
   if (0 == strcmp(&argv[x][0], "-resize")) {
      is_resize = 1;
      sscanf(argv[x+1], "%d", &percentage);
			x += 2;
			continue;      
   }
   
   /* cut */
   if (0 == strcmp(&argv[x][0], "-cut")) {
      is_cut = 1;
			if(x < argc - 1){
				if (sscanf(argv[x+1], "%d-%d", &from_cut, &to_cut) == 2) {/* */}
				else {
             printf("Cut Input Format Error\n");
             return 5;
        }
			}
			else{
				printf("Missing argument for cut operation!");
				free(fname);
				free(out_name);
        free(no_frames);
				return 5;
			}
   
			x += 2;
			continue;      
   }
   
   /* Fast Forward */
   if (0 == strcmp(&argv[x][0], "-fast")) {
      is_fast = 1;
      sscanf(argv[x+1], "%d", &ff_factor);
			x += 2;
			continue;      
   }
   

   
   /* Reverse */
   if (0 == strcmp(&argv[x][0], "-rvs")) {
      is_rvs = 1;
			x ++;
			continue;      
   }

   
		/*help option*/
		if(0 == strcmp(&argv[x][0], "-h")) { 
      is_h = 1;
			PrintUsage();
				free(fname);
				free(out_name);
        free(no_frames);
			return 0;
		}
		x++;
	}
 
  if (is_bw){
     Movie_DIP_Operation(movie, BlackNWhite);
     printf("Operation BlackNWhite is done!\n");
  
  }
  
  if (is_vflip){
     Movie_DIP_Operation(movie, VFlip);
     printf("Operation VFlip is done!\n");
  }
  
  if (is_hmirror){
     Movie_DIP_Operation(movie, HMirror);
     printf("Operation HMirror is done!\n");
  }
  
  if (is_edge){
     Movie_DIP_Operation(movie, Edge);
     printf("Operation Edge is done!\n");
  }
  
  if (is_poster){
     Movie_DIP_Operation(movie, Posterize);
     printf("Operation Posterize is done!\n");
  }
  
  if (is_resize){
     unsigned int r_w = (int)W*(percentage/100.00);
     unsigned int r_h = (int)H*(percentage/100.00);
     ResizeImageList(movie->Frames, percentage);
     movie->Width = r_w;
     movie->Height = r_h;
     printf("Operation Resize is done! New Width/Height = %dx%d\n", r_w, r_h);
  }
  
  if (is_cut){
     CropImageList(movie->Frames, from_cut, to_cut);
     printf("Operation Frame Cropping is done!\n");
  }
  
  if (is_fast){
     unsigned int n_frames = FastImageList(movie->Frames, ff_factor);
     printf("Operation Fast Forward is done! Number of frames = %d\n", n_frames);
  }
  
  if (is_rvs){
     ReverseImageList(movie->Frames);
     printf("Operation Reverse Movie is done!\n");
  }
  
  
  
 


  if ((is_i == 0 || is_o == 0 || is_f == 0 || is_s == 0) && is_h == 0) {
     printf("Missing default arguments. Try again\n");
				free(fname);
				free(out_name);
        free(no_frames);
     return 5;
  } 

	if(!fname){
		printf("Missing argument for input name!\n");
		PrintUsage();
				free(fname);
				free(out_name);
        free(no_frames);
		return 5;
	}

	if(!out_name){
		printf("Missing argument for output name!\n");
		PrintUsage();
				free(fname);
				free(out_name);
        free(no_frames);
		return 5;
	}

  Frame = movie->Frames->First;
  while (Frame){
        RGB2YUVImage(Frame->Image);
        Frame = Frame->Next;
  }
	SaveMovie(out_name, movie);
  DeleteMovie(movie);
  free(fname);
  free(out_name);
  free(no_frames);
  free(Frame);
	fname = NULL;
	out_name = NULL;
  no_frames = NULL;
  Frame = NULL;
  
	return 0;
}

void PrintUsage()
{
	printf("\nFormat on command line is:\n"
	"MovieLab [option]\n"
	"-i [file_name]    to provide the input file name\n"
	"-o [file_name]    to provide the	output file name\n"
	"-f [no_frames]    to determine how many frames desired in the input stream\n"
	"-s [WidthxHeight] to set resolution of the input stream (widthxheight)\n"
	"-j                to generate the movie with JuliaSet sequences\n"
	"-bw               to activate the conversion to black and white\n"
	"-vflip            to activate vertical flip\n"
	"-hmirror          to activate horizontal flip\n"
	"-edge             to activate edge filter\n"
	"-poster           to activate posterize filter\n"
	"-cut [Start-End]  to crop the frame from the video from frame Start to frame End\n"  
	"-resize [factor]  to resize the video with the provided factor [1-100]\n"
	"-fast   [factor]  to fast forward the video with the provided factor [1+]\n"
	"-rvs              to reverse the frame order of the input stream\n"
	"-h                to show this usage information\n"
	);
}

IMAGE* ReadOneFrame(const char *fname, int nFrame, unsigned int W, unsigned H)
{
        /*defining local variables*/
        FILE *file;

        unsigned int x, y;
        unsigned char ch;
        IMAGE* image ;

        /*checking error*/
        assert(fname);
        assert(nFrame >= 0);

        image = CreateImage(W, H) ;
        assert(image) ;

        /*opening file stream*/
        file = fopen(fname, "r");
        assert(file) ;

        /*find desired frame*/
        fseek(file, 1.5 * nFrame * W * H, SEEK_SET);

        for(y = 0; y < H; y ++){
                for(x = 0; x < W; x ++){
                        ch = fgetc(file);
                        SetPixelY(image, x, y, ch);
                }/*rof*/
        }

        for(y = 0; y < H ; y += 2){
                for(x = 0; x < W ; x += 2){
                        ch = fgetc(file);
                        SetPixelU(image, x, y, ch);
                        SetPixelU(image, x + 1, y, ch);
                        SetPixelU(image, x, y + 1, ch);
                        SetPixelU(image, x + 1, y + 1, ch);
                }
        }

        for(y = 0; y < H ; y += 2){
                for(x = 0; x < W ; x += 2){
                        ch = fgetc(file);
                        SetPixelV(image, x, y, ch);
                        SetPixelV(image, x + 1, y, ch);
                        SetPixelV(image, x, y + 1, ch);
                        SetPixelV(image, x + 1, y + 1, ch);
                }
        }

        /*checking for error*/

        assert(ferror(file) == 0) ;

        /*closing stream and terminating*/
        fclose(file);
        file = NULL;
        return image;
}


/*save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie)
{
	int i ; 
	int x, y;
	FILE *file;
	IENTRY *currFrame;

	 /*opening file stream*/
	 if(!(file = fopen(fname, "w"))){
			return 1;
	 }
	 
	 i = 0 ; 
	 /*printf("start savemovie, total frame %d\n", movie->NumFrames) ; */
	 currFrame = movie->Frames->First;
	 while(currFrame){
		for(y = 0; y < movie->Height; y ++){ 
			for(x = 0; x < movie->Width; x ++){
				fputc(GetPixelY(currFrame->Image, x, y), file);
			}
		}
		for(y = 0; y < movie->Height; y += 2){ 
			for(x = 0; x < movie->Width; x += 2){
				fputc(GetPixelU(currFrame->Image, x, y), file);
			}
		}
		for(y = 0; y < movie->Height; y += 2){ 
			for(x = 0; x < movie->Width; x += 2){
				fputc(GetPixelV(currFrame->Image, x, y), file);
			}
		}
		currFrame = currFrame->Next;	 
		i++ ; 
	 }

	 fclose(file);
	 file = NULL;

	 printf("The movie file %s has been written successfully! \n", fname);
	 printf("%d frames are written to the file %s in total \n", i, fname); 
	 return 0;
}


/*read the movie frames from the input file */
int ReadMovie(const char *fname, int nFrame, unsigned int W, unsigned H, MOVIE *movie){

    assert(fname);
    int frame_num = 0;
    while (frame_num < nFrame) {
          IMAGE *image = ReadOneFrame(fname, frame_num, W, H);
          YUV2RGBImage(image);
          AppendImage(movie->Frames, image);
          frame_num++;
    }
    printf("The movie file %s has been read successfully\n", fname);
    return 0;

}



















