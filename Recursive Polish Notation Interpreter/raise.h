#ifndef __RAISE_H__
#define __RAISE_H__

#include <cstdlib>
#include <exception>

enum Err { tok_len_exceeded, prog_len_exceeded, invalid_op, invalid_num, invalid_ident, invalid_tok, ctx_overflow, num_overflow, num_div_by_0, unknown_ident, eof_reached, prog_not_consumed, };

class interpreter_error : std::exception {};

[[noreturn]] void raise(Err e);

#endif
