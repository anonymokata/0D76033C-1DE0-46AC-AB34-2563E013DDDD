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

    while(i < strlen(numeral)){
        if((numeral[i] == 'I') || (numeral[i] == 'V') || (numeral[i] == 'X')) {
            // NoOp
        } else {
            ret = INVALID_NUMERAL;
        }

        i++;
    }

    return ret;
}
