#include "file_util.h"
#include "scanner.h"


//GET_FILE_NAME
int getfilename(int argc, char *argv[]) // getting the file name from user, accepts 2 character strings for input and output respectively
{
	
int Length, check, i=0;

	if(argc == 1)       // there is one string entered into the command line as user input
	{
	printf("please enter an input file name\n");
	fflush(stdin); //flush our input stream
	scanf("%99[^\n]%*c", inputfile); // attempting to scan again for aappropriate string, checks for if just enter typed
		if(inputfile[0] == '\0')  
		{	
		
		}
		else
		{
		printf("please enter a output file name\n");			// the input file was found
		fflush(stdin);
		scanf("%99[^\n]%*c", outputfile);      //scan user input, place into output file variable
			
			if(outputfile[0] == '\0') // of the user typed in nothing, name output file input file's name with .out extension
			{
			strcpy(outputfile, inputfile);  //copy string of inputfile into outputfile
			Length = strlen(outputfile);    //set the Length var to the string length of outputfile
				while( i <= Length)         
				{
					if(outputfile[i] == '.')      //if reach the '.' character
					{
					//outputfile[i+1] = 'o';        //add the .out extension
					//outputfile[i+2] = 'u';
					//outputfile[i+3] = 't';
					outputfile[i+1] = 'c';
					check = 1;                   //set the check flag to 1
					i= i+2;                      //adjust the loop counter
					}
					if(check == 1 && i <= Length)
					{
					outputfile[i] = '\0';        //set to NULL
					}
				i++;                             //inc the counter
				}
			}
		}
	}
	else if(argc == 2)         //there are 2 strings entered into the command line  as user input
	{
	strcpy(inputfile, argv[1]);        //copy the user input into the inputfile var
	fflush(stdin);                     //flush the input stream
	printf("please enter a output file name\n");
	scanf("%99[^\n]%*c", outputfile);           //scan user input, place into outputfile 
		if(outputfile[0] == '\0') // of the user typed in nothing, name output file input file's name with .out extension
		{
		strcpy(outputfile, inputfile);      //copy string of inputfile into outputfile 
		Length = strlen(outputfile);        //set the Length var to the string length of outputfile
			while( i <= Length)
			{
				if(outputfile[i] == '.')    //if reach the '.' character
				{
				//outputfile[i+1] = 'o';      //add the .out extension
				//outputfile[i+2] = 'u';
				//outputfile[i+3] = 't';
				outputfile[i+1] = 'c';
				check = 1;                  //set check flag to 1
				i= i+2;                     //adjust the loop counter
				}
				if(check == 1 && i <= Length+1)
				{
				outputfile[i] = '\0';          //set to NULL
				}
			i++;                               //inc the counter
			}
		}
	}
	else if (argc == 3)   // there are 3 strings entered into the commmand line  as user input
	{
	strcpy(inputfile, argv[1]);    //copy user inputted string into inputfile
	strcpy(outputfile, argv[2]);   //copy user inputted string into outputfile
	}
	else
	{
	printf("Too many command line parameters, exiting\n");   //print this error if argc >3 (or <0)?
	}
	
}



//CHECK_FILE: checks if file is a valid name, may change files extension if file has no extension, or if file typed in has no extension
// will add a .in or .out extenstion to see if it exists
int checkfile(int true2)
{
char temporaryfile[103];
int Length;
int check = 0, check2 = 0, check3 = 0; 
int i = 0;

Length = strlen(inputfile);         //enter the string length of the inputfile var into the var Length

	if((Length > 0) && (Length <= 99))
	{
		while (Length > 0)
		{
			if(inputfile[Length] == '.')    //if reached the '.' character
			{
			check = 1;           //set the check flag to 1
			Length--;
			}
			if(check == 1 && inputfile[Length] == '.')
			{
			check2 = 1;      //set check2 flag to 1
			}
		Length --;  //subtract from the length
		}
	}	
	if( check != 1)
	{
	strcpy(temporaryfile, inputfile );  //copies string from inputfile  to  temporaryfile 
	strcat(temporaryfile, ".in");   // add the .in extension to  temporaryfile 
	rename(inputfile, temporaryfile);
	strcpy(inputfile,temporaryfile); //copies temporaryfile  to inputfile
	}
	
check = 0;                           //reset check back to 0
Length = strlen(outputfile);         //enter the string length of the outputfile var into the var Length

	if((Length > 0) && (Length <= 99)) //checks for a '.' if more than 1 exists, will show error later in checkfile
	{
		while (Length > 0)
		{
			if(outputfile[Length] == '.')
			{
			check = 1;               //set check value to 1
			Length--;
			}
			if(check == 1 && outputfile[Length] == '.')
			{
			check3 = 1;   //set check3 flag to 1
			}
			Length --;  //subtract from length
		}
	}
	if( check != 1)
	{
	strcpy(temporaryfile, outputfile );   //copies string from outputfile to temporaryfile
	strcat(temporaryfile, ".c");   //add the .out extension to temporaryfile
	rename(outputfile, temporaryfile);
	strcpy(outputfile,temporaryfile); //copies the temporaryfile to outputfile
	}

	while (i < 99)     //checks to see if input name is the same as output name                 
	{
		if(inputfile[i] == outputfile[i])
		{
			if(true2 == 1)
			{
			}
			else
			{
			true2 = 0;    //set true2 flag to 0
			}
		}
		else
		{
		true2 = 1;        //set true2 flag to 1
		}
	i++;
	}
	//display any errors we may encounter here, and end program
	if(check2 == 1)
	printf("cannot have more than 1 . in your input file, exiting\n");
	if(check3 == 1)
	printf("cannot have more than 1 . in your output file, exiting\n");
	if(true2 != 1)
	printf("in and out file are the same, exiting\n");
	//returns a 1 if no errors encountered, a 0 if any errors encountered
	if(true2 == 1 && check2 != 1 && check3 != 1)
	return 1;
	else
	return 0;


}


