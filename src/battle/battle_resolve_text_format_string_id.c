#include "psx/types.h"

enum BattleTextFormatCode {
    BATTLE_TEXT_FORMAT_RAMZA_NAME = 0xe0,
    BATTLE_TEXT_FORMAT_UNIT_NAME = 0xe1,
    BATTLE_TEXT_FORMAT_SECTION_9000 = 0xe5,
    BATTLE_TEXT_FORMAT_ITEM_NAME = 0xe9,
    BATTLE_TEXT_FORMAT_ABILITY_NAME = 0xea,
    BATTLE_TEXT_FORMAT_EXPLICIT_ID = 0xeb,
};

/* Convert a text-format substitution opcode into its string-table ID. */
s32 battle_resolve_text_format_string_id(s32 format_code, s32 value) {
    s32 string_id;
    /* Pin: unpinned, the 0xeb constant is not hoisted into $v1 and the
     * final compare loses its filled delay slot (112 bytes vs 108). */
    register s32 explicit_id_code __asm__("$3");

    if (format_code == BATTLE_TEXT_FORMAT_RAMZA_NAME) {
        return 0x4000;
    }
    if (format_code == BATTLE_TEXT_FORMAT_UNIT_NAME) {
        return value + 0x4000;
    }
    if (format_code == BATTLE_TEXT_FORMAT_SECTION_9000) {
        return value + 0x9000;
    }
    if (format_code == BATTLE_TEXT_FORMAT_ITEM_NAME) {
        return value + 0x3800;
    }
    if (format_code == BATTLE_TEXT_FORMAT_ABILITY_NAME) {
        return value + 0x7000;
    }
    explicit_id_code = BATTLE_TEXT_FORMAT_EXPLICIT_ID;
    string_id = value;
    if (format_code != explicit_id_code) {
        string_id = -1;
    }
    return string_id;
}
