#######################################################################
# Homework Assignment 5, for EECS 22, Winter 2020
#
#
# Makefile: Makefile for HW 5
#
#######################################################################

# Variables
FLAGS = -ansi -std=c99 -Wall -g

# Default target
all: MovieLab

######################### Generate object files #######################
# Target for FileIO.o
FileIO.o: FileIO.h FileIO.c Image.h
	gcc -c FileIO.c -o FileIO.o $(FLAGS)

# Target for DIPs.o
DIPs.o: DIPs.h DIPs.c Image.h
	gcc -c DIPs.c -o DIPs.o $(FLAGS)

# Target for Image.o
Image.o: Image.h Image.c
	gcc -c Image.c -o Image.o $(FLAGS)
	
# Target for MovieIO.o
MovieIO.o: Movie.h MovieIO.h MovieIO.c FileIO.h Constants.h
	gcc -c MovieIO.c -o MovieIO.o $(FLAGS)

# Target for IterativeFilter.o
IterativeFilter.o: Image.h IterativeFilter.h Movie.h IterativeFilter.c
	gcc -c IterativeFilter.c -o IterativeFilter.o $(FLAGS)

# Target for MovieLab.o
MovieLab.o: MovieLab.c Constants.h DIPs.h FileIO.h Image.h IterativeFilter.h MovieIO.h Movie.h
	gcc -c MovieLab.c -o MovieLab.o $(FLAGS)

# Target for Movie.o
Movie.o: Movie.c Movie.h ImageList.h
	gcc -c Movie.c -o Movie.o $(FLAGS)

# Target for ImageList.o
ImageList.o: ImageList.c Image.h ImageList.h
	gcc -c ImageList.c -o ImageList.o $(FLAGS)


######################### Generate the executable #####################
# Target for MovieLab
MovieLab: ImageList.o DIPs.o MovieIO.o Image.o Movie.o FileIO.o IterativeFilter.o MovieLab.o
	gcc -WALL ImageList.o DIPs.o MovieIO.o Image.o Movie.o FileIO.o IterativeFilter.o MovieLab.o -o MovieLab -lm


###############################  others  ##############################
# Target for clean
clean: 
	rm -f MovieLab *.yuv *.o