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

int getBadge(char s[3][1024]){
    char buffer[53] = {0};
    for(int i = 0; i < 3; i++){
        printf("%s \n", s[i]);
        for(int j = 0; j < strlen(s[i]); j++){
            int priority = 0;
            if ('a' <= s[i][j] && s[i][j] <= 'z')
                priority = (s[i][j] - 'a') + 1;
            else
                priority = (s[i][j] - 'A') + 27;

            if (buffer[priority] == i){
                printf("%c = %d (p %d)\n", s[i][j], i+1, priority);
                buffer[priority] = i + 1;
            }
        }
    }
    for(int i = 0; i < 53; i++){
        if (buffer[i] == 3)
            return i;
    }
}

int main() {
    size_t size;
    char *data = stb_include_load_file("day3.input", &size);
    stb_lexer lex;
    char store[1024];
    char s[3][1024];
    int n = 0;
    int sum = 0;
    stb_c_lexer_init(&lex, data, &data[size], store, 1024);

    while(1){
        int res = stb_c_lexer_get_token(&lex);
        if (res == 0){
            break;
        }

        if (lex.token == CLEX_id){
            assert(strlen(lex.string)< 1023);
            strncpy(s[n], lex.string, strlen(lex.string) + 1);
            n = (n + 1) % 3;
            if (n == 0){
                int badge = getBadge(s);
                printf("badge %d\n", badge);
                sum += badge;
                printf("------------------\n");
            }
        }
    }

    printf("sum %d\n", sum);
}
