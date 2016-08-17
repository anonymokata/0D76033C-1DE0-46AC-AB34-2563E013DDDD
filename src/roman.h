#ifndef ROMAN_H
#define ROMAN_H

#include <stdlib.h>
#include <stdint.h>

static const uint8_t VALID_NUMERAL = 1;
static const uint8_t  INVALID_NUMERAL = 0;

uint8_t is_valid_numeral(uint8_t*);

#endif /* ROMAN_H */
