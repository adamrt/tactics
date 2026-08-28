#ifndef FFT_EVENT_H
#define FFT_EVENT_H

enum {
    /* WORLD compares the two 32-bit event operands and stores a boolean in
     * operand 0; these values are the script opcodes 0xA0 through 0xA5. */
    EVENT_CONDITION_SECOND_GTE_FIRST = 0xa0,
    EVENT_CONDITION_FIRST_GTE_SECOND = 0xa1,
    EVENT_CONDITION_EQUAL = 0xa2,
    EVENT_CONDITION_NOT_EQUAL = 0xa3,
    EVENT_CONDITION_FIRST_LT_SECOND = 0xa4,
    EVENT_CONDITION_SECOND_LT_FIRST = 0xa5,
};

#endif
