#include <stdio.h>

#include "input.h"
#include "lista.h"
#include "../controller/scanner.h"
#include "../controller/parser.h"
#include "../view/errors.h"
#include "../view/output.h"

void init(){
	cursor = 0;
	listaInit(&symbol,criaVar);
	labelCount = 0;
	nextChar();
	nextToken();
	matchString("PROGRAM");
	semiColon();
	header();
	topDecls();
	matchString("BEGIN");
	prolog();
	block();
	matchString("END");
	epilog();
}

void nextChar(){
	lookahead = source[cursor++];
}
