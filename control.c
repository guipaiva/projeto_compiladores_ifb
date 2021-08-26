/*
The Cradle - O Ber�o

O c�digo abaixo foi escrito por Felipo Soranz e � uma adapta��o
do c�digo original em Pascal escrito por Jack W. Crenshaw em sua
s�rie "Let's Build a Compiler".

Este c�digo � de livre distribui��o e uso.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

char look; /* O caracter lido "antecipadamente" (lookahead) */
int labelCount; /* Contador usado pelo gerador de r�tulos */

/* prot�tipos */
void init();
void nextChar();
void error(char *fmt, ...);
void fatal(char *fmt, ...);
void expected(char *fmt, ...);
void match(char c);
char getName();
char getNum();
void emit(char *fmt, ...);
int isAddOp(char c);
void other();
void program();
void block();
int newLabel();
int postLabel();
void doIf();
void condition();
void doWhile();
void doLoop();
void doRepeat();
void doFor();
void expression();
void doDo();
void doBreak(int exitLabel);

/* PROGRAMA PRINCIPAL */
int main()
{
    init();
    program();

    return 0;
}

/* inicializa��o do compilador */
void init()
{
    nextChar();
    labelCount = 0;
}

/* l� pr�ximo caracter da entrada */
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

/* recebe um n�mero inteiro */
char getNum()
{
    char num;

    if (!isdigit(look))
        expected("Integer");
    num = look;
    nextChar();

    return num;
}

/* emite uma instru��o seguida por uma nova linha */
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

/* reconhece e traduz um comando qualquer */
void other()
{
    emit("# %c", getName());
}

/* analisa e traduz um programa completo */
void program()
{
        block(-1);
        if (look != 'e')
            expected("End");
        emit("END");
}

/* analisa e traduz um bloco de comandos */
void block(int exitLabel)
{
    int follow;

    follow = 0;

    while (!follow) {
        switch (look) {
            case 'i':
                doIf();
                break;
            case 'w':
                doWhile();
                break;
            case 'p':
                doLoop();
                break;
            case 'r':
                doRepeat();
                break;
            case 'f':
                doFor();
                break;
            case 'd':
                doDo();
                break;
            case 'b':
                doBreak(exitLabel);
                break;
            case 'e':
            case 'l':
            case 'u':
                follow = 1;
                break;
            default:
                other();
                break;
        }
    }
}

/* gera um novo r�tulo �nico */
int newLabel()
{
    return labelCount++;
}

/* emite um r�tulo */
int postLabel(int lbl)
{   
    printf("L%d:\n", lbl);
}

/* analisa e traduz um comando IF */
void doIf(int exitLabel)
{
    int l1, l2;

    match('i');
    condition();
    l1 = newLabel();
    l2 = l1;
    emit("JZ L%d", l1);
    block(exitLabel);
    if (look == 'l') {
        match('l');
        l2 = newLabel();
        emit("JMP L%d", l2);
        postLabel(l1);
        block(exitLabel);
    }
    match('e');
    postLabel(l2);
}

/* analisa e traduz uma condi��o */
void condition()
{   
    emit("# condition");
}

/* analisa e traduz um comando WHILE */
void doWhile()
{
    int l1, l2;

    match('w');
    l1 = newLabel();
    l2 = newLabel();
    postLabel(l1);
    condition();
    emit("JZ L%d", l2);
    block(l2);
    match('e');
    emit("JMP L%d", l1);
    postLabel(l2);
}


/* analisa e traduz um comando LOOP */
void doLoop()
{
    int l1,l2;

    match('p');
    l1 = newLabel();
    l2 = newLabel();
    postLabel(l1);
    block(l2);
    match('e');
    emit("JMP L%d", l1);
    postLabel(l2);
}

/* analisa e traduz um REPEAT-UNTIL*/
void doRepeat()
{
    int l1, l2;

    match('r');
    l1 = newLabel();
    l1 = newLabel();
    postLabel(l1);
    block(l2);
    match('u');
    condition();
    emit("JZ L%d", l1);
    postLabel(l2);
}

/* analisa e traduz um comando FOR*/
void doFor()
{
    int l1, l2;
    char name;

    match('f');
    l1 = newLabel();
    l2 = newLabel();
    name = getName();
    match('=');
    expression();
    emit("DEC AX");
    emit("MOV [%c], AX", name);
    expression();
    emit("PUSH AX");
    postLabel(l1);
    emit("MOV AX, [%c]", name);
    emit("INC AX");
    emit("MOV [%c], AX", name);
    emit("POP BX");
    emit("PUSH BX");
    emit("CMP AX, BX");
    emit("JG L%d", l2);
    block(l2);
    match('e');
    emit("JMP L%d", l1);
    postLabel(l2);
    emit("POP AX");
}

void expression()
{
    emit("# EXPR");
}

/* analisa e traduz um comando DO */
void doDo()
{
    int l1, l2;

    match('d');
    l1 = newLabel();
    l2 = newLabel();
    expression();
    emit("MOV CX, AX");
    postLabel(l1);
    emit("PUSH CX");
    block(l2);
    emit("POP CX");
    emit("LOOP L%d", l1);
    emit("PUSH CX");
    postLabel(l2);
    emit("POP CX");
}

/* analisa e traduz um comando BREAK */
void doBreak(int exitLabel)
{
    match('b');
    if (exitLabel == -1)
            fatal("No loop to break from");
    emit("JMP L%d", exitLabel);
}