
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "roman.h"

typedef struct Roman_Numeral_Count Roman_Numeral_Count;

static const uint8_t INVALID_INPUT_ERROR[] = "Invalid Input";

/*
is_valid_numeral:
This class method evalutates the given numeral and ensures it vaild
per the Roman Numeral Constraints defined in the requirements.

returns: 1 is valid, zero otherwise
*/
uint8_t is_valid_numeral(uint8_t * numeral) {
    uint8_t i = 0;
    uint8_t duplicate_count = 1;
    uint8_t last_value = NULL;
    uint8_t ret = VALID_NUMERAL;

    while(i < strlen(numeral)) {
        // We need to keep track of how many times the values are duplicated
        if(last_value == numeral[i]) {
            duplicate_count++;
        } else {
            // No match - rest our counters
            last_value = numeral[i];
            duplicate_count = 1;
        }

        if((numeral[i] == 'I') || (numeral[i] == 'C') || (numeral[i] == 'X')) {
            // We can upto 3 of these values in a row
            if(duplicate_count > 3) {
                ret = INVALID_NUMERAL;
                break;
            }
            
        } else if((numeral[i] == 'V') || (numeral[i] == 'L') || (numeral[i] == 'D')) {
           // We can't have any duplicates at all
            if(duplicate_count > 1) {
                ret = INVALID_NUMERAL;
                break;
            }
        } else if(numeral[i] == 'M') {
            // Rather than to any math on this, we can just as easily check to see that
            // we dont have more than 3 "M"s in a row as a 4th would put us at 4000
            if(duplicate_count > 3) {
                ret = INVALID_NUMERAL;
                break;
            }
        } else {
            ret = INVALID_NUMERAL;
        }

        i++;
    }

    return ret;
}

struct Roman_Numeral_Count {
    uint8_t I;
    uint8_t V;
    uint8_t X;
    uint8_t L;
    uint8_t C;
    uint8_t D;
    uint8_t M;
};

struct Roman {
    Roman_Numeral_Count* rnc_op1;
    Roman_Numeral_Count* rnc_op2;
    Roman_Numeral_Count* rnc_result;
    uint8_t result[MAX_ROMAN_LENGTH];
};

Roman * roman_create(void){
    Roman* r = malloc(sizeof(Roman));

    if(r == NULL) {
        return NULL;
    }

    memset(r->result, '\0', MAX_ROMAN_LENGTH);
    
    return r;
};

void roman_free(Roman* r) {
    free(r);
    return;
}

uint8_t roman_add(Roman* obj, uint8_t* op1, uint8_t* op2, uint8_t* result) {
    strcpy(result, INVALID_INPUT_ERROR);
    return 1;
};



