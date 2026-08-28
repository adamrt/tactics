#ifndef FFT_DATA_H
#define FFT_DATA_H

#include "fft/unit_position.h"
#include "psx/types.h"

enum {
    ENTD_UNITS_PER_ENCOUNTER = 16,
    ENTD_ENCOUNTERS_PER_FILE = 128,
};

/*
 * Ability ID classes.  The class boundaries are the SCUS Data Tables
 * "Ability Secondary Data" ranges (Default 0x000-0x16f, Item 0x170-0x17d,
 * Throw 0x17e-0x189, Jump 0x18a-0x195, Charge 0x196-0x19d, Math 0x19e-0x1a5,
 * R/S/M 0x1a6-0x1ff); the R/S/M split into 32 reaction, 32 support and the
 * movement abilities is the one applied by the SCUS ability classifiers.
 */
enum {
    ABILITY_ID_MASK = 0x1ff,
    ABILITY_ID_ITEM_FIRST = 0x170,
    ABILITY_ID_THROW_FIRST = 0x17e,
    ABILITY_ID_JUMP_FIRST = 0x18a,
    ABILITY_ID_CHARGE_FIRST = 0x196,
    ABILITY_ID_MATH_FIRST = 0x19e,
    ABILITY_ID_REACTION_FIRST = 0x1a6,
    ABILITY_ID_SUPPORT_FIRST = 0x1c6,
    ABILITY_ID_MOVEMENT_FIRST = 0x1e6,
};

typedef enum ability_type {
    ABILITY_TYPE_DEFAULT = 0,
    ABILITY_TYPE_ITEM = 1,
    ABILITY_TYPE_THROW = 2,
    ABILITY_TYPE_JUMP = 3,
    ABILITY_TYPE_CHARGE = 4,
    ABILITY_TYPE_MATH = 5,
    ABILITY_TYPE_REACTION = 6,
    ABILITY_TYPE_SUPPORT = 7,
    ABILITY_TYPE_MOVEMENT = 8,
} ability_type_t;

/* Hard-coded BATTLE ability dispatches, not a complete ability-ID table. */
typedef enum ability_id {
    ABILITY_ID_SONG_ANGEL_SONG = 0x56,
    ABILITY_ID_SONG_LIFE_SONG = 0x57,
    ABILITY_ID_SONG_CHEER_SONG = 0x58,
    ABILITY_ID_SONG_BATTLE_SONG = 0x59,
    ABILITY_ID_SONG_MAGIC_SONG = 0x5a,
    ABILITY_ID_SONG_NAMELESS_SONG = 0x5b,
    ABILITY_ID_SONG_LAST_SONG = 0x5c,
    ABILITY_ID_DANCE_WITCH_HUNT = 0x5d,
    ABILITY_ID_DANCE_WIZNAIBUS = 0x5e,
    ABILITY_ID_DANCE_SLOW_DANCE = 0x5f,
    ABILITY_ID_DANCE_POLKA_POLKA = 0x60,
    ABILITY_ID_DANCE_DISILLUSION = 0x61,
    ABILITY_ID_DANCE_NAMELESS_DANCE = 0x62,
    ABILITY_ID_DANCE_LAST_DANCE = 0x63,
    ABILITY_ID_TALK_PERSUADE = 0x75,
    ABILITY_ID_TALK_PRAISE = 0x76,
    ABILITY_ID_TALK_THREATEN = 0x77,
    ABILITY_ID_TALK_PREACH = 0x78,
    ABILITY_ID_TALK_SOLUTION = 0x79,
    ABILITY_ID_TALK_DEATH_SENTENCE = 0x7a,
    ABILITY_ID_TALK_NEGOTIATE = 0x7b,
} ability_id_t;

/*
 * An ENTD entry is the static 0x28-byte encounter definition read from an
 * ENTD#.ENT file.  It is input to the SCUS unit initializers; it is neither a
 * persistent party_data_t record nor a runtime BattleStats record.
 *
 * Names below are established by target SCUS initialization routines.
 * The remaining bytes intentionally retain neutral names until their runtime
 * consumers are matched.
 */
