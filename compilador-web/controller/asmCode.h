#ifndef ASMCODE_H
#define ASMCODE_H

void asm_clear();

void asm_negative();

void asm_loadconst(char *val);

void asm_loadvar(char *name);

void asm_push();

void asm_popadd();

void asm_popsub();

void asm_popmul();

void asm_popdiv();

void asm_store(char *name);

void asm_not();

void asm_popand();

void asm_popor();

void asm_popxor();

void asm_popcompare();

void asm_relop(char op, int l1,int l2);

void asm_jmp(int label);

void asm_jmpfalse(int label);

void asm_read(char *vaue);

void asm_write();

void allocVar(char *name, int value);

#endif