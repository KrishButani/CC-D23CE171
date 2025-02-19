#include <iostream>
#include <cstring>
using namespace std;

char input[100];
int pos = 0;

bool S();
bool L();
bool LPrime();
void checkString(); 


void skipWhitespace() {
    while (input[pos] == ' ') {
        pos++;
    }
}

bool S() {
    skipWhitespace();
    if (input[pos] == '(') {
        pos++;
        if (L()) {
            skipWhitespace();
            if (input[pos] == ')') {
                pos++;
                return true;
            }
        }
        return false;
    } 
    else if (input[pos] == 'a') {
        pos++;
        return true;
    }
    return false;
}


bool L() {
    if (S()) {
        if (LPrime()) {
            return true;
        }
    }
    return false;
}


bool LPrime() {
    skipWhitespace();
    if (input[pos] == ',') {
        pos++;
        if (S()) {
            return LPrime();
        }
        return false;
    }
   
    return true;
}


void checkString() {
    pos = 0; 
    if (S() && input[pos] == '\0') {
        cout << "Valid string" << endl;
    } else {
        cout << "Invalid string" << endl;
    }
}

int main() {
    cout << "Enter strings to validate (enter 'END' to finish):" << endl;
    
    while (true) {
        cin.getline(input, 100);
        
        
        if (strcmp(input, "END") == 0) {
            break;
        }
        
       
        switch (input[0]) {
            case 'a':
            case '(':
                checkString();
                break;
            default:
                cout << "Invalid string" << endl;
        }
    }
    
    return 0;
}
