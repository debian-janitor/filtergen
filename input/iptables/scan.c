#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"

extern char * yytext;
int yylex();
long int lineno();
char * filename();

char * tok_map(int c) {
    char * r;
    switch (c) {
      case TOK_TABLE:
	r = strdup("table"); break;
      case TOK_CHAIN:
	r = strdup("chain"); break;
      case TOK_OPTION:
	r = strdup("option"); break;
      case TOK_IDENTIFIER:
	r = strdup("identifier"); break;
      case TOK_LSQUARE:
	r = strdup("lsquare"); break;
      case TOK_RSQUARE:
	r = strdup("rsquare"); break;
      case TOK_COLON:
	r = strdup("colon"); break;
      case TOK_BANG:
	r = strdup("bang"); break;
      case TOK_QUOTE:
	r = strdup("quote"); break;
      case TOK_COMMIT:
	r = strdup("commit"); break;
      case TOK_NEWLINE:
	r = strdup("newline"); break;
      default:
	r = strdup("UNRECOGNISED"); break;
    }
    return r;
}  

int main(int argc __attribute__((unused)), char ** argv __attribute__((unused))) {
    int c;

    /* if running in make distcheck the cwd isn't the same as the srcdir */
    if (getenv("srcdir")) {
	chdir(getenv("srcdir"));
    }

    while ((c = yylex())) {
	printf("kind = %s, spelling = \"%s\", file = \"%s\", line = %ld\n", tok_map(c), yytext, filename(), lineno());
    }
    return 0;
}

