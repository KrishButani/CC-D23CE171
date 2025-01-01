#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LEN 100

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum",
    "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return",
    "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};

int isKeyword(const char *word) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

void printToken(const char *token, const char *category) {
    printf("%-20s : %s\n", token, category);
}

void getNextToken(FILE *file) {
    char ch;
    char token[MAX_TOKEN_LEN];
    int idx = 0;

    while ((ch = fgetc(file)) != EOF && isspace(ch));

    if (ch == EOF) return;

    if (isalpha(ch) || ch == '_') {
        token[idx++] = ch;
        while ((ch = fgetc(file)) != EOF && (isalnum(ch) || ch == '_')) {
            token[idx++] = ch;
        }
        token[idx] = '\0';
        if (isKeyword(token)) {
            printToken(token, "KEYWORD");
        } else {
            printToken(token, "IDENTIFIER");
        }
        ungetc(ch, file);

    } else if (isdigit(ch)) {
        token[idx++] = ch;
        while ((ch = fgetc(file)) != EOF && isdigit(ch)) {
            token[idx++] = ch;
        }
        if (ch == '.') {
            token[idx++] = ch;
            while ((ch = fgetc(file)) != EOF && isdigit(ch)) {
                token[idx++] = ch;
            }
            printToken(token, "FLOAT LITERAL");
        } else {
            token[idx] = '\0';
            printToken(token, "INTEGER LITERAL");
        }
        ungetc(ch, file);

    } else if (ch == '\'') {
        token[idx++] = ch;
        ch = fgetc(file);
        token[idx++] = ch;
        ch = fgetc(file);
        if (ch == '\'') {
            token[idx++] = ch;
            token[idx] = '\0';
            printToken(token, "CHARACTER LITERAL");
        } else {
            ungetc(ch, file);
        }

    } else if (ch == '"') {
        token[idx++] = ch;
        while ((ch = fgetc(file)) != EOF && ch != '"') {
            token[idx++] = ch;
        }
        token[idx++] = '"';
        token[idx] = '\0';
        printToken(token, "STRING LITERAL");

    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' ||
               ch == '>' || ch == '<' || ch == '!' || ch == '&' || ch == '|' ||
               ch == '%' || ch == '^' || ch == '(' || ch == ')' || ch == '{' ||
               ch == '}' || ch == '[' || ch == ']' || ch == ';' || ch == ',' ||
               ch == '.' || ch == ':') {
        token[0] = ch;
        token[1] = '\0';
        printToken(token, "OPERATOR / PUNCTUATION");

    } else if (ch == '/') {
        ch = fgetc(file);
        if (ch == '/') {
            // Single-line comment
            while ((ch = fgetc(file)) != EOF && ch != '\n');
            token[0] = '\0';
        } else if (ch == '*') {
            // Multi-line comment
            while ((ch = fgetc(file)) != EOF) {
                if (ch == '*') {
                    ch = fgetc(file);
                    if (ch == '/') break;
                    ungetc(ch, file);
                }
            }
            token[0] = '\0';
        } else {
            ungetc(ch, file);
        }
    } else {
        token[0] = ch;
        token[1] = '\0';
        printToken(token, "MISMATCH TOKEN");
    }
}

void lexicalAnalysis(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    printf("Tokenized Output:\n");
    while (!feof(file)) {
        getNextToken(file);
    }

    fclose(file);
}

int main() {
    const char *filename = "example.c";  // Replace with the name of your C file
    lexicalAnalysis(filename);
    return 0;
}
