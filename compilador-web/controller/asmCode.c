#include <stdio.h>
#include "asmCode.h"
#include "../view/output.h"


void asm_clear(){
	emit("\tXOR AX, AX\n<br>");
}

void asm_negative(){
	emit("NEG AX");
}

void asm_loadconst(char *val){
	emit("\tMOV AX, %s\n<br>", val);
}

void asm_loadvar(char *name){
	emit("\tMOV AX, WORD PTR %s\n<br>", name);
}

void asm_push(){
	emit("\tPUSh AX\n<br>");
}

void asm_popadd(){
	emit("\tPOP BX\n<br>");
	emit("\tADD AX, BX\n<br>");
}

void asm_popsub(){
	emit("\tPOP BX\n<br>");
	emit("\tSUB AX, BX\n<br>");
	emit("\tNEG AX\n<br>");
}

void asm_popmul(){
	emit("\tPOP BX\n<br>");
	emit("\tIMUl BX\n<br>");
}

void asm_popdiv(){
	emit("\tPOP BX\n<br>");
	emit("\tXCHg AX, BX\n<br>");
	emit("\tCWD\n<br>");
	emit("\tIDIv BX\n<br>");
}

void asm_store(char *name){
	emit("\tMOV WORD PTR %s, AX\n<br>",name);
}

void asm_not(){
	emit("\tNOT AX\n<br>");
}

void asm_popand(){
	emit("\tPOP BX\n<br>");
	emit("\tAND AX, BX\n<br>");
}

void asm_popor(){
	emit("\tPOP BX\n<br>");
	emit("\tOR AX, BX\n<br>");	
}

void asm_popxor(){
	emit("\tPOP BX\n<br>");
	emit("\tXOR AX, BX\n<br>");
}

void asm_popcompare(){
	emit("\tPOP BX\n<br>");
	emit("\tCMP BX, AX\n<br>");	
}

void asm_relop(char op, int l1,int l2){
	char *jump;
	switch(op){
		case '=':
			jump = "je";
			break;
		case '#':
			jump = "jne";
			break;
		case '<':
			jump = "jl";
			break;
		case '>':
			jump = "jg";
			break;
		case 'L':
			jump = "jle";
			break;
		case 'G':
			jump = "jge";
			break;
	}
	emit("\t%S L%d\n<br>",jump,l1);
	emit("\tXOR AX, AX\n<br>");
	emit("\tJMP L%d\n<br>",l2);
	emit("L%d:\n<br>",l1);
	emit("\tMOV AX, -1\n<br>");
	emit("L%d:\n<br>",l2);
}

void asm_jmp(int label){
	emit("\tJMP L%d\n<br>", label);
}

void asm_jmpfalse(int label){
	emit("\tJZ L%d\n<br>", label);
}

void asm_read(char *value){
	emit("\tCALl READ\n<br>");
	asm_store(value);
}

void asm_write(){
	emit("\tCALL WRITE\n<br>");
}

void allocVar(char *name, int value){
	emit("%s:\tDW %d\n<br>",name,value);
}