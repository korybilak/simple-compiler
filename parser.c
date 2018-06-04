#include "file_util.h"
#include "scanner.h"
#include "parser.h"
#include "time.h"

static int current_symbol = 0;  //symbol table index

//typedef char string[100];
//enum expr{IDEXPR, LITERALEXPR, TEMPEXPR};

char *_getcwd       //get the current working directory (CWD) of the file 
(      
   char *buffer,  
   int maxlen   
);  

//processes a variable
expr_rec process_id()            
{
expr_rec t;                      //create the record
check_id(buffer);                //check the symbol table
t.kind = IDEXPR;                 //set the kind field of that record
strcpy(t.data,buffer);           //copy the contents of the buffer into the data field 
//expr_rec erec;
//erec.kind(TEMPEXPR);
//strcpy(erec.data, get_temp());
//generate( t.data, "=", e1.data, op.field, e2.data);
return t;
}

//identfies a variable
expr_rec ident()    
{
expr_rec t;         //create the record
match(ID);          //match the ID
t = process_id();   //call process id to get the expr rec
return t;
}


//creates a temporary value
char* get_temp()
{
static int max_temp = 0;   //static var to prevent from resetting back to 0
static char tempname[100]; //static var to prevent from disappearing when function closes
max_temp++;
sprintf(tempname, "temp%d", max_temp);
check_id(tempname);
return tempname;
}


//processes an operator
op_rec process_op()         
{
op_rec t;                             //create the record
if( strcmp(buffer, "+") == 0 )       //see if the char is a +, then set the operator field to + 
	strcpy(t.operator, "+");
else if(strcmp(buffer, "-") == 0)    //see if the char is a -, then set the operator field to - 
	strcpy(t.operator, "-");
else if(strcmp(buffer, "/") == 0)    //see if the char is a /, then set the operator field to / 
	strcpy(t.operator, "/");
else if (strcmp(buffer, "*") == 0)    //see if the char is a *, then set the operator field to *
	strcpy(t.operator, "*");
else if(strcmp(buffer,"<") == 0)       //see if the char is a <, then set the operator field to , 
	strcpy(t.operator, "<");
else if(strcmp(buffer, ">") == 0)       //see if the char is a >, then set the operator field to > 
	strcpy(t.operator,">");
else if(strcmp(buffer, "AND") == 0 )     //see if the char is a AND, then set the operator field to && 
	strcpy(t.operator, "&&");
else if(strcmp(buffer,"OR") == 0)   //see if the char is a OR, then set the operator field to  || 
	strcpy(t.operator, "||");
else if(strcmp(buffer, "NOT") == 0 )       //see if the char is a NOT, then set the operator field to ! 
	strcpy(t.operator, "!");
else if(strcmp(buffer,"<=") == 0 )  //see if the char is a <=, then set the operator field to <= 
	strcpy(t.operator, "<=");
else if(strcmp(buffer,">=") == 0)    //see if the char is a >=, then set the operator field to >= 
	strcpy(t.operator,">=");
else if(strcmp(buffer,":=") == 0 )    //see if the char is a :=, then set the operator field to = 
	strcpy(t.operator,"=");
else if(strcmp(buffer, "=") == 0)      //see if the char is a =, then set the operator field to == 
	strcpy(t.operator,"==");
else if(strcmp(buffer,"<>") == 0)       //see if the char is a !, then set the operator field to ! 
	strcpy(t.operator,"!=");
strcpy(t.data, buffer);
//printf("%s\n", buffer);
return t;
}

//processes a literal
expr_rec process_literal()  
{
expr_rec t;                 //create the record
t.kind = LITERALEXPR;       //set the kind field of that record
strcpy(t.data, buffer);     //copy the contents of the buffer into the data field
return t;
}

//generates an infix expression
expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2)
{
expr_rec t;                 //create the record
t.kind = TEMPEXPR;          //set the kind field of that record
strcpy(t.data, get_temp()); //copy what is returned from get_temp into the data field 
generate_to_temp(t,'=' , e1, op, e2);   //generate the infix of the expression
return t;
}
//generates an infix expression for a condition (aka without ;)
expr_rec gen_infix1(expr_rec e1, op_rec op, expr_rec e2)
{
expr_rec t;                  //create the record
t.kind = TEMPEXPR;           //set the kind field of that record
strcpy(t.data, get_temp());  //copy what is returned from get_temp into the data field
generate_to_temp1(t,'=' , e1, op, e2);   //generate the infix of the expression
return t;
}

