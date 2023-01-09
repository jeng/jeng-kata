#define STB_INCLUDE_IMPLEMENTATION
#define STB_C_LEXER_IMPLEMENTATION
#define STB_LIB_IMPLEMENTATION
#include "stb_lib.h"

int myWhite(char *c){
    return (*c == ' ' || *c == '\t' || *c == '\f');
}
#define STB_C_LEX_ISWHITE(x) myWhite(x)

#include "stb_include.h"
#include "stb_c_lexer.h"

int eol(int c) {
    return (c == '\n' || c == '\r');
}

int main() {
    size_t size;
    char *data = stb_include_load_file("day1.input", &size);
    stb_lexer lex;
    char store[1024];
    stb_c_lexer_init(&lex, data, &data[size], store, 1024);
    int n = 0;
    int result = 0;
    int last = 0;
    int maxres = 0;
    while(1){
        int res = stb_c_lexer_get_token(&lex);
        if (res == 0){
            printf("sum: %d max: %d\n", result, max(result, maxres));
            break;
        } else if (eol(last) && eol(lex.token)){
            printf("sum: %d max: %d\n~~~~~~\n", result, maxres);
            maxres = max(result, maxres);
            result = 0;
        } else if (lex.token == CLEX_intlit){
            printf("%d\n", lex.int_number);
            result += lex.int_number;
        }

        last = lex.token;
    }
}
