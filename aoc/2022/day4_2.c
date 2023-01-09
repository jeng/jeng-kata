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

typedef struct {
    int low;
    int high;
} range_t;

int overlap(range_t a, range_t b){
    return !(a.high < b.low || b.high < a.low);
}

int main() {
    size_t size;
    char *data = stb_include_load_file("day4.input", &size);
    stb_lexer lex;
    char store[1024];
    range_t pair[2];

    int n = 0;
    int sum = 0;
    int low = 1;
    stb_c_lexer_init(&lex, data, &data[size], store, 1024);

    while(1){
        int res = stb_c_lexer_get_token(&lex);

        if (res == 0){
            break;
        }

        if (lex.token == CLEX_intlit){
            if (low)
                pair[n].low = lex.int_number;
            else
                pair[n].high = lex.int_number;
        } else if (lex.token == '-'){
            low = 0;
        } else if (lex.token == ','){
            low = 1;
            n++;
        } else if (eol(lex.token)){
            n = 0;
            low = 1;
            if (overlap(pair[0], pair[1])){
                sum++; 
                printf("sum %d p1 %d, %d p2 %d, %d\n", sum, pair[0].low, pair[0].high, pair[1].low, pair[1].high);
            }
        }
    }

    //if (contains(pair[0], pair[1])){
    //    sum++; 
    //    printf("sum %d p1 %d, %d p2 %d, %d\n", sum, pair[0].low, pair[0].high, pair[1].low, pair[1].high);
    //}

    printf("sum %d\n", sum);
}
