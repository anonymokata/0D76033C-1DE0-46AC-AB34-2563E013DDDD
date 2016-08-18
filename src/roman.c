
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "roman.h"

typedef struct Roman_Numeral_Count Roman_Numeral_Count;
static const uint8_t INVALID_INPUT_ERROR[] = "Invalid Input";
static const uint8_t RESULT_OUT_OF_RANGE_ERROR[] = "Out of Range";
static const uint8_t MAX_I_VALUES = 5;
static const uint8_t MAX_V_VALUES = 2;
static const uint8_t MAX_X_VALUES = 5;
static const uint8_t MAX_L_VALUES = 2;
static const uint8_t MAX_C_VALUES = 5;
static const uint8_t MAX_D_VALUES = 2;

// Private / helper prototypes
static void expand_compressed_numerals(uint8_t* src, uint8_t* dst);
static void extract_numeral_counts(uint8_t* numeral, Roman_Numeral_Count* rnc);
static void sum_roman_numeral_counts(Roman_Numeral_Count* rnc1, Roman_Numeral_Count* rnc2, Roman_Numeral_Count* result); 
static void build_roman_numeral_str_from_counts(Roman_Numeral_Count* counts, uint8_t* result_str);
static uint8_t borrow_roman_numeral_counts(uint8_t borrower, Roman_Numeral_Count* rnc);
static uint8_t subtract_roman_numeral_counts(Roman_Numeral_Count* rnc1, Roman_Numeral_Count* rnc2, Roman_Numeral_Count* result);
static void compress_additive_roman_numeral_counts(Roman_Numeral_Count* rnc);

