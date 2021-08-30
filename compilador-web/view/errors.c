#include <stdio.h>
#include <stdlib.h>
#include "output.h"
#include "errors.h"

void finalize(){
	printf("</div>\n\n");
	printf("<footer> <p>Autor: Guilherme Paiva</p></footer>");
	printf("</body></html>\n");
	exit(1);
}

void error(char *s){
	emit("<span class='error'>Error: %s</span><br>\n", s);
}

void fatal(char *s){
	error(s);
	finalize();
}

void expected(char *s){
	emit("<span class='error'>Error: %s expected</span><br>\n",s);
	finalize();
}

void undefined(char *name){
	emit("<span class='error'>Error: Undefinied identifier %s</span><br>\n",name);
	finalize();
}

void  duplicated(char *name){
	emit("<span class='error'>Duplicated variable name: %s</span><br>\n",name );
	finalize();
}