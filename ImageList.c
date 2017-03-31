#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"
#include "Advanced.h"


static IENTRY *NewImageEntry(IMAGE *image){
       
       IENTRY *i;
       i = malloc(sizeof(IENTRY));
       if (!i) {
          perror("Out of memory! Aborting...\n");
          exit(10);
       }
       
       i->List = NULL;
       i->Next = NULL;
       i->Prev = NULL;
       i->Image = image;
       
       return i;
}



/* allocate a new image list */
ILIST *NewImageList(void){
      ILIST *imageList;
      
      imageList = malloc(sizeof(ILIST));
      if (! imageList) {
         perror("Out of memory! Aborting...\n");
         exit(10);
      }
      
      imageList->Length = 0;
      imageList->First = NULL;
      imageList->Last = NULL;
      
      return imageList;
}



static IMAGE *DeleteImageEntry (IENTRY *i) {

     IMAGE *tmp;
     assert(i);
     tmp = i->Image;
     i->List->Length--;
        
     
     if (i->Next == NULL && i->Prev == NULL){
        i->List->First = NULL;
        i->List->Last = NULL;   
     }
     
     else if (i->Prev == NULL && i->Next != NULL){
        i->Next->Prev = NULL;
        i->List->First = i->Next;
     }
        
     else if (i->Next == NULL && i->Prev != NULL){
        i->Prev->Next = NULL;
        i->List->Last = i->Prev;
     }
        
     else {
          i->Next->Prev = i->Prev;
          i->Prev->Next = i->Next;
     }
        
     free(i);
     return tmp; 
     
      
}


/* delete a image list (and all entries) */
void DeleteImageList(ILIST *l){

     assert(l);
     IENTRY *i = NULL, *n = NULL;
     IMAGE *image = NULL;
     i = l->First;
  
     while (i) {
           n = i->Next;
           image = DeleteImageEntry(i);
           DeleteImage(image);
           i = n;
     }
     
     free(i);
     free(n);
     free(l);


}

/* insert a frame into a list at the end*/
void AppendImage(ILIST *l, IMAGE *image){

     IENTRY *e = NULL;
     assert(l);
     assert(image);
     e = NewImageEntry(image);
     if (l->Last)
        { e->List = l;
          e->Next = NULL;
          e->Prev = l->Last;
          l->Last->Next = e;
          l->Last = e;
        }
     else
        { e->List = l;
          e->Next = NULL;
          e->Prev = NULL;
          l->First = e;
          l->Last = e;
        }
     l->Length++;
}

/* reverse an image list */
void ReverseImageList(ILIST *l){
     
     assert(l);
     IENTRY *tmp = l->First;
     l->First = l->Last;
     l->Last = tmp;
     
     free(tmp);
     
     IENTRY *i = l->First, *n = NULL;
     
     while (i) {
           n = i->Next;
           i->Next = i->Prev;
           i->Prev = n;
           i = i->Next;
     }
     
     free(n);
     free(i); 

}

/*Crop frames from the list starting from SFrame to EFrame*/
void CropImageList(ILIST *l, unsigned int SFrame, unsigned int EFrame) {
     
     assert(l);
     int x = 1;
     IENTRY *i = l->First, *n;
     IMAGE *image;
     while (i) {
           n = i->Next;
           if (x < SFrame){
              image = DeleteImageEntry(i);
              DeleteImage(image);
           }
           if (x == SFrame) {
              l->First = i;
              l->First->Prev = NULL;
           }
           if (x == EFrame){
              l->Last = i;
           }
           if (x > EFrame) {
              image = DeleteImageEntry(i);
              DeleteImage(image);
           }
           i = n;
           x++;
     }
     l->Last->Next = NULL;
     free(i);
     free(n);
    /* free(image); */
     
}

/*Resize the images in the list*/
void ResizeImageList(ILIST *l, unsigned int percentage) {
     
     assert(l);
     IENTRY *i = l->First;
     
     while(i){
              i->Image = Resize(percentage, i->Image);
              i = i->Next;
     }
     
     free(i);
}

/*Fast forward the video*/
unsigned int FastImageList(ILIST *l, unsigned int ff_factor) {
         
         if (ff_factor == 1)
            return l->Length;
            
         IENTRY *i = NULL, *n = NULL; 
         IMAGE *image = NULL;
         int to_skip;
         
         i = l->First;
         int num_frames = 0, in_frame = 2;
         while(i){
               num_frames++;
               i = i->Next;
         }
         
         i = l->First->Next;
         while (i) {
               to_skip = 0;
               while (to_skip < ff_factor - 1) {
                     n = i->Next;
                     image = DeleteImageEntry(i);
                     DeleteImage(image);
                     i = n;
                     to_skip++;
                     in_frame++;
               }
               
							 if ((num_frames - in_frame) < ff_factor) {
								l->Last = i;
								i = i->Next;
								int to_trav = num_frames - in_frame;
								int x = 0;
								while (x < to_trav) {
									  n = i->Next;
									  image = DeleteImageEntry(i);
									  DeleteImage(image);
									  i = n;
									  x++;
								}
								free(i);
								free(n);
                l->Last->Next = NULL;
								return l->Length;
							 }
                                  
               in_frame++;
               i = i->Next;
         }
         free(i);
         free(n);
         /*free(image); */
         return l->Length; 
       
}        











































