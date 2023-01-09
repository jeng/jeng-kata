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

typedef struct v2_t {
    int x;
    int y;
} v2_t;

typedef struct row_t {
    v2_t *points;
} row_t;

typedef enum {
    GT_EMPTY = 0,
    GT_WALL,
    GT_SAND
} gridtype_t;

typedef struct grid_t {
    gridtype_t *grid;
    int width;
    int height;
    v2_t offset;
    v2_t minPoint;
    v2_t maxPoint;
} grid_t;

int inBounds(grid_t *grid, v2_t point){
    return (
        grid->minPoint.x <= point.x && point.x <= grid->maxPoint.x && 
        grid->minPoint.y <= point.y && point.y <= grid->maxPoint.y);
}

int isEmpty(grid_t *grid, v2_t point){
    if (inBounds(grid, point)){
        int x = point.x - grid->offset.x;
        int y = point.y - grid->offset.y;
        gridtype_t cell = grid->grid[y * grid->width + x];
        return (cell == GT_EMPTY);
    } else {
        return 0;
    }
}

void putPixel(grid_t *grid, v2_t point, gridtype_t gridtype){
    int x = point.x - grid->offset.x;
    int y = point.y - grid->offset.y;
    grid->grid[y * grid->width + x] = gridtype;
}

void drawWall(grid_t *grid, v2_t start, v2_t stop){
    if (start.x == stop.x){
        int y1 = min(start.y, stop.y);
        int y2 = max(start.y, stop.y);
        for(int y = y1; y <= y2; y++){
            v2_t v = {start.x, y};
            assert(inBounds(grid, v));
            putPixel(grid, v, GT_WALL);
        }
    } else {
        int x1 = min(start.x, stop.x);
        int x2 = max(start.x, stop.x);
        for(int x = x1; x <= x2; x++){
            v2_t v = {x, start.y};
            assert(inBounds(grid, v));
            putPixel(grid, v, GT_WALL);
        }
    }
}

void dump(grid_t *grid){
    for(int y = 0; y < grid->height; y++){
        for(int x = 0; x < grid->width; x++){
            switch(grid->grid[y * grid->width + x]){
                case GT_EMPTY: printf("."); break;
                case GT_SAND : printf("o"); break;
                case GT_WALL : printf("#"); break;
            }
        }
        printf("\n");
    }
}

int main() {
    size_t size;
    char *data = stb_include_load_file("day14.input", &size);
    stb_lexer lex;
    char store[1024];
    stb_c_lexer_init(&lex, data, &data[size], store, 1024);
    row_t row;
    row.points = NULL;
    row_t *rows = NULL;
    v2_t p;
    int getx = 1;

    while(1){
        int res = stb_c_lexer_get_token(&lex);

        if (res == 0){
            break;
        }

        switch(lex.token){
            case '\n':{
                getx = 1;
                arrput(row.points, p);
                arrput(rows, row);
                row.points = NULL;
                break;
            }
            case ',': {
                getx = 0;
                break;
            }
            case CLEX_arrow:{
                getx = 1;
                arrput(row.points, p);
                break;
            }
            case CLEX_intlit: {
                if (getx){
                    p.x = lex.int_number;
                } else {
                    p.y = lex.int_number;
                }
                break;
            }
        }
    }
    
    //First pass get the min and max so we know howmany pigeon wholes we need
    v2_t minP;
    v2_t maxP;
    minP.x = INT_MAX;
    minP.y = INT_MAX;
    maxP.x = INT_MIN;
    maxP.y = INT_MIN;
    for(int i = 0; i < arrlen(rows); i++){
        //printf("Row i\n");
        for (int j = 0; j < arrlen(rows[i].points); j++){
            minP.x = min(minP.x, rows[i].points[j].x);
            minP.y = min(minP.y, rows[i].points[j].y);
            maxP.x = max(maxP.x, rows[i].points[j].x);
            maxP.y = max(maxP.y, rows[i].points[j].y);
            //printf("\t%d %d\n", rows[i].points[j].x, rows[i].points[j].y);
        }
    }
    //printf("min (%d, %d) max (%d, %d)\n", minP.x, minP.y, maxP.x, maxP.y);
    int dx = maxP.x - minP.x;
    int dy = maxP.y;
    //printf("dx (%d) dy (%d)\n", dx, dy);

    //TODO this one needs to be cleaned up
    for (int k = 300; k < 500; k++){
        int widthAllowance = k; 
        grid_t grid;
        grid.maxPoint = (v2_t){maxP.x + widthAllowance, maxP.y+2};
        grid.minPoint = (v2_t){minP.x- (widthAllowance/2), 0};
        grid.offset.x = minP.x-(widthAllowance/2); 
        grid.offset.y = 0;
        grid.width = dx + (widthAllowance + 1);
        grid.height = dy + 2;
        grid.grid = calloc(grid.width * grid.height, sizeof(gridtype_t));

        //Draw the original play field
        for(int i = 0; i < arrlen(rows); i++){
            for (int j = 0; j < arrlen(rows[i].points)-1; j++){
                drawWall(&grid, rows[i].points[j], rows[i].points[j+1]);
            }
        }
        //dump(&grid);
    
        //Play the sand particles one at a time
        v2_t start = {500, 0};
        v2_t current = start;
        int total = 0;
        //int first = 1;
        while(1 /*|| inBounds(&grid, current)*/){
            //first = 0;
            if (isEmpty(&grid, (v2_t){current.x, current.y+1})){
                if (inBounds(&grid, current))
                    putPixel(&grid, current, GT_EMPTY);            
                current.y++;
                putPixel(&grid, current, GT_SAND);            
            } else if (isEmpty(&grid, (v2_t){current.x-1, current.y+1})){
                if (inBounds(&grid, current))
                    putPixel(&grid, current, GT_EMPTY);            
                current.x--;
                current.y++;
                putPixel(&grid, current, GT_SAND);            
            } else if (isEmpty(&grid, (v2_t){current.x+1, current.y+1})){
                if (inBounds(&grid, current))
                    putPixel(&grid, current, GT_EMPTY);            
                current.x++;
                current.y++;
                putPixel(&grid, current, GT_SAND);            
            } else {
                if (current.x == start.x && current.y == start.y)
                    break;
                //first = 1;
                current = start;
                total++;
                //if (inBounds(&grid, (v2_t){current.x, current.y+1}) || 
                //    inBounds(&grid, (v2_t){current.x-1, current.y+1}) || 
                //    inBounds(&grid, (v2_t){current.x+1, current.y+1})){
                //        first = 1;
                //        current = start;
                //        total++;
                //    }
                //    else{
                //        break;
                //    }
            }
            //dump(&grid);
        }
        printf("total %d\n", total + 1);

        total = 0;
        for(int i = 0; i < grid.width * grid.height; i++){
            if (grid.grid[i] == GT_SAND){
                total++;
            } 
        }
        printf("(c) total %d\n", total + 1);
    }
    //dump(&grid);
}
