#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const char null = '\0';
const char EMPTYSTR[1] = ""; //  char emptyStr[] = {'\"','\"','\0'};
const int SIZE = 100;
const int MAX_TOKEN_LEN = 999;
const int MAX_IDENT_LEN = 999;
const unsigned int MAX_CTX_LEN = 64;


int to_num(const char s[]) {
    int res;
    istringstream ss (s);
    ss >> res;

    return res;
}


void strcpy(char output[],char input[],int idx){

    if (input[idx] == '\0')
        return;

    else{
        output[idx] = input[idx];
        strcpy(output,input,++idx); // NO idx++ -> Segmentation fault
    }

}


void replaceByChar(const char input, char output[]){ //char copy -> replace by a char

    output[0] = input;
    output[1] = '\0';
    return;

}

bool eq_len(const char lhs[], const char rhs[], unsigned int idx){

    if (lhs[idx] == '\0' && rhs[idx] == '\0')
        return true;

    if ((lhs[idx] == '\0' && rhs[idx] != '\0') || (lhs[idx] != '\0' && rhs[idx] == '\0'))
        return false;

    return eq_len(lhs, rhs, ++idx);

}


bool eq_impl(const char lhs[], const char rhs[], unsigned int idx){

    if (lhs[idx] == '\0' && rhs[idx] == '\0') // Length 
        return true;

    if (lhs[idx] == rhs[idx]) // Whether char are the same
        return eq_impl(lhs,rhs,++idx);
    else
        return false;

}

bool eq(const char lhs[], const char rhs[]){
    
    int idx = 0;

    // if (eq_len(lhs,rhs,idx))
    //     return eq_impl(lhs,rhs,idx);
    // else
    //     return false;

    return eq_impl(lhs,rhs,idx);


}

void copy_impl(const char input[], char output[], unsigned int idx){

    if (input[idx] == '\0'){
        output[idx] = '\0';
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

void ctx_append_impl(const char ident[], int val, char ctx_k[][MAX_IDENT_LEN], int ctx_v[], unsigned int size, unsigned int idx){


    if (eq(ctx_k[idx],EMPTYSTR)){ //{"a","b","c",""} Size = 4 // {"a","b",""} 
                
        // if (idx+1 >= size){
        //     raise(ctx_overflow);
        //     return;
        // }

        copy(ident, ctx_k[idx]);
        copy(EMPTYSTR, ctx_k[idx+1]); 
        ctx_v[idx+1] = val; // Why idx-1;
        return;

    }

    else
        ctx_append_impl(ident,val,ctx_k,ctx_v,size,++idx);

}

void ctx_append(const char ident[], int val, char ctx_k[][MAX_IDENT_LEN], int ctx_v[], unsigned int size){

    int idx = 0;

    ctx_append_impl(ident,val,ctx_k,ctx_v,size,idx);

}

int ctx_lookup_impl(const char ident[], const char ctx_k[][MAX_IDENT_LEN], const int ctx_v[], unsigned int idx){

    int count = 0;

    if (eq(ctx_k[idx], ident)){
     
        count = ctx_v[idx];
    }

    if (!eq(ctx_k[idx], EMPTYSTR)){

        int next_count = ctx_lookup_impl(ident, ctx_k, ctx_v, ++idx);
        if (next_count != 0)
            count = next_count;
    
    }
    
    return count;

}

int eval_impl(char prog[][MAX_TOKEN_LEN], unsigned int& cur, char ctx_k[][MAX_IDENT_LEN], int ctx_v[]) {
    
    int count = 0; // LET Var Expr1 Expr2 // LET a 42 ADD a 1 // ADD 42 1
    
    if (prog[cur][0] >= '0' && prog[cur][0] <= '9') {
        return to_num(prog[cur]);
    }

    if (prog[cur][0] >= 'a' && prog[cur][0] <= 'z'){
        return ctx_lookup_impl(prog[cur], ctx_k, ctx_v, 0);
    }

    if (prog[cur][0] == 'L'){

        cur++;
        if (prog[cur][0] >= 'a' && prog[cur][0] <= 'z'){
            char token[MAX_TOKEN_LEN];
            copy(prog[cur], token);
            cur++;
            int val = eval_impl(prog, cur, ctx_k, ctx_v); //Evaluate Expr1
            ctx_append_impl(token, val, ctx_k, ctx_v, 9999, 0);
            cur++;
       
        }

        count = eval_impl(prog, cur, ctx_k, ctx_v); //Evaluate Expr2
        //cur++;

    }

    if (prog[cur][0] == 'A'){

        cur++;
        count += eval_impl(prog, cur, ctx_k, ctx_v);
        cur++;
        count += eval_impl(prog, cur, ctx_k, ctx_v);
        //cur++; // Extra cur
        
    }

    if (prog[cur][0] == 'M'){

        int op1, op2;
        
        if (prog[cur][1] == 'U'){
        
            cur++;
            op1 = eval_impl(prog, cur, ctx_k, ctx_v);
            cur++;
            op2 = eval_impl(prog, cur, ctx_k, ctx_v);
            count = op1 * op2;
            //cur++; // Extra cur

        }

        else{
        
            cur++;
            op1 = eval_impl(prog, cur, ctx_k, ctx_v);
            cur++;
            op2 = eval_impl(prog, cur, ctx_k, ctx_v);
            count = op1 % op2;
            
        }
        
    }

    if (prog[cur][0] == 'D'){

        int op1, op2;

        cur++;
        op1 = eval_impl(prog, cur, ctx_k, ctx_v);
        cur++;
        op2 = eval_impl(prog, cur, ctx_k, ctx_v);
        count = op1 / op2;
        
    }

    cout << cur << endl;
    return count;
}

int main() {

    //char prog[][MAX_TOKEN_LEN] = { "LET", "a", "2", "LET", "a2", "DIV", "a", "a", "LET", "a4", "DIV", "a2", "a2", "DIV", "a2", "a4"};
    //char prog[][MAX_TOKEN_LEN] = {"LET", "a", "42", "ADD", "a", "1"};
    //char prog[][MAX_TOKEN_LEN] = {"LET", "a2", "LET", "a", "2", "MUL", "a", "a", "LET", "a4", "MUL", "a2", "a2", "MUL", "a2", "a4"};
    char prog[][MAX_TOKEN_LEN] = {"ADD","MUL","2","2","MUL","2","2"};

    unsigned int cur = 0;
    unsigned int size = 64;
    char ctx_k[MAX_CTX_LEN][MAX_IDENT_LEN] = {""};  // No variables used in the program
    int ctx_v[MAX_CTX_LEN] = {};  // No variables used in the program

    ctx_append("a",100,ctx_k,ctx_v,size);

    cout << ctx_k[0] << endl;
    cout << ctx_v[0] << endl;
    cout << ctx_v[1] << endl;


    return 0;

}


