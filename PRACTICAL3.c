#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LEN 100

// Keywords in C
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum",
    "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return",
    "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};

int isKeyword(const char *word) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;  // Keyword found
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

    // Skip whitespaces and newlines
    while ((ch = fgetc(file)) != EOF && isspace(ch));

    if (ch == EOF) return;

    // Handling identifiers and keywords
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
        ungetc(ch, file);  // Push the character back to the file

    // Handling numbers (integer or float)
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
        ungetc(ch, file);  // Push the character back to the file

    // Handling character literals
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
            ungetc(ch, file);  // Error: unmatched single quote
        }

    // Handling string literals
    } else if (ch == '"') {
        token[idx++] = ch;
        while ((ch = fgetc(file)) != EOF && ch != '"') {
            token[idx++] = ch;
        }
        token[idx++] = '"';
        token[idx] = '\0';
        printToken(token, "STRING LITERAL");

    // Handling operators and punctuation
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' ||
               ch == '>' || ch == '<' || ch == '!' || ch == '&' || ch == '|' ||
               ch == '%' || ch == '^' || ch == '(' || ch == ')' || ch == '{' ||
               ch == '}' || ch == '[' || ch == ']' || ch == ';' || ch == ',' ||
               ch == '.' || ch == ':') {
        token[0] = ch;
        token[1] = '\0';
        printToken(token, "OPERATOR / PUNCTUATION");
    // Handling comments
    } else if (ch == '/') {
        ch = fgetc(file);
        if (ch == '/') {
            // Single-line comment
            while ((ch = fgetc(file)) != EOF && ch != '\n');
            token[0] = '\0'; // Comment is not printed as a token
        } else if (ch == '*') {
            // Multi-line comment
            while ((ch = fgetc(file)) != EOF) {
                if (ch == '*') {
                    ch = fgetc(file);
                    if (ch == '/') break;
                    ungetc(ch, file);
                }
            }
            token[0] = '\0'; // Comment is not printed as a token
        } else {
            ungetc(ch, file);  // Invalid token
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
