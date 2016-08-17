#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "roman.h"

/*
is_valid_numeral:
This method evalutates the given numeral and ensures it vaild
per the Roman Numeral Constraints defined in the requirements.

returns: 1 is valid, zero otherwise
*/
uint8_t is_valid_numeral(uint8_t * numeral) {
    uint8_t i = 0;
    uint8_t ret = VALID_NUMERAL;

    printf("strlen %d\n", strlen(numeral));

    while(i < strlen(numeral)){
        printf("\tNumeral[i] %c\n", numeral[i]);
        if(numeral[i] == (uint8_t)('I')) {
            // NoOp
        } else {
            ret = INVALID_NUMERAL;
        }

        i++;
    }

    return ret;
}
