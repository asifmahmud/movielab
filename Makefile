#Makefile: PhotoLab


CC     = gcc
CFLAGS = -ansi -Wall -c
LFLAGS = -Wall

DESIGN = MovieLab

all: MovieLab
MovieLab : MovieLab

clean:
	rm -f *.o out.yuv out1.yuv out2.yuv $(DESIGN)

	
#compilation rules
	
Image.o : Image.c Image.h
	gcc -Wall -ansi -c Image.c -o Image.o
 
Movie.o : Movie.c Movie.h Image.h ImageList.h
	gcc -Wall -ansi -c Movie.c -o Movie.o
	
ImageList.o : ImageList.c ImageList.h Movie.h Image.h Advanced.h
	gcc -Wall -ansi -c ImageList.c -o ImageList.o
         
DIPs.o     : DIPs.c DIPs.h Image.h
	gcc -Wall -ansi -c DIPs.c -o DIPs.o
         
Advanced.o : Advanced.c Advanced.h Image.h
	gcc -Wall -ansi -c Advanced.c -o Advanced.o

MovieLab.o : MovieLab.c Movie.h Advanced.h DIPs.h Image.h ImageList.h
	gcc -Wall -ansi -c MovieLab.c -o MovieLab.o
	  
MovieLab : Movie.o Image.o DIPs.o Advanced.o MovieLab.o ImageList.o