uint8_t is_valid_numeral(uint8_t * numeral) {
    /*
    Note: The following TODO's are based on a previous knowledge about roman numerals. 
          They were not added as the requirements did not indicate to limit these values.
          More information is needed from the customer to determine if we should block these values.
    TODO: Consider protecting against invalid subtractives (valid: IV, IX, XL, XC, CD, CM)
    TODO: Consider protecting against invalid subtractive combinations (CMCD, XCXL, IXIV)
    */
    uint8_t i = 0;
    uint8_t duplicate_count = 1;
    uint8_t last_value = NULL;
    uint8_t ret = VALID_NUMERAL;

    if(strlen(numeral) >= MAX_VALID_ROMAN_LENGTH) {
        return INVALID_NUMERAL;
    }

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
    Roman_Numeral_Count rnc_op1;
    Roman_Numeral_Count rnc_op2;
    Roman_Numeral_Count rnc_result;
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

void roman_add(Roman* obj, uint8_t* op1, uint8_t* op2, uint8_t* result) {
    uint8_t scratch[MAX_VALID_ROMAN_EXPANDED_LENGTH];
    uint8_t scratch_int;

    // We first need to check the operands to ensure they're formatted correctly
    if(INVALID_NUMERAL == is_valid_numeral(op1)){
        strcpy(result, INVALID_INPUT_ERROR);
        return;
    }

    if(INVALID_NUMERAL == is_valid_numeral(op2)){
        strcpy(result, INVALID_INPUT_ERROR);
        return;
    }

    // We need to:
    // 1.  expand the compressed values (4 and 9 multiples)
    // 2.  Count the number of occurances in each numeral
    memset(scratch, '\0', MAX_VALID_ROMAN_EXPANDED_LENGTH);    
    expand_compressed_numerals(op1, scratch);
    extract_numeral_counts(scratch, &obj->rnc_op1);

    memset(scratch, '\0', MAX_VALID_ROMAN_EXPANDED_LENGTH);    
    expand_compressed_numerals(op2, scratch);
    extract_numeral_counts(scratch, &obj->rnc_op2);

    // Sum up the values
    sum_roman_numeral_counts(&obj->rnc_op1, &obj->rnc_op2, &obj->rnc_result);

    // Compress additive logic (IIIII == V) using 'values' of the roman numerals
    compress_additive_roman_numeral_counts(&obj->rnc_result);

    // Ok - knowing that everything has been expanded we can safely use 
    // the total number of "M"s to see if we're over 3999
    if(obj->rnc_result.M >= 4){
        strcpy(result, RESULT_OUT_OF_RANGE_ERROR);
        return;
    }

    // Rebuild the roman numeral output string
    build_roman_numeral_str_from_counts(&obj->rnc_result, result);

    return;
};

void roman_subtract(Roman* obj, uint8_t* op1, uint8_t* op2, uint8_t* result) {
    uint8_t scratch[MAX_VALID_ROMAN_EXPANDED_LENGTH];
    uint8_t scratch_int;

    // We first need to check the operands to ensure they're formatted correctly
    if(INVALID_NUMERAL == is_valid_numeral(op1)){
        strcpy(result, INVALID_INPUT_ERROR);
        return;
    }

    if(INVALID_NUMERAL == is_valid_numeral(op2)){
        strcpy(result, INVALID_INPUT_ERROR);
        return;
    }

    // We need to:
    // 1.  expand the compressed values (4 and 9 multiples)
    // 2.  Count the number of occurances in each numeral
    memset(scratch, '\0', MAX_VALID_ROMAN_EXPANDED_LENGTH);    
    expand_compressed_numerals(op1, scratch);
    extract_numeral_counts(scratch, &obj->rnc_op1);

    memset(scratch, '\0', MAX_VALID_ROMAN_EXPANDED_LENGTH);    
    expand_compressed_numerals(op2, scratch);
    extract_numeral_counts(scratch, &obj->rnc_op2);

    // Subtact up the values 
    if(!subtract_roman_numeral_counts(&obj->rnc_op1, &obj->rnc_op2, &obj->rnc_result)){
        // Looks like they were asking more than we could give
        strcpy(result, "");
        return;
    }

    // Compress additive logic (IIIII == V) using 'values' of the roman numerals
    compress_additive_roman_numeral_counts(&obj->rnc_result);

    // Rebuild the roman numeral output string
    build_roman_numeral_str_from_counts(&obj->rnc_result, result);

    return;
};


void expand_compressed_numerals(uint8_t* src, uint8_t* dst){
    // We can assume the src will be valid as it's should checked prior to this call
    // convert the legal compressed values (IV, IX, XL, etc...) to an expanded form
    // (IIII, VIIII, XXXX, etc...)
    uint8_t total = 0;
    uint8_t i = 0;

    while(i<strlen(src)) {
        if((src[i] == 'I') && src[i+1] == 'V') {
            dst[total++] = 'I';
            dst[total++] = 'I';
            dst[total++] = 'I';
            dst[total++] = 'I';
            i+=2;
        } else if((src[i] == 'I') && src[i+1] == 'X') {
            dst[total++] = 'V';
            dst[total++] = 'I';
            dst[total++] = 'I';
            dst[total++] = 'I';
            dst[total++] = 'I';
            i+=2;
        } else if((src[i] == 'X') && src[i+1] == 'L') {
            dst[total++] = 'X';
            dst[total++] = 'X';
            dst[total++] = 'X';
            dst[total++] = 'X';
            i+=2;
        } else if((src[i] == 'X') && src[i+1] == 'C') {
            dst[total++] = 'L';
            dst[total++] = 'X';
            dst[total++] = 'X';
            dst[total++] = 'X';
            dst[total++] = 'X';
            i+=2;
        } else if((src[i] == 'C') && src[i+1] == 'D') {
            dst[total++] = 'C';
            dst[total++] = 'C';
            dst[total++] = 'C';
            dst[total++] = 'C';
            i+=2;
        } else if((src[i] == 'C') && src[i+1] == 'M') {
            dst[total++] = 'D';
            dst[total++] = 'C';
            dst[total++] = 'C';
            dst[total++] = 'C';
            dst[total++] = 'C';
            i+=2;
        } else {
            // Just add it to the output & advance
            dst[total++] = src[i++];
        }
    }
    // Ensure it's null terminated
    dst[total++] = '\0';
    return;
}

void extract_numeral_counts(uint8_t* numeral, Roman_Numeral_Count* counts) {
    uint8_t i = 0;

    // Clear out all of the counts
    counts->I = 0;
    counts->V = 0;
    counts->X = 0;
    counts->L = 0;
    counts->C = 0;
    counts->D = 0;
    counts->M = 0;

    while(i<strlen(numeral)) {
        if(numeral[i] == 'I')
            counts->I++;
        else if(numeral[i] == 'V')
            counts->V++;
        else if(numeral[i] == 'X')
            counts->X++;
        else if(numeral[i] == 'L')
            counts->L++;
        else if(numeral[i] == 'C')
            counts->C++;
        else if(numeral[i] == 'D')
            counts->D++;
        else if(numeral[i] == 'M')
            counts->M++;
        i++;
    }

    return;
}

void sum_roman_numeral_counts(Roman_Numeral_Count* rnc1, Roman_Numeral_Count* rnc2, Roman_Numeral_Count* result) {
    result->I = rnc1->I + rnc2->I;
    result->V = rnc1->V + rnc2->V;
    result->X = rnc1->X + rnc2->X;
    result->L = rnc1->L + rnc2->L;
    result->C = rnc1->C + rnc2->C;
    result->D = rnc1->D + rnc2->D;
    result->M = rnc1->M + rnc2->M;
}

uint8_t borrow_roman_numeral_counts(uint8_t borrower, Roman_Numeral_Count* rnc) {
    // Recursive function used to keep borrowing from the next value
    uint8_t neighbor_has_goods = 1;

    if(borrower == 'I') {
        if(!rnc->V)
            neighbor_has_goods = borrow_roman_numeral_counts('V', rnc);

        if(neighbor_has_goods) {
            rnc->I += MAX_I_VALUES;
            rnc->V -= 1;
        }
        return neighbor_has_goods;

    } else if(borrower == 'V') {
        if(!rnc->X)
            neighbor_has_goods = borrow_roman_numeral_counts('X', rnc);

        if(neighbor_has_goods) {
            rnc->V += MAX_V_VALUES;
            rnc->X -= 1;
        }
        return neighbor_has_goods;
        
    } else if(borrower == 'X') {
        if(!rnc->L)
            neighbor_has_goods = borrow_roman_numeral_counts('L', rnc);

        if(neighbor_has_goods) {
            rnc->X += MAX_X_VALUES;
            rnc->L -= 1;
        }
        return neighbor_has_goods;
        
    } else if(borrower == 'L') {
        if(!rnc->C)
            neighbor_has_goods = borrow_roman_numeral_counts('C', rnc);

        if(neighbor_has_goods) {
            rnc->L += MAX_L_VALUES;
            rnc->C -= 1;
        }
        return neighbor_has_goods;
        
    } else if(borrower == 'C') {
        if(!rnc->D)
            neighbor_has_goods = borrow_roman_numeral_counts('D', rnc);

        if(neighbor_has_goods) {
            rnc->C += MAX_C_VALUES;
            rnc->D -= 1;
        }
        return neighbor_has_goods;

    }  else if(borrower == 'D') {
        if(!rnc->M)
            neighbor_has_goods = 0;

        if(neighbor_has_goods) {
            rnc->D += MAX_D_VALUES;
            rnc->M -= 1;
        }
        return neighbor_has_goods; 
    }
}

uint8_t subtract_roman_numeral_counts(Roman_Numeral_Count* rnc1, Roman_Numeral_Count* rnc2, Roman_Numeral_Count* result) {
    // Subract the values, borrowing from the next highest value as needed
    if(rnc2->I > rnc1->I) {
        if(!borrow_roman_numeral_counts('I', rnc1)) {
            return 0; 
        }
    }
    result->I = rnc1->I - rnc2->I;

    if(rnc2->V > rnc1->V) {
        if(!borrow_roman_numeral_counts('V', rnc1)) {
            return 0; 
        }
    }
    result->V = rnc1->V - rnc2->V;

    if(rnc2->X > rnc1->X) {
        if(!borrow_roman_numeral_counts('X', rnc1)) {
            return 0; 
        }
    }
    result->X = rnc1->X - rnc2->X;

    if(rnc2->L > rnc1->L) {
        if(!borrow_roman_numeral_counts('L', rnc1)) {
            return 0; 
        }
    }
    result->L = rnc1->L - rnc2->L;

    if(rnc2->C > rnc1->C) {
        if(!borrow_roman_numeral_counts('C', rnc1)) {
            return 0; 
        }
    }
    result->C = rnc1->C - rnc2->C;

    if(rnc2->D > rnc1->D) {
        if(!borrow_roman_numeral_counts('D', rnc1)) {
            return 0; 
        }
    }
    result->D = rnc1->D - rnc2->D;

    if(rnc2->M > rnc1->M) {
        // No one else to borrow from...  
        return 0;
    }
    result->M = rnc1->M - rnc2->M;
    return 1;
}

void build_roman_numeral_str_from_counts(Roman_Numeral_Count* counts, uint8_t* result_str) {
    uint8_t i;
    uint8_t total = 0;

    // Build the string in order of highest values
    for(i=0; i<counts->M; i++){
        result_str[total++] = 'M';
    }

    if(counts->C == 4){
        if(counts->D) {
            // DCCCC -> CM
            result_str[total++] = 'C';
            result_str[total++] = 'M';
        } else { 
            // CCCC -> CD
            result_str[total++] = 'C';
            result_str[total++] = 'D';
        }
    } else {
        for(i=0; i<counts->D; i++){
            result_str[total++] = 'D';
        }
        for(i=0; i<counts->C; i++){
            result_str[total++] = 'C';
        }
    }
        
    if(counts->X == 4) {
        if(counts->L) {
            // LXXXX -> XC
            result_str[total++] = 'X';
            result_str[total++] = 'C';
        } else { 
            // XXXX -> XL
            result_str[total++] = 'X';
            result_str[total++] = 'L';
        }
    } else {
        for(i=0; i<counts->L; i++){
            result_str[total++] = 'L';
        }
        for(i=0; i<counts->X; i++){
            result_str[total++] = 'X';
        }
    }
    
    if(counts->I == 4) {
        // Ok so there is a more compact way to write this... 
        if(counts->V) {
            // VIIII -> IX
            result_str[total++] = 'I';
            result_str[total++] = 'X';
        } else { 
            // IIII -> IV
            result_str[total++] = 'I';
            result_str[total++] = 'V';
        }
    } else {
        // No compaction is needed
        for(i=0; i<counts->V; i++){
            result_str[total++] = 'V';
        }

        for(i=0; i<counts->I; i++){
            result_str[total++] = 'I';
        }
    }

    result_str[total++] = '\0';

    return;
}

void compress_additive_roman_numeral_counts(Roman_Numeral_Count* rnc) {
    // Compress additive logic (IIIII == V) using 'values' of the roman numerals
    rnc->V += (rnc->I / MAX_I_VALUES);
    rnc->I = rnc->I % MAX_I_VALUES;

    rnc->X += (rnc->V / MAX_V_VALUES);
    rnc->V = rnc->V % MAX_V_VALUES;

    rnc->L += (rnc->X / MAX_X_VALUES);
    rnc->X = rnc->X % MAX_X_VALUES;

    rnc->C += (rnc->L / MAX_L_VALUES);
    rnc->L = rnc->L % MAX_L_VALUES;

    rnc->D += (rnc->C / MAX_C_VALUES);
    rnc->C = rnc->C % MAX_C_VALUES;

    rnc->M += (rnc->D / MAX_D_VALUES);
    rnc->D = rnc->D % MAX_D_VALUES;

    // M is allowed to grow
    return;
}
