#include <cstring>
#include <iostream>
#include "interpreter.h"
#include "raise.h"

using namespace std;

bool eq_n(const char it1[][MAX_IDENT_LEN], const char it2[][MAX_IDENT_LEN], int count) {
    return equal(it1, it1 + count, it2, [](const char s1[], const char s2[]) { return strcmp(s1, s2) == 0; });
}

bool eq_n(const int it1[], const int it2[], int count) {
    return equal(it1, it1 + count, it2);
}

// `eq`
void test1() {
    const char s[] = "Hello world!";
    cout
        << "s: \"Hello world!\"\n"
        << "eq(s, s): " << eq(s, s) << "\n";
}
void test2() {
    const char s1[] = "Hello world!";
    const char s2[] = "Hello hello!";
    cout
        << "s1: \"Hello world!\"\n"
        << "s2: \"Hello hello!\"\n"
        << "eq(s1, s2): " << eq(s1, s2) << "\n";
}

// `copy`
void test3() {
    const char s1[] = "Hello world!";
    char s2[20] = "Hello hello!";
    copy(s1, s2);
    cout
        << "s1: \"Hello world!\"\n"
        << "s2: \"Hello hello!\"\n"
        << "copy(s1, s2);\n"
        << "strcmp(s1, s2): " << strcmp(s1, s2) << "\n";
}

// `ctx_append`
void test4() {
    char ctx_k[20][MAX_IDENT_LEN], ans_k[20][MAX_IDENT_LEN] { "a", "" };
    int ctx_v[20], ans_v[20] { 42 };
    ctx_k[0][0] = '\0';
    ctx_append("a", 42, ctx_k, ctx_v, 20);
    cout
        << "ctx_k: { \"\" }\n"
        << "ctx_v: { }\n"
        << "ctx_append(\"a\", 42, ctx_k, ctx_v, 20);\n"
        << "is ctx_k { \"a\", \"\" }? " << eq_n(ctx_k, ans_k, 2) << "\n"
        << "is ctx_v { 42 }? " << eq_n(ctx_v, ans_v, 1) << "\n";
}
void test5() {
    char ctx_k[20][MAX_IDENT_LEN], ans_k[20][MAX_IDENT_LEN] { "a", "b", "c", "" };
    int ctx_v[20], ans_v[20] { 42, 43, 44 };
    ctx_k[0][0] = '\0';
    ctx_append("a", 42, ctx_k, ctx_v, 20);
    ctx_append("b", 43, ctx_k, ctx_v, 20);
    ctx_append("c", 44, ctx_k, ctx_v, 20);
    cout
        << "ctx_k: { \"\" }\n"
        << "ctx_v: { }\n"
        << "ctx_append(\"a\", 42, ctx_k, ctx_v, 20);\n"
        << "ctx_append(\"b\", 43, ctx_k, ctx_v, 20);\n"
        << "ctx_append(\"c\", 44, ctx_k, ctx_v, 20);\n"
        << "is ctx_k { \"a\", \"b\", \"c\", \"\" }? " << eq_n(ctx_k, ans_k, 4) << "\n"
        << "is ctx_v { 42, 43, 44 }? " << eq_n(ctx_v, ans_v, 3) << "\n";
}

// `ctx_remove`
void test6() {
    char ctx_k[20][MAX_IDENT_LEN] { "a", "b", "c", "" }, ans_k[20][MAX_IDENT_LEN] { "a", "b", "" };
    int ctx_v[20] { 42, 43, 44 }, ans_v[20] { 42, 43 };
    ctx_remove(ctx_k, ctx_v);
    cout
        << "ctx_k: { \"a\", \"b\", \"c\", \"\" }\n"
        << "ctx_v: { 42, 43, 44 }\n"
        << "ctx_remove(ctx_k, ctx_v);\n"
        << "is ctx_k { \"a\", \"b\", \"\" }? " << eq_n(ctx_k, ans_k, 3) << "\n"
        << "is ctx_v { 42, 43 }? " << eq_n(ctx_v, ans_v, 2) << "\n";
}

