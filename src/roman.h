#ifndef ROMAN_H
#define ROMAN_H

#include <stdlib.h>
#include <stdint.h>

#define MAX_ROMAN_LENGTH 32

typedef struct Roman Roman;

static const uint8_t VALID_NUMERAL = 1;
static const uint8_t  INVALID_NUMERAL = 0;

/*
is_valid_numeral:
This class method evalutates the given numeral and ensures it vaild
per the Roman Numeral Constraints defined in the requirements.

returns: 1 is valid, zero otherwise
*/
uint8_t is_valid_numeral(uint8_t*);

/* roman_create:
Create a new roman calculator instance.
*/
Roman* roman_create(void);

/* roman_free:
Destory an existing roman calculator instance.
*/
void roman_free(Roman*);

/* roman_add:
Using a provided instance, add Roman Numerals `op1` and `op2` to gether 
and copy it to the `result` string.

`op1 and `op` must be valid roman numerals
Size of `result` must be atleast MAX_ROMAN_LENGTH bytes.

returns: Resvered for future use
*/
void roman_add(Roman* obj, uint8_t* op1, uint8_t* op2, uint8_t* result);


#endif /* ROMAN_H */
