%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int line_number = 1;
%}

/* Define Regular Expressions */
KEYWORD      "int"|"float"|"char"|"double"|"if"|"else"|"for"|"while"|"return"|"void"
IDENTIFIER   [a-zA-Z_][a-zA-Z0-9_]*
CONSTANT     [0-9]+(\.[0-9]+)?
STRING       \"[^\"]*\"
OPERATOR     "=="|"!="|"<="|">="|"&&"|"||"|"!"|"+"|"-"|"*"|"/"|"="|"<"|">"
PUNCTUATION  "["|"]"|"{"|"}"|"("|")"|";"|","
COMMENT      "//".*|"/*"([^*]|\*+[^/*])*\*+"/"
WHITESPACE   [ \t\r]+

%%

{KEYWORD}      { printf("[KEYWORD]      %s\n", yytext); }
{IDENTIFIER}   { printf("[IDENTIFIER]   %s\n", yytext); }
{CONSTANT}     { printf("[CONSTANT]     %s\n", yytext); }
{STRING}       { printf("[STRING]       %s\n", yytext); }
{OPERATOR}     { printf("[OPERATOR]     %s\n", yytext); }
{PUNCTUATION}  { printf("[PUNCTUATION]  %s\n", yytext); }
{COMMENT}      { printf("[COMMENT]      %s\n", yytext); }
{WHITESPACE}   { /* Ignore spaces */ }
\n             { line_number++; }
.              { printf("[LEXICAL ERROR] Unrecognized token: %s (Line %d)\n", yytext, line_number); }

%%

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            printf("Error: Cannot open file %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    }

    yylex();  // Start lexical analysis

    printf("Lexical analysis completed.\n");
    return 0;
}

int yywrap() {
    return 1;  // End of file
}
