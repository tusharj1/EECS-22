#ifndef ADVANCED_H_INCLUDED_
#define ADVANCED_H_INCLUDED_

#include "Constants.h"
#include "Image.h"


/* add noise to an image */
//void Noise( int percentage, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);
IMAGE *Noise(IMAGE *image, int percentage);
/* posterize the image */
//void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits);
IMAGE *Posterize(IMAGE *image, unsigned int rbits, unsigned int gbits, unsigned int bbits);
/* motion blur */
//void MotionBlur(int BlurAmount, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);
IMAGE *MotionBlur(IMAGE *image, int BlurAmount);
// makes the image square
IMAGE *Square(IMAGE *image,int x, int y, int L);
// enlarge the image by percentage
IMAGE *Enlarge(IMAGE *image, int percentage);
// change the brightness and contrast
IMAGE *BrightnessAndContrast(IMAGE *image, int brighntess, int contrast);

#endif /* ADVANCED_H_INCLUDED_ */

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
