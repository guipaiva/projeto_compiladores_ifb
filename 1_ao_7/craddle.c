/*
The Cradle - O Berço

O código abaixo foi escrito por Felipo Soranz e é uma adaptação
do código original em Pascal escrito por Jack W. Crenshaw em sua
série "Let's Build a Compiler".

Este código é de livre distribuição e uso.
*/

#include "craddle.h"


// /* PROGRAMA PRINCIPAL */
// int main()
// {
//     init();

//     return 0;
// }

/* inicialização do compilador */
void init()
{
    nextChar();
}

/* lê próximo caracter da entrada */
void nextChar()
{
    look = getchar();
}

/* exibe uma mensagem de erro formatada */
void error(char *fmt, ...)
{
    va_list args;

    fputs("Error: ", stderr);

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputc('\n', stderr);
}

/* exibe uma mensagem de erro formatada e sai */
void fatal(char *fmt, ...)
{
    va_list args;

    fputs("Error: ", stderr);

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputc('\n', stderr);

    exit(1);
}

/* alerta sobre alguma entrada esperada */
void expected(char *fmt, ...)
{
    va_list args;

    fputs("Error: ", stderr);

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputs(" expected!\n", stderr);

    exit(1);
}

/* verifica se entrada combina com o esperado */
void match(char c)
{
    if (look != c)
        expected("'%c'", c);
    nextChar();
}

/* recebe o nome de um identificador */
char getName()
{
    char name;

    if (!isalpha(look))
        expected("Name");
    name = toupper(look);
    nextChar();

    return name;
}

/* recebe um número inteiro */
char getNum()
{
    char num;

    if (!isdigit(look))
        expected("Integer");
    num = look;
    nextChar();

    return num;
}

/* emite uma instrução seguida por uma nova linha */
void emit(char *fmt, ...)
{
    va_list args;

    putchar('\t');

    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    putchar('\n');
}

/* reconhece operador aditivo */
int isAddOp(char c)
{
    return (c == '+' || c == '-');
}


/* reconhece operador multiplicativo */
int isMulOp(char c)
{
    return (c == '*' || c == '/');
}

/* captura um caracter de nova linha */
void newLine()
{
    if (look == '\n')
        nextChar();
}

/* pula caracteres de espaço */
void skipWhite()
{
    while(look == ' ' || look == '\t')
        nextChar();
}