typedef struct entd_unit {
    u8 sprite_set;             /* 0x00 */
    u8 flags;                  /* 0x01 */
    u8 name_id;                /* 0x02 */
    u8 level;                  /* 0x03 */
    u16 birthday;              /* 0x04 */
    u8 bravery;                /* 0x06 */
    u8 faith;                  /* 0x07 */
    u8 job_unlock;             /* 0x08 */
    u8 job_level;              /* 0x09 */
    u8 job_id;                 /* 0x0a */
    u8 secondary_skillset;     /* 0x0b */
    u16 reaction_ability;      /* 0x0c */
    u16 support_ability;       /* 0x0e */
    u16 movement_ability;      /* 0x10 */
    u8 equipment[5];           /* 0x12 */
    u8 palette;                /* 0x17 */
    u8 battle_flags;           /* 0x18 */
    s8 x;                      /* 0x19 */
    entd_unit_position_t position; /* 0x1a */
    u8 experience;             /* 0x1c */
    u8 primary_skillset;       /* 0x1d */
    u8 war_trophy;             /* 0x1e */
    u8 bonus_money_modifier;   /* 0x1f */
    u8 unit_id;                /* 0x20 */
    u8 _pad21[2];
    u8 ai_flags;          /* 0x23 */
    u8 ai_target_unit_id; /* 0x24 */
    u8 _pad25[3];
} entd_unit_t;

typedef char ENTDUnit_size_must_be_0x28[(sizeof(entd_unit_t) == 0x28) ? 1 : -1];

typedef struct entd_encounter {
    entd_unit_t units[ENTD_UNITS_PER_ENCOUNTER];
} entd_encounter_t;

typedef char ENTDEncounter_size_must_be_0x280[(sizeof(entd_encounter_t) == 0x280) ? 1 : -1];

typedef struct entd_file {
    entd_encounter_t encounters[ENTD_ENCOUNTERS_PER_FILE];
} entd_file_t;

typedef char ENTDFile_size_must_be_0x14000[(sizeof(entd_file_t) == 0x14000) ? 1 : -1];

/*
 * Persistent roster record. Its 0x100-byte stride is established by the
 * indexed SCUS lookup, while its named prefix is established by the target
 * party_data_t-to-BattleStats initializer. It is distinct from entd_unit_t.
 */
typedef struct party_data {
    u8 sprite_set;              /* 0x00 */
    u8 party_id;                /* 0x01 */
    u8 job_id;                  /* 0x02 */
    u8 palette;                 /* 0x03 */
    u8 gender_flags;            /* 0x04 */
    u8 birthday_day;            /* 0x05 */
    u8 zodiac;                  /* 0x06 */
    u8 secondary_skillset;      /* 0x07 */
    u16 reaction_ability;       /* 0x08 */
    u16 support_ability;        /* 0x0a */
    u16 movement_ability;       /* 0x0c */
    u8 equipment[7];            /* 0x0e */
    u8 experience;              /* 0x15 */
    u8 level;                   /* 0x16 */
    u8 bravery;                 /* 0x17 */
    u8 faith;                   /* 0x18 */
    u8 raw_stats[0x0f];         /* 0x19 */
    u8 unlocked_jobs[3];        /* 0x28 */
    u8 learned_abilities[0x39]; /* 0x2b */
    u8 job_levels[0x0a];        /* 0x64 */
    u8 job_points[0x28];        /* 0x6e; per-job "Base Job JP" (wiki page 00000309) */
    u8 total_job_points[0x28];  /* 0x96; per-job "Total Base Job JP" (wiki page 00000309) */
    u8 name[0x10];              /* 0xbe */
    u16 name_id;                /* 0xce */
    u8 proposition_status;      /* 0xd0; nonzero while unavailable on a proposition */
    u8 _pad_d1[0x2f];
} party_data_t;

typedef char PartyData_size_must_be_0x100[(sizeof(party_data_t) == 0x100) ? 1 : -1];

/* party_data_t.party_id sentinel: "0xFF - Unit doesn't appear on Formation"
 * (wiki page 00000309); tested by the roster scans in src/main and the
 * WORLD/WLDCORE party walks. */
enum {
    PARTY_ID_NONE = 0xff,
};