//generates a temp value for a condition (without ;)
void generate_to_temp1(expr_rec t, char character, expr_rec l, op_rec op, expr_rec r) 
{
fprintf(tempfile, "(%s",t.data);         //format print out the string of the expression record t's data field to the tempfile
fprintf(tempfile, "% c ", character);   //format print out the character from the character var to the tempfile
fprintf(tempfile, "%s ", l.data);       //format print out the string from the expression record 1's data field to the tempfile
fprintf(tempfile,"%s ", op.data);       //format print out the string from the operator record's data field to the tempfile
fprintf(tempfile,"%s) ", r.data);	    //format print out the string from the expression record r's data field to the tempfile
}

//geterates the temp value
void generate_to_temp(expr_rec t, char character , expr_rec l, op_rec op, expr_rec r)
{
//expr_rec t;
//printf("%s",op.data);
fprintf(tempfile, "%s",t.data);                  //format print out the string of the expression record t's data field to the tempfile
fprintf(tempfile, "% c ", character);            //format print out the character from the character var to the tempfile
fprintf(tempfile, "%s ", l.data);                //format print out the string from the expression record 1's data field to the tempfile
fprintf(tempfile,"%s ", op.operator);            //format print out the string from the operator record's operator field to the tempfile
fprintf(tempfile,"%s;\n", r.data);               //format print out the string from the expression record r's data field to the tempfile
//fprintf(tempfile,"%s\n", r.data);
}

//checks if id already exists in symbol table
void check_id(string s)
{
	int i = 0;       
	i = lookup(s);   //search for s in the symbol table
	if(i == 0)       //if it is nnot there
	{
	enter(s); 
	generate("int", s, "", "", ""); // take n parameters
	//write to appropriate output file
	}
}

//enters an id into symbol table
void enter(string s)              //enter the symbol s into the symbol table
{
static int i = 0;                 //set the count
strcpy(symbol_table[i], s);       //copy contents of string s into the symbol table array
i++;                              //inc the count
}

//generates a string
void generate(string a, string s, string b, string c, string d)
{
fprintf(output, "%s ", a);     //format print out the strings to the outputfile 
fprintf(output, "%s;\n", s);
}

//lookup a id on the symbol table
int lookup(string s)
{
	int i= 0;
	int found = 0;
	
 while( found == 0 && i < 100)
 {
  int ret = strcmp(s, symbol_table[i]);       //string compare to see if s is already in the symbol table array
 if(ret == 0)                                 //if the symbol has been found
 {
 found = 1;                                  //set the flag
 }
 i++;                                       //inc the count
 }
 return found;
}

