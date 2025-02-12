%{
#include <stdio.h>
#include <string.h>
%}

%%
charusat     { printf("university"); }
CHARUSAT     { printf("university"); }
.            { printf("%s", yytext); }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}