%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
int getREindex(const char *);
char productions[MAX][MAX];
int count=0, i, j;
char temp[200], temp2[200];
%}

%token ALPHABET
%left '|'
%left '.'
%nonassoc '*' '+'

%%

S : re '\n' {
	printf("Right-most derivation:-\n");
	for(i=count-1; i>=0; --i)
	{
		if(i==count-1)
		{
			printf("\nre => ");
			strcpy(temp,productions[i]);
			printf("%s",productions[i]);
		}
		else 
		{
			printf("\n => ");
			j = getREindex(temp);
			temp[j] = '\0';
			sprintf(temp2, "%s%s%s", temp, productions[i], (temp+j+2));
			printf("%s",temp2);
			strcpy(temp,temp2);
		}
	}
	printf("\n");
	exit(0);
}

re : ALPHABET {
	temp[0] = yylval;
	temp[1] = '\0';
	strcpy(productions[count++],temp);
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
| re '.' re {
	strcpy(productions[count++],"re . re");
}
;

%%

int main( int argc, char ** argv)
{
	printf("Enter expression:\n");
	yyparse();
	return 0;
}

yylex()
{
	char ch = getchar();
	yylval = ch;
	if( isalpha(ch) )
		return ALPHABET;
	else
		return ch;
}

yyerror()
{
	fprintf(stderr, "Invalid Regular Expression!\n");
	exit(1);
}

int getREindex(const char * str)
{
	int i;
	for( i =strlen(str); i>=0; i--)
	{
		if(str[i]=='e' && str[i-1] =='r')
			return (i-1);
	}
}