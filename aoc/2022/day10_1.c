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
typedef struct {
    int up;
    int down;
    int left;
    int right;
} history_t;

//Yuck I'm going to brute force it.  I don't want to deal with a divide and conquer right now.
//Plus it will be fun to see how fast an optimized build of the stupid algorithm is. 
//
//lol, it was like instant with a debug build

int goleft(int x, int y, string_t *lines){
    int n = lines[y].s[x] - '0';
    int result = 0;
    x--;
    while(x >= 0){
        result++;
        if ((lines[y].s[x] - '0') >= n)
            break;
        x--;
    }
    return result;
}
int goright(int x, int y, string_t *lines){
    int n = lines[y].s[x] - '0';
    int width = lines[y].length;
    int result = 0;
    x++;
    while(x < width){
        result++;
        if ((lines[y].s[x] - '0') >= n)
            break;
        x++;
    }
    return result;
}
int goup(int x, int y, string_t *lines){
    int n = lines[y].s[x] - '0';
    int result = 0;
    y--;
    while(y >= 0){
        result++;
        if ((lines[y].s[x] - '0') >= n)
            break;
        y--;
    }
    return result;
}
int godown(int x, int y, string_t *lines){
    int n = lines[y].s[x] - '0';
    int height = arrlen(lines);
    int result = 0;
    y++;
    while(y < height){
        result++;
        if ((lines[y].s[x] - '0') >= n)
            break;
        y++;
    }
    return result;
}

#define W (300)
#define H (500)

#define SX (200)
#define SY (400)

void drawGrid(char *grid){
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            printf("%c", grid[i * W + j]);
        }
        printf("\n");
    }
}

void putCell(char *grid, char c, int x, int y){
    assert(y >= 0);
    assert(y < H);
    assert(x >= 0);
    assert(x < W);
    grid[(y * W) + x] = c;
}

typedef enum {
    ADD,
    NOP
} OPS;

int checkSignal(int regx, int pc){
    if (pc == 20 || pc == 60 || pc == 100 || pc == 140 || pc == 180 || pc == 220){
        return regx * pc;
    }
    return 0;
}

int main() {
    size_t size;
    char *data = stb_include_load_file("day10.input", &size);
    char *start = data;
    int regx = 1;
    OPS op = NOP;
    stb_lexer lex;
    char store[1024];
    stb_c_lexer_init(&lex, data, &data[size], store, 1024);
    int pc = 1;
    int sign = 1;
    int sum = 0;

    //Plow through the lexer until we get to the 
    //20th, 60th, 100th, 140th, 180th, and 220th cycles
    while(1){
        int res = stb_c_lexer_get_token(&lex);

        if (res == 0){
            break;
        }

        if (lex.token == CLEX_id && strcmp(lex.string, "addx") == 0){
            op = ADD;
            sign = 1;
        } else if (lex.token == CLEX_id && strcmp(lex.string, "noop") == 0){
            op = NOP;
            pc++;
            sum += checkSignal(regx, pc);
        } else if (op == ADD && lex.token == '-'){
            sign = -1;
        } else if (op == ADD && lex.token == CLEX_intlit){
            pc++;
            sum += checkSignal(regx, pc);
            pc++;
            regx += (sign * lex.int_number);
            sum += checkSignal(regx, pc);
        }
        printf("pc %d %d\n", pc, regx);
    }

    printf("total %d\n", pc * regx);
    printf("sum %d\n", sum);

}
