/*
	* Documented by:
		Aditi Mohanty
		github.com/rheaditi

	* Problem Statement:
		Write a C program for a syntax directed definition of:
		"if E then S1" and "if E then S1 else S2"

*/

#include <stdio.h>
#include <string.h>

char statement[3][50];
char input[200];
int count=0;

void generate()
{
	/* We've assumed some random line-numbers/label-numbers */
	int label1=666, label2=667, label3=668; 

	/* The first part: common to both versions */
	printf("if %s goto %d\n",statement[0],label1);
	printf("goto %d\n", label2);
	printf("%d : %s\n",label1,statement[1]);

	if(count<3) /* heart =P */
	{
		printf("%d : STOP\n", label2);
	}
	else
	{
		printf("goto %d\n", label3);
		printf("%d : %s\n", label2, statement[2]);
		printf("%d : STOP\n", label3);	
	}
}

/* parse input and store statements in array */
void parse(const char *str)
{
	int len=strlen(str), i, j, k;
	for(i=0; i<len && str[i]!=';'; i++)
	{
		if(str[i]=='(')
		{
			k=0;
			for(j=i; str[j-1]!=')'; j++)
				statement[count][k++]=str[j];
			count++;
			i=j;
		}
	}
}

int main()
{
	printf("Example if-else structures:-\n");
	printf("if (a<=5) then (x++);\n");
	printf("if (b>10) then (a=b) else (a=c);\n");

	printf("\n\nEnter statement:\n");
	scanf("%[^\n]s",input); /* read until a \n encountered */

	parse(input);

	printf("\n\nGenerated output:\n");
	generate();
	return 0;
}