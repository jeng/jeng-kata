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
    char *filename;
    int size;
} file_t;

typedef struct dir_t {
    struct dir_t *parent;
    struct dir_t *directories;
    file_t *files;
    char *name;
} dir_t;

typedef enum {
    CMD_PROMPT,
    CMD_CD,
    CMD_LS,
    CMD_DIR,
    CMD_FILE,
} cmdstate_t;

int directoryExist(dir_t *working, char *dir){
    for(int i = 0; i < arrlen(working->directories); i++){
        if (strcmp(dir, working->directories[i].name) == 0){
            return 1;
        }
    }
    return 0;
}

int fileExist(dir_t *working, char *file){
    for(int i = 0; i < arrlen(working->files); i++){
        if (strcmp(file, working->files[i].filename) == 0){
            return 1;
        }
    }
    return 0;
}

dir_t *gotoDirectory(dir_t *working, char *s){
    printf("goto direction %s\n", s);
    if (strcmp(s, "..") == 0){
        return working->parent;
    }
    for(int i = 0; i < arrlen(working->directories); i++){
        if (strcmp(s, working->directories[i].name) == 0){
            return &(working->directories[i]);
        }
    }
    assert(0);
    return NULL;
 }

void storeFile(dir_t *working, int fileSize, char *s){
    printf("store file %s size %d\n", s, fileSize);
    if (fileExist(working, s))
        return;
    file_t file;// = malloc(sizeof(file_t));
    file.filename = malloc(sizeof(char) * strlen(s) + 1);
    strcpy(file.filename, s);
    file.size = fileSize;
    arrput(working->files, file);
}

void storeDirectory(dir_t *working, char *s){
    printf("store directory %s\n", s);
    if (directoryExist(working, s))
        return;
    dir_t dir;// = malloc(sizeof(dir_t));
    dir.name = malloc(sizeof(char) * strlen(s) + 1);
    strcpy(dir.name, s);
    dir.parent = working;
    dir.directories = NULL;
    dir.files = NULL;
    arrput(working->directories, dir);
}

int getDirSize(dir_t *working){
    if (working == NULL)
        return 0;

    int sum = 0;
    for(int i = 0; i < arrlen(working->files); i++){
        sum += working->files[i].size;
    }
    for(int i = 0; i < arrlen(working->directories); i++){
        sum += getDirSize(&(working->directories[i]));
    }
    return sum;
}

#define DIR_SZ_LIMIT (100000)

int printDirSizes(dir_t *working, int prefix, int *total){
    char s[1024];
    for (int i = 0; i < prefix; i++){
        s[i] = ' ';
    }
    s[prefix] = '\0';
    for(int i = 0; i < arrlen(working->files); i++){
        printf("%s%s %d\n", s, working->files[i].filename, working->files[i].size);
    }
    for(int i = 0; i < arrlen(working->directories); i++){
        int sz = getDirSize(&(working->directories[i]));
        if (sz <= DIR_SZ_LIMIT){
            *total += sz;
            printf("%s*%s %d\n", s, working->directories[i].name, sz);
        } else {
            printf("%s%s %d\n", s, working->directories[i].name, sz);
        }
        printDirSizes(&(working->directories[i]), prefix + 2, total);
    }
}


int main() {
    size_t size;
    char *data = stb_include_load_file("day7.test", &size);
    char store[1024];

    stb_lexer lex;

    stb_c_lexer_init(&lex, data, &data[size], store, 1024);

    cmdstate_t state;

    int currentFileSize;

    char *currentFile = malloc(sizeof(char) * 1024);
    char *currentDir = malloc(sizeof(char) * 1024);
    currentFile[0] = '\0';
    currentDir[0] = '\0';
    
    dir_t *root = malloc(sizeof(dir_t));
    root->directories = NULL;
    root->parent = NULL;
    root->files = NULL;

    dir_t *working = root;

    while(1){
        int res = stb_c_lexer_get_token(&lex);

        if (res == 0){
            break;
        }
        switch(lex.token){
            case '\n':
            case '\r': {
                if (state == CMD_FILE){
                    storeFile(working, currentFileSize, currentFile);
                    currentFile[0] = '\0';
                    state = CMD_LS;
                } else if (state == CMD_CD){
                    if (strcmp(currentDir, "/") == 0){
                        working = root;
                    } else {
                        working = gotoDirectory(working, currentDir);
                    }
                    currentDir[0] = '\0';
                    state = CMD_PROMPT;
                } else if (state == CMD_DIR){
                    storeDirectory(working, lex.string);
                    currentDir[0] = '\0';
                    state = CMD_LS;
                }
                break;
            }
            case CLEX_id: {
                if (strcmp("$", lex.string) == 0){
                    state = CMD_PROMPT;
                } else if (state == CMD_PROMPT && strcmp("cd", lex.string) == 0){
                    state = CMD_CD;
                } else if (state == CMD_PROMPT && strcmp("ls", lex.string) == 0){
                    state = CMD_LS;
                } else if (state == CMD_LS && strcmp("dir", lex.string) == 0){
                    state = CMD_DIR;
                } else {
                    if (state == CMD_DIR || state == CMD_CD){
                        strcat(currentDir, lex.string);
                    } else if (state == CMD_FILE) {
                        strcat(currentFile, lex.string);
                    }
                }
                break;
            }
            case CLEX_intlit: {
                if (state == CMD_LS){
                    currentFile[0] = '\0';
                    currentFileSize = lex.int_number;
                    state = CMD_FILE;
                }
                break;
            }
            default: {
                char s[2];
                s[0] = lex.token;
                s[1] = '\0';
                if (state == CMD_FILE){
                    strcat(currentFile, s);
                } else if (state == CMD_CD || state == CMD_DIR){
                    strcat(currentDir, s);
                }
            }
        }
    }
    int total = 0;
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("/ %d\n", getDirSize(root));
    printDirSizes(root, 2, &total);
    printf("total: %d\n", total);
    //if (contains(pair[0], pair[1])){
    //    sum++; 
    //    printf("sum %d p1 %d, %d p2 %d, %d\n", sum, pair[0].low, pair[0].high, pair[1].low, pair[1].high);
    //}

    //printf("sum %d\n", sum);
}
