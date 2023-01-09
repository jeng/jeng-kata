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

typedef enum {
    NT_DEAD,
    NT_INT,
    NT_LIST
} nodetype_t;

typedef struct node_t {
    nodetype_t type;
    int x;
    struct node_t *list;
} node_t;

typedef enum parse_state_t{
    PST_LINE1,
    PST_LINE2,
    PST_NEXT
} parse_state_t;

void dump(node_t n){
    if(n.type == NT_INT){
        printf("%d ", n.x);
    } else {
        printf("(");
        for(int i = 0; i < arrlen(n.list); i++){
            dump(n.list[i]);
        }
        printf(")");
    }
}

typedef enum compare_state_t {
    CS_SUCCESS,
    CS_CONTINUE,
    CS_FAIL
} compare_state_t;

int compare(node_t l1, node_t l2){
    if (l1.type == NT_INT && l2.type == NT_INT && l1.x < l2.x){
        return CS_SUCCESS;
    } else if(l1.type == NT_INT && l2.type == NT_INT && l1.x > l2.x){ 
        return CS_FAIL;
    } else if (l1.type == NT_INT && l2.type == NT_INT && l1.x == l2.x){
        return CS_CONTINUE;
    }
    if (l1.type == NT_LIST && l2.type == NT_LIST){
        for (int i = 0; i < arrlen(l1.list); i++){
            if (i >= arrlen(l2.list)){
                return CS_FAIL;                
            }
            int state = compare(l1.list[i], l2.list[i]);
            if (state == CS_SUCCESS || state == CS_FAIL)
                return state;
        }
        if (arrlen(l2.list) == arrlen(l1.list))
            return CS_CONTINUE;
        else
            return CS_SUCCESS;
    }
    if (l1.type == NT_LIST && l2.type == NT_INT){
        node_t n;
        n.type = NT_LIST;
        n.list = NULL;
        arrput(n.list, l2);        
        int state = compare(l1, n);
        if (state == CS_SUCCESS || state == CS_FAIL)
            return state;
     }
    if (l1.type == NT_INT && l2.type == NT_LIST){
        node_t n;
        n.type = NT_LIST;
        n.list = NULL;
        arrput(n.list, l1);        
        int state = compare(n, l2);
        if (state == CS_SUCCESS || state == CS_FAIL)
            return state;
     }
}

int qsortCompare(node_t *ln1, node_t *ln2){
    int state = compare(*ln1, *ln2);
    if (state == CS_SUCCESS)
        return -1;
    else if (state == CS_CONTINUE)
        return 0;
    else
        return 1;
}

node_t makeDivider(int n){
    node_t result;
    node_t innerList;
    node_t val;
    val.type = NT_INT;
    val.x = n;
    innerList.type = NT_LIST;
    innerList.list = NULL;
    arrput(innerList.list, val);
    result.type = NT_LIST;
    result.list = NULL;
    arrput(result.list, innerList);
    return result;
}

int main() {
    size_t size;
    char *data = stb_include_load_file("day13_with_divider.input", &size);
    stb_lexer lex;
    char store[1024];
    stb_c_lexer_init(&lex, data, &data[size], store, 1024);
    node_t ln1;
    node_t ln2;
    node_t current;
    current.type = NT_DEAD;
    current.x = 0;
    current.list = NULL;
    node_t *stack = NULL;
    node_t *allPackets = NULL;
    parse_state_t state = PST_LINE1;
    node_t d1 = makeDivider(2);
    node_t d2 = makeDivider(6);

    while(1){
        int res = stb_c_lexer_get_token(&lex);

        if (res == 0){
            break;
        }

        switch(lex.token){
            case '\n':{
                if (state == PST_LINE1){
                    ln1 = current;
                    state = PST_LINE2;
                } else if (state == PST_LINE2){
                    ln2 = current;
                    state = PST_NEXT;
                    arrput(allPackets, ln1);
                    arrput(allPackets, ln2);
                } else if (state == PST_NEXT){
                    //printf("\n");
                    state = PST_LINE1;
                }


                current.type = NT_DEAD;
                current.list = NULL;
            
                assert(arrlen(stack) == 0);
                break;
            }
            case '[': {
                node_t n;
                n.type = NT_LIST;
                n.list = NULL;
                n.x = 0;
                if (current.type != NT_DEAD){
                    arrput(stack, current);
                }
                current = n;
                break;
            }
            case ']': {
                if (arrlen(stack) > 0){
                    node_t n = arrpop(stack);
                    arrput(n.list, current);
                    current = n;
                }
                break;
            }
            case CLEX_intlit: {
                node_t n;
                n.type = NT_INT;
                n.list = NULL;
                n.x = lex.int_number;
                arrput(current.list, n);
            }
        }
    }
    qsort(allPackets, arrlen(allPackets), sizeof(node_t), qsortCompare);
    int result = 1;
    for(int i = 0; i < arrlen(allPackets); i++){
        dump(allPackets[i]);
        if (compare(allPackets[i], d1) == CS_CONTINUE){
            printf("Packet 1 at %d", i + 1);
            result *= (i + 1);
        } else if (compare(allPackets[i], d2) == CS_CONTINUE){
            printf("Packet 2 at %d", i + 1);
            result *= (i + 1);
        }
        printf("\n");
    }
    printf("result %d\n", result); 
}
