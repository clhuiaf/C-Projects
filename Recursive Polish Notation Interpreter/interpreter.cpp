#include "interpreter.h"
#include "raise.h"

const char EMPTYSTR[1] = ""; //  char EMPTYSTR[1] = {'\0'};
const char NULLSTR = '\0';

bool eq_impl(const char lhs[], const char rhs[], unsigned int idx){

    if (lhs[idx] == NULLSTR && rhs[idx] == NULLSTR) // Length 
        return true;

    if (lhs[idx] == rhs[idx]) // Whether char are the same
        return eq_impl(lhs,rhs,++idx);
    else
        return false;

}

bool eq(const char lhs[], const char rhs[]){
    
    int idx = 0;

    return eq_impl(lhs,rhs,idx);

}


void copy_impl(const char input[], char output[], unsigned int idx){

    if (input[idx] == NULLSTR){
        output[idx] = NULLSTR;
        return;
    }

    else{
        output[idx] = input[idx];
        copy_impl(input,output,++idx);
    }

}

void copy(const char input[], char output[]){

    int idx = 0;

    copy_impl(input,output,idx);

}

void replaceByChar(const char input, char output[]){ //char copy -> replace by a char

    output[0] = input;
    output[1] = NULLSTR;
    return;

}

void ctx_append_impl(const char ident[], int val, char ctx_k[][MAX_IDENT_LEN], int ctx_v[], unsigned int size, unsigned int idx){


    if (eq(ctx_k[idx],EMPTYSTR)){ //{"a","b","c",""} Size = 4 // {"a","b",""} 
                
        if (idx+1 >= size){
            raise(ctx_overflow);
            return;
        }

        copy(ident, ctx_k[idx]);
        copy(EMPTYSTR, ctx_k[idx+1]); 
        ctx_v[idx] = val; // Why idx-1; ++idx , then idx-1 So idx+1;
        return;

    }

    else
        ctx_append_impl(ident,val,ctx_k,ctx_v,size,++idx);

}

void ctx_append(const char ident[], int val, char ctx_k[][MAX_IDENT_LEN], int ctx_v[], unsigned int size){

    int idx = 0;

    ctx_append_impl(ident,val,ctx_k,ctx_v,size,idx);

}


void ctx_remove_impl(char ctx_k[][MAX_IDENT_LEN], int ctx_v[], unsigned int idx){

    if (eq(ctx_k[idx],EMPTYSTR)){

        copy(EMPTYSTR, ctx_k[--idx]);
        replaceByChar(NULLSTR, ctx_k[idx]);
        ctx_v[idx] = 0;
        return;

    }

    else{
        ctx_remove_impl(ctx_k, ctx_v, ++idx);
    }

}

void ctx_remove(char ctx_k[][MAX_IDENT_LEN], int ctx_v[]){

    int idx = 0;

    ctx_remove_impl(ctx_k,ctx_v,idx);

}

int ctx_lookup_impl(const char ident[], const char ctx_k[][MAX_IDENT_LEN], const int ctx_v[], unsigned int idx){

    int count = 0;
    bool reachedEnd = false;


    if (!eq(ctx_k[idx], EMPTYSTR)){

        if (eq(ctx_k[idx], ident)){
            count = ctx_v[idx];
        }

        int next_count = ctx_lookup_impl(ident, ctx_k, ctx_v, ++idx);
        if (next_count != 0)
            count = next_count;

    }

    else{
        reachedEnd = true;
    }

    if (reachedEnd && idx == 0 && count ==0)
        raise(unknown_ident);

    return count;

}

int ctx_lookup(const char ident[], const char ctx_k[][MAX_IDENT_LEN], const int ctx_v[]){

    int idx = 0;

    return ctx_lookup_impl(ident, ctx_k, ctx_v, idx); //warning: non-void function does not return a value [-Wreturn-type]

}

