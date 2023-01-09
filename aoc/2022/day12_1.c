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

typedef struct v2_t {
    int x;
    int y;
    char c;
    int level;
    int parent;
} v2_t;



int main() {
    size_t size;
    char *data = stb_include_load_file("day12.input", &size);
    stb_lexer lex;
    char store[1024];
    string_t *lines = slurp(&data);
    int width = lines[0].length;
    int height = arrlen(lines);
    v2_t *starts = NULL;

    v2_t end;
    end.c = '{';

    //Find start
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if (lines[i].s[j] == 'S'){
                v2_t start;
                start.c = '`';
                start.level = 0;
                start.x = j;
                start.y = i;
                arrput(starts, start);
            }
            if (lines[i].s[j] == 'a'){
                v2_t start;
                start.c = 'a';
                start.level = 0;
                start.x = j;
                start.y = i;
                arrput(starts, start);
            }
             if (lines[i].s[j] == 'E'){
                lines[i].s[j] = '{';
            }
            printf("%c", lines[i].s[j]);
        }
        printf("\n");
    }
    //printf("start (%d %d)\n", start.x, start.y);


    int winner = width * height;
    for (int si = 0; si < arrlen(starts); si++){
        int *visited = calloc(width * height, sizeof(int));
        v2_t start = starts[si];
        v2_t *queue = NULL;
        arrput(queue, start);
        while(arrlen(queue) > 0){
            v2_t current = queue[0];
            arrdel(queue, 0);
            visited[(current.y * width) + current.x] = 1;
            /*printf("%d %d %c %d\n", current.x, current.y, current.c, current.level );*/

            if (current.c == end.c){
                end.x = current.x;
                end.y = current.y;
                winner = min(winner, current.level);   
                printf("found it %d\n", current.level);
                break;
            }

            if (current.x > 0){
                char c = lines[current.y].s[current.x - 1];
                if (c <= current.c || c == current.c + 1){ 
                    if (!visited[(current.y * width) + (current.x -1)]){
                        v2_t n = {current.x -1, current.y, c, current.level + 1, (current.y * width) + current.x};
                        int found = 0;
                        for (int i = 0; i < arrlen(queue); i++){
                            if (queue[i].x == n.x && queue[i].y == n.y) {found = 1; break;}
                        }
                        if (!found)
                            arrput(queue, n);
                    } else {
                        //printf("arg\n");
                    }
                }
            }
            if (current.x + 1 < width){
                char c = lines[current.y].s[current.x + 1];
                if (c <= current.c || c == current.c + 1){ 
                    if (!visited[(current.y * width) + (current.x +1)]){
                        v2_t n = {current.x +1, current.y, c, current.level + 1, (current.y * width) + current.x};
                        int found = 0;
                        for (int i = 0; i < arrlen(queue); i++){
                            if (queue[i].x == n.x && queue[i].y == n.y) {found = 1; break;}
                        }
                        if (!found)
                            arrput(queue, n);
                    } else {
                        //printf("arg\n");
                    }
                }
            }
            if (current.y > 0){
                char c = lines[current.y-1].s[current.x];
                if (c <= current.c || c == current.c + 1){ 
                    if (!visited[((current.y-1) * width) + current.x]){
                        v2_t n = {current.x, current.y-1, c, current.level + 1, (current.y * width) + current.x};
                        int found = 0;
                        for (int i = 0; i < arrlen(queue); i++){
                            if (queue[i].x == n.x && queue[i].y == n.y) {found = 1; break;}
                        }
                        if (!found)
                            arrput(queue, n);
                    } else {
                        //printf("arg\n");
                    }
                }
            }
            if (current.y + 1 < height){
                char c = lines[current.y+1].s[current.x];
                if (c <= current.c || c == current.c + 1){ 
                    if (!visited[((current.y+1) * width) + current.x]){
                        v2_t n = {current.x, current.y+1, c, current.level + 1, (current.y * width) + current.x};
                        int found = 0;
                        for (int i = 0; i < arrlen(queue); i++){
                            if (queue[i].x == n.x && queue[i].y == n.y) {found = 1; break;}
                        }
                        if (!found)
                            arrput(queue, n);
                    } else {
                        //printf("arg\n");
                    }
                }
            }
        }
    }
    printf("Winner %d\n", winner);

    /*
    printf("Solution\n");
    int i = (end.y * width) + end.x;
    while(1){
        int x = i % width;
        int y = i / width;
        printf("%d %d\n", x, y);
        if (lines[y].s[x] == 'S') break;
        i = visited[i];
        i--;
    }
    */
    
}