// `ctx_lookup`
void test7() {
    char ctx_k[20][MAX_IDENT_LEN] { "a", "b", "c", "" };
    int ctx_v[20] { 42, 43, 44 };
    cout
        << "ctx_k: { \"a\", \"b\", \"c\", \"\" }\n"
        << "ctx_v: { 42, 43, 44 }\n"
        << "ctx_lookup(\"a\", ctx_k, ctx_v): " << ctx_lookup("a", ctx_k, ctx_v) << "\n"
        << "ctx_lookup(\"b\", ctx_k, ctx_v): " << ctx_lookup("b", ctx_k, ctx_v) << "\n"
        << "ctx_lookup(\"c\", ctx_k, ctx_v): " << ctx_lookup("c", ctx_k, ctx_v) << "\n";
}
void test8() {
    char ctx_k[20][MAX_IDENT_LEN];
    int ctx_v[20];
    strcpy(ctx_k[0], "a");
    strcpy(ctx_k[1], "b");
    strcpy(ctx_k[2], "c");
    strcpy(ctx_k[3], "");
    ctx_v[0] = 42;
    ctx_v[1] = 43;
    ctx_v[2] = 44;
    cout
        << "ctx_k: { \"a\", \"b\", \"c\", \"\" }\n"
        << "ctx_v: { 42, 43, 44 }\n"
        << "ctx_lookup(\"a\", ctx_k, ctx_v): " << ctx_lookup("a", ctx_k, ctx_v) << "\n"
        << "ctx_lookup(\"b\", ctx_k, ctx_v): " << ctx_lookup("b", ctx_k, ctx_v) << "\n"
        << "ctx_lookup(\"c\", ctx_k, ctx_v): " << ctx_lookup("c", ctx_k, ctx_v) << "\n";
}
void test9() {
    char ctx_k[20][MAX_IDENT_LEN] { "a", "a", "a", "" };
    int ctx_v[20] { 42, 43, 44 };
    cout
        << "ctx_k: { \"a\", \"a\", \"a\", \"\" }\n"
        << "ctx_v: { 42, 43, 44 }\n"
        << "ctx_lookup(\"a\", ctx_k, ctx_v): " << ctx_lookup("a", ctx_k, ctx_v) << "\n";
}

