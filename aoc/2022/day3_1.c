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

int getPriority(char *string, int len){
    //get the char that is in both 
    char buffer[53] = {0};
    int half = len/2;
    for(int i = 0; i < len; i++){
        int priority = 0;
        if ('a' <= string[i] && string[i] <= 'z')
            priority = (string[i] - 'a') + 1;
        else
            priority = (string[i] - 'A') + 27;

        if (i < half)
            printf("%c", string[i]);

        if (buffer[priority] == 1 && i >= half){
            return priority;
        } else if (i < half)
            buffer[priority] = 1;
    }
}

int main() {
    size_t size;
    char *data = stb_include_load_file("day3.input", &size);
    stb_lexer lex;
    char store[1024];
    int sum = 0;
    stb_c_lexer_init(&lex, data, &data[size], store, 1024);

    while(1){
        int res = stb_c_lexer_get_token(&lex);
        if (res == 0){
            break;
        }

        if (lex.token == CLEX_id){
            printf("s = %s len = %d\n", lex.string, strlen(lex.string));
            int n = getPriority(lex.string, strlen(lex.string));
            printf("\npriority %d\n", n);
            sum+=n;
        }
    }

    printf("sum %d\n", sum);
}
