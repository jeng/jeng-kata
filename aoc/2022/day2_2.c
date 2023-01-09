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

#define ROCK ('A')
#define PAPER ('B')
#define SCISSORS ('C')

#define LOSE ('X')
#define DRAW ('Y')
#define WIN ('Z')

int getScore(char theirMove, char myMove){
    int shape = 0;
    int score = 0;
    if (myMove == ROCK) shape = 1;
    if (myMove == PAPER) shape = 2;
    if (myMove == SCISSORS) shape = 3;

    if (theirMove == ROCK && myMove == PAPER) score = 6;
    if (theirMove == PAPER && myMove == SCISSORS) score = 6;
    if (theirMove == SCISSORS && myMove == ROCK) score = 6;

    if (theirMove == ROCK && myMove == ROCK) score = 3;
    if (theirMove == PAPER && myMove == PAPER) score = 3;
    if (theirMove == SCISSORS && myMove == SCISSORS) score = 3;

    return shape + score;
}

char myMove(char theirMove, char outcome){
    if (outcome == WIN){
        if (theirMove == ROCK) return PAPER;
        if (theirMove == PAPER) return SCISSORS;
        if (theirMove == SCISSORS) return ROCK;
        assert(0);
    } else if (outcome == LOSE){
        if (theirMove == ROCK) return SCISSORS;
        if (theirMove == PAPER) return ROCK;
        if (theirMove == SCISSORS) return PAPER;
        assert(0);
    }
    return theirMove;
}

int main() {
    size_t size;
    char *data = stb_include_load_file("day2.input", &size);
    stb_lexer lex;
    char store[1024];
    stb_c_lexer_init(&lex, data, &data[size], store, 1024);
    int n = 0;
    char theirMove = ' ';
    char outcome = ' ';
    int win = 0;
    while(1){
        int res = stb_c_lexer_get_token(&lex);
        if (res == 0){
            break;
        } else if (eol(lex.token) && n == 2){
           printf("%c %c %c %d\n", theirMove, outcome, myMove(theirMove, outcome), getScore(theirMove, myMove(theirMove, outcome)));
           win += getScore(theirMove, myMove(theirMove, outcome));
           n = 0;
        } else if (lex.token == CLEX_id){
            assert(n < 2);
            if(n == 0) theirMove = lex.string[0];
            if(n == 1) outcome = lex.string[0];
            n++;
            printf("%d %s\n", lex.token, lex.string);
        }
    }

    if(n == 2){
        printf("%c %c %c %d\n", theirMove, outcome, myMove(theirMove, outcome), getScore(theirMove, myMove(theirMove, outcome)));
        win += getScore(theirMove, myMove(theirMove, outcome));
    }

    printf("wins %d\n", win);
}
