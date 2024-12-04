#include <iostream>
#include "raise.h"

using namespace std;

[[noreturn]] void raise(Err e) {
    std::cout << (
        e == tok_len_exceeded ? "tok_len_exceeded\n" :
        e == prog_len_exceeded ? "prog_len_exceeded\n" :
        e == invalid_op ? "invalid_op\n" :
        e == invalid_num ? "invalid_num\n" :
        e == invalid_ident ? "invalid_ident\n" :
        e == invalid_tok ? "invalid_tok\n" :
        e == ctx_overflow ? "ctx_overflow\n" :
        e == num_overflow ? "num_overflow\n" :
        e == num_div_by_0 ? "num_div_by_0\n" :
        e == unknown_ident ? "unknown_ident\n" :
        e == eof_reached ? "eof_reached\n" :
        e == prog_not_consumed ? "prog_not_consumed\n" :
        ""
    );
    throw interpreter_error();
    // exit(0);
}
