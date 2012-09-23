#include <stdio.h>
#include <gc.h>
#include "macros.hpp"
#include "y.tab.h"
#include <set>
#include <string>

using namespace std;

//extern "C"
//{
int yyparse(void);
//}
main()
{
    GC_INIT();
    mdl_interp_init();
    yyparse();
}

set<string> compass_words;

extern "C"
{
    void add_compass_word(char *s)
    {
	compass_words.insert(string(s));
//	printf("CWord: %s\n", s);
    }

    int is_compass_word(char *s)
    {
	return compass_words.find(string(s)) != compass_words.end();
    }

    void yyerror(char *s)
    {
	extern int yychar, zil_line;
	fprintf(stderr, "YYERROR: line %6d %s\n", zil_line, s);
    }
    
    int yywrap()
    {
	return 1;
    }
}
