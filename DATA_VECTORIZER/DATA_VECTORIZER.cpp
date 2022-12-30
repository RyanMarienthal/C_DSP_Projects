// TIME_PROJECT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#define STRG_SIZE 20
//operative variables
unsigned int T; 
float* STORAGE[STRG_SIZE];
float CURRENT_OUT;
bool STRG_INIT;
unsigned int STRG_POS = 1;
unsigned int TIME_POS;
int TIME_POS_M;
int STRG_POS_M;
FILE* SG_FILE;

//user variables

//sets time of data stored
unsigned int TIME = 150;
//activates vector operation
bool VECTOR_OP = 1;


int main()
{
	//Memory just for output
	float* CURRENT_STRG = (float*)malloc(sizeof(float) * TIME);
	
	//set output file
	SG_FILE = fopen("ROOT DIRECTORY", "w");
	
	//Set to while(1) for continous operation, runtime is arbitrary for testing
	while (T < 2000) 
	{
		//set Input Function
		CURRENT_OUT = 2*cos(T/7.2)+3*cos(2*T)+1.25*cos(1.3*T)+2*cos(100*T);
		CURRENT_STRG[TIME_POS] = CURRENT_OUT;
		
		//check if a vector is full
		if (!STRG_INIT) 
		{
			free(STORAGE[STRG_POS]);
			//reset init
			STRG_INIT = 1;
			//allocate vector memory
			STORAGE[STRG_POS] = (float*)calloc(TIME, sizeof(float) * TIME);

			
		}
		//iterate through vector
		if (TIME_POS < TIME-1)
		{
			
			
			//store value
			STORAGE[STRG_POS][TIME_POS] = CURRENT_OUT;

			//VECTOR OPERATION, BASE ON TIME POS WILL AFFECT SIGNAL CYCLICALLY
			if (VECTOR_OP)
			{
				STORAGE[STRG_POS][TIME_POS] *= 1 / (pow(1.2, TIME_POS/10));

			}
			TIME_POS++;
		}
		else
		{
			//reset Pos in Vector
			TIME_POS = 0;
			
			//output to file, formatted as white spaces in between for GNUplot
			//GNUPLOT COMMAND: Set Source directory the same as SG_FILE Direcory
			//plot "SOURCE_DIRECTORY" using 1:2 with lines, "SOURCE_DIRECTORY" using 1:4 with lines
					for (int i = 0; i < TIME - 1; i++)
					{
						fprintf(SG_FILE, "%d", T + i);
						fprintf(SG_FILE, " ");
						fprintf(SG_FILE, "%.2f", CURRENT_STRG[i]);
						fprintf(SG_FILE, " ");
						fprintf(SG_FILE, "%d", T+i);
						fprintf(SG_FILE, " ");
						fprintf(SG_FILE, "%.2f", STORAGE[STRG_POS][TIME_POS+i]);
						fprintf(SG_FILE, "\n");
					}

			//reset storage
			STRG_INIT = 0;
			//iterate through vector storage
			if (STRG_POS < STRG_SIZE-1)
			{
				STRG_POS++;
			}
			else
			{
				STRG_POS = 0;
			}
		}
		
		

		
		
		T += 1;
	}
	fclose(SG_FILE);
}
