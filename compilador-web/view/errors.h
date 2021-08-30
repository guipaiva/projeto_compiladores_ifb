#ifndef ERRORS_H
#define ERRORS_H

void finalize();

void error(char *s);

void fatal(char *s);

void expected(char *s);

void undefined(char *name);

void  duplicated(char *name);

#endif