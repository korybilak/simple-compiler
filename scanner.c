#include "file_util.h"
#include "scanner.h"


//SCANNING: Identifies character sequences from an input stream and returns the associated token 
int scanner(int destruct)
{
int i = 0, y = 0, a = 0, b = 0, loc;  			//loop counters	
static int test = 1;                // more loop counters
char c, d;
char z[0];                         //var to hold a char read from the sequence
int token = MORE;             
	i = 0;
	while(buffer[i] != '\0')
	{
	buffer[i] = '\0';
	i++;
	}
	i = 0;
	if (destruct == 0)
	{
	loc = ftell(input); //saves current file location if non destructive
	}
	
	if(((c = getc(input)) == EOF)|| feof(input))  //if the char received is the EOF at the end of the file
	{
	if (destruct == 1)
	{
	token = SCANEOF;                               //set the token to SCANEOF
		i = 0;
		while(buffer[i] != '\0')                   //while the buffer is not null
		{
		buffer[i] = '\0';                          //set the buffer to null
		i++;                                       //inc the loop
		}
		buffer[0] = c;                             //set the 1st slot of buffer to the char
		while(linebuffer[i] != '\0')               //while the linebuffer is not null
		{
		i++;                                       //inc the loop
		}
	linebuffer[i] = buffer[0];                     //set the line buffer to the 1st slot of the buffer
	}
	}
	
	else
	{
		
		c = toupper(c);
		i = 0;
		while(buffer[i] != '\0' && i < 99)      //as long as the buffer has something in it and is not NULL
		{
		buffer[i] = '\0';                       //if the buffer becomes NULL inc the count
		i++;
		}
	
		do
		{
		//i = 0; //resets i (reset place in buffer)
			if(isspace(c))                         //if the char is whitespace
			{
			i = 0;                                 //reset the count
			
			
				while(isspace(c)  && i < 99 ) //as long as the buffer has something in it and is not NULL  
				{                                            
				     y = 0;                                              //place the char into linebuffer
					while(linebuffer[y] != '\0')
					y++;
					if(destruct == 1)
					linebuffer[y] = c;
				
					if(c == '\n')                                                 //if the char is a newline
					{
					//printf("%c",c);
					token = NEWLINE;
					if(destruct == 1)
					{
					listing_placer(token, 0, destruct);//the token is a newline
					//output_placer(token);
					}
					}
					//if(feof(input))
					//{
					//token = SCANEOF;
					//}
				i++;                                                              //inc the count
				c = getc(input);
				}
			//ungetc(c,input);
			}

			if(isalpha(c))        //if the character is an alpha aka a letter
			{
				i = 0;                 //reset the count
				//buffer[0] = c;
				while(isalnum(c) && i < 99)      //while the char is alphanumeric
				{
				test++;
				c = toupper(c);
				buffer[i] = c;                 //place the char into buffer
				c = getc(input);      //conver the char from input to uppercase
				i++;
				}
				
				ungetc(c,input);
			
				if(strcmp(buffer,"BEGIN") == 0)      //compare the string from the buffer to token 'BEGIN'
				{
				token = BEGIN;                       //set token if comparison successful
				}
			
				else if(strcmp(buffer,"END") == 0)    //compare the string from the buffer to token 'END'
				{
				//printf("flag");
				token = END;                           //set token if comparison successful
				}
			
				else if(strcmp(buffer,"READ") == 0)    //compare the string from the buffer to token 'READ'
				{
				token = READ;                           //set token if comparison successful
				}     
			
		
				else if(strcmp(buffer,"WRITE") == 0)    //compare the string from the buffer to token 'WRITE'
				{
				token = WRITE;                           //set token if comparison successful
				}
			
				else if(strcmp(buffer,"IF") == 0)        //compare the string from the buffer to token 'IF'
				{
				token = IF;                               //set token if comparison successful
				}
			
				else if(strcmp(buffer, "ELSE") == 0)      //compare the string from the buffer to token 'ELSE'
				{
				token = ELSE;                             //set token if comparison successful
				}
				else if(strcmp(buffer, "THEN") == 0)
				{
				token = THEN;
				}
				else if(strcmp(buffer,"ENDIF") == 0 )     //compare the string from the buffer to token 'ENDIF'
				{
				token = ENDIF;                             //set token if comparison successful
				}
			
				else if(strcmp(buffer,"WHILE") == 0)         //compare the string from the buffer to token 'GOTO'
				{
				token = WHILE;                                //set token if comparison successful
				}
				
				else if(strcmp(buffer,"ENDWHILE") == 0)
				{
				token = ENDWHILE;
				}
				
				else if(strcmp(buffer,"AND") == 0)            //compare the string from the buffer to token 'AND'
				{
				token = ANDOP;                                  //set token if comparison successful
				}
			
				else if(strcmp(buffer,"OR") == 0)             //compare the string from the buffer to token 'OR'      
				{
				token = OROP;                                   //set token if comparison successful
				}
			
				else if(strcmp(buffer,"NOT") == 0)            //compare the string from the buffer to token 'NOT'
				{
				token = NOTOP;                                  //set token if comparison successful
				}
			
				else
				{
				token = ID;                                  //it is not any of the other alpha tokens so it is a variable name
				}
			}
		
			else if(isdigit(c))                              //if the char from input stream is a digit
			{
			i = 0;   		                                 //reset the count
		
				while(isdigit(c) && i < 99)                            
				{
				buffer[i] = c;                               //place char into buffer
				c = getc(input);                             //get char from input stream
				i++;                                         //inc the count
				}
			
			token = INTLITERAL;                              //set integer char sequence to INTLITERAL
			ungetc(c,input);                                 //place the char back into input stream
			}
		
			else if( c == '-')                               //if the char is a '-'
			{
			buffer[0] = c;
			c = fgetc(input);  		                         //get the next char from input stream
		
				if( isdigit(c))                              //check to see if it's a digit
				{
				i = 1;                                       //reset the count
					                                         
					while(isdigit(c) && i < 98)                        
					{
					buffer[i] = c;                            //place char into buffer
					c = getc(input);                          //get char from input stream
					i++;                                      //inc the count
					} 
				
				ungetc(c,input);                              //place the char back into input stream
				token = INTLITERAL;                          //it is a negative number sequence so token is INTLITERAL
				}
			
				else if(c == '-')                            //if the char is a '-'
				{
				i = 2;                                       //reset the count
				buffer[1] = '-';
			
					while(c != '\n' && !feof(input) && i < 99)                          //while the char is not NULL
					{
					c = toupper(getc(input));
				
						if(!feof(input))
						{                                                               //get char from input stream
						buffer[i] = c;                                                   //place char into buffer
						i++;                                                              //inc the count
						}				
					}
				if(destruct == 1)
				strcat(linebuffer,buffer);
				i = 0;
				while(buffer[i] != '\0' && i < 99)      //as long as the buffer has something in it and is not NULL
				{
				buffer[i] = '\0';                       //if the buffer becomes NULL inc the count
				i++;
				}
				i = 0;
				if(destruct == 1)
				{
				token = COMMENT;      //the token is a comment
				listing_placer(token, 0, 1);
				//output_placer(token);
				token = MORE;
				}
				}
			
				else
				{
				token = MINUSOP;      //the token is a minus, send char back
				ungetc(c, input);
				}
			}
		
			else if(c == '*')                                      //if the char is a '*'
			{
			buffer[0] = c;                                          //set the char to the first slot of the buffer
			token = MULTOP;                                         //it is the multiplication operator
			}
			
			else if(c == '/')                                    //if the char is a '/'
			{
			buffer[0] = c;                                        //set the char to the first slot of the buffer
			token = DIVOP;                                        //is is the divsion operator
			}
			
			else if (c == ',')                                     //if the char is ','
			{
			token = COMMA;                                        //it is a comma
			buffer[0] = c;                                        //set the char to the first slot of the buffer
			}
		
			else if( c == '(')                                 //if the char is a '('
			{
			token = LPAREN;
			buffer[0] = c;                                     //set the char to the first slot of the buffer 
			}
		
			else if(c == ')')                                  //if the char is a ')'
			{
			token = RPAREN;
			buffer[0] = c;                                      //set the char to the first slot of the buffer
			}
		
			else if(c == ';')                                   //if the char is a ';'
			{
			token = SEMICOLON;
			buffer[0] = c;                                       //set the char to the first slot of the buffer
			//printf(buffer , "\n");                               //print the contents of the buffer [PS] 
			}
		
			else if(c == ':')                                    //if the char is a ':'
			{
			buffer[0] = c;                                   //set the char to the first slot of the buffer       
			c = getc(input);                                 //get the next char from input stream
				                                            
				if(c == '=')                                     //if the char is a '='
				{
				token = ASSIGNOP;                                //it is the assignment operator
				buffer[1] = c;                                    //set the char to the second slot of the buffer
				}
			
				else
				{
				ungetc(c, input);                                 //place the char back into input stream
				token = ERROR;                                    //it is a lexical error
				}
			
			}
		
			else if(c == '+')                                        //if the char is a '+'
			{
			buffer[0] = c;                                         //set the char to the first slot of the buffer
			token = PLUSOP;
			}
		
			else if(c == '<')                                         //if the char is a '<'
			{
			buffer[0] = c; 		                                      //set the char to the first slot of the buffer
			c = getc(input);                                          //get the next char in input stream
		
				if( c == '>')                                         //if the char is a '>'
				{
				buffer[1] = c;                                        //set the second slot of the buffer to the char
				token = NOTEQOP;                                    //set the token to not equal
				}
			
				else if( c == '=')                                    //if the char is a '='
				{
				buffer[1] = c;                                        //set the second slot of the buffer to the char
				token = LESSEQOP;                                    //set the token to less equal
				}
			
				else
				{
				ungetc(c,input);                                       //send the char back
				token = LESSOP;                                           //the token is just the less than operator
				}
			
			}
			else if(c == '>')                                          //if the char is a '>'
			{
			buffer[0] = c;                                             //set the char to the first slot of the buffer
			c = getc(input);                                            //get the next char in input stream
		
				if(c == '=')                                              //if the char is a '='
				{
				buffer[1] = c;                                            //set the char to the first slot of the buffer
				token = GREQOP;                                     //set the token to greater equal
				}
			
				else
				{
				ungetc(c, input);                                          //send the char back
				token = GREATEROP;                                              //the token is just the greater than operator
				}
			
			}
		
			else if (c == '=')                                          //if the char is a '='       
			{
			buffer[0] = c;                                            //set the char to the first slot of the buffer
			token = EQUALOP;
			}
			
			else if(feof(input) || c == EOF)
			{
		    //buffer[0] = c;
			token = SCANEOF;
			}
			
			else                     //it is a lexical error
			{
			token = ERROR;
			buffer[0] = c;                                                      //set the char to the first slot of the buffer                                                
			i = 0;       			                                                //reset the count
			
			while(errorbuffer[i] != '\0' && i < 99)                              //while the error buffer is not NULL
			i++;                                                       //inc the count and place chars into errorbuffer
			errorbuffer[i] = c;
			}
			
		}while(token == MORE);	                                       //while there are more tokens to be scanned
	
		if((strlen(linebuffer)+strlen(buffer) < 100) && destruct == 1)
		{
		strcat(linebuffer, buffer); 
		}
	
		else
		{
		if(destruct == 1)
		{
		i = 0;
		a = 100-strlen(linebuffer);               
		b = strlen(linebuffer);                    //var to hold the length of the string in linebuffer
		token = ID;                                // will make whatever we grabbed a variable since its not a complete grab
	
		while(a > 0 && i<strlen(buffer))
		{
		linebuffer[b] = buffer[i];                 //set the buffers equal to each other
		i++;                                       //inc the count
		a--;                                       
		b++;                                       //inc length of the linebuffer string
		}
	
		linebuffer[99] = '\n';
		}
		}

	}
	i = 0;
	while(linebuffer[i] != '\0' && destruct != 1)
	{
	if(linebuffer[i] == '\n')
		linebuffer[i] = '\0';
	i++;
	}
	if( destruct == 0)
	{
	fseek(input, loc, SEEK_SET); //resets the input pointer if non destructive
	}
	
return token;                                                      //return the value stored in token var

}




