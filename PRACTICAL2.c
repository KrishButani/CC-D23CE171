#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 100

typedef struct {
    int nextState[MAX_SYMBOLS];
} State;


int findSymbolIndex(char symbols[], int numSymbols, char symbol) {
    for (int i = 0; i < numSymbols; i++) {
        if (symbols[i] == symbol) {
            return i;
        }
    }
    return -1; 
}

int validateString(State automata[], char symbols[], int numSymbols, int initialState, int acceptingStates[], int numAcceptingStates, char *inputString) {
    int currentState = initialState;

    for (int i = 0; inputString[i] != '\0'; i++) {
        int symbolIndex = findSymbolIndex(symbols, numSymbols, inputString[i]);

        if (symbolIndex == -1) {
            return 0; 
        }

        currentState = automata[currentState].nextState[symbolIndex];

        if (currentState == -1) {
            return 0; 
        }
    }

    for (int i = 0; i < numAcceptingStates; i++) {
        if (currentState == acceptingStates[i]) {
            return 1; 
        }
    }

    return 0; 
}

int main() {
    int numSymbols, numStates, initialState, numAcceptingStates;
    char symbols[MAX_SYMBOLS];
    State automata[MAX_STATES];
    int acceptingStates[MAX_STATES];

    printf("Number of input symbols: ");
    scanf("%d", &numSymbols);

    printf("Input symbols: ");
    for (int i = 0; i < numSymbols; i++) {
        scanf(" %c", &symbols[i]);
    }

    printf("Enter number of states: ");
    scanf("%d", &numStates);

    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < numSymbols; j++) {
            automata[i].nextState[j] = -1; 
        }
    }

   
    printf("Initial state: ");
    scanf("%d", &initialState);

    printf("Number of accepting states: ");
    scanf("%d", &numAcceptingStates);

    printf("Accepting states: ");
    for (int i = 0; i < numAcceptingStates; i++) {
        scanf("%d", &acceptingStates[i]);
    }

    printf("Transition table (format: state symbol next_state):\n");
    int fromState, toState;
    char symbol;
    while (1) {
        printf("Enter transition (or -1 to stop): ");
        scanf("%d", &fromState);

        if (fromState == -1) {
            break;
        }

        scanf(" %c %d", &symbol, &toState);

        int symbolIndex = findSymbolIndex(symbols, numSymbols, symbol);
        if (symbolIndex != -1) {
            automata[fromState].nextState[symbolIndex] = toState;
        } else {
            printf("Invalid symbol in transition!\n");
        }
    }

    char inputString[100];
    printf("Input string: ");
    scanf("%s", inputString);

    if (validateString(automata, symbols, numSymbols, initialState, acceptingStates, numAcceptingStates, inputString)) {
        printf("Valid string\n");
    } else {
        printf("Invalid string\n");
    }

    return 0;
}
