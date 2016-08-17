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
            
        } else if((numeral[i] == 'V') || 
           (numeral[i] == 'L') || 
           (numeral[i] == 'D') || 
           (numeral[i] == 'M')) {
           // No Op
        } else {
            ret = INVALID_NUMERAL;
        }

        i++;
    }

    return ret;
}
