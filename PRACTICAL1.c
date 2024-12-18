#include <stdio.h>
#include <string.h>
#include <stdbool.h>


bool validate_string(char* str) {
    int len = strlen(str);
    int i = 0;
    

    while (i < len && str[i] == 'a') {
        i++;
    }
    

    if (i + 2 == len && str[i] == 'b' && str[i+1] == 'b') {
        return true;
    }
    
    return false;
}

int main() {
    char input[100];
    

    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);
    

    input[strcspn(input, "\n")] = 0;
    

    if (validate_string(input)) {
        printf("Valid String\n");
    } else {
        printf("Invalid String\n");
    }
    
    return 0;
}
