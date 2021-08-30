#include <stdio.h>
#include <stdlib.h>

int look; /* O caracter lido "antecipadamente" (lookahead) */
char cur_class, cur_sign, cur_type;

/* protótipos */
void init();
void nextchar();
void error(char *s);
void fatal(char *s);
void expected(char *s);
void match(char c);
char getname();
char getnum();
int isaddop(char c);
int ismulop(char c);

void getclass();
void gettype();
void topdecl();
void dofunc(char name);
void dodata(char name);

int main()
{
	init();

        while (look != EOF) {
                getclass();
                gettype();
                topdecl();
        }

	return 0;
}

void init()
{
	nextchar();
}

void nextchar()
{
	look = getchar();
}

void error(char *s)
{
	fprintf(stderr, "Error: %s\n", s);
}

void fatal(char *s)
{
	error(s);
	exit(1);
}

void expected(char *s)
{
	fprintf(stderr, "Error: %s expected\n", s);
	exit(1);
}

void match(char c)
{
	char s[2];

	if (look == c)
		nextchar();
	else {
		s[0] = c; /* uma conversao r�pida (e feia) */
		s[1] = '\0'; /* de um caracter em string */
		expected(s);
	}
}

char getname()
{
	char name;

	if (!isalpha(look))
		expected("Name");
	name = toupper(look);
	nextchar();

	return name;
}

char getnum()
{
	char num;

	if (!isdigit(look))
		expected("Integer");
	num = look;
	nextchar();

        return num;
}

int isaddop(char c)
{
        return (c == '+' || c == '-');
}

int ismulop(char c)
{
        return (c == '*' || c == '/');
}

void skipwhite()
{
	while (look == ' ' || look == '\t')
		nextchar();
}

void getclass()
{
	if (look == 'a' || look == 'x' || look == 's') {
	  	cur_class = look;
	  	nextchar();
	} else
	  	cur_class = 'a';
}

void gettype()
{
	cur_type = ' ';
	if (look == 'u') {
		cur_sign = 'u';
		cur_type = 'i';
		nextchar();
	} else {
		cur_sign = 's';
	}
	if (look == 'i' || look == 'l' || look == 'c') {
		cur_type = look;
		nextchar();
	}
}

void topdecl()
{
        char name;

        name = getname();
        if (look == '(')
                dofunc(name);
        else
                dodata(name);
}

void dofunc(char name)
{
	match('(');
	match(')');
	match('{');
	match('}');
	if (cur_type == ' ')
		cur_type = 'i';
	printf("Class: %c, Sign: %c, Type: %c, Function: %c\n",
		cur_class, cur_sign, cur_type, name);
}

void dodata(char name)
{
	if (cur_type == ' ')
		expected("Type declaration");
	for (;;) {
		printf("Class: %c, Sign: %c, Type: %c, Data: %c\n",
			cur_class, cur_sign, cur_type, name);
		if (look != ',')
			break;
		match(',');
		name = getname();
	}
	match(';');
}