typedef struct item_data {
    u8 palette;
    u8 sprite_id;
    u8 required_level;
    u8 type_flags;
    u8 secondary_data_id;
    u8 type;
    u8 unused_06;
    u8 attributes;
    u16 price;
    u8 shop_availability;
    u8 unused_0b;
} item_data_t;

typedef struct job_data {
    u8 skillset; /* 0x00 */
    u8 _pad01[47];
} job_data_t;

typedef char JobData_size_must_be_48[(sizeof(job_data_t) == 48) ? 1 : -1];

/*
 * WORLD.BIN cooperative thread record.  The thread array (pointer at
 * 0x8015327c, wiki page 00009421) is indexed with `thread_id << 10`, so each
 * slot is 0x400 bytes; the stack/frame pointers start at slot+0x3f0.
 * 0x4c is the "TaskID" and 0x5c/0x60 are per-task words (wiki pages
 * 00010211, 00010213); 0x00-0x0c are the function parameters
 * (world_store_thread_function_parameters[_4]).
 */
typedef struct world_thread {
    s32 function_parameter_1;
    s32 function_parameter_2;
    s32 function_parameter_3;
    s32 unk_0c;
    u8 _pad10[0x28];
    void* global_pointer;
    u32* stack_pointer;
    u32* frame_pointer;
    void (*code_pointer)(void);
    s32 is_running;
    s32 task_id;
    s32 unk_50[7];
    u8 _pad6c[0x394];
} world_thread_t;

typedef char world_thread_t_size_must_be_0x400[(sizeof(world_thread_t) == 0x400) ? 1 : -1];

extern world_thread_t* g_world_threads;
extern s32 g_world_current_thread_id;

void world_switch_to_next_thread(void);

/*
 * WORLD.BIN formation-screen unit record ("Temporary Stats" on the FFHacktics
 * World Stats page, wiki page 00000309).  One 0x128-byte record per roster
 * slot, addressed through g_world_formation_unit_pointers (0x801cd5ec).
 * Halfword fields are the ones the page lists as "(halfword)"; the byte
 * fields from 0x70 on mirror the party_data_t layout above.  The page lists
 * "Magical Shield/Accessory Evade" at 0x40/0x42, which collides with the
 * physical fields; they are placed at 0x50/0x52 here to follow the halfword
 * sequence.  Unlisted bytes stay as padding.
 */
typedef struct world_formation_unit {
    s16 level;  /* 0x000 */
    s16 unk_02; /* 0x002; guest marker (wiki page 00006334) */
    u8 _pad04[4];
    s16 experience;  /* 0x008 */
    s16 party_index; /* 0x00a; portrait (wiki page 00006334) */
    s16 hp;          /* 0x00c */
    u8 _pad0e[2];
    s16 max_hp; /* 0x010 */
    s16 mp;     /* 0x012 */
    u8 _pad14[2];
    s16 max_mp; /* 0x016 */
    s16 ct;     /* 0x018 */
    u8 _pad1a[0xa];
    s16 job_id; /* 0x024; "Current Job" */
    s16 brave;  /* 0x026 */
    s16 faith;  /* 0x028 */
    u8 _pad2a[2];
    s16 roster_slot; /* 0x02c; "Roster Slot Index" */
    u8 _pad2e[2];
    s16 move;               /* 0x030 */
    s16 speed;              /* 0x032 */
    s16 jump;               /* 0x034 */
    s16 right_weapon_power; /* 0x036 */
    s16 left_weapon_power;  /* 0x038 */
    s16 right_weapon_evade; /* 0x03a */
    s16 left_weapon_evade;  /* 0x03c */
    s16 unk_3e;             /* 0x03e; nonzero blocks equip changes (lock_equipment_and_abilities) */
    u8 _pad40[2];
    s16 physical_attack;          /* 0x042 */
    s16 physical_class_evade;     /* 0x044 */
    s16 physical_shield_evade;    /* 0x046 */
    s16 physical_accessory_evade; /* 0x048 */
    u8 _pad4a[2];
    s16 magical_attack;          /* 0x04c */
    s16 magical_class_evade;     /* 0x04e */
    s16 magical_shield_evade;    /* 0x050 */
    s16 magical_accessory_evade; /* 0x052 */
    u16 equipment[5];            /* 0x054; right hand, left hand, head, body, accessory */
    s16 primary_skillset;        /* 0x05e */
    s16 secondary_skillset;      /* 0x060 */
    s16 reaction_ability;        /* 0x062 */
    s16 support_ability;         /* 0x064 */
    s16 movement_ability;        /* 0x066 */
    u8 _pad68[8];
    u8 gender_flags; /* 0x070; UnitGenderFlags (fft/job.h) */
    u8 _pad71;
    u8 sprite_set;               /* 0x072; "Sprite Set ID": party_data_t.sprite_set / character identity */
    u8 equippable_item_types[4]; /* 0x073; bit per item type, read by can_unit_equip_item_id */
    u8 unlocked_jobs[3];         /* 0x077 */
    u8 learned_abilities[0x39];  /* 0x07a through 0x0b2 */
    u8 job_levels[0x0a];         /* 0x0b3 */
    u8 _padbd;
    u16 job_points[0x14];       /* 0x0be; per-job JP */
    u16 total_job_points[0x14]; /* 0x0e6; per-job total JP */
    u8 name[0x10];              /* 0x10e; "Unit Nickname" */
    u8 _pad11e;
    u8 proposition_status; /* 0x11f; "Proposition Byte" */
    u16 unk_120;           /* 0x120; "Current Job?" -- readers split it into nibbles */
    u8 egg_color;          /* 0x122; party_data_t 0xd2 */
    u8 _pad123[3];
    u8 support_sets_3; /* 0x126; "Unit Support Sets #3", WORLD_SUPPORT_SET_3_* (fft/job.h) */
    u8 _pad127;
} world_formation_unit_t;