//LISTING FILE : lines are copied from the input file and written to the listing file with a line number, lexical errors, and total number of lexical errors
int listing_placer(int token, int sytax_error, int destruct)                                      //pass in the value of the token var
{
static int line_number = 1, error_count,syntax_error_count;                           //create unchanging static vars of the line number and error count [PS]
int i = 0;                                                         //loop count
char c = 'a';                                                        // holds the char read from input stream
	c = getc(input);
	if(destruct == 1)
	{
	if((token == NEWLINE && linebuffer[0] != '\n')|| token == SEMICOLON || token == COMMENT || token == END || strlen(linebuffer) == 100 || token == COMMENT)      //if the token is a newline, scaneof, comment or if the string legth of the buffer is 100
	{	
		fprintf(list, "%d ", line_number);                           //formatted print to the listing file the line number 
		
		while(linebuffer[i] != '\0')                               //while the error buffer is not NULL
		{
		fprintf(list, "%c", linebuffer[i]);                        //formatted print to the listing file the char and the contents of linebuffer
		i++;                                                       //inc the count
		}
		
		if(linebuffer[i-1] != '\n')                                //if there is not a newline at the end of the line buffer
		{
		fprintf(list, "\n");	                                   //print a new line
		}
		
		if(strlen(linebuffer) == 100)
		{
			
			while((c != '\n') && !feof(input))                          //while the char is not newline and havent reached the feof on input file
			{
				if(!feof(input) || c !=  '\n')
				c = toupper(getc(input));
			}
		c = getc(input);
		}
		i = 0;                                                     //reset the count
		
		while(errorbuffer[i] != '\0')                              //while the errorbuffer is not NULL
		{
		error_count++;
		fprintf(list, "ERROR AT LINE %d %c NOT RECOGNIZED.\n", line_number, errorbuffer[i]);      //format print to the listing file the error msg and the contents of errorbuffer
		errorbuffer[i] = '\0';                                             //reset errorbuffer back to NULL
		i++;                                                                //inc the count        
		}
		
		i = 0;
	    int l = 0;
		if(syntaxBuffer[i] != '\0')                                 //adding new while loop for syntax errors [PS]
		{
		  while(syntaxBuffer[i] != '\0')                            //while this buffer is not null
		  {
          syntax_error_count++;                                     //inc the syntax error count
          fprintf(list, "SYNTAX ERROR NUMBER %d AT LINE %d, EXPECTED TOKEN ", syntax_error_count, line_number,token);
		  if(expectedToken[l] == BEGIN)      
			 fprintf(list, "BEGIN");            //print the expected rokens to listing file
		 else if(expectedToken[l] == END)
			 fprintf(list, "END");
		 else if(expectedToken[l] == READ)
			 fprintf(list, "READ");
		 else if(expectedToken[l] == WRITE)
			 fprintf(list, "WRITE");
		 else if(expectedToken[l] == IF)
			 fprintf(list, "IF");
		 else if(expectedToken[l] == ELSE)
			 fprintf(list, "ELSE");
		 else if(expectedToken[l] == THEN)
			 fprintf(list, "THEN");
		 else if(expectedToken[l] == ENDIF)
			 fprintf(list, "ENDIF");
		 else if(expectedToken[l] == ANDOP)
			 fprintf(list, "AND");
		 else if(expectedToken[l] == OROP)
			 fprintf(list, "OR");
		 else if(expectedToken[l] == NOTOP)
			 fprintf(list, "NOT");
		 else if(expectedToken[l] == LESSEQOP)
			 fprintf(list, "<=");
		 else if(expectedToken[l] == GREQOP)
			 fprintf(list,"<=");
		 else if(expectedToken[l] == NOTEQOP)
			 fprintf(list,"<>");
		 else if(expectedToken[l] == ID)
			 fprintf(list, "A VARIABLE");
		 else if(expectedToken[l] == INTLITERAL)
			 fprintf(list, "A NUMBER");
		 else if(expectedToken[l] == LPAREN)
			 fprintf(list, "(");
		 else if(expectedToken[l]  == RPAREN)
			 fprintf(list,")");
		 else if(expectedToken[l] == SEMICOLON)
			 fprintf(list, ";");
		 else if(expectedToken[l] == COMMA)
			 fprintf(list,"COMMA");
		 else if(expectedToken[l] == ASSIGNOP)
			 fprintf( list, ":=");
		 else if(expectedToken[l] == PLUSOP)
			 fprintf(list, "+");
		 else if(expectedToken[l] == MINUSOP)
			 fprintf(list, "-");
		 else if(expectedToken[l] == DIVOP)
			 fprintf(list, "/");
		 else if(expectedToken[l] == MULTOP)
			 fprintf(list, "*");
		 else if(expectedToken[l] == LESSOP)
			 fprintf(list,"<");
		 else if(expectedToken[l] == GREATEROP)
			 fprintf(list, ">");
		 else if(expectedToken[l] == EQUALOP)
			 fprintf(list,"=");
		 else if(expectedToken[l] == WHILE)
			 fprintf(list, "WHILE");
		 else if(expectedToken[l] == ENDWHILE)
			 fprintf(list,"ENDWHILE");
		 else if(expectedToken[l] == SCANEOF)
			 fprintf(list, "THE END OF FILE");
		 else
			 fprintf(list, "ERROR, MISSING A TOKEN, EXPECTED SOME TOKEN IN THIS LINE (did you have a relation op without a integer or variable?)");
		  fprintf(list, " AND GOT ");
		  expectedToken[l] = 0;   //reset the 2nd slot of expected token 
			while(syntaxBuffer[i] != ' ')
			{
				fprintf(list, "%c", syntaxBuffer[i]);   //print out the char to listing file
				i++;          //inc the loop
			}
			i++;    //inc the loop
			l++;
			fprintf(list,"\n");     //print a newline to the listing file
		  }
		 i = 0;                 //reset the loop counter
		 while(syntaxBuffer[i] != '\0')                 //while the syntax buffer is not null
		 {
		  syntaxBuffer[i] = '\0'; //set the syntax buffer to null
		  i++;            //inc the loop
		 }
         
        }

		
		
	line_number++;        //inc the line number
	}                     
	i = 0 ;               //reset the loop counter

	
		i = 0;
	if(linebuffer[0] == '\n')
	linebuffer[0] = '\0';
	if(token == SCANEOF)                                                  //if reach the EOF for the input stream
	{
	fprintf(list, "\n%d Lexical Errors\n", error_count);  
    fprintf(list, "\n%d Syntax Errors \n", syntax_error_count);         //  [PS]
		if(syntax_error_count == 0 && error_count == 0)
		{
			fprintf(list, "\n Program ran without errors\n");
			fprintf(tempfile,"\n //Program compiled without errors\n");
		}
		else
			fprintf(tempfile, "\n //Program compiled with %d errors\n", error_count+syntax_error_count);
	//return token;//format print to the lisiting file the msg containign the number of lexical errors gotten from error_count
	}
	if((token == NEWLINE && linebuffer[0] != '\n') || token == SEMICOLON  || token == SCANEOF  || token == COMMENT)
	{
	//fprintf(output,"%s", linebuffer);
	int i = 0;
	while(linebuffer[i] != '\0')
		{
		linebuffer[i] = '\0';
		i++;
		}
	}
	}
	ungetc(c,input);//return the value stored in token var
}


