#include "Advanced.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

/* Add noise to an image */
//void Noise(int n, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
IMAGE *Noise(IMAGE *image, int n)
{
	int x, y, i;
	int num; /* number of noise added */
	num = ( n*ImageHeight(image)*ImageWidth(image) )/100;
	srand(time(NULL));

	for ( i = 0; i < num; i++ )
        {
            x = ( (double)rand()/RAND_MAX )*(ImageWidth(image)-1);
            y = ( (double)rand()/RAND_MAX )*(ImageHeight(image)-1);
            SetPixelR(image,x,y,255);
            SetPixelG(image,x,y,255);
            SetPixelB(image,x,y,255);
	    }
	    return image;
}

/* make the image posterized */
//void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits)
IMAGE *Posterize(IMAGE *image, unsigned int rbits,unsigned int gbits, unsigned int bbits)
{
	int x, y;
	for(x=0; x<ImageWidth(image); x++) {
		for(y=0; y<ImageHeight(image); y++) {
			unsigned char one = 1;
			int i;
			for(i=0; i<rbits-1; i++) {
				unsigned char b1 = (GetPixelR(image,x,y) | one);
				SetPixelR(image,x,y,b1);
				one <<= 1;
			}
			one = ~one;
			unsigned char b2 = (GetPixelR(image,x,y) & one);
			SetPixelR(image,x,y,b2);

			one = 1;
			for(i=0; i<gbits-1; i++) {
                unsigned char b3 = (GetPixelG(image,x,y) | one);
				SetPixelG(image,x,y,b3);
				one <<= 1;
			}
			one = ~one;
			unsigned char b4 = (GetPixelG(image,x,y) & one);
			SetPixelG(image,x,y,b4);

			one = 1;
			for(i=0; i<bbits-1; i++) {
				unsigned char b5 = (GetPixelB(image,x,y) | one);
				SetPixelB(image,x,y,b5);
				one <<= 1;
			}
			one = ~one;
			unsigned char b6 = (GetPixelB(image,x,y) & one);
			SetPixelB(image,x,y,b6);
		}
	}
	return image;
}

/* add motion blur to the image */
//void MotionBlur(int BlurAmount, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
IMAGE *MotionBlur(IMAGE *image, int BlurAmount)
{
	int x,y,m;
	int temp_r , temp_g , temp_b;

	for (x = 0; x <ImageWidth(image); x++)
	{
        	for (y = ImageHeight(image) - 1; y >= 0 ; y--)
		{
			int count = 0;
			temp_r = temp_g = temp_b = 0.0;
			for (m = 1; m<=BlurAmount ; m++)
			{
				//if ((x-m) >= 0)
				if((y-m) >= 0)
				{
					//temp_r += R[x][y-m];
					temp_r+= GetPixelR(image,x,y-m);
					temp_b += GetPixelB(image,x,y-m);
					temp_g += GetPixelG(image,x,y-m);
					count++;
				}
			}
			count = (count==0)?1:count;
			unsigned char a1 = temp_r / 2.0 / count + GetPixelR(image,x,y) / 2.0;
			SetPixelR(image,x,y,a1);
			unsigned char a2 = temp_b / 2.0 / count + GetPixelB(image,x,y) / 2.0;
			SetPixelB(image,x,y,a2);
			unsigned char a3 = temp_g / 2.0 / count + GetPixelG(image,x,y)/ 2.0;
			SetPixelG(image,x,y,a3);
		}
	}
	return image;

}
IMAGE *Square(IMAGE *image,int x, int y, int L)
{
    IMAGE *sqimg = CreateImage(L,L);

    for ( int i=x ; i<L+x ; i++)
    {
        for(int j=y ; j<L+y ; j++)
        {
            SetPixelR(sqimg,i-x,j-y,GetPixelR(image,i,j));
            SetPixelG(sqimg,i-x,j-y,GetPixelG(image,i,j));
            SetPixelB(sqimg,i-x,j-y,GetPixelB(image,i,j));
        }
    }
    DeleteImage(image);
    image = NULL;
    return sqimg;
}

IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast)
{
    int r,g,b;
    int r1,g1,b1;
    double factor = (double)(259 * (contrast + 255)) / (double)(255 * (259 - contrast));

    for( int i=0 ; i<ImageWidth(image); i++)
    {
        for(int j=0 ; j<ImageHeight(image); j++)
        {
            r=GetPixelR(image,i,j)+brightness;
            g=GetPixelG(image,i,j)+brightness;
            b=GetPixelB(image,i,j)+brightness;
            r1=r;
            g1=g;
            b1=b;
            //new_pixel_value = (int)(factor * (pixel_value - 128) + 128);
            r1=(int)(factor * (r1 - 128) + 128);
            g1=(int)(factor * (g1 - 128) + 128);
            b1=(int)(factor * (b1 - 128) + 128);


            SetPixelR(image,i,j,(r1>255)?255:(r1<0)?0:r1);
            SetPixelG(image,i,j,(g1>255)?255:(g1<0)?0:g1);
            SetPixelB(image,i,j,(b1>255)?255:(b1<0)?0:b1);
        }
    }
    return image;
}

IMAGE *Enlarge(IMAGE *image, int percentage)
{
    IMAGE *enlimage = CreateImage(ImageWidth(image) * percentage / 100.00, ImageHeight(image) * percentage / 100.00);

    for (int x = 0 ; x < ImageWidth(enlimage) ; x++)
    {
        for (int y = 0 ; y < ImageHeight(enlimage) ; y++)
        {
            unsigned int original_x = round(x / (percentage / 100.00));
            unsigned int original_y = round(y / (percentage / 100.00));
            SetPixelR(enlimage, x, y, GetPixelR(image, original_x, original_y));
            SetPixelG(enlimage, x, y, GetPixelG(image, original_x, original_y));
            SetPixelB(enlimage, x, y, GetPixelB(image, original_x, original_y));
        }
    }

    DeleteImage(image);
    image = NULL;
    return enlimage;
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
