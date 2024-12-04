#include <iostream>
#include <sstream>
#include "interpreter.h"
#include "raise.h"

using namespace std;

void read(istream& ss, char prog[][MAX_TOKEN_LEN], unsigned int size, unsigned int idx) {
    if ( size <= idx ) {
        raise(prog_len_exceeded);
    } else if ( ss.eof() ) {
        prog[idx][0] = '\0';
        return;
    } else {
        ss.getline(prog[idx], MAX_TOKEN_LEN, ' ');
        if ( prog[idx][0] == '\0' )
            return read(ss, prog, size, idx);
        else if ( ss.fail() )
            raise(tok_len_exceeded);
        else
            return read(ss, prog, size, idx + 1);
    }
}

int main() {
    char input[MAX_PROG_LEN * MAX_TOKEN_LEN];
    char prog[MAX_PROG_LEN][MAX_TOKEN_LEN];
    cin.getline(input, MAX_PROG_LEN * MAX_TOKEN_LEN);
    istringstream ss (input);
    read(ss, prog, MAX_PROG_LEN, 0);
    cout << eval(prog) << "\n";
    return 0;
}
