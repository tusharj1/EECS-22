/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"

/* Create a new image entry */
IENTRY *CreateImageEntry(void)
{
    IENTRY *i;
    i=malloc(sizeof(IENTRY));
    if(! i)
    {
        perror("Out of memory! Aborting...");
        exit(10);
    }
    i->List=NULL;
    i->Next=NULL;
    i->Prev=NULL;
    i->YUVImage=NULL;
    i->RGBImage=NULL;

    return i;
}

/* Delete image entry (and image objects)*/
void DeleteImageEntry(IENTRY *entry)
{assert(entry);
    if(entry->RGBImage)
    {
        DeleteImage(entry->RGBImage);
        entry->RGBImage=NULL;
    }
    else if(entry->YUVImage)
    {
        DeleteYUVImage(entry->YUVImage);
        entry->YUVImage=NULL;
    }

    if(entry->List)
    {
        if(entry->List->length==1)
        {

            entry->List->First=NULL;
            entry->List->Last=NULL;
        }
        else if(entry->List->Last== entry)
        {

            entry->Prev->Next= NULL;
            entry->List->Last= entry->Prev;
        }
        else if(entry->List->First==entry)
        {
            entry->Next->Prev=NULL;
            entry->List->First=entry->Next;
        }
        else
        {
            entry->Next=entry->Prev;
            entry->Prev=entry->Next;
        }
        entry->List->length=entry->List->length-1;
    }
    free(entry);

}

/* Create a new image list */
ILIST *CreateImageList(void)
{
    ILIST *l;
    l=(ILIST *)malloc(sizeof(ILIST));
    if(! l)
    {
        perror("Out of memoery! Aborting...");
        exit(10);
    }
    l->First=NULL;
    l->Last=NULL;
    l->length=0;
    return l;

}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
    IENTRY *e, *n;

    assert(list);
    e = list->First;
    while(e)
    {
        n=e->Next;
        DeleteImageEntry(e);
        e=n;
    }
    free(list);


}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
    assert(RGBimage);
    assert(list);
    IENTRY *newent = CreateImageEntry();
    newent->RGBImage=RGBimage;
    newent->List=list;

    if(newent->List->length==0)
    {
         newent->List->First=newent;
         newent->List->Last=newent;
    }
    else
    {
        newent->Prev=newent->List->Last;
        newent->Prev->Next=newent;
        newent->List->Last=newent;
    }
    newent->List->length=newent->List->length+1;


}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{
    assert(YUVimage);
    assert(list);
    IENTRY *newent = CreateImageEntry();
    newent->YUVImage=YUVimage;
    newent->List=list;

    if(newent->List->length==0)
    {
         newent->List->First=newent;
         newent->List->Last=newent;
    }
    else
    {
        newent->Prev=newent->List->Last;
        newent->Prev->Next=newent;
        newent->List->Last=newent;
    }
    newent->List->length=newent->List->length+1;

}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
    assert(list);
    IENTRY *flist = list->First;
    IENTRY *temp = list->First;
    IENTRY *n;
    IENTRY *p;
    IENTRY *l = list->Last;

    while(temp)
    {
        p=temp->Prev;
        n=temp->Next;
        temp->Next=p;
        temp->Prev=n;
        temp=n;
    }
    list->First=l;
    list->Last=flist;
}























/* EOF */