typedef char world_formation_unit_t_size_must_be_0x128[(sizeof(world_formation_unit_t) == 0x128) ? 1 : -1];

extern world_formation_unit_t* g_world_formation_unit_pointers[];
extern u8 g_world_formation_unit_count;

/* world_formation_unit_t.equipment halfwords carry the item id in the low ten
 * bits and flags above (bit 14 is tested by world_buy_from_fitting_room and the
 * job wheel, wiki page 00007087 "andi 0x3ff / andi 0x4000"); the WORLD item
 * tables are indexed by the masked id (world_get_item_price, world_get_item_type). */
enum {
    WORLD_ITEM_ID_MASK = 0x3ff,
};

/* sprite_set / character identity thresholds (wiki page 00000309:
 * 0x00-0x7f special, 0x80 generic male, 0x81 generic female, 0x82 monster). */
enum {
    WORLD_SPRITE_SET_GENERIC_FIRST = 0x80,
    WORLD_SPRITE_SET_MONSTER = 0x82,
};

/* WORLD.BIN event word indices (g_world_event_words).  0x1e holds the 12-bit
 * camera yaw: "Initialize Camera Yaw Angle" (wiki page 00000836, routine at
 * 0x800e1f58) writes it and world_get_event_word_0x1e_mod_0x1000 normalises
 * it into 0..0xfff. */
enum {
    WORLD_EVENT_WORD_CAMERA_YAW = 0x1e,
};

/*
 * WORLD.BIN tutorial command stream (wiki page 00010216 "Handle Tutorial
 * Command").  Commands below 0x10 are one-byte shifts; the rest are
 * ID (1) followed by the listed parameters: 0x10 message id (2) + y (1),
 * 0x11 message id (2), 0x13 x, y, size, width mod, height mod (1 each),
 * 0x15 time (1).
 */
enum {
    WORLD_TUTORIAL_CMD_SHIFT_LIMIT = 0x10,
    WORLD_TUTORIAL_CMD_DISPLAY_MESSAGE = 0x10,
    WORLD_TUTORIAL_CMD_CHANGE_DIALOG = 0x11,
    WORLD_TUTORIAL_CMD_WAIT_FOR_MESSAGE = 0x12,
    WORLD_TUTORIAL_CMD_DRAW_CIRCLE = 0x13,
    WORLD_TUTORIAL_CMD_WAIT = 0x14,
    WORLD_TUTORIAL_CMD_WAIT_TIME = 0x15,
    WORLD_TUTORIAL_CMD_WAIT_FOR_MESSAGE_2 = 0x16,
    WORLD_TUTORIAL_CMD_END = 0x17,
};

#endif
