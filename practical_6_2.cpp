#include <iostream>
#include <cstring>
using namespace std;

char input[100];
int pos = 0;


bool E();
bool EPrime();
bool T();
bool TPrime();
bool F();
void skipWhitespace();

void skipWhitespace() {
    while (input[pos] == ' ') {
        pos++;
    }
}


bool E() {
    if (T()) {
        if (EPrime()) {
            return true;
        }
    }
    return false;
}


bool EPrime() {
    skipWhitespace();
    if (input[pos] == '+') {
        pos++;
        if (T()) {
            return EPrime();
        }
        return false;
    }

    return true;
}


bool T() {
    if (F()) {
        if (TPrime()) {
            return true;
        }
    }
    return false;
}


bool TPrime() {
    skipWhitespace();
    if (input[pos] == '*') {
        pos++;
        if (F()) {
            return TPrime();
        }
        return false;
    }
  
    return true;
}

bool F() {
    skipWhitespace();
   
    if (input[pos] == '(') {
        pos++;
        if (E()) {
            skipWhitespace();
            if (input[pos] == ')') {
                pos++;
                return true;
            }
        }
        return false;
    }
    
    if (isalpha(input[pos])) {
        pos++;
        return true;
    }
    return false;
}

int main() {
    cout << "Enter the input string: ";
    cin.getline(input, 100);  
    
    if (E() && input[pos] == '\0') {
        cout << "Valid string" << endl;
    } else {
        cout << "Invalid string" << endl;
    }
    
    return 0;
}
