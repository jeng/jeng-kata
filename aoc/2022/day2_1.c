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

int getScore(char theirMove, char myMove){
    int shape = 0;
    int score = 0;
    if (myMove == 'X') shape = 1;
    if (myMove == 'Y') shape = 2;
    if (myMove == 'Z') shape = 3;
    if (theirMove == 'A' && myMove == 'Y') score = 6;
    if (theirMove == 'B' && myMove == 'Z') score = 6;
    if (theirMove == 'C' && myMove == 'X') score = 6;
    if (theirMove == 'A' && myMove == 'X') score = 3;
    if (theirMove == 'B' && myMove == 'Y') score = 3;
    if (theirMove == 'C' && myMove == 'Z') score = 3;
    return shape + score;
}

int main() {
    size_t size;
    char *data = stb_include_load_file("day2.input", &size);
    stb_lexer lex;
    char store[1024];
    stb_c_lexer_init(&lex, data, &data[size], store, 1024);
    int n = 0;
    char theirMove = ' ';
    char myMove = ' ';
    int win = 0;
    while(1){
        int res = stb_c_lexer_get_token(&lex);
        if (res == 0){
            break;
        } else if (eol(lex.token) && n == 2){
           printf("%c %c %d\n", theirMove, myMove, getScore(theirMove, myMove));
           win += getScore(theirMove, myMove);
           n = 0;
        } else if (lex.token == CLEX_id){
            assert(n < 2);
            if(n == 0) theirMove = lex.string[0];
            if(n == 1) myMove = lex.string[0];
            n++;
            printf("%d %s\n", lex.token, lex.string);
        }
    }

    if(n == 2){
        printf("%c %c %d\n", theirMove, myMove, getScore(theirMove, myMove));
        win += getScore(theirMove, myMove);
    }

    printf("wins %d\n", win);
}
