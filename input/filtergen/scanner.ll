%option noyywrap
%option nounput
%option prefix="filtergen_"
%x include
%x comment
%{
/* input scanner for filtergen language
 *
 * Copyright (c) 2003 Jamie Wilkinson <jaq@spacepants.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "parser.h"
#include "driver.h"

static void scan_err(const char * fmt, ...);
void include_file(const char *);
%}

string  \"[^\n]+\"
space   [ \t]+
id      [[:alnum:]_][[:alnum:]_+-]*

%%

"/*"	BEGIN(comment);

<comment>{
[^*\n]*		/* eat anything that's not a '*' */
"*"+[^*/\n]*	/* eat up '*'s not followes by '/'s */
\n		/* eat newlines */
"*"+"/"		BEGIN(INITIAL);
<<EOF>>		{
			scan_err("warning: comment reached end of file");
			yyterminate();
		}
}

#[^\n]*      /* strip shell style comments */

{string}     {
		/* we do not store the " characters in the string, so lop
		 * them off.  We can "safely" assume that the first and last
		 * characters in this regex are ", otherwise there's a bug
		 * in flex...  The result is somethign that is syntactically
		 * identical to an identifier for our purposes. */
		yylval->u_str = strndup(filtergen_text + 1, filtergen_leng - 2);
		return TOK_IDENTIFIER;
             }

{space}      /* ignore */

include      BEGIN(include);

accept       return TOK_ACCEPT;
dest         return TOK_DEST;
dport        return TOK_DPORT;
drop         return TOK_DROP;
forward      return TOK_FORWARD;
icmptype     return TOK_ICMPTYPE;
input        return TOK_INPUT;
local        return TOK_LOCAL;
log          return TOK_LOG;
masq         return TOK_MASQ;
oneway       return TOK_ONEWAY;
output       return TOK_OUTPUT;
proto        return TOK_PROTO;
proxy        return TOK_PROXY;
redirect     return TOK_REDIRECT;
reject       return TOK_REJECT;
source       return TOK_SOURCE;
sport        return TOK_SPORT;
text         return TOK_TEXT;

"{"          return TOK_LCURLY;
"}"          return TOK_RCURLY;
"["          return TOK_LSQUARE;
"]"          return TOK_RSQUARE;
";"          return TOK_SEMICOLON;
":"          return TOK_COLON;
"!"          return TOK_BANG;

{id}(\.{id})*	{
    yylval->u_str = strndup(filtergen_text, filtergen_leng);
    return TOK_IDENTIFIER;
}

"/"          return TOK_SLASH;

.            return TOK_ERR;

<include>[ \t]*       /* eat whitespace after include */
<include>[^ \t\n;]+    { /* include file name */
    char * name;

    name = strdup(yytext);
    scan_err("including %s", name);
    include_file(name);
    free(name);
    
    BEGIN(INITIAL);
}

<<EOF>>                {
    scan_err("eof! popping state");
    yypop_buffer_state();

    if (!YY_CURRENT_BUFFER) {
	yyterminate();
    }
}

%%

/* FIXME: make this return an immutable string */
char * filtergen_filename(void) {
    char * fn = NULL;

    /*fn = inc_stack[inc_stackptr].filename;*/
    return fn ? fn : strdup("(unknown)");
}

static void scan_err(const char * fmt, ...) {
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "%s:%d: ", filtergen_filename(), filtergen_get_lineno());
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
}

/* include a file or directory */
void include_file(const char * name) {
    struct stat st;
    DIR * d;
    struct dirent * r;
    char * fn;

    if (stat(name, &st)) {
	scan_err("warning: stat failed on \"%s\": %s", name, strerror(errno));
    } else {
	if (S_ISDIR(st.st_mode)) {
	    if ((d = opendir(name)) == NULL) {
		scan_err("warning: opendir failed on %s: %s", name, strerror(errno));
	    } else {
		while ((r = readdir(d)) != NULL) {
		    /* FIXME: assumes d_name */
		    if (r->d_name[0] == '.')
			continue;
		    asprintf(&fn, "%s/%s", name, r->d_name);
		    include_file(fn);
		    free(fn);
		}
		closedir(d);
	    }
	} else {
	    scan_err("opening %s as file", name);
		     
	    yyin = fopen(name, "r");
	    if ( !yyin ) {
		scan_err("boned: %s", yytext);
	    }

	    yypush_buffer_state(yy_create_buffer(yyin, YY_BUF_SIZE));
		     
	}
    }
}

void
filtergen_driver::scan_begin()
{
    yy_flex_debug = trace_scanning;
    filtergen_restart(file);
}

void
filtergen_driver::scan_end()
{
}

	