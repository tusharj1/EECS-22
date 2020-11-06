/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22,  Fall 2017       */
/*                                                                   */
/* Author: Mina Moghadam                                                */
/* Date:   11/8/2017                                                */
/*                                                                   */
/* Comments: */
/*                                                                   */
/* Please use this template to submit your hw3.                      */
/*********************************************************************/

#include <stdio.h>
#include <string.h>

#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Image.h"
#include "Test.h"

/*** function declarations ***/
/* print a menu */
void PrintMenu();
int main()
{

#ifdef DEBUG
    AutoTest();
#else
   // int rc;
    IMAGE *image=NULL;
    int option;            /* user input option */
    char fname[SLEN];        /* input file name */

    //rc = 1;
    PrintMenu();
    scanf("%d", &option);

    /* Hue() parameter */
    int hue;

    /* Posterize() parameter */
    unsigned char rbits, gbits, bbits;

    /* Noise() parameter */
    int n;

    /* MotionBlur() parameter */
    int blur_amount;

    // Enlarge parameter
    int enlarge;

    // square parameters
    int x,y,L;

    //variables for brightness and contrast
    int bright;
    int contr;


    while (option != EXIT) {
        if (option == 1) {
            printf("Please input the file name to load: ");
            scanf("%s", fname);
            if(image!=NULL)
            {
                DeleteImage(image);
            }
            image=LoadImage(fname);
        }

        /* menu item 2 - 14 requires image is loaded first */
        else if (option >= 2 && option <=11) {
            if (image == NULL)
            {
                printf("No image is read.\n");
            }
            /* now image is loaded */
            else {
                switch (option) {
                    case 2:
                        printf("Please input the file name to save: ");
                        scanf("%s", fname);
                        SaveImage(fname, image);
                        break;
                    case 3:
                        image= BlackNWhite(image);
                        printf("\"Black and White\" operation is done!\n");
                        break;
                    case 4:
                        image=Sharpen(image);
                        printf("\"Sharpen\" operation is done!\n");
                        break;
                    case 5:
                        printf("Please input the degree of changing hue: ");
                        scanf("%d", &hue);
                        Hue(image, hue);
                        printf("\"Hue\" operation is done!\n");
                        break;
                    case 6:
                        printf("Please input noise percentage: ");
                        scanf("%d", &n);
                        image=Noise(image,n);
                        printf("\"Noise\" operation is done!\n");
                        break;
                    case 7:
                        printf("Enter the number of posterization bits for R chennel (1 to 8):");
                        scanf("%hhu", &rbits);
                        printf("Enter the number of posterization bits for G chennel (1 to 8):");
                        scanf("%hhu", &gbits);
                        printf("Enter the number of posterization bits for B chennel (1 to 8):");
                        scanf("%hhu", &bbits);
                        image=Posterize(image,rbits,gbits,bbits);
                        printf("\"Posterize\" operation is done!\n");
                        break;
                    case 8:
                        printf("Please input motion blur amount: ");
                        scanf("%d", &blur_amount);
                        image=MotionBlur(image,blur_amount);
                        printf("\"Motion Blur\" operation is done!\n");
                        break;
                    case 9:
                        printf("Please input the enlarging percentage (integer between 100-120): ");
                        scanf("%d", &enlarge);
                        image=Enlarge(image,enlarge);
                        printf("\"Enlarge the image\" operation is done!\n");
                        break;
                    case 10:
                        printf("Please enter the X offset value: ");
                        scanf("%d", &x);
                        printf("Please enter the Y offset value: ");
                        scanf("%d", &y);
                        printf("Please input the cropped square size: ");
                        scanf("%d", &L);
                        image=Square(image,x,y,L);
                        printf("\"Square\" operation is done!\n");
                        break;
                    case 11:
                        printf("Please input the brightness level (integer between -255 - 255): ");
                        scanf("%d", &bright);
                        printf("Please input the contrast level (integer between -255 - 255): ");
                        scanf("%d", &contr);
                        image=BrightnessAndContrast(image,bright,contr);
                        printf("\"Brightness and Contrast Adjustment\" operation is done!\n");
                        break;
		    default:
                        break;

                }
            }
        }

        else if (option == 12) {
            AutoTest();
            //rc = SUCCESS;    /* set returned code SUCCESS, since image is loaded */
        }
        else if (option != 13) {
            printf("Invalid selection!\n");
        }

        /* Process finished, waiting for another input */
        PrintMenu();
        scanf("%d", &option);
    }
    printf("You exit the program.\n");

     if (image != NULL)
        {
        DeleteImage(image);
        image = NULL;
        }

#endif

    return 0;
}


/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void PrintMenu()
{

    printf("\n-------------------------\n");
    printf("1: Load a PPM image\n");
    printf("2: Save the image in PPM and JPEG format\n");
    printf("3: Change the color image to black and white\n");
    printf("4: Sharpen the image\n");
    printf("5: Change the hue of image\n");
    printf("6: Add Noise to an image\n");
    printf("7: Posterize an image\n");
    printf("8: Add Motion Blur to an image\n");
    printf("9: Enlarge the picture by percentage\n");
    printf("10: Crop a square portion of the image\n");
    printf("11: Adjust the brightness and contrast of an image\n");
    printf("12: Test all functions\n");
    printf("13: Exit\n");
    printf("\n-------------------------\n");
    printf("Please make your choice: ");
}
