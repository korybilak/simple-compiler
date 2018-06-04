#include "file_util.h"
#include "scanner.h"
#include "parser.h"

/*
CSC 460 Language Translation
Program #4 -  Compiler
Kory Bilak	BIL7208@calu.edu


version .1 made 1/22/2018 - base program, works if you dont try to break it, only some error checking working properly
version .2 made 1/24/2018 - fixed errors (all errors involving getfilename (made more robust)
version .3 made 1/26/2018 - fixed more errors (all errors involving checkfile, (made more robust)
version .4 made 1/27/2018- fixed more errors (all errors involving openfile, (made more robust)
version 1.0 made 1/28/2018- passed all checks I could think of, including if user types in more than 99 characters (only takes first 99 user types, extra space to add extension), code cleanup, further comments made
version 1.1 made 2/02/2018 - created scanner.c and scanner.h
version 1.2 made 2/03/2018 - started scanner function
version 1.3 made 2/04/2018 - added listing placer function
version 1.4 made 2/05/2018 - added ouput placer funciton
version 1.5 made 2/06/2018 - added appending temp to output and delete temp file
version 1.6 made 2/07/2018 - fixed scanner function - now works for up to 100 characters, and doesnt crash if there are more
version 1.7 made 2/08/2018 - scan for eof now shows up as not an error, and shows up properly on output
version 1.8 made 2/09/2018 - output placer function now spaces things out bettter and is way nicer
version 1.9 made 2/09/2018 - listing placer function displays correct line numbers now
version 2.0 made 2/10/2018 - scanner now passes all tests I can throw at it. 
version 2.01 made 2/12/2018 - fixed some stuff in file_util, it wasnt asking for a new input file if the input doesnt exist, now it does
version 2.02 made 2/14/2018 - added else, and, or, not, <=, >=, and <> and tested to work properly
version 2.03 made 2/17/2018 -added comments, tested one more time. added * and / if we use them later. - happy birthday to me btw.
version 2.04 made 2/17/2018 - fixed a small - where it would show an error if there was an error before an eof, and also if there was an eof after a space (regression)
version 2.05 made 2/20/2018 - fixed another error where scaneof would  be considered an error (another regression), also added endwhile, while, got rid of goto, and changed the names of some tokens.
version 2.1 made 2/12/2018 - added non-destructive functionality to our scanner
version 2.2 made 2/22/2018 - added the main bulk of our parser file, not tested yet
version 2.3 made 2/23/2018 - adjusted our listing file to have syntax errors
version 2.3 made 2/24/2018 - adjusted our output file to display buffer instead of hard coded stuff, also displays the line like the listing file
version 2.4 made 2/25/2018 - adjusted our listing file to display if compiled without errors
version 2.6 made 2/26/2018 - adjusted our syntax errors to be displayed after each line
version 2.7 made 2/27/2018 - adjusted our scanner because it was nextToken was still able to add to the line buffer
version 2.8 made 2/27/2018 - adjusted our scanner to protect from nextToken able to call listing_placer
version 2.9 made 3/01/2018 - adjusted our parser, now works for multiple errors in one line
version 2.9.1 made 3/02/2018 - adjusted our grammer, parser now handles syntax properly
version 2.9.2 made 3/03/2018 - testing/revisions for parser and scanner
version 2.9.3 made 3/04/2018 - adjusted our grammer to match new stuff
version 2.9.4 made 3/05/2018 - found an error in the grammar when using () with a not
version 2.9.5 made 3/06/2018 - fixed errors
version 2.9.6 made 3/07/2018 - adjusted program for new grammar, not works with () now
version 2.9.7 made 3/08/2018 - adjusted program for anticipation of and and or having (), tested and working, not yet fully implemented
version 3.0 made 3/08/2018 - fully tested and working parser
version 3.1 made 4/01/2018 - added the start method
version 3.2 made 4/02/2018 - added the finish method, and the generates mathmatical operations
version 3.3 made 4/03/2018 - generates the ints and temps
version 3.4 made 4/04/2018 - generates the reads
version 3.5 made 4/05/2018 -generates the writes
version 3.6 made 4/06/2018 -started to generate if and while
version 3.7 made 4/07/2018 -generates if statements
version 3.8 made 4/08/2018 -generates whiles
version 3.9 made 4/09/2018 - checks for any data after an and or or, generates an appropriate error message without
version 4.0 made 4/10/2018 - generates a line of code if program compiled without errors
version 4.0.1 made 4/18/2018 - added anything that was missing, cleanup code, commented, tested compiling of both non error code and error, only compiles code without errors!

to compile: go on command line and cd into your folder
0)if on flash drive first do E: or F:
1) cd to whererever
2) gcc -o <*program_name> main.c file_util.c scanner.c
3) <program_name> <**arg2> <**arg3>
*program_name can be whatever you want
** arg2 and arg3 are optional, arg2 is the input file name, and arg 3 is the output file
***not sure how to compile on compiler, I only use the command line
*/


FILE *input, *output, *list, *tempfile; //files
char inputfile[103], outputfile[103], temporary1[103], buffer[103], linebuffer[103], errorbuffer[103],syntaxBuffer[103];   //character arrays - made user's input only fill up first 99 slots with scanf, so that we can have .in, .out, .lis, .bak, and /0 for extensions
int expectedToken[100];

int main(int argc, char *argv[])
{
int c;
int true, true2, token, sytax_error;
int destruct;
printf(" all file names must be less than 100 characters long\n"); //windows file name size is 255 characters total, including path to the file, I think 100 is fair

	if(argc <= 3)
	{
	getfilename(argc, argv);
		if(inputfile[0] != '\0')       //if the command line is not blank
		{
		true2 = checkfile(true2);	//check to see if the input file exists
			if(true2 == 1)
			{
		
			true = openfile(true);
				if(true == 1)
				{
				printf("Exiting\n");         //user chose to quit the program instead of changing output file
				}
				else // if all is well, do copy file and close file
				{
				int i = 0;
				while( i < 99)
				{
				expectedToken[i] = 0;
				i++;
				}
				while(token != SCANEOF)
				{
				//token = scanner(destruct);
			    //listing_placer(token,0);
				//output_placer(token);
				token = systemGoal();
				} 
				//add everything else here
				file_append();
				closefile();
				}
			}
			else
			{
				
			}
		}
		else
		{
		printf("user chose not to type in input file, exiting\n");
		}
	}else
	{
	printf("Too many parameters typed exiting\n");
	}

system("pause"); //useful if not compiled and run on command prompt (but why wouldn't you use terminal, its convenient)
return EXIT_SUCCESS; //exits program
}