void start()  //start action routine
{
char temp[100];       
fprintf(output, "/* \n");
strcpy(temp, inputfile); //copy the contents of the input file into temp
_getcwd(inputfile, 101); //get current working directory of the input file 
fprintf(output, "C program of MICRO program %s\\%s\n", inputfile,temp);    
int i = 0;      //initialize loop counter
char buff[32];
time_t t = time(NULL);       
struct tm tm = *localtime(&t);    //create new structure for time
size_t last;
struct tm *ts;                    
time_t rawtime;
time(&rawtime);
ts = localtime(&rawtime);
last = strftime(buff, 32, "%A", ts);
buff[last] = '\0';
fprintf(output, " %s %d-%d-%d %d:%d:%d\n", buff, tm.tm_mon +1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
fprintf(output, "*/\n\n");
fprintf(output, "#include <stdio.h>\n");
fprintf(output,"int main()\n");
if(strcmp(buffer,"BEGIN") == 0)
fprintf(output,"{\n");
}

//assigns a value to an id
void assign(expr_rec id1, expr_rec t)   //assign action routine
{
fprintf(tempfile,"%s", id1.data);  //format print to the tempfile the string of the data field of the id1 expression record
fprintf(tempfile," = ");           //format print to the tempfile the = 
if(buffer[0] == ';')
fprintf(tempfile,"%s;\n",t.data);  //format print to the tempfile the string of the data field of the expression record t
else
fprintf(tempfile,"%s\n", t.data);
}

//assigns a value for the condition statements
void assign1(expr_rec t)         //assign action routine
{
fprintf(tempfile, "%s ", t.data);         //format print to the tempfile the string of the data field of the expression record t
}

//generates scanf
void read_id(expr_rec t) //read id action routine
{
fprintf(tempfile,"scanf(\"%%d\",&%s);\n", t.data);         //format print to the tempfile the scanned integer and string of the data field of the expression record t
}

//generates printf
void write_expr(expr_rec t)      //write expression action routine
{
fprintf(tempfile,"printf(\"%%d\\n\",%s);\n", t.data);  //format print to tempfile the scanned integer and string of the data field of the expression record t
}

//not used
void gen_condition()                      //generate condition action routine
{

}

//generates the finish routine
void finish()       //finish action routine
{
if(strcmp(buffer,"END") == 0)
fprintf(tempfile, "}");      //format print to the tempfile 
}

int systemGoal()   //systemGoal function that will check for a program
{
int e = 0;         //initialize the token to 0
e = program();     //call program function   
finish();
e = match(SCANEOF);   //if there is no program, it is the EOF
	return e;
}

int match(int token)   //function that matches enumerated tokens 
{
int destruct = 1, i = 0, j = 0, k = 0, test;      //initialize destruct value to 1 , set up loop vars and test flag
test = nextToken();
if(test == token)
{
test = scanner(destruct);
listing_placer(token,  0, destruct);      //place into the listing file and output file the token and destruct value
//output_placer(token);
}
else
{
int loc = ftell(input);
while(test != SCANEOF && test != token)   // while the test flag is not the EOF or a token
{
i = 0;     //initialize all loops to 0
j = 0;
k = 0;
while(expectedToken[k] != 0) //while there is not a token
{
k++;                   //inc the loop
}
expectedToken[k] = token;
while (syntaxBuffer[i] != '\0')  //while the syntax buffer is not null
	i++;               // inc the loop
	
while(buffer[j] != '\0')  
{
syntaxBuffer[i] = buffer[j];
i++;
j++;
}
i = 0;          //reset loop to 0 
while(syntaxBuffer[i] != '\0')  //while the syntax buffer is not null
	i++;   // inc the loop
syntaxBuffer[i] = ' ';
//listing_placer(token, 1, destruct);      //place into the listing file and outputfile the token and destruct value
//output_placer(token);
test = scanner(destruct);
}
if(test == token || test == SCANEOF)        //if the test flag is the token
{
	
fseek(input, loc, SEEK_SET); //resets the input pointer if non destructive

i = 0;
while(buffer[i] != '\0')
{
buffer[i] = '\0';
i++;

}

i = 0;
while(linebuffer[i] != '\0' || i <= 100)
{
linebuffer[i] = '\0';
i++;
}
listing_placer(token, 0, destruct);    //place into the listing file and outputfile the token and destruct value
//output_placer(token);
return token;
}
}
return token;
}




int nextToken()      //function to check the next token being scanned
{
int token;           //var to hold the enumerated token
int destruct = 0;          
token = scanner(destruct); //place into token var the characters the scanner has gotten
return 	token;             //return that token
}

op_rec add_op(op_rec *result)
{
op_rec op;           
int token;
if(nextToken() == MULTOP || nextToken() ==  DIVOP || nextToken() == PLUSOP || nextToken() == MINUSOP)      //if the next token is a math op
{
mathOP();      //call mathop function
op = process_op();    //set the op field of the operator record to what is returned from the process operator function
}
return op;
}

int program()             //function to match the program grammar
{
 int OK = 1;
 
 OK = match(BEGIN);
 start();
 if (OK == BEGIN)   //error here, something happening after matching the first 'BEGIN' that prevents from parsing the next tokens
 {
       OK = stmtList(); 
	   if(OK == SEMICOLON || OK == ENDIF || OK == ENDWHILE)
       OK = match(END);   
		if(OK == END)
			return OK;
  }
return OK;

}

int stmtList()            //function to match the stmt list grammar
{
int OK;
OK = statement();              //call the statement grammar function
	while(nextToken() == ID || nextToken() == READ || nextToken() == WRITE || nextToken() == IF || nextToken() == WHILE) //continue reading the next token as long it contains ID, READ, WRITE, IF, or WHILE keywords
	{
	OK = statement();	  // call statement grammar function
	}
return OK;
}



int statement()       //function to match the stmt grammar
{
int n;              //var to hold the next token
expr_rec id1, t;
n = nextToken();      //read into the token var the next token
	switch(n)
	{
	case ID:          //if the token is an ID
	//n = match(ID);        //match it to the ID keyword
	id1 = ident();
	n = match(ASSIGNOP);  //match to the assignment operator :=
	t = expr();           //call expression grammar function
	n = match(SEMICOLON);      //match to the semicolon at the end of the statement
	assign(id1, t);
	break;
	
	case READ:             //if the token is a READ
	n = match(READ);          //match it to the READ keyword
	n = match(LPAREN);
	n = idList();                //call id list grammar function
	n = match(RPAREN);
	n = match(SEMICOLON);       //match to the semicolon at the end of the statement
	break;
	
    case WRITE:      //if the token is a WRITE
	n = match(WRITE);    //match it to the WRITE keyword
	n = match(LPAREN);
	n = exprList();      // call expression list grammar function
	n = match(RPAREN);
	n = match(SEMICOLON);   //match to the semicolon at the end of the statement
	break;
	
	case IF:         //if the token is an IF
	n = match(IF);       //match it to the IF keyword
	fprintf(tempfile, "if");
	n = match(LPAREN);
	if(strcmp(buffer,"(") == 0)
	fprintf(tempfile,"(");
	n = condition();     //call condition grammar function
	n = match(RPAREN);
	if(strcmp(buffer, ")") == 0)
	fprintf(tempfile, ")\n");
	n = match(THEN);     //match to the THEN keyword
	if(strcmp(buffer,"THEN") == 0)
	fprintf(tempfile, "{\n");
	n = stmtList();      //call statement list grammar function
	n = ifTail();        //call the if tail grammar function
	break;
	
	case WHILE:      //if the token is a WHILE
	n = match(WHILE);    //match it to the WHILE keyword
	fprintf(tempfile,"while");
	n = match(LPAREN);
	if(strcmp(buffer, "(") == 0)
	fprintf(tempfile, "(");
	n = condition();     //call condition grammar function
	n = match(RPAREN);
	fprintf(tempfile,")\n{\n");
	//if(nextToken() == ID || nextToken() == READ || nextToken() == WRITE || nextToken() == IF || nextToken() == WHILE)
	n = stmtList();      //call statement list grammar function
	n = match(ENDWHILE); //match to the ENDWHILE keyword
	if(strcmp(buffer, "ENDWHILE") == 0)
	fprintf(tempfile,"}\n");
	break;
	
	default:
	match(OTHER);
	break;
	
	}
	
	return n;       //return the token
}

int ifTail()        //function to match the ifTail grammar
{
int n; //var to hold the next token
n = nextToken(); //put into token var the next token

	switch(n)
	{
	case ELSE:   //if the token is an ELSE 
	n = match(ELSE); //match it to the ELSE keyword
	if(strcmp(buffer, "ELSE") == 0)
	fprintf(tempfile,"}\nelse{\n");
	n = stmtList();  //call statement list grammar function
	fprintf(tempfile,"}\n");
	n = match(ENDIF);       //match to the ENDIF keyword
	break;
	
	case ENDIF:         //if the token is an ENDIF
	fprintf(tempfile,"}\n");
	n = match(ENDIF);       //match it to the ENDIF keyword
	break;
	
	default:
	n = match(ENDIF);
	break;
	}
	return n;
}

int idList()            //function to match the idList grammar
{
expr_rec t;
int n;
t = ident();                  //call id grammar function
read_id(t);
	while( nextToken() == COMMA)  //continue to call function as long as token is matching the ID keyword
	{
		n = match(COMMA);
		t = ident();
		read_id(t);
	}
return n;
}


int exprList()   //function to match the expression list grammar
{
int n;
expr_rec t;
t = expr();          //call expression grammar function
write_expr(t);
	while(nextToken() == COMMA)  //while the token is either ID, INTLITERAL, PLUSOP, MINUSOP, DIVOP, or MULTOP keyword
	{
	n = match(COMMA);
	t = expr();
	write_expr(t);
	}
return n;
}

/*int expr()                                                           //function to match the expression grammar
{
int n;                                                              //var to hold the next token
n = primary();                                                      //call primary grammar function to place into token var                                              
	while(nextToken() == PLUSOP || nextToken() == MINUSOP || nextToken() == DIVOP || nextToken() == MULTOP) //while the token is either ID, INTLITERAL, PLUSOP, MINUSOP, DIVOP, or MULTOP keyword
	{
		//printf("flag");
		n = mathOP();  
		n = primary();
	}
return n;                                                     //return the token
}*/

expr_rec expr()
{
	int n;
	expr_rec left, right, t;
	op_rec op;
	if(nextToken() != LPAREN)                                 //if the next token is not the (
	{
	primary(&left);                                           //go back to the primary function and pass the address of the left expression record
	
	}
	else
	left = primary(&left);                                    //set the contents of the left expression record to what primary function returns
	if(nextToken() == PLUSOP || nextToken() == MINUSOP || nextToken() == DIVOP || nextToken() == MULTOP)       //if the next token is a math operator
	{
	while(nextToken() == PLUSOP || nextToken() == MINUSOP || nextToken() == DIVOP || nextToken() == MULTOP)
	{
	//n = mathOP();
    op = add_op(&op);
	//printf("%s", op.data);
	primary(&right);        //pass into the primary function the address of the right expression
	t = gen_infix(left,op,right);  //generate the infix of the expression and set into t expression record
	left = t;                      //set into left expression record contents of t expression record
	}
	}else{
	t = left;	                   //set into t expression record contents of left expression record
	}
	return t;
}
expr_rec expr1()
{
int n;
expr_rec left, right, t;
op_rec op;

if(nextToken() != LPAREN)   //if the next token is not the (
primary1(&left);
else
left = primary1(&left);
              //set the contents of the left expression record to what primary function returns
if(nextToken() == PLUSOP || nextToken() == MINUSOP || nextToken() == DIVOP || nextToken() == MULTOP)       //if the next token is a math operator
{
while(nextToken() == PLUSOP || nextToken() == MINUSOP || nextToken() == DIVOP || nextToken() == MULTOP)
	{
	//n = mathOP();
    op = add_op(&op);
	//printf("%s", op.data);
	primary1(&right);                       //pass into the primary function the address of the right expression
	t = gen_infix1(left,op,right);         //generate the infix of the expression
	left = t;                              //set into left expression record contents of t expression record
	}
	}else{
	t = left;                              //set into t expression record contents of left expression record
	assign1(t);
	}
	return t;
}
expr_rec primary(expr_rec * operand)
{
int n, flag = 0;          //initialize vars
expr_rec t;               //create the record
n = nextToken();          //check the next token
switch(n)
{
case LPAREN:              //if it is the (
do{
n = match(LPAREN);
t = expr();               //call expression function, place in t
n = match(RPAREN);        //match the )
if(nextToken() == LPAREN) // if ( instead, set flag
flag = 1;
else
flag = 0;
}while(flag == 1);
break;

case ID:    //if it is ID
*operand = ident(); 
break;

case INTLITERAL:    //if it is an int literal
*operand = process_literal();
match(INTLITERAL);           //match the int literal
break;

default:
match(OTHER);
break;
}
return t;
}

expr_rec primary1(expr_rec * operand)
{
int n, flag = 0;          //initialize vars
expr_rec t;               //create the record
n = nextToken();          //check the next token
switch(n)
{
case LPAREN:              //if it is the (
do{
n = match(LPAREN); 
fprintf(tempfile, "(");       
t = expr1();               //call expression function, place in t
n = match(RPAREN);        //match the )
if(strcmp(buffer, ")") == 0 );
fprintf(tempfile,")");
if(nextToken() == LPAREN) // if ( instead, set flag
flag = 1;
else
flag = 0;
}while(flag == 1);
break;

case ID:    //if it is ID
*operand = ident(); 
return t;
break;

case INTLITERAL:    //if it is an int literal
*operand = process_literal();
match(INTLITERAL);           //match the int literal
return t;
break;

default:
match(OTHER);
return t;
break;
}

}
/*int primary()        //function to match the primary grammar
{
int n; //var to hold the next token
n = nextToken(); //put into token var the next token
	switch(n)
	{
	case LPAREN: //if the next token is the left parenthesis match it
	n = match(LPAREN);    
	n = expr();           //call the expression grammar function
	n = match(RPAREN);    //match the right parenthesis
	break;
	
	case ID:          //if the next token is the ID keyword match it
	n = match(ID);
	break;
	
	case INTLITERAL:  //if the next token is an interliteral match it
	n = match(INTLITERAL);
	break;
	}
	return n; //return the token
}*/



int mathOP() //function to match the math operator grammar
{
int n; //var to hold the next token
n = nextToken(); //put into token var the next token
	switch(n)
	{
	case PLUSOP:       //if it is the plus operator match it
	n = match(PLUSOP);
	break;
	
	case MINUSOP:      //if it is the minus operator match it
	n = match(MINUSOP);
	break;
	
	case MULTOP:   //if it is the multiplication operator match it
	n = match(MULTOP);
	break;
	
	case DIVOP:   //if it is the division operator match it
	n = match(DIVOP);
	break;
	
	default:
	match(OTHER);
	break;
	}
return n; //return the token
}


int condition()  //function to see if there are multiple conditions
{
int n;
n = notCondition();
op_rec t;
while(nextToken() == ANDOP || nextToken() == OROP)
{
t = logicalOP();
fprintf(tempfile, "%s ", t.operator);
//n = match(LPAREN); //dont need this for now, but may want it later, tested and works
n = notCondition();
//n = match(RPAREN); //dont need this for now, but may want it later, tested and works
gen_condition();
}
return n;
}

int notCondition() //function to match if there is a not or not
{
int n;
if(nextToken() == NOTOP)
{
n = match(NOTOP); //match the not operator
fprintf(tempfile, "!(");  //print the not (!) symbol
n = match(LPAREN);        //match the (
n = condition();          //call the condition function
n = match(RPAREN);        //match the )
fprintf(tempfile,")");    
}
else
{
n = relationalCondition();
}
return n;
}

//function to do comparison of expressions
int relationalCondition()
{
int n;
op_rec t;                //create the operator record t
expr_rec l, r;           //create expression records for the left and right side
l = expr1();
t = relOP();
fprintf(tempfile, "%s ", t.operator);        //format print to the tempfile the string of the operator record t's operator field
r = expr1();

return n;
}

op_rec logicalOP() //function to match the logical operator grammar
{
int n;          //token var
op_rec t;
n = nextToken();        //put into token var the next token
	switch(n)
	{
	case ANDOP:         //if it is the AND operator match it
	n = match(ANDOP);
	t = process_op();
	break;
	
	case OROP:          //if it is the OR operator match it
	n = match(OROP);
	t = process_op();
	break;
	
	default:
	match(OTHER);
	break;
	}
return t; //return the token
}



op_rec relOP()      //function to match the relational operator grammar
{
int n;                     //token var
op_rec t;
n = nextToken();        //put into token var the next token
	switch(n)
	{
	case LESSOP:        //if it is the less operator match it
	n = match(LESSOP);
	t = process_op();
	break;
	
	case LESSEQOP:      //if it is the less equal operator match it
	n = match(LESSEQOP);
	t = process_op();
	break;
	
	case GREATEROP:     //if it is the greater  operator match it
	n = match(GREATEROP);
	t = process_op();
	break;
	
	case GREQOP:     //if it is the greater equal operator match it
	n = match(GREQOP);
	t = process_op();
	break;
	
	case EQUALOP:    //if it is the equal operator match it 
	n = match(EQUALOP);
	t = process_op();
	break;
	
	case NOTEQOP: //if it is the not equal operator match it
	n = match(NOTEQOP);
	t = process_op();
	break;
	
	default:
	match(OTHER);
	break;
	}
return t; //return the token
}
