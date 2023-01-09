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

int inRange(sensor_meta_t sensor, v2_t check){
    if (sensor.position.x == check.x && sensor.position.y == check.y)
        return 0;

    if (sensor.beacon.x == check.x && sensor.beacon.y == check.y)
        return 0;

    int success = 0;
    int xOffset = getXOffset(sensor, check, &success);
    if (success){
        return ((sensor.position.x - xOffset) <= check.x && check.x <= (sensor.position.x + xOffset));
    }
    return 0;
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
    int maxX = 0;
    int minX = INT32_MAX;

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

                maxX = max(currentSensor.beacon.x, maxX);
                maxX = max(currentSensor.position.x + currentSensor.radius, maxX);

                minX = min(currentSensor.beacon.x, minX);
                minX = min(currentSensor.position.x - currentSensor.radius, minX);                

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

    //int checkRow = 10;
    int checkRow = 2000000;
    int result = 0;
    for(int x = minX; x < maxX; x++){
        int hit = 0;
        for(int i = 0; i < arrlen(sensors); i++){
            hit |= inRange(sensors[i], (v2_t){x, checkRow});
        }
        if (hit){
            result++;
            //printf("# %d %d\n", x, checkRow);
        } else {
            //printf(". %d %d\n", x, checkRow);
        }
    }
    printf("\n");
    printf("Min %d max %d Result %d\n", minX, maxX, result);
}