// `eval_impl`
void test10() {
    char prog[20][MAX_TOKEN_LEN] { "42", "" };
    unsigned int cur = 0;
    char ctx_k[MAX_CTX_LEN][MAX_IDENT_LEN];
    int ctx_v[MAX_CTX_LEN];
    cout
        << "prog: 42\n"
        << "cur: 0\n"
        << "ctx_k: { }\n"
        << "ctx_v: { }\n"
        << "eval_impl(prog, cur, ctx_k, ctx_v): " << eval_impl(prog, cur, ctx_k, ctx_v) << "\n"
        << "cur: " << cur << "\n";
}
void test11() {
    char prog[20][MAX_TOKEN_LEN] { "a", "" };
    unsigned int cur = 0;
    char ctx_k[MAX_CTX_LEN][MAX_IDENT_LEN] { "a", "b", "c1A", "" };
    int ctx_v[MAX_CTX_LEN] { 42, 43, 44 };
    cout
        << "prog: a\n"
        << "cur: 0\n"
        << "ctx_k: { \"a\", \"b\", \"c1A\", \"\" }\n"
        << "ctx_v: { 42, 43, 44 }\n"
        << "eval_impl(prog, cur, ctx_k, ctx_v): " << eval_impl(prog, cur, ctx_k, ctx_v) << "\n"
        << "cur: " << cur << "\n";
}
void test12() {
    char prog[20][MAX_TOKEN_LEN] { "c1A", "" };
    unsigned int cur = 0;
    char ctx_k[MAX_CTX_LEN][MAX_IDENT_LEN] { "a", "b", "c1A", "" };
    int ctx_v[MAX_CTX_LEN] { 42, 43, 44 };
    cout
        << "prog: c1A\n"
        << "cur: 0\n"
        << "ctx_k: { \"a\", \"b\", \"c1A\", \"\" }\n"
        << "ctx_v: { 42, 43, 44 }\n"
        << "eval_impl(prog, cur, ctx_k, ctx_v): " << eval_impl(prog, cur, ctx_k, ctx_v) << "\n"
        << "cur: " << cur << "\n";
}
void test13() {
    char prog1[20][MAX_TOKEN_LEN] { "ADD", "7", "3", "" },
        prog2[20][MAX_TOKEN_LEN] { "SUB", "7", "3", "" },
        prog3[20][MAX_TOKEN_LEN] { "MUL", "7", "3", "" },
        prog4[20][MAX_TOKEN_LEN] { "DIV", "7", "3", "" },
        prog5[20][MAX_TOKEN_LEN] { "MOD", "7", "3", "" };
    unsigned int cur1 = 0,
        cur2 = 0,
        cur3 = 0,
        cur4 = 0,
        cur5 = 0;
    char ctx_k[MAX_CTX_LEN][MAX_IDENT_LEN];
    int ctx_v[MAX_CTX_LEN];
    cout
        << "ctx_k: { }\n"
        << "ctx_v: { }\n\n"
        << "prog1: ADD 7 3\n"
        << "cur1: 0\n"
        << "eval_impl(prog1, cur1, ctx_k, ctx_v): " << eval_impl(prog1, cur1, ctx_k, ctx_v) << "\n"
        << "cur1: " << cur1 << "\n\n"
        << "prog2: SUB 7 3\n"
        << "cur2: 0\n"
        << "eval_impl(prog2, cur2, ctx_k, ctx_v): " << eval_impl(prog2, cur2, ctx_k, ctx_v) << "\n"
        << "cur2: " << cur2 << "\n\n"
        << "prog3: MUL 7 3\n"
        << "cur3: 0\n"
        << "eval_impl(prog3, cur3, ctx_k, ctx_v): " << eval_impl(prog3, cur3, ctx_k, ctx_v) << "\n"
        << "cur3: " << cur3 << "\n\n"
        << "prog4: DIV 7 3\n"
        << "cur4: 0\n"
        << "eval_impl(prog4, cur4, ctx_k, ctx_v): " << eval_impl(prog4, cur4, ctx_k, ctx_v) << "\n"
        << "cur4: " << cur4 << "\n\n"
        << "prog5: MOD 7 3\n"
        << "cur5: 0\n"
        << "eval_impl(prog5, cur5, ctx_k, ctx_v): " << eval_impl(prog5, cur5, ctx_k, ctx_v) << "\n"
        << "cur5: " << cur5 << "\n\n";
}
void test14() {
    char prog[20][MAX_TOKEN_LEN] { "LET", "foo", "42", "0", "" };
    unsigned int cur = 0;
    char ctx_k[MAX_CTX_LEN][MAX_IDENT_LEN] { "" }, ans_k[MAX_CTX_LEN][MAX_IDENT_LEN] { "" };
    int ctx_v[MAX_CTX_LEN], ans_v[MAX_CTX_LEN];
    cout
        << "prog: LET foo 42 0\n"
        << "cur: 0\n"
        << "ctx_k: { \"\" }\n"
        << "ctx_v: { }\n"
        << "eval_impl(prog, cur, ctx_k, ctx_v): " << eval_impl(prog, cur, ctx_k, ctx_v) << "\n"
        << "cur: " << cur << "\n"
        << "is ctx_k { \"\" }? " << eq_n(ctx_k, ans_k, 1) << "\n"
        << "is ctx_v { }? " << eq_n(ctx_v, ans_v, 0) << "\n";
}
void test15() {
    char prog[20][MAX_TOKEN_LEN] { "LET", "foo", "42", "foo", "" };
    unsigned int cur = 0;
    char ctx_k[MAX_CTX_LEN][MAX_IDENT_LEN] { "" }, ans_k[MAX_CTX_LEN][MAX_IDENT_LEN] { "" };
    int ctx_v[MAX_CTX_LEN], ans_v[MAX_CTX_LEN];
    cout
        << "prog: LET foo 42 foo\n"
        << "cur: 0\n"
        << "ctx_k: { \"\" }\n"
        << "ctx_v: { }\n"
        << "eval_impl(prog, cur, ctx_k, ctx_v): " << eval_impl(prog, cur, ctx_k, ctx_v) << "\n"
        << "cur: " << cur << "\n"
        << "is ctx_k { \"\" }? " << eq_n(ctx_k, ans_k, 1) << "\n"
        << "is ctx_v { }? " << eq_n(ctx_v, ans_v, 0) << "\n";
}
void test16() {
    char prog[20][MAX_TOKEN_LEN] { "LET", "a", "2", "LET", "a2", "MUL", "a", "a", "LET", "a4", "MUL", "a2", "a2", "MUL", "a2", "a4", "" };
    unsigned int cur = 0;
    char ctx_k[MAX_CTX_LEN][MAX_IDENT_LEN] { "" }, ans_k[MAX_CTX_LEN][MAX_IDENT_LEN] { "" };
    int ctx_v[MAX_CTX_LEN], ans_v[MAX_CTX_LEN];
    cout
        << "prog: LET a 2 LET a2 MUL a a LET a4 MUL a2 a2 MUL a2 a4\n"
        << "cur: 0\n"
        << "ctx_k: { \"\" }\n"
        << "ctx_v: { }\n"
        << "eval_impl(prog, cur, ctx_k, ctx_v): " << eval_impl(prog, cur, ctx_k, ctx_v) << "\n"
        << "cur: " << cur << "\n"
        << "is ctx_k { \"\" }? " << eq_n(ctx_k, ans_k, 1) << "\n"
        << "is ctx_v { }? " << eq_n(ctx_v, ans_v, 0) << "\n";
}
void test17() {
    char prog[20][MAX_TOKEN_LEN] { "ADD", "LET", "a", "2", "MUL", "a", "a", "2", "" };
    unsigned int cur = 0;
    char ctx_k[MAX_CTX_LEN][MAX_IDENT_LEN] { "" }, ans_k[MAX_CTX_LEN][MAX_IDENT_LEN] { "" };
    int ctx_v[MAX_CTX_LEN], ans_v[MAX_CTX_LEN];
    cout
        << "prog: ADD LET a 2 MUL a a 2\n"
        << "cur: 0\n"
        << "ctx_k: { \"\" }\n"
        << "ctx_v: { }\n"
        << "eval_impl(prog, cur, ctx_k, ctx_v): " << eval_impl(prog, cur, ctx_k, ctx_v) << "\n"
        << "cur: " << cur << "\n"
        << "is ctx_k { \"\" }? " << eq_n(ctx_k, ans_k, 1) << "\n"
        << "is ctx_v { }? " << eq_n(ctx_v, ans_v, 0) << "\n";
}
void test18() {
    char prog[20][MAX_TOKEN_LEN] { "LET", "a", "2", "LET", "b", "3", "LET", "a", "5", "MUL", "a", "b", "" };
    unsigned int cur = 0;
    char ctx_k[MAX_CTX_LEN][MAX_IDENT_LEN] { "" }, ans_k[MAX_CTX_LEN][MAX_IDENT_LEN] { "" };
    int ctx_v[MAX_CTX_LEN], ans_v[MAX_CTX_LEN];
    cout
        << "prog: LET a 2 LET b 3 LET a 5 MUL a b\n"
        << "cur: 0\n"
        << "ctx_k: { \"\" }\n"
        << "ctx_v: { }\n"
        << "eval_impl(prog, cur, ctx_k, ctx_v): " << eval_impl(prog, cur, ctx_k, ctx_v) << "\n"
        << "cur: " << cur << "\n"
        << "is ctx_k { \"\" }? " << eq_n(ctx_k, ans_k, 1) << "\n"
        << "is ctx_v { }? " << eq_n(ctx_v, ans_v, 0) << "\n";
}

