%{
/*
*	Authored & Documented by:
		Aditi Anomita Mohanty
		github.com/rheaditi
		
		Abinav Nithya Seelan
		github.com/abinavseelan

	* Problem Statement:
		Write a yacc program that accepts a regular expression
		as input and produces its parse tree as output.

*/
/* Declaration section, copied verbatim to the output y.tab.c file */
#include <stdio.h>
#include <stdlib.h> //for exit()
#include <string.h> // for strcpy(), strlen()
#include <ctype.h> //for isalpha()
#define MAX 100

char productions[MAX][MAX];
char temp1[2*MAX], temp2[2*MAX];
int count=0, i, j;

int getREindex(const char *str);
%}

%token ALPHABET
%left '|'
%left '.'
%nonassoc '*' '+'

%% /* These are the production rules, only expressions derived from these rules are 'valid' */

S : re '\n' {
	/* This occurs at the end of parsing, therefore we must print the output accordingly */
	printf("The right-most derivation is:- \n");
	for( i=count-1; i>=0; i-- )
	{
		if(i == count-1)
		{
			printf("\nre => ");
			strcpy(temp1,productions[i]);
			printf("%s",productions[i]);
		}
		else
		{
			printf("\n=> ");
			j = getREindex(temp1);
			temp1[j]='\0';
			sprintf(temp2,"%s%s%s",temp1,productions[i],(temp1+j+2));			
			printf("%s",temp2);
			strcpy(temp1,temp2);
		}
	}
	printf("\n");
	exit(0);
}

re : ALPHABET {
	temp1[0]=yylval;
	temp1[1]='\0';
	strcpy(productions[count++],temp1);
}
| '(' re ')' {
	strcpy(productions[count++],"(re)");
}
| re '*' {
	strcpy(productions[count++],"re*");
}
| re '+' {
	strcpy(productions[count++],"re+");
}
| re '|' re {
	strcpy(productions[count++],"re | re");
}
| re '.' {
	strcpy(productions[count++],"re . re");
}
;

%%

int main()
{
	printf("Enter expression:\n");
	yyparse();
	return 0;
}

yylex()
{
	char ch = getchar();
	yylval=ch;
	if( isalpha(ch) )
		return ALPHABET;
	else
		return ch;
}

yyerror()
{
	fprintf(stderr,"Invalid Regular Expression.\n");
	exit(1);
}

int getREindex(const char *str)
{
	int i;
	for(i=strlen(str); i>=0; i--)
	{
		if( (str[i]=='e') && (str[i-1]=='r') )
		{
			return (i-1);
		}
	}
}
