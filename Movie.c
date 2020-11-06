/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "Movie.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
    MOVIE *m = (MOVIE *)malloc(sizeof(MOVIE));
	if (!m)
    {
		return NULL;
    }
    m->Frames=CreateImageList();
    return m;

}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
    assert(movie);
    if(movie->Frames)
    {
        DeleteImageList(movie->Frames);
    }
    free(movie);

}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
    IENTRY *m , *n;
    assert(movie->Frames);
    m=movie->Frames->First;
    while(m)
    {
        n=m->Next;
        m->RGBImage= CreateImage(MovieWidth(movie),MovieHeight(movie)); //image has a new image. It is an RGB image
        // iterate through YUV pixels and then do the formula to calculate each pixel
        for(int x=0; x<MovieWidth(movie); x++)
        {
            for( int y=0; y<MovieHeight(movie); y++)
             {
                int Y=GetPixelY(m->YUVImage,x,y);
                int U=GetPixelU(m->YUVImage,x,y);
                int V=GetPixelV(m->YUVImage,x,y);

                int C = Y - 16;
                int D = U - 128;
                int E = V - 128;

                int R = (( 298 * C + 409 * E + 128) >> 8);
                int G = (( 298 * C - 100 * D - 208 * E + 128) >> 8);
                int B = (( 298 * C + 516 * D + 128) >> 8);

                SetPixelR(m->RGBImage,x,y,(R>255)?255:(R<0)?0:R);
                SetPixelG(m->RGBImage,x,y,(G>255)?255:(G<0)?0:G);
                SetPixelB(m->RGBImage,x,y,(B>255)?255:(B<0)?0:B);

             }
		 }
        DeleteYUVImage(m->YUVImage);
        m->YUVImage=NULL;
        m=n;


    }

}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
    IENTRY *m , *n;
    assert(movie->Frames);
    m=movie->Frames->First;
    while(m)
    {
        n=m->Next;
        m->YUVImage = CreateYUVImage(MovieWidth(movie),MovieHeight(movie)); //image has a new image. It is an RGB image
        // iterate through YUV pixels and then do the formula to calculate each pixel
        for(int x=0; x<MovieWidth(movie); x++)
        {
            for( int y=0; y<MovieHeight(movie); y++)
             {
                int R=GetPixelR(m->RGBImage,x,y);
                int G=GetPixelG(m->RGBImage,x,y);
                int B=GetPixelB(m->RGBImage,x,y);

                int Y=((( 66*R+129*G+ 25*B+128)>>8)+ 16);
                int U=(((-38*R- 74*G+112*B+128)>>8)+128);
                int V=(((112*R- 94*G- 18*B+128)>>8)+128);

                SetPixelY(m->YUVImage,x,y,(Y>255)?255:(Y<0)?0:Y);
                SetPixelU(m->YUVImage,x,y,(U>255)?255:(U<0)?0:U);
                SetPixelV(m->YUVImage,x,y,(V>255)?255:(V<0)?0:V);

             }
		 }
        DeleteImage(m->RGBImage);
        m->RGBImage=NULL;
        m=n;

}
}
int MovieLength(const MOVIE *movie)
{
    return movie->Frames->length;
}

int MovieHeight(const MOVIE *movie)
{
    if(movie->Frames->First->RGBImage)
    {
        return movie->Frames->First->RGBImage->H;
    }//fi

    else if(movie->Frames->First->YUVImage)
    {
        return movie->Frames->First->YUVImage->H;
    }//fi esle

    else
    return 0;
}

int MovieWidth(const MOVIE *movie)
{
    if(movie->Frames->First->RGBImage)
        {
                return movie->Frames->First->RGBImage->W;
        }//fi

        else if(movie->Frames->First->YUVImage)
        {
                return movie->Frames->First->YUVImage->W;
        }//fi esle

        else
        return 0;
}

/* EOF */
