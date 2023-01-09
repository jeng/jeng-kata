#include <stdint.h>
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

typedef enum {
    OP_ADD,
    OP_MUL
} op_t;

typedef enum {
    TT_LIT,
    TT_SYM
} term_type_t;

typedef struct {
    term_type_t type;
    int literal;
    int symbol;//TODO we only have one symbol in this env
} term_t;

typedef struct {
    uint64_t *items;
    op_t operator;
    term_t left;
    term_t right;
    int mod;
    int trueCon;
    int falseCon;
    int inspect;
} monkey_t;

typedef enum{
    MPS_ID,
    MPS_START,
    MPS_OP,
    MPS_TEST,
    MPS_LEFT,
    MPS_RIGHT,
    MPS_SYM,
    MPS_TRUE,
    MPS_FALSE,
    MPS_END
} monkey_parse_state_t;

int main() {
    size_t size;
    char *data = stb_include_load_file("day11.input", &size);
    stb_lexer lex;
    char store[1024];
    monkey_t *monkeys = NULL;
    monkey_parse_state_t state = MPS_ID;
    stb_c_lexer_init(&lex, data, &data[size], store, 1024);

    while(1){
        int res = stb_c_lexer_get_token(&lex);

        if (res == 0){
            break;
        }

        if (lex.token == CLEX_intlit && state == MPS_ID){
            monkey_t currentMonkey;
            currentMonkey.items = NULL;
            currentMonkey.inspect = 0;
            arrput(monkeys, currentMonkey);
            assert(arrlen(monkeys)-1 == lex.int_number);
        } else if (lex.token == CLEX_intlit && state == MPS_START){
            arrput(monkeys[arrlen(monkeys)-1].items, lex.int_number);
        } else if (lex.token == CLEX_intlit && state == MPS_TEST){
            monkeys[arrlen(monkeys)-1].mod = lex.int_number;
        } else if (lex.token == CLEX_intlit && state == MPS_TRUE){
            monkeys[arrlen(monkeys)-1].trueCon = lex.int_number;
        } else if (lex.token == CLEX_intlit && state == MPS_FALSE){
            monkeys[arrlen(monkeys)-1].falseCon = lex.int_number;
        } else if (lex.token == '=' && state == MPS_OP){
            state = MPS_LEFT;
        } else if (state == MPS_LEFT && lex.token == CLEX_intlit){
            monkeys[arrlen(monkeys)-1].left.type = TT_LIT;
            monkeys[arrlen(monkeys)-1].left.literal = lex.int_number;
            state = MPS_SYM;
        } else if (state == MPS_LEFT && lex.token == CLEX_id){
            monkeys[arrlen(monkeys)-1].left.type = TT_SYM;
            monkeys[arrlen(monkeys)-1].left.symbol = 0;
            state = MPS_SYM;
        } else if (state == MPS_RIGHT && lex.token == CLEX_intlit){
            monkeys[arrlen(monkeys)-1].right.type = TT_LIT;
            monkeys[arrlen(monkeys)-1].right.literal = lex.int_number;
        } else if (state == MPS_RIGHT && lex.token == CLEX_id){
            monkeys[arrlen(monkeys)-1].right.type = TT_SYM;
            monkeys[arrlen(monkeys)-1].right.symbol = 0;
        } else if (state == MPS_SYM && lex.token == '+'){
            monkeys[arrlen(monkeys)-1].operator = OP_ADD;
            state = MPS_RIGHT;
        } else if (state == MPS_SYM && lex.token == '*'){
            monkeys[arrlen(monkeys)-1].operator = OP_MUL;
            state = MPS_RIGHT;
        } else if (eol(lex.token)){
            switch (state) {
            case MPS_ID: state = MPS_START; break;
            case MPS_START: state = MPS_OP; break;
            case MPS_RIGHT: state = MPS_TEST; break;
            case MPS_TEST: state = MPS_TRUE; break;
            case MPS_TRUE: state = MPS_FALSE; break;
            case MPS_FALSE: state = MPS_END; break;
            case MPS_END: state = MPS_ID; break;
            default:
                assert(0);
            }
        }
    }

    //Output start states
    for(int i = 0; i < arrlen(monkeys); i++){
        printf("m%d: ", i);
        for(int j = 0; j < arrlen(monkeys[i].items); j++){
            printf("%lld ", monkeys[i].items[j]);
        }
        printf("\n");
        printf("%d %c %d\n", 
            ((monkeys[i].left.type == TT_SYM) ? -1 : monkeys[i].left.literal), 
            ((monkeys[i].operator == OP_ADD) ? '+' : '*' ),
            ((monkeys[i].right.type == TT_SYM) ? -1 : monkeys[i].right.literal));
        printf("mod: %d\n", monkeys[i].mod);
        printf("true: %d\n", monkeys[i].trueCon);
        printf("false: %d\n\n", monkeys[i].falseCon);
    }

    //get global mod
    int globalMod = 1;
    for(int i = 0; i < arrlen(monkeys); i++){
        globalMod *= monkeys[i].mod;
    }

    //Play the game
    int rounds = 10000;
    for(int r = 0; r < rounds; r++){
        for(int i = 0; i < arrlen(monkeys); i++){
            while(arrlen(monkeys[i].items) > 0){
                uint64_t item = monkeys[i].items[0];
                uint64_t right = 0;
                uint64_t left = 0;

                arrdel(monkeys[i].items, 0);
                monkeys[i].inspect++;

                if (monkeys[i].left.type == TT_SYM){
                    left = item;
                } else {
                    left = monkeys[i].left.literal;
                }
                if (monkeys[i].right.type == TT_SYM){
                    right = item;
                } else {
                    right = monkeys[i].right.literal;
                }

                uint64_t ans = 0;
                if (monkeys[i].operator == OP_ADD) {
                    ans = left + right;
                } else if (monkeys[i].operator == OP_MUL) {
                    ans = left * right;
                }

                //ans = ans/3;
                ans = ans % globalMod;

                if ((ans % monkeys[i].mod) == 0){
                    arrput(monkeys[monkeys[i].trueCon].items, ans);
                } else {
                    arrput(monkeys[monkeys[i].falseCon].items, ans);
                }
            }
        }
    }
    printf("==========\n");

    //Output start states
    uint64_t m1 = 0;
    uint64_t m2 = 0;
    for(int i = 0; i < arrlen(monkeys); i++){
        printf("m%d: ", i);
        for(int j = 0; j < arrlen(monkeys[i].items); j++){
            printf("%lld ", monkeys[i].items[j]);
        }
        printf("\n");
        printf("%d %c %d\n", 
            ((monkeys[i].left.type == TT_SYM) ? -1 : monkeys[i].left.literal), 
            ((monkeys[i].operator == OP_ADD) ? '+' : '*' ),
            ((monkeys[i].right.type == TT_SYM) ? -1 : monkeys[i].right.literal));
        printf("mod: %d\n", monkeys[i].mod);
        printf("true: %d\n", monkeys[i].trueCon);
        printf("false: %d\n", monkeys[i].falseCon);
        printf("inspect: %d\n\n", monkeys[i].inspect);
        if (monkeys[i].inspect > m1){
            m2 = m1;
            m1 = monkeys[i].inspect;
        } else if (monkeys[i].inspect > m2){
            m2 = monkeys[i].inspect;
        }
    }

    printf("total %llu\n", m1 * m2);
}
