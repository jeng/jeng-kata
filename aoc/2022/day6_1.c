#define STB_INCLUDE_IMPLEMENTATION
#define STB_C_LEXER_IMPLEMENTATION
#define STB_LIB_IMPLEMENTATION
#include "stb_lib.h"
#define STB_DS_IMPLEMENTATION
      #include "stb_ds.h"

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
    char *s;
    int length;
} string_t;

typedef struct {
    char *s;
    int index;
    int size;
} stack_t;

typedef struct {
    int num;
    int from;
    int to;
} move_t;

string_t *split(string_t line, char c){
    string_t *results = NULL;
    for(int i = 0; i < line.length; ){
        string_t s;
        s.length = 0;
        s.s = &(line.s[i]);
        while(i < line.length && line.s[i] != c){
            s.length++;
            i++;
        }
        arrput(results, s);
        i++;
    }
    return results;
}

string_t getLine(char **data){
    string_t s;
    s.s = *data;
    s.length = 0;
    while(!eol(**data) && **data != 0){
        (*data)++;
        s.length++;
        //printf("%d %c\n", **data, **data);
    }
    return s;
}

string_t *slurp(char **data){
    string_t *result = NULL;
    while(**data != 0){
        arrput(result, getLine(data));
        if (eol(**data))
            (*data)++;
    }
    return result;
}

int *getPositions(string_t *lines){
    int *positions = NULL;
    for(int i = 0; i < arrlen(lines); i++){
        if (lines[i].length == 0){
            for(int j = 0; j < lines[i-1].length; j++){
                if (lines[i-1].s[j] != ' ')
                    arrput(positions, j);
            }
            return positions;
        }
    }
    return positions;
}

int getStartPosition(string_t *lines){
    int start = 0;
    for(int i = 0; i < arrlen(lines); i++){
        if (lines[i].length == 0){
            start = i;
            break;
        }
    }
    return start;
}

stack_t *getStacks(string_t *lines){
    int *positions = getPositions(lines);
    stack_t *stacks = NULL;
    int start = getStartPosition(lines) - 2;
    int size = (start + 1) * arrlen(positions);
    for(int i = 0; i < arrlen(positions); i++){
        stack_t stack;
        stack.s = calloc(size, sizeof(stack_t));
        stack.index = 0;
        stack.size = size;
        for(int j = start; j >= 0; j--){
            if (lines[j].s[positions[i]] != ' ')
                stack.s[stack.index++] = lines[j].s[positions[i]];
        }
        arrput(stacks, stack);
    }
    return stacks;
}

int getNumber(string_t *parts, int index){
    char s[100];
    int x;
    sprintf(s, "%.*s", parts[index].length, parts[index].s);
    sscanf(s, "%d", &x);
    return x;
}

void move(stack_t *stacks, int amount, int from, int to){
    to--;
    from--;
    assert(to >= 0);
    assert(from <= arrlen(stacks));
    assert(stacks[to].index < stacks[to].size);
    assert(stacks[from].index >= 0);
    for(int j = stacks[from].index - amount; j < stacks[from].index; j++){
        stacks[to].s[stacks[to].index++] = stacks[from].s[j];
    }
    stacks[from].index = stacks[from].index - amount;
}

void getPacket(char *data, int start, int len, char *packet){
    int j = 0;
    for(int i = start; i < len && i < start + 4; i++){
        packet[j++] = data[i];
    }
}

int isSeq(char *packet){
    char buffer[26] = {0};
    for(int i = 0; i < 4; i++){
        buffer[packet[i]-'a']++;
    }
    for(int i = 0; i < 26; i++){
        if (buffer[i] > 1)
            return 0;
    }
    return 1;
}

int main() {
    size_t size;
    char *data = stb_include_load_file("day6.input", &size);
    //char *test = "mjqjpqmgbljsphdztnvjfqwrcgsmlb";
    //char *test = "bvwbjplbgvbhsrlpgdmjqwftvncz";
    //char *test = "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw";
    //char *data = test; 
    //size = strlen(test);
    //char *start = data;
    stb_lexer lex;
    char store[1024];
    for(int i = 0; i < size - 4; i++){
        char packet[4];
        getPacket(data, i, size, packet);
        printf("%.*s\n", 4, packet);
        if (isSeq(packet)){
            printf("got it %d\n", i + 4);
            break;
        }
    }
    // string_t *lines = slurp(&data);
    // for(int i = 0; i < arrlen(lines); i++)
    //     printf("(%d) %.*s\n", lines[i].length, lines[i].length, lines[i].s);

    // int *positions = getPositions(lines);
    // for(int i = 0; i < arrlen(positions); i++){
    //     printf("%d\n", positions[i]);
    // }

    // stack_t *stacks = getStacks(lines);
    // for(int i = 0; i < arrlen(stacks); i++){
    //     for(int j = 0; j < stacks[i].index; j++){
    //         printf("%c ", stacks[i].s[j]);
    //     }
    //     printf(" index (%d)\n", stacks[i].index);
    // }

    // int start = getStartPosition(lines) + 1;
    // for(int i = start; i < arrlen(lines); i++){
    //     string_t *parts = split(lines[i], ' ');
    //     if (arrlen(parts) < 6)
    //         continue;
    //     int amount = getNumber(parts, 1);
    //     int from = getNumber(parts, 3);
    //     int to = getNumber(parts, 5);
    //     move(stacks, amount, from, to);
    //     printf("%d %d %d\n", amount, from, to);
    // }

    // //answer
    // char s[1024] = {0};
    // for(int i = 0; i < arrlen(stacks); i++){
    //     s[i] = stacks[i].s[stacks[i].index-1];
    // }
    // printf("-------------------------------\n");
    // printf("%s\n", s);



    // Line out[1024];
    // ConStack *stack;
    // int numStacks;
    // int len;
    // int i = 0;

    // while(1){
    //     getLine(&data, &(out[i].s[0]), &(out[i].len));
    //     printf("(%d) %s\n", out[i].len, out[i].s);
    //     if (out[i].len == 0){
    //         i--;
    //         break;
    //     }
    //     i++;
    // }
   
    // numStacks = getTheContainers(i, out);
    // stack = (ConStack*)malloc(sizeof(ConStack) * numStacks);
    // for(int i = 0; i < numStacks; i++){
    // } 
    // printf("con %d\n", getTheContainers(i, out));

    // for(int j = 0; j < i; j++){
    //     printf("blaa %s strlen(%s)\n", out[j].s, out[j].len);
    // }

    /*
    for(int i = 0; i < 6; i++){
        getLine(&data, out, &len);
        printf("(%d) %s\n", len, out);
        if (len == 0){
            printf("fuck this\n");
        }
    }

    int n = 0;
    int sum = 0;
    int low = 1;
    stb_c_lexer_init(&lex, data, &data[size], store, 1024);

    //Plow through the lexer until we get to the 

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
    */

    //if (contains(pair[0], pair[1])){
    //    sum++; 
    //    printf("sum %d p1 %d, %d p2 %d, %d\n", sum, pair[0].low, pair[0].high, pair[1].low, pair[1].high);
    //}

    //printf("sum %d\n", sum);
}