//OPEN_FILE:attempts to open our files, does additional checks in case file opening fails
int openfile(int true)
{
//openfile does more checks, uses a lot of variables
char userinput = 0, i = 0, i2 = 0, i3 = 0,flag, Length, check, check3;    
char temporary[103], listfile[103],temporaryfile[103];
int true2;

true = 0; 


input = fopen(inputfile, "r"); //open the input file and read from it

	if(!input)//if input doesnt exist
	{
	true = 1; //if no input file by the entered name exists, true is set to 1 and program exits
	printf("input file does not exist \n");		
	
	do // will run if output file exists still (including if inputfile = outputfile), and if user types in garbage. user must type in good data
				{
					
				i3 = 0;
				printf("please enter a input file name\n");
				fflush(stdin);
					while(inputfile[i] != '\0')
					{
					inputfile[i] = '\0';
					i++;
					}
					
				i=0;
				scanf("%99[^\n]%*c", inputfile);      //scan for the string
				
					if(inputfile[0] == '\0') // if user just presses enter
					{
					//strcpy(outputfile, inputfile); //makes output file same name as input
					//Length = strlen(outputfile);
						while( i <= Length) //adds .in
						{
							if(inputfile[i] == '.')
							{
							inputfile[i+1] = 'i';
							inputfile[i+2] = 'n';
							check = 1;
							i= i+3;
							}
							if(check == 1 && i <= Length)
							{
							inputfile[i] = '\0';
							}
						i++;
						}
					}
					while (i3 < 99)   //check if input = output
					{
						if(inputfile[i3] == outputfile[i3])
						{
							if(true2 == 1)
							{
							}
							else
							{
							true2 = 0;
							}
						}
						else
						{
						true2 = 1;
						}
					i3++;
					}	
				input = fopen(inputfile,"r"); //checks if it exists again
				}while( true2 == 0 || !input && inputfile[0] != '\0');	//end of do while
				if(!input)
				true = 1;
				else
				true = 0;
	}

	if(true != 1)     //the program continues
	{
	char ch;
	output = fopen(outputfile, "r");  //open output file and read from it (checks if file already exists, 'w' would automatically overwrite, so we use 'r' first)
		if(output)             //if the output file exists already
		{
		printf("output file already exists, press 1 to pick a new name, press 2 to backup the output file, or any other number to terminate\n");
		fflush(stdin);
		scanf("%99[^\n]%*c", &userinput);     //scan for the userinput integer
			if(userinput == '1')      //if an input file has been entered
			{
				do // will run if output file exists still (including if inputfile = outputfile), and if user types in garbage. user must type in good data
				{
				fclose(output); //closes outputfile for reading
				i3 = 0;
				printf("please enter a output file name\n");
				fflush(stdin);
					while(outputfile[i] != '\0')
					{
					outputfile[i] = '\0';
					i++;
					}
					
				i=0;
				scanf("%99[^\n]%*c", outputfile);      //scan for the string
				
					if(outputfile[0] == '\0') // if user just presses enter
					{
					strcpy(outputfile, inputfile); //makes output file same name as input
					Length = strlen(outputfile);
						while( i <= Length) //adds .out
						{
							if(outputfile[i] == '.')
							{
							//outputfile[i+1] = 'o';
							//outputfile[i+2] = 'u';
							//outputfile[i+3] = 't';
							outputfile[i+1] = 'c';
							check = 1;
							i= i+2;
							}
							if(check == 1 && i <= Length)
							{
							outputfile[i] = '\0';
							}
						i++;
						}
					}while (i3 < 99)   //check if input = output
					
					{
						if(inputfile[i3] == outputfile[i3])
						{
							if(true2 == 1)
							{
							}
							else
							{
							true2 = 0;
							}
						}
						else
						{
						true2 = 1;
						}
					i3++;
					}	
				output = fopen(outputfile,"r"); //checks if it exists again
				}while( true2 == 0 || output);	//end of do while
				fclose(output);
				if((Length > 0) && (Length <= 99)) //checks if there is only 1 '.'
				{
					while (Length > 0)
					{
						if(outputfile[Length] == '.')
						{
						check = 1;            //set check value to 1
						Length--;
						}
						if(check == 1 && outputfile[Length] == '.')
						{
						check3 = 1;
						}
					Length --;  //subtract from length
					}
				}
				if( check != 1)
				{
				strcpy(temporaryfile, outputfile );   //copies string from outputfile to temporaryfile
				strcat(temporaryfile, ".c");   //add the .out extension to temporaryfile
				rename(outputfile, temporaryfile);
				strcpy(outputfile,temporaryfile); //copies the temporaryfile to outputfile
				}
			
			output = fopen(outputfile,"w"); //open the output file to write to it
			}
			else if(userinput == '2') //user chose to make old output a .bak, (dont care if the .bak already exists)
			{
			strcpy(temporary, outputfile);
			i = 0;
			i2 = strlen(outputfile);
				while(i < i2) //takes out the extension from the temporary file
				{
					if(outputfile[i] == '.')
					{
					temporary[i] = '\0';
					flag = 1;
					}
					if(flag == 1)
					{
					temporary[i] = '\0';
					}
				i++;
				}
			strcat(temporary, ".bak"); // replaces the extension of temp file with .bak
			output = fopen(outputfile, "r"); //opens the files for use
			tempfile = fopen(temporary, "w");
				while( ( ch = fgetc(output) ) != EOF )   // get characters from the stream until reach end of the tempfile, place into the ch var
					fputc(ch, tempfile);        					// write to the output file the data from the ch var by writing chars to stream	
			fclose(tempfile);                 //close the files
			fclose(output);
			output = fopen(outputfile, "w");
			}
			else if(userinput != 1 && userinput != 2)
			{
			true = 1;         //if user selects anything other than 1 or 2  true var is set back to 1
			}
		}
		else
		{
		fclose(output); //closes the output file for reading & reopens it for writing if it doesnt exist
		output = fopen(outputfile, "w");
		}
	}
	if(userinput != '1' && userinput !='2' && true == 1) // if user doesnt type in a valid answer, they wish to abort the program
	{
	fclose(input);
	return 1;
	}
	else //opens all other files if there was nothing wrong
	{
	check = 0;
	i = 0;

	strcpy(temporary1, inputfile);//open the tempfile
	Length = strlen(temporary1);
		while(i <=Length)
		{
		if(temporary1[i] == '.')
			{
			temporary1[i+1] = 't';       //adds the .tmp extension
			temporary1[i+2] = 'm';
			temporary1[i+3] = 'p';
			check = 1;
			i= i+4;
			}
			if(check == 1 && i <= Length)
			{
			temporary1[i] = '\0';
			}
		i++;
		}
	tempfile = fopen(temporary1, "w"); 
	strcpy(listfile,inputfile);
	Length = strlen(listfile);
	check = 0;
	i = 0;
		while( i <= Length) //makes list file outputname.lis instead of outputname.out (or whatever other extension)
		{
			if(listfile[i] == '.')
			{
			listfile[i+1] = 'l';
			listfile[i+2] = 'i';
			listfile[i+3] = 's';
			check = 1;
			i= i+4;
			}
			if(check == 1 && i <= Length)
			{
			listfile[i] = '\0';
			}
		i++;
		}
	list =  fopen(listfile, "w");
	return 0;
	}
	
}




//COPY_FILE: Copies contents of input into each file
int copyfile()
{
char ch;
	while( ( ch = fgetc(input) ) != EOF )       //while haven't reached end of file, read the character stream and place into ch var
		fputc(ch, output);  // place data from ch var into output

fseek(input, 0 , SEEK_SET);     //reposition stream position indicator  to beginning of file with a 0 for text files
	
	while( ( ch = fgetc(input) ) != EOF )
		fputc(ch, list);
	
	fseek(input, 0 , SEEK_SET);
	
	while( ( ch = fgetc(input) ) != EOF )
		fputc(ch, tempfile);

}


//FILE_CLOSE: Closes our files
int closefile()      
{
fclose(input);
fclose(output);
fclose(tempfile);
remove(temporary1);
fclose(list);
printf("Program complete, exiting\n");
}
