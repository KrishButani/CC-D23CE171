%{
#include <stdio.h>
%}

%%
[0-9]+  { printf("%s\n", yytext); }
.       ;  /* Ignore all other characters */
%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
