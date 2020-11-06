Student Name - Tushar Jain
Student ID : 82777648
Assignment 3:
For assignment 3 we were required to refer to Assignment 2 and work on new function such as: Noise, Posterize and Motion Blur. According to algorithms in the discussion we shall formulate our calculations correctly to manipulate the R,G,B values of our image accroding to our aim.
Our aim was to also make sure to divide our program into multiple modules and compile them with the help of Makefile tool.
As per the requirements, all files were divided into necessary modules and the headerfiles were included to ensure their linkage.
For Noise, If the percentage of noise is n, then the number of noise pixels added to the image is given by n*WIDTH*HEIGHT / 100, where WIDTH and HEIGHT are the image size. 
For Motion Blur, we can average each pixel with those in a specific direction, which gives the
illusion of motion. I calculated the new pixel's value as half  of its origninal value. The other half is averaged from a fixed number of pixel to the up. 
For Posterize, I calculated the nth least signinficant bit of the color intensity value to be 0, and the n-1 bits to be all 1.

