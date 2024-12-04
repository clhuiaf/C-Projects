#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include "num.h"

const unsigned int MAX_PROG_LEN = 512;
const unsigned int MAX_IDENT_LEN = 64;
const unsigned int MAX_TOKEN_LEN = MAX_IDENT_LEN > MAX_NUM_LEN ? MAX_IDENT_LEN : MAX_NUM_LEN;
const unsigned int MAX_CTX_LEN = 64;

bool eq(const char lhs[], const char rhs[]);
void copy(const char input[], char output[]);

void ctx_append(const char ident[], int val, char ctx_k[][MAX_IDENT_LEN], int ctx_v[], unsigned int size);
void ctx_remove(char ctx_k[][MAX_IDENT_LEN], int ctx_v[]);
int ctx_lookup(const char ident[], const char ctx_k[][MAX_IDENT_LEN], const int ctx_v[]);

int eval(char prog[][MAX_TOKEN_LEN]);
int eval_impl(char prog[][MAX_TOKEN_LEN], unsigned int& cur, char ctx_k[][MAX_IDENT_LEN], int ctx_v[]);

#endif
