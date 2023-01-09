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

int main() {
    size_t size;
    char *data = stb_include_load_file("day8.input", &size);
    string_t *lines = slurp(&data);
    int width = lines[0].length;
    int height = arrlen(lines);
    history_t *hm = calloc(height * width, sizeof(history_t));
    //Build history
    for(int y = 0; y < arrlen(lines); y++){
        for(int x = 0; x < lines[0].length; x++){

            int i = (width * y) + x;
            int xx = (width  - 1) - x;
            int yy = (height - 1) - y;
            int j = (width * yy) + xx;

            if (x == 0){
                hm[i].left = lines[y].s[x] - '0';
            } else {
                int k = (width * y) + (x-1);
                hm[i].left = max(hm[k].left, lines[y].s[x] - '0');
            }

            if (y == 0){
                hm[i].up = lines[y].s[x] - '0';
            } else {
                int k = (width * (y-1)) + x;
                hm[i].up = max(hm[k].up, lines[y].s[x] - '0');
            }

            if (xx == (width-1)){
                hm[j].right = lines[yy].s[xx] - '0';
            } else {
                int k = (width * yy) + (xx + 1);
                hm[j].right = max(hm[k].right, lines[yy].s[xx] - '0');
 
            }

            if (yy == (height-1)){
                hm[j].down = lines[yy].s[xx] - '0';
            } else {
                int k = (width * (yy + 1)) + xx;
                hm[j].down = max(hm[k].down, lines[yy].s[xx] - '0');
            }

        }
    }

    //dump the table
    for(int y = 0; y < height; y++){
        printf("| ");
        for(int x = 0; x < width; x++){
            int i = (width * y) + x;
            printf("%d %d %d %d | ", hm[i].left, hm[i].right, hm[i].up, hm[i].down);
        }
        printf("\n");
    }


    int visible = lines[0].length *2;
    //Remove the top bottom row.  Count test start and end column
    visible = (visible - 2) * 2;
    //What is visible on the interior
    for(int y = 1; y < arrlen(lines)-1; y++){
        for(int x = 1; x < lines[0].length - 1; x++){

            int il = (width * y)     + (x - 1);
            int ir = (width * y)     + (x + 1);
            int iu = (width * (y-1)) + x;
            int id = (width * (y+1)) + x;
            int n = lines[y].s[x] - '0';
            if (n > hm[il].left || n > hm[ir].right || n > hm[iu].up || n > hm[id].down){
                printf("(%d, %d) %d\n", x, y, n);
                visible++;
            }
        }
    }        

    for(int i = 0; i < arrlen(lines); i++)
        printf("(%d) %.*s\n", lines[i].length, lines[i].length, lines[i].s);

    printf("Visible: %d\n", visible);
}
