#ifndef TEXT_H
#define TEXT_H

/* Encoded menu-string controls (FFHacktics page 00007047). */
typedef enum text_control {
    TEXT_EXTENDED_GLYPH_PREFIX_FIRST = 0xd0,
    TEXT_EXTENDED_GLYPH_PREFIX_LAST = 0xdf,
    TEXT_NEWLINE = 0xf8,
    TEXT_END_WAIT_FOR_CONFIRM = 0xfe,
    TEXT_END_AUTO_CLOSE = 0xff,
} text_control_t;

#endif
