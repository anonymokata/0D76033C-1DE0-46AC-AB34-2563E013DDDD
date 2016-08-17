#ifndef ROMAN_H
#define ROMAN_H

#include <stdlib.h>
#include <stdint.h>

#define MAX_ROMAN_LENGTH 32

typedef struct Roman Roman;

static const uint8_t VALID_NUMERAL = 1;
static const uint8_t  INVALID_NUMERAL = 0;

uint8_t is_valid_numeral(uint8_t*);

Roman* roman_create(void);
void roman_free(Roman*);

uint8_t roman_add(Roman* obj, uint8_t* op1, uint8_t* op2, uint8_t* result);


#endif /* ROMAN_H */