// `eval`
void test19() {
    char prog[20][MAX_TOKEN_LEN] { "ADD", "42", "1", "" };
    cout
        << "prog: ADD 42 1\n"
        << "eval(prog): " << eval(prog) << "\n";
}
void test20() {
    char prog[20][MAX_TOKEN_LEN] { "LET", "a2", "LET", "a", "2", "MUL", "a", "a", "LET", "a4", "MUL", "a2", "a2", "MUL", "a2", "a4", "" };
    cout
        << "prog: LET a2 LET a 2 MUL a a LET a4 MUL a2 a2 MUL a2 a4\n"
        << "eval(prog): " << eval(prog) << "\n";
}

constexpr unsigned int test_count = 20;

void run(unsigned int from, unsigned int to) {
    if ( from < to ) {
        cout << "====================\nTest " << from << "\n====================\n\n";
        try {
            switch ( from ) {
                case 1: test1(); break;
                case 2: test2(); break;
                case 3: test3(); break;
                case 4: test4(); break;
                case 5: test5(); break;
                case 6: test6(); break;
                case 7: test7(); break;
                case 8: test8(); break;
                case 9: test9(); break;
                case 10: test10(); break;
                case 11: test11(); break;
                case 12: test12(); break;
                case 13: test13(); break;
                case 14: test14(); break;
                case 15: test15(); break;
                case 16: test16(); break;
                case 17: test17(); break;
                case 18: test18(); break;
                case 19: test19(); break;
                case 20: test20(); break;
            }
        }
        catch (const interpreter_error&) {}
        cout << "\n";
        return run(from + 1, to);
    } else
        return;
}

int main() {
    unsigned int test_idx;
    cout << "Enter a test case number (1-" << test_count << ", 0 to run all): ";
    cin >> test_idx;
    cout << "\n\n";
    if ( test_idx > 0 )
        if ( test_idx <= test_count )
            run(test_idx, test_idx + 1);
        else
            cout << "Test " << test_idx << " does not exist\n";
    else
        run(1, test_count + 1);
    return 0;
}
