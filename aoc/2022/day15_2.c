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

typedef struct sensor_meta_t {
    v2_t position;
    v2_t beacon;
    int radius;
} sensor_meta_t;

int globalY = 0;

int getXOffset(sensor_meta_t sensor, v2_t check, int *success){
    int checkDy = abs(sensor.position.y - check.y);
    if (checkDy > sensor.radius){
        *success = 0;
        return 0;
    }
    *success = 1;

    int xOffset = sensor.radius - checkDy;
    return xOffset;
}

int sortSensor(sensor_meta_t a, sensor_meta_t b){
    v2_t pos = (v2_t){0, globalY};
    int success1 = 0;
    int success2 = 0;
    int offset1 = getXOffset(a, pos, &success1);
    int offset2 = getXOffset(b, pos, &success2);
    if (success1 && success2){
        int dx1 = a.position.x - offset1;
        int dx2 = b.position.x - offset2;
        if (dx1 == dx2){
            return 0;
        } else if (dx1 < dx2){
            return -1;
        } else {
            return 1;
        }
    } else if (success1 && !success2){
        return -1;
    } else if (!success1 && success2){
        return 1;
    } else {
        return 0;
    }
}

int main() {
    size_t size;
    char *data = stb_include_load_file("day15.input", &size);
    stb_lexer lex;
    char store[1024];
    stb_c_lexer_init(&lex, data, &data[size], store, 1024);
    sensor_meta_t *sensors = NULL;
    sensor_meta_t currentSensor;
    int inputNum = 0;

    while(1){
        int res = stb_c_lexer_get_token(&lex);

        if (res == 0){
            break;
        }

        switch(lex.token){
            case '\n':{
                inputNum = 0;

                int dx = abs(currentSensor.position.x - currentSensor.beacon.x);
                int dy = abs(currentSensor.position.y - currentSensor.beacon.y);
                currentSensor.radius = dx + dy;
                arrput(sensors, currentSensor);
                break;
            }
            case '=':{
                inputNum++; break;
            }
            case CLEX_intlit: {
                switch(inputNum){
                    case 1: currentSensor.position.x = lex.int_number; break;
                    case 2: currentSensor.position.y = lex.int_number; break;
                    case 3: currentSensor.beacon.x   = lex.int_number; break;
                    case 4: currentSensor.beacon.y   = lex.int_number; break;
                    default:
                        assert(0);
                        break;
                }
            }
        }
    }

    int minx = 0;
    int miny = 0;
    int maxx = 4000000;
    int maxy = 4000000;
    //int maxx = 20;
    //int maxy = 20;
    int checkRow = 2000000;
    int result = 0;
    
    for(int y = miny; y <= maxy; y++){
        if (y % 1000 == 0)
            printf("checking row %d\n", y);
        globalY = y;
        qsort(sensors, arrlen(sensors), sizeof(sensor_meta_t), sortSensor);
        int x = 0;
        while(x < maxx){
            int hit = 0;
            for(int i = 0; i < arrlen(sensors); i++){
                int success = 0;
                int offset = getXOffset(sensors[i], (v2_t){0, y}, &success);
                if (success){
                    int right = (sensors[i].position.x + offset);
                    int left  = (sensors[i].position.x - offset);
                    if (left <= x && x <= right){
                        x = (sensors[i].position.x + offset) + 1;
                    }
                    if (x < left){
                        printf("found it %d %d\n", x, y);
                        exit(0);
                    }
               }
            }
        }
    }
}
