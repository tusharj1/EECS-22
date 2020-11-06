/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2018                     */
/*                                                                   */
/* Author: Jordan Bonecutter                                         */
/*                                                                   */
/* IterativeFilter.c: file for iterative filters                     */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#include "IterativeFilter.h"

MOVIE *doIterativeFilter(IMAGE *image, iterableFilter filter, int start, int end, int change)
{
    MOVIE *m = CreateMovie();
    if(start<end)
    {
        for(int i=start ; i<=end; i=i+change)
        {
            IMAGE *copy = CopyImage(image);
            AppendRGBImage(m->Frames,(filter)(copy,i));
        }
    }
    else
    {
        for(int i=end ; i<=start ; i=i+change)
        {
            IMAGE *copy = CopyImage(image);
            AppendRGBImage(m->Frames,(filter)(copy,i));
        }
    }
    return m;
}