//OUTPUT FILE: prints to the output file table labeling a token number, token type, and actual token
int output_placer(int token)
{
char c;
	if((token == NEWLINE && linebuffer[0] != '\n') || token == SEMICOLON  || token == SCANEOF  || token == COMMENT)
	{
	fprintf(output,"%s", linebuffer);
	int i = 0;
	while(linebuffer[i] != '\0')
		{
		linebuffer[i] = '\0';
		i++;
		}
		
	if(token == SEMICOLON  || token == SCANEOF)
	fprintf(output,"\n");
	
	}

	if( token == BEGIN)                             //if the token is 'BEGIN'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tBEGIN \t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);     //format print to the output the actual token
	}
	
	else if( token == END)                              //if the token is 'END'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tEND \t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);    //format print to the output the actual token
	}
	
	else if( token == ANDOP)                              //if the token is 'END'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tANDOP \t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);    //format print to the output the actual token
	}
	
	else if( token == NOTOP)                              //if the token is 'END'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tNOTOP \t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);    //format print to the output the actual token
	}
	
	else if( token == OROP)                             //if the token is 'IF'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tOROP \t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);     //format print to the output the actual token
	}
	
	else if( token == READ)                             //if the token is 'READ'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tREAD \t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);     //format print to the output the actual token
	}
	
	else if( token == WRITE)                             //if the token is 'WRITE'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tWRITE \t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);    //format print to the output the actual token
	}
	
	else if( token == IF)                             //if the token is 'IF'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tIF \t\t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer); fprintf(output, "actual token: IF\n");     //format print to the output the actual token
	}
	
	else if(token == ELSE)
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tELSE \t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);     //format print to the output the actual token	
	}
	
	else if( token == ENDIF)                             //if the token is 'ENDIF'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tENDIF \t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);     //format print to the output the actual token
	}
	
	else if( token == ID && strlen(buffer) != 0)                             //if the token is 'ID'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tID \t\t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);     //format print to the output the actual token
	}
	
	else if( token == INTLITERAL)                             //if the token is 'INTLITERAL'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tINTLITERAL \t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);     //format print to the output the actual token
	}
	
	else if( token == LPAREN)                             //if the token is 'LPAREN'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tLPAREN \t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);   //format print to the output the actual token
	}
	
	else if( token == RPAREN)                             //if the token is 'RPAREN'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tRPAREN \t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);     //format print to the output the actual token
	}
	
	else if( token == SEMICOLON)                             //if the token is 'SEMICOLON'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tSEMICOLON \t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);   //format print to the output the actual token
	}
	
	else if( token == COMMA)                             //if the token is 'COMMA'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tCOMMA \t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);   //format print to the output the actual token
	}
	
	else if( token == ASSIGNOP)                             //if the token is 'ASSIGNOP'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tASSIGNOP \t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);    //format print to the output the actual token
	}
	
	else if( token == LESSEQOP)                             //if the token is 'ASSIGNOP'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tLESSEQOP \t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);     //format print to the output the actual token
	}
	
	else if( token == GREQOP)                             //if the token is 'ASSIGNOP'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tGREQOP \t\t\t"); //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);      //format print to the output the actual token
	}
	
	else if( token == NOTEQOP)                             //if the token is 'ASSIGNOP'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tNOTEQOP \t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);      //format print to the output the actual token
	}
	
	else if( token == PLUSOP)                             //if the token is 'PLUSOP'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tPLUSOP \t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);      //format print to the output the actual token
	}
	
	else if( token == MINUSOP)                             //if the token is 'MINUSOP'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tMINUSOP \t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);    //format print to the output the actual token
	}
	//todo: add these if we decide to use them - tested and working -KB
	else if( token == DIVOP)                             //if the token is 'MINUSOP'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tDIVOP \t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);    //format print to the output the actual token
	}
	
	else if( token == MULTOP)                             //if the token is 'MINUSOP'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tMULTOP \t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);     //format print to the output the actual token
	}
	
	else if( token == LESSOP)                             //if the token is 'LESS'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tLESSOP \t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);    //format print to the output the actual token
	}
	
	else if( token == GREATEROP)                             //if the token is 'GREATER'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tGREATEROP \t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);    //format print to the output the actual token
	}
	
	else if( token == EQUALOP)                             //if the token is 'EQUAL'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tEQUALOP \t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);     //format print to the output the actual token
	}
	
	if( token == WHILE)                             //if the token is 'EQUAL'
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tWHILE \t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);     //format print to the output the actual token
	}
	
	if(token == ENDWHILE)
	{
	fprintf(output, "token  number: %d \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tENDWHILE \t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);      //format print to the output the actual token
	}
	
	/*else if( token == SCANEOF)                             //if the token is 'SCANEOF'
	{
	fprintf(output, "token  number: %d  \t", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tSCANEOF \t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);      //format print to the output the actual token
	return token;
	}*/
	
	else if( token == ERROR && token != SCANEOF)                             //if the token is 'ERROR'
	{
	fprintf(output, "token  number: %d   ", token);  //format print to the output the token number
	fprintf(output, "token type:\t\tERROR \t\t\t");         //format print to the output the token type
	fprintf(output, "actual token: %s\n", buffer);     //format print to the output the actual token
	}
	
	}

// Appends temporary file to the output file
int file_append()
{

char c;
 
fclose(output);
fclose(tempfile);
output = fopen(outputfile, "a");                                   //open the output file for appending
tempfile = fopen(temporary1, "r");
	while( ( c = fgetc(tempfile) ) != EOF )             // get character from the tempfile until reach EOF
	{
	fputc(c, output);        				        //place character into output file
	}
}