int eval_impl(char prog[][MAX_TOKEN_LEN], unsigned int& cur, char ctx_k[][MAX_IDENT_LEN], int ctx_v[]) {
    
    int count = 0; // LET Var Expr1 Expr2 

    if (eq(prog[cur], EMPTYSTR)){ 
        raise(eof_reached);
    }

    if ((prog[cur][0] >= '0' && prog[cur][0] <= '9')||(prog[cur][0] == '-')) {

        if (eq(prog[cur+1],EMPTYSTR)){
            cur++;
            return to_num(prog[cur-1]);
        }

        return to_num(prog[cur]);

    }

    if (prog[cur][0] >= 'a' && prog[cur][0] <= 'z'){
        
        if (eq(prog[cur+1],EMPTYSTR)){
            cur++;
            return ctx_lookup(prog[cur-1], ctx_k, ctx_v);
        }

        return ctx_lookup(prog[cur], ctx_k, ctx_v);

    }

    if (prog[cur][0] == 'L'){
        
        if (prog[cur][1] != 'E'){
            raise(invalid_op);
        }

        cur++; // Go to second token

        if (eq(prog[cur],EMPTYSTR)){
            raise(eof_reached);
        }

        if (!(prog[cur][0] >= 'a' && prog[cur][0] <= 'z')){
            raise(invalid_ident);
        }

        char token[MAX_TOKEN_LEN];
        copy(prog[cur], token);
        cur++;
        int val = eval_impl(prog, cur, ctx_k, ctx_v);
        ctx_append(token, val, ctx_k ,ctx_v, MAX_CTX_LEN); //Size = MAX_CTX_LEN?
        cur++;

        count = eval_impl(prog, cur, ctx_k, ctx_v);
        ctx_remove(ctx_k, ctx_v);
        
    }

    else if (prog[cur][0] == 'A'){

        if (prog[cur][1] != 'D'){
            raise(invalid_op);
        }

        cur++;
        count += eval_impl(prog, cur, ctx_k, ctx_v);
        cur++;
        count += eval_impl(prog, cur, ctx_k, ctx_v);

    }

    else if (prog[cur][0] == 'S'){

        if (prog[cur][1] != 'U'){
            raise(invalid_op);
        }

        cur++;
        count += eval_impl(prog, cur, ctx_k, ctx_v);
        cur++;
        count -= eval_impl(prog, cur, ctx_k, ctx_v);

    }

    else if (prog[cur][0] == 'M'){

        int op1, op2;
        
        if (prog[cur][1] == 'U'){
        
            cur++;
            op1 = eval_impl(prog, cur, ctx_k, ctx_v);
            cur++;
            op2 = eval_impl(prog, cur, ctx_k, ctx_v);
            count = op1 * op2;

        }

        else if (prog[cur][1] == 'O'){
        
            cur++;
            op1 = eval_impl(prog, cur, ctx_k, ctx_v);
            cur++;
            op2 = eval_impl(prog, cur, ctx_k, ctx_v);

            if (op2 == 0){
                raise(num_div_by_0);
            }

            count = op1 % op2;
            
        }

        else{
            raise(invalid_op);
        }
        
    }

    else if (prog[cur][0] == 'D'){

        if (prog[cur][1] != 'I'){
            raise(invalid_op);
        }

        int op1, op2;

        cur++;
        op1 = eval_impl(prog, cur, ctx_k, ctx_v);
        cur++;
        op2 = eval_impl(prog, cur, ctx_k, ctx_v);

        if (op2 == 0){
            raise(num_div_by_0);
        }

        count = op1 / op2;
        
    }

    else{
        raise(invalid_tok);
    }

    return count;

}

int eval(char prog[][MAX_TOKEN_LEN]){
    
    unsigned int cur;
    char ctx_k[MAX_CTX_LEN][MAX_IDENT_LEN];
    int ctx_v[MAX_CTX_LEN];
    return eval_impl(prog, cur, ctx_k, ctx_v);

}

