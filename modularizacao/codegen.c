#include "output.h"
#include "codegen.h"

void asmLoadConstant(char *s){
	emit("MOV AX, %s",s);
}

void asmLoadVariable(char *s){
	emit("MOV AX, [%s]",s);	
}

void asmNegate(){
	emit("NEG AX");
}

void asmPush(){
	emit("PUSH AX");
}

void asmPopAdd(){
	emit("POP BX");
	emit("ADD AX, BX");
}

void asmPopSub(){
	emit("POP BX");
	emit("SUB AX, BX");
	asmNegate();
}

void asmPopMul(){
	emit("POP BX");
	emit("IMUL BX");
}

void asmPopDiv(){
	emit("POP BX");
	emit("XCHG AX, BX");
	emit("CWD");
	emit("IDIV BX");
}

void asmStoreVariable(char *name){
	emit("MOV [%s], AX", name);
}

void asmPopOr(){
	emit("POP BX");
	emit("OR AX, BX");
}

void asmPopXor(){
	emit("POP BX");
	emit("XOR AX, BX");
}

void asmPopAnd(){
	emit("POP BX");
	emit("AND AX, BX");
}

void asmNot(){
	emit("NOT AX");
}