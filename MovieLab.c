#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"
#include "MovieIO.h"
#include "IterativeFilter.h"

int main(int argc, char *argv[])
{
    int start;
    int end;
    int step;
    int frameNum;
    unsigned int width;
    unsigned height;
    iterableFilter filter;
    int reverse = 0;

    IMAGE *input = NULL;

    char *imfname;
    char *exfname;

    int importFlag = 0;
 

    
    for(int n = 0; n < argc; n++)
    {
        
        if(!strcmp(argv[n], "-i"))
        {
            
            if(n == argc - 1)
            {
                printf("\n\tPlease provide the name of the image you want to import\n");
                return 0;
            }

            input = LoadImage(argv[++n]);

            if(!input)
            {
                printf("\n\tThe image file %s could not be read\n", argv[n]);
                return 0;
            }

          
           importFlag = 1;
        }

       
        else if(!strcmp(argv[n], "-m"))
        {
            
            if(n == argc - 1)
            {
                printf("\n\tPlease provide the name of the movie you want to import\n");
                return 0;
            }

            imfname = argv[++n];

           
            importFlag = 2;

        }

        
        else if(!strcmp(argv[n], "-hue"))
        {
            filter = &HueRotate;
        }

        
        else if(!strcmp(argv[n], "-bw"))
        {
            filter = &BlackNWhite;
        }

        
        else if(!strcmp(argv[n], "-start"))
        {
            
            if(n == argc - 1)
            {
                printf("\n\tPlease provide the start parameter\n");
                return 0;
            }

            start = atoi(argv[++n]);
        }

        
        else if(!strcmp(argv[n], "-end"))
        {
           
            if(n == argc - 1)
            {
                printf("\n\tPlease provide the end parameter\n");
                return 0;
            }

            end = atoi(argv[++n]);
        }

        
        else if(!strcmp(argv[n], "-step"))
        {
            
            if(n == argc - 1)
            {
                printf("\n\tPlease provide the step parameter\n");
                return 0;
            }

            step = atoi(argv[++n]);
        }

        
        else if(!strcmp(argv[n], "-o"))
        {
           
            if(n == argc - 1)
            {
                printf("\n\tPlease provide the name of the output file\n");
                return 0;
            }

            exfname = argv[++n];
        }

        
        else if(!strcmp(argv[n], "-f"))
        {
            
            if(n == argc - 1)
            {
                printf("\n\tMissing argument for the number of frames!\n");
                return 0;
            }

            frameNum = atoi(argv[++n]);
        }

        
        else if(!strcmp(argv[n], "-reverse"))
        {
            reverse = 1;
        }

        
        else if(!strcmp(argv[n], "-s"))
        {
            
            if(n == argc - 1)
            {
                printf("\n\tMissing argument for the resolution of the frame!\n");
                return 0;
            }
            char *tok1 = strtok(argv[++n],"x");
            char *tok2 = strtok(NULL,"x");

            width = atoi(tok1);
            height = atoi(tok2);
        }
    }

    
    if(!importFlag)
    {
        printf("\nNo -i nor -m for input file to read\n");
        return 0;
    }
    else if(importFlag == 1)
    {
        MOVIE *m;

        m=doIterativeFilter(input, filter, start, end, step);
        DeleteImage(input);
        input = NULL;

        RGB2YUVMovie(m);
        int save = SaveMovie(exfname, m);
        DeleteMovie(m);
        m = NULL;
        if(save)
        {
            printf("\nSaveMovie failed!\n");
        }
    }
    else if(importFlag == 2)
    {

        MOVIE *m = LoadMovie(imfname, frameNum, width, height);

        if(!m)
        {
            printf("The movie file %s could not be read\n", imfname);
            return 0;
        }

        if(reverse)
        {
            ReverseImageList(m->Frames);
            printf("Operation Reverse is done!\n");
        }
        int save = SaveMovie(exfname, m);
        DeleteMovie(m);
        m = NULL;

        if(save)
        {
            printf("\nSaveMovie failed!\n");
        }
        
    }
    return 0;
}

/* EOF */
