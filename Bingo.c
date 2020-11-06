#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"

int main(void)
{
    int m,n; // initialze of variables for no of players and tiles
             // m is the number of players and n is the number of tiles


    FILE *fp; // file pointer
    fp=fopen ("BingoSampleInput1.txt","r"); // initiating the process to read the file.
    if(fp==NULL)
    {
            fprintf(stderr,"Can't open input file BingoSampleInput1! \n");
            exit(1);

    }

    fscanf(fp," %d %d \n", &n, &m); // we have taken a note of no of players and the no of tiles

    char namesList[n][64]; // initilaize list for storing the names
    bool bingoName[n];     // initialize list for storing the names of players that got BINGO!
    int tiles[n][m][m];    // to make my matrix
    int lastLine[m*m];     // we need this for the last line of our input file
    int tracker [m*m];     // tracker keeps the track of numbers that have been called and matches in case of BINGO!
    for (int x=0 ; x<n ; x++)
    {
        fscanf(fp, "%64s\n", namesList[x]);   // as the max char allowed in names in 64
        bingoName[x] = false;                 // by default we make all the names in the bingoName list to be false
        for (int i=0 ; i<m ; i++)             // Loop begins
        {
            for (int t=0 ; t<m ; t++)
            {
                fscanf(fp, "%d ", &tiles[x][i][t]);        //read the numbers from the text file
            }
        }
    }

    for (int x=0 ; x<m*m ; x++)                          // we need this loop to read the last line of my text file i.e the list of called numbers
    {
        fscanf(fp, "%d ", &lastLine[x]);
    }

    printf("Start the game \n");

    for (int x=0 ; x<n ; x++)
    {
        printf("*** %s ***\n", namesList[x]);
        for (int i=0 ; i<m ; i++)
        {
            for (int t=0 ; t<m ; t++)
            {
                printf("%d ", tiles[x][i][t]);
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("\n");

    for (int h=0 ; h<m*m ; h++)
    {
        bool anybingo = false;

        printf("Caller called: %d \n", lastLine[h]);
        for (int x=0 ; x<n ; x++)
        {
            bool bingo = false;

            int countDiagonal1 = 0;
            for (int c=0 ; c<m ; c++) // left to right diagonal
            {
                for( int g=0 ; g<m*m ; g++)
                {
                    if(tiles[x][c][c] == tracker[g] || tiles[x][c][c] == lastLine[h]) // checking if the diagonal is true
                    {
                        countDiagonal1++;
                        break;
                    }
                }
            }
            if (countDiagonal1 == m)
            {
                bingo = true;
                anybingo = true;
            }

            int countDiagonal2 = 0;
            for (int c=0 ; c<m ; c++) // right to left diagonal
            {
                for( int g=0 ; g<m*m ; g++)
                    {
                        if(tiles[x][c][m - c - 1] == tracker[g] || tiles[x][c][m - c - 1] == lastLine[h])  //checking if the diagonal is true
                        {
                            countDiagonal2++;
                            break;
                        }
                    }

            }
            if (countDiagonal2 == m)
            {
                bingo = true;
                anybingo = true;
            }

            for( int c=0 ; c<m ; c++)                            // row by row
            {
                int countRow = 0;
                for( int p=0 ; p<m ; p++)
                {
                    for( int g=0 ; g<m*m ; g++)
                    {
                        if(tiles[x][c][p] == tracker[g] || tiles[x][c][p] == lastLine[h])       //checking if any one of my rows has become true
                        {
                            countRow++;
                            break;
                        }
                    }
                    if (countRow == m)
                    {
                        bingo = true;
                        anybingo = true;
                    }

                }
            }

            for( int c=0 ; c<m ; c++)                              // column by column
            {
                int countCol = 0;
                for( int p=0 ; p<m ; p++)
                {
                    for( int g=0 ; g<m*m ; g++)
                    {
                        if(tiles[x][p][c] == tracker[g] || tiles[x][p][c] == lastLine[h])       //checking if any one of my columns has become true
                        {
                            countCol++;
                            break;
                        }
                    }
                    if (countCol == m)
                    {
                        bingo = true;
                        anybingo = true;
                    }
                }
            }

            if (bingo == true)
            {
                printf("*** %s Bingo! ***\n", namesList[x]);
                bingoName[x] = true;
            }
            else
            {
                printf("*** %s ***\n", namesList[x]);
            }
            for (int i=0 ; i<m ; i++)
            {
                for (int t=0 ; t<m ; t++)
                {
                    if(tiles[x][i][t]== lastLine[h])                    // if the number called matches with the number present in the tiles, we turn it to green
                    {
                        printf("%s", KGRN);
                    }
                    else
                    {
                        for (int k=0 ; k<h+1 ; k++)
                        {
                            if(tiles[x][i][t]==tracker[k])
                            {
                                printf("%s", KRED);                     // color it red after we move on to the next number that is being called
                            }
                        }
                    }
                    printf("%d ", tiles[x][i][t]);                      //  other tiles be black ( reset to be black )
                    printf("%s", KNRM);
                }
                printf("\n");
            }
            printf("\n");
        }
        tracker[h]=lastLine[h];
        if (anybingo == true)
        {
            printf("%d ", lastLine[h]);
            for( int r = 0 ; r<n ; r++)
            {
                if (bingoName[r] == true)
                {
                    printf("%s ", namesList[r]);
                }
            }
            break;
        }
        else
        {
            printf("\n");
        }

    }

    printf("\n");
    return 0;


}
