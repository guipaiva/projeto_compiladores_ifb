#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "model/input.h"
#include "view/output.h"
#include "controller/parser.h"
#include "controller/scanner.h"


#define MAXLEN 512
#define EXTRA 7
#define MAXINPUT MAXLEN + EXTRA + 2

void urldecode2(char *dst, const char *src)
{
	char a, b;
	while (*src) {
		if ((*src == '%') &&
			((a = src[1]) && (b = src[2])) &&
			(isxdigit(a) && isxdigit(b))) {
				if (a >= 'a')
						a -= 'a'-'A';
				if (a >= 'A')
						a -= ('A' - 10);
				else
						a -= '0';
				if (b >= 'a')
						b -= 'a'-'A';
				if (b >= 'A')
						b -= ('A' - 10);
				else
						b -= '0';
				*dst++ = 16*a+b;
				src+=3;
		} else if (*src == '+') {
				*dst++ = ' ';
				src++;
		} else {
				*dst++ = *src++;
		}
	}
	*dst++ = '\0';
}


void style()
{
	printf("<style>");
	printf("*{margin:10px; padding:0}");
	printf("span.error{color:red;font-weight:bold}\n");
	printf("body{height:100vh; display:flex;flex-direction:column; }");
	printf("footer{margin-top:auto;}");
	printf("button {\
		margin-top:10px;\
		border: none;\
		color: white;\
		text-align: center;\
		text-decoration: none;\
		font-size: 16px;\
		padding: 10px 20px;\
		cursor: pointer;\
		background-color: #4CAF50;}\
	");
	printf("</style>\n");
}

void form()
{
	printf("<h4>Insira seu código abaixo</h4>\n");
	printf("<form method=post action=compilador form='codigo'>\n");
	printf("<textarea id='codigo' name='codigo' class='input' cols='50' rows ='15'></textarea><br>");
	printf("<button type='submit'>Compilar</button>\n");
	printf("</form>\n");
}

void main()
{
	char *data;
	char *codigo;
	long len = 0;
	data = getenv("CONTENT_LENGTH");
	printf("Content-type:text/html\n\n");
	printf("<html><head><title>Compilador</title></head>\n");
	printf("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css'>\n");
	printf("<meta charset='utf-8'/>\n");
	style();
	printf("<body>\n");
	
	printf("<div id='content'>\n\n");
	printf("<h3>Compilador Tiny online</h3>\n");
	
	if (data == NULL || sscanf(data,"%ld",&len)!= 1) {
		form();
	} 	
	else if (len == 7){
		printf("<span class='error'> Erro: Insira um código primeiro! </span><br>\n");
	}
	else {
		sscanf(data, "%ld", &len);
		fgets(data, len+1, stdin);
		urldecode2(codigo, data+EXTRA);
		source = malloc(sizeof(char)*(strlen(codigo)+1));
		strcpy(source,codigo);
		init();
	}

	printf("</div>\n\n");
	printf("<footer> <p>Autor: Guilherme Paiva</p></footer>");
	printf("</body></html>\n");
}