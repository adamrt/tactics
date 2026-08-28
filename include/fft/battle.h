#ifndef FFT_BATTLE_H
#define FFT_BATTLE_H

#include "fft/unit_position.h"
#include "psx/types.h"

enum BattleActionType {
    BATTLE_ACTION_TYPE_PSEUDO_STATUS = 0x01,
    BATTLE_ACTION_TYPE_MP_HEALING = 0x10,
    BATTLE_ACTION_TYPE_MP_DAMAGE = 0x20,
    BATTLE_ACTION_TYPE_HP_HEALING = 0x40,
    BATTLE_ACTION_TYPE_HP_DAMAGE = 0x80,
};

enum BattleTeamFlags {
    BATTLE_TEAM_MASK = 0x30,
    BATTLE_TEAM_BLUE = 0x00,
    BATTLE_TEAM_RED = 0x10,
    BATTLE_TEAM_GREEN = 0x20,
    BATTLE_TEAM_LIGHT_BLUE = 0x30,
    BATTLE_HORIZONTAL_FLIP = 0x02,
    BATTLE_TEAM_FLAG_IMMORTAL = 0x04,
};

enum BattleUnitFlags {
    BATTLE_UNIT_FLAG_SAVE_FORMATION = 0x01,
    BATTLE_UNIT_FLAG_LOAD_FORMATION = 0x08,
};

typedef enum battle_facing {
    BATTLE_FACING_SOUTH = 0x000,
    BATTLE_FACING_WEST = 0x400,
    BATTLE_FACING_NORTH = 0x800,
    BATTLE_FACING_EAST = 0xc00,
    BATTLE_FACING_QUARTER_TURN = 0x400,
    BATTLE_FACING_MASK = 0x0fff,
} battle_facing_t;

enum ElementFlags {
    BATTLE_ELEMENT_FIRE = 0x80,
    BATTLE_ELEMENT_LIGHTNING = 0x40,
    BATTLE_ELEMENT_ICE = 0x20,
    BATTLE_ELEMENT_WIND = 0x10,
    BATTLE_ELEMENT_EARTH = 0x08,
    BATTLE_ELEMENT_WATER = 0x04,
    BATTLE_ELEMENT_HOLY = 0x02,
    BATTLE_ELEMENT_DARK = 0x01,
};

/*
 * Values dispatched by battle_game_loop.  The names follow the corresponding
 * FFHacktics game-state handler descriptions, verified against the target's
 * switch table.  The target has no explicit handler for value 0x32.
 */
typedef enum battle_game_state {
    BATTLE_GAME_STATE_FREE_CURSOR = 0x00,
    BATTLE_GAME_STATE_FREE_CURSOR_HELP = 0x01,
    BATTLE_GAME_STATE_HIGHLIGHT_UNITS = 0x02,
    BATTLE_GAME_STATE_OPEN_ACTION_MENUS = 0x03,
    BATTLE_GAME_STATE_IDLING_ACTION_MENUS = 0x04,
    BATTLE_GAME_STATE_MENU_TO_TARGETING = 0x05,
    BATTLE_GAME_STATE_ACTION_HELP_MENU = 0x06,
    BATTLE_GAME_STATE_DISPLAY_MOVE_AREA = 0x07,
    BATTLE_GAME_STATE_MINI_MENU = 0x08,
    BATTLE_GAME_STATE_MINI_MENU_HELP = 0x09,
    BATTLE_GAME_STATE_ACTIVE_TURN = 0x0a,
    BATTLE_GAME_STATE_STATUS_EXECUTE = 0x0b,
    BATTLE_GAME_STATE_UNIT_MOVE = 0x0c,
    BATTLE_GAME_STATE_CLOSE_MOVE_HELP = 0x0d,
    BATTLE_GAME_STATE_MOVE_RANGE_EXCEPTION = 0x0e,
    BATTLE_GAME_STATE_ILLEGAL_MOVE_MENU = 0x0f,
    BATTLE_GAME_STATE_UNIT_MOVING_SETUP = 0x10,
    BATTLE_GAME_STATE_UNIT_MOVING = 0x11,
    BATTLE_GAME_STATE_MOVE_CONFIRM_MENU = 0x12,
    BATTLE_GAME_STATE_WAIT_DIRECTION = 0x13,
    BATTLE_GAME_STATE_WAIT_MENU = 0x14,
    BATTLE_GAME_STATE_CRYSTAL_LEARN = 0x15,
    BATTLE_GAME_STATE_ACTION_EXECUTE_SETUP = 0x16,
    BATTLE_GAME_STATE_TARGETING_RANGE = 0x17,
    BATTLE_GAME_STATE_ILLEGAL_RANGE = 0x18,
    BATTLE_GAME_STATE_ABILITY_PREVIEW_HANDLING = 0x19,
    BATTLE_GAME_STATE_ABILITY_PREVIEW_HELP = 0x1a,
    BATTLE_GAME_STATE_CONFIRM_ACTION = 0x1b,
    BATTLE_GAME_STATE_PRE_ATTACK_ANIMATION = 0x1c,
    BATTLE_GAME_STATE_ACTION_CAST = 0x1d,
    BATTLE_GAME_STATE_COMMENCE_ATTACK_PHASE = 0x1e,
    BATTLE_GAME_STATE_TARGET_SELECT_START = 0x1f,
    BATTLE_GAME_STATE_TARGET_SELECT = 0x20,
    BATTLE_GAME_STATE_TARGET_SELECT_DENIED = 0x21,
    BATTLE_GAME_STATE_TARGET_SELECT_CONFIRM = 0x22,
    BATTLE_GAME_STATE_TARGET_DISPLAY_START = 0x23,
    BATTLE_GAME_STATE_TARGET_DISPLAY = 0x24,
    BATTLE_GAME_STATE_AFTER_COMMAND = 0x25,
    BATTLE_GAME_STATE_JP_EXP_GAIN = 0x26,
    BATTLE_GAME_STATE_CHANGE_TURN = 0x27,
    BATTLE_GAME_STATE_LEARN_ABILITY_ON_HIT = 0x28,
    BATTLE_GAME_STATE_EFFECT_DAMAGE_DISPLAY = 0x29,
    BATTLE_GAME_STATE_OPEN_SP2_FILES = 0x2a,
    BATTLE_GAME_STATE_START_EFFECT_FILE_OPEN = 0x2b,
    BATTLE_GAME_STATE_SECONDARY_EFFECT = 0x2c,
    BATTLE_GAME_STATE_ACTION_EXECUTE = 0x2d,
    BATTLE_GAME_STATE_BATTLE_MESSAGE_DISPLAY = 0x2e,
    BATTLE_GAME_STATE_RESUME_ATTACK_PHASE = 0x2f,
    BATTLE_GAME_STATE_DEEP_DUNGEON_MESH_LOAD = 0x30,
    BATTLE_GAME_STATE_DEEP_DUNGEON_MESH_FINISH = 0x31,
    BATTLE_GAME_STATE_EFFECT = 0x33,
    BATTLE_GAME_STATE_EVENT = 0x34,
    BATTLE_GAME_STATE_MAP_JUMPING_OUT = 0x35,
    BATTLE_GAME_STATE_MAP_INITIALIZE = 0x36,
    BATTLE_GAME_STATE_MAP_JUMPING_IN = 0x37,
    BATTLE_GAME_STATE_MAP_JUMPING_OUT_2 = 0x38,
    BATTLE_GAME_STATE_MAP_INITIALIZE_2 = 0x39,
    BATTLE_GAME_STATE_MAP_JUMPING_IN_2 = 0x3a,
    BATTLE_GAME_STATE_CLOSE_BATTLE = 0x3b,
} battle_game_state_t;

/*
 * Temporary action results, 0x2c bytes at battle_stats_t+0x18c.  Layout from the
 * FFHacktics Battle Stats page ("Battle Action Data", 0x18c..0x1b7); the
 * g_target_current_action / g_attacker_current_action pointers address this
 * block directly.  status_infliction/status_removal mirror the five
 * current_status bytes.
 */
typedef struct battle_action_data {
    u8 hit;          /* 0x00; 1 hit, 0 miss */
    u8 critical;     /* 0x01 */
    u8 miss_type;    /* 0x02; 0 hit, 1/2 guarded, 5 nullified, 6 miss, 7 catch */
    u8 item_lost;    /* 0x03; potion / break / steal / draw out */
    u16 hp_damage;   /* 0x04 */
    u16 hp_healing;  /* 0x06 */
    u16 mp_damage;   /* 0x08 */
    u16 mp_healing;  /* 0x0a */
    s16 gil_change;  /* 0x0c; stolen / lost */
    u16 reaction_id; /* 0x0e */
    /* The wiki lists 0x10 "Special Effect" and 0x11 "Special Flags 2" as bytes,
     * but every reader/writer in src/battle uses one halfword (lhu/sh:
     * formula_set_golem, formula_steal_equipment, elemental_absorption,
     * called_by_nullify_action, ...).  Low byte: level up 0x80, switch team
     * 0x40, poach 0x20, steal 0x10, break 0x04, malboro 0x02, golem 0x01.
     * High byte: knockback 0x40, weakness 0x08, absorb 0x04, nullify 0x02,
     * level down 0x01. */
    u16 special_effect;       /* 0x10 */
    u8 sp_change;             /* 0x12 */
    u8 ct_change;             /* 0x13 */
    u8 pa_change;             /* 0x14 */
    u8 ma_change;             /* 0x15 */
    u8 brave_change;          /* 0x16 */
    u8 faith_change;          /* 0x17 */
    u8 status_change;         /* 0x18 */
    u8 equipment_destroyed;   /* 0x19; slot mask, 0xfe triggers weapon attack */
    u8 stolen_item_id;        /* 0x1a */
    u8 status_infliction[5];  /* 0x1b */
    u8 status_removal[5];     /* 0x20 */
    u8 attack_type;           /* 0x25; HP/MP damage/heal, status, pseudo-status */
    u16 last_received_attack; /* 0x26; reaction data, varies by ability */
    u8 exp_change;            /* 0x28; Steal EXP */
    u8 jp_change;             /* 0x29; Move-JP Up / JP stolen */
    /* Written as a halfword everywhere (battle_apply_status lhu/sh,
     * arrow_guard_usability, battle_catch, force_attack_miss). */
    u16 attack_accuracy; /* 0x2a */
} battle_action_data_t;

typedef char BattleActionData_size_must_be_0x2c[(sizeof(battle_action_data_t) == 0x2c) ? 1 : -1];

/*
 * Battle Stats are the simulation-side unit records.  They occupy 0x1c0
 * bytes, with 21 consecutive slots beginning at 0x801908cc in BATTLE.BIN.
 * Do not confuse this with Misc Unit Data, the renderer-side record that
 * points back to battle_stats_t at offset 0x134.
 *
 * Field names and offsets come from the FFHacktics Battle Stats reference.
 * Undocumented areas intentionally remain explicit padding until evidence
 * supports a name and type.
 */
typedef struct battle_stats {
    u8 character_identity; /* 0x000 */
    u8 entd_slot;          /* 0x001; 0xff means absent */
    u8 formation_index;    /* 0x002 */
    u8 job_id;             /* 0x003 */
    u8 sprite_palette;     /* 0x004 */
    u8 team_flags;         /* 0x005 */
    u8 unit_flags;         /* 0x006; mixed sex, monster, guest, and formation flags */
    u8 death_counter;      /* 0x007 */
    u8 _pad008;
    u8 zodiac;                   /* 0x009 */
    u16 innate_abilities[4];     /* 0x00a */
    u8 primary_skillset;         /* 0x012 */
    u8 secondary_skillset;       /* 0x013 */
    u16 reaction_ability;        /* 0x014 */
    u16 support_ability;         /* 0x016 */
    u16 movement_ability;        /* 0x018 */
    u8 equipment[7];             /* 0x01a; head through left-hand shield */
    u8 experience;               /* 0x021 */
    u8 level;                    /* 0x022 */
    u8 original_brave;           /* 0x023 */
    u8 brave;                    /* 0x024 */
    u8 original_faith;           /* 0x025 */
    u8 faith;                    /* 0x026 */
    u8 transparent_removal_flag; /* 0x027 */
    u16 hp;                      /* 0x028 */
    u16 max_hp;                  /* 0x02a */
    u16 mp;                      /* 0x02c */
    u16 max_mp;                  /* 0x02e */
    u8 base_attributes[3];       /* 0x030; PA, MA, SP */
    u8 equipment_attributes[3];  /* 0x033; PA, MA, SP */
    u8 attributes[3];            /* 0x036; PA, MA, SP */
    u8 ct;                       /* 0x039 */
    u8 move;                     /* 0x03a */
    u8 jump;                     /* 0x03b */
    u8 evasion[11];              /* 0x03c */
    u8 x;                        /* 0x047 */
    battle_unit_position_t position; /* 0x048 */
    u8 equipment_categories[4];  /* 0x04a */
    u8 innate_status[5];         /* 0x04e */
    u8 status_immunity[5];       /* 0x053 */
    u8 current_status[5];        /* 0x058 */
    u8 status_ct[16];            /* 0x05d */
    u8 elemental_affinity[5];    /* 0x06d */
    u8 raw_stats[0x19];          /* 0x072 */
    u8 reaction_abilities[4];    /* 0x08b */
    u8 support_abilities[4];     /* 0x08f */
    u8 movement_abilities[3];    /* 0x093 */
    u8 unlocked_jobs[3];         /* 0x096 */
    u8 learned_abilities[0xc0];  /* 0x099 through 0x158 */
    u8 _pad159[3];
    u8 ko_count;           /* 0x15c */
    u8 charged_ability_ct; /* 0x15d */
    u8 _pad15e;
    u8 spritesheet_id;                 /* 0x15f */
    u8 job_portrait_palette;           /* 0x160 */
    u8 unit_id;                        /* 0x161 */
    u8 base_job_skillset;              /* 0x162 */
    u8 war_trophy;                     /* 0x163 */
    u8 bonus_money_modifier;           /* 0x164 */
    u8 ai_target_x;                    /* 0x165 */
    u8 ai_target_y;                    /* 0x166 */
    u8 ai_flags;                       /* 0x167 */
    u8 prioritized_target;             /* 0x168 */
    u8 entd_unknown_left;              /* 0x169 */
    u8 entd_unknown_flags;             /* 0x16a */
    u8 entd_unknown_right;             /* 0x16b */
    u16 quote_name_id;                 /* 0x16c */
    u8 action_actor_id;                /* 0x16e */
    u8 last_skillset_id;               /* 0x16f */
    s16 last_ability_id;               /* 0x170 */
    u16 calculator_type_ability;       /* 0x172 */
    u16 calculator_multiplier_ability; /* 0x174 */
    u16 used_item_or_equipment;        /* 0x176 */
    u8 action_reaction_id;             /* 0x178 */
    u8 action_target_id;               /* 0x179 */
    s16 action_target_x;               /* 0x17a */
    s16 action_target_elevation;       /* 0x17c */
    s16 action_target_y;               /* 0x17e */
    u8 death_on_chocobo;               /* 0x180 */
    u8 action_tile_flags;              /* 0x181 */
    u8 mount_info;                     /* 0x182 */
    u8 existence;                      /* 0x183 */
    u8 equipped_flags;                 /* 0x184 */
    u8 _pad185;
    u8 has_turn;             /* 0x186 */
    u8 movement_taken;       /* 0x187 */
    u8 action_taken;         /* 0x188 */
    u8 ability_outcome;      /* 0x189 */
    u8 misc_unit_id;         /* 0x18a */
    u8 ability_ct;           /* 0x18b */
    battle_action_data_t action; /* 0x18c through 0x1b7 */
    u8 auto_battle_setting;  /* 0x1b8 */
    u8 auto_battle_target;   /* 0x1b9 */
    u8 initial_team_flags;   /* 0x1ba */
    u8 inflicted_status[5];  /* 0x1bb */
} battle_stats_t;

typedef char BattleStats_size_must_be_0x1c0[(sizeof(battle_stats_t) == 0x1c0) ? 1 : -1];

typedef union battle_movement {
    u32 word;
    struct {
        u8 destination_x;
        u8 destination_y;
        u8 destination_z;
        u8 flags;
    } bytes;
} battle_movement_t;

typedef struct battle_sprite_display_data battle_sprite_display_data_t;

typedef struct battle_svector {
    s16 vx;
    s16 vy;
    s16 vz;
    s16 pad;
} battle_svector_t;

/*
 * The documented, currently used prefix of a Misc Unit Data record.  There
 * are 16 renderer-side slots, each 0x440 bytes; this declaration intentionally
 * ends after the verified status-word prefix at 0x148.  The record links to
 * its simulation-side battle_stats_t record at 0x134.
 */
typedef struct battle_misc_data {
    u32 previous;             /* 0x000; previous Misc Unit Data */
    u8 unit_id;               /* 0x004; Misc Unit Data ID */
    u8 spritesheet_vram_slot; /* 0x005 */
    u8 spritesheet_id;        /* 0x006 */
    u8 stored_palette;        /* 0x007 */
    u16 unit_check;           /* 0x008 */
    u8 ability_in_use;        /* 0x00a */
    u8 _pad00b;
    u16 requested_animation; /* 0x00c */
    u16 vram_spritesheet_id; /* 0x00e */
    u16 vram_palette_id;     /* 0x010 */
    u8 sprite_display_flags; /* 0x012 */
    u8 _pad013[5];
    s32 real_x; /* 0x018 */
    s32 real_z; /* 0x01c */
    s32 real_y; /* 0x020 */
    u8 _pad024[0x14];
    u16 walk_speed;      /* 0x038 */
    u16 walk_speed_copy; /* 0x03a */
    u8 _pad03c[4];
    s16 screen_x; /* 0x040 */
    s16 screen_z; /* 0x042 */
    s16 screen_y; /* 0x044 */
    u8 _pad046[0xa];
    /* Two more X/Height/Y halfword triples (FFHacktics Miscellaneous Unit
     * Data 0x050/0x052/0x054 and 0x060/0x062/0x064, "used to create vectors
     * for effects processing").  battle_move_unit_forward_or_backward and
     * battle_add_signed_byte_to_unit_height read-modify-write the first;
     * increment_another_coords_by_misc_id(_copy) accumulate into the second. */
    s16 effect_vector_x; /* 0x050 */
    s16 effect_vector_z; /* 0x052 */
    s16 effect_vector_y; /* 0x054 */
    u8 _pad056[0xa];
    s16 effect_vector_2_x; /* 0x060 */
    s16 effect_vector_2_z; /* 0x062 */
    s16 effect_vector_2_y; /* 0x064 */
    u8 _pad066[0xa];
    u16 facing;                /* 0x070 */
    u16 attack_facing;         /* 0x072 */
    u16 depth_height_offset;   /* 0x074 */
    u16 mounted_height_offset; /* 0x076 */
    u8 _pad078[2];
    s16 special_graphic_y_offset; /* 0x07a */
    u8 map_x;                     /* 0x07c */
    u8 map_y;                     /* 0x07d */
    u8 map_z;                     /* 0x07e */
    u8 centre_tile_offset;        /* 0x07f */
    battle_movement_t movement;
    u8 previous_map_x; /* 0x084 */
    u8 previous_map_y; /* 0x085 */
    u8 previous_map_z; /* 0x086 */
    u8 _pad087[0xd];
    u16 previous_facing; /* 0x094 */
    u8 _pad096[2];
    u32 movement_path_offset; /* 0x098; relative to this record */
    /*
     * Movement path (FFHacktics Miscellaneous Unit Data 0x9c/0x9d).  A count of
     * 0xfe means 0x9d..0x9f hold an explicit x/y/z instead of a step list
     * (initialize_units_coordinates_animation_facing); a non-zero count means
     * the unit is still moving (unit_moving_check_by_misc_id,
     * process_unit_movement); set_unit_movement_flag ORs 0x10 into a step.
     */
    u8 movement_path_count; /* 0x09c */
    u8 movement_path[0x7c]; /* 0x09d..0x118; step: direction | 0x20 higher elevation | jump length */
    u8 movement_flags;      /* 0x119; fly/float/water/teleport/silent walk (wiki, speculative) */
    u8 _pad11a;
    u8 mount_byte;     /* 0x11b */
    u8 movement_value; /* 0x11c */
    u8 _pad11d;
    u8 current_unit_id_plus_one;  /* 0x11e */
    u8 previous_unit_id_plus_one; /* 0x11f */
    s16 item_get_camera_x;        /* 0x120 */
    s16 item_get_camera_y;        /* 0x122 */
    u8 _pad124[4];
    u32 otag_depth_index; /* 0x128 */
    u8 _pad12c[4];
    u8 mount_rider_value;          /* 0x130 */
    u8 mount_rider_id;             /* 0x131 */
    u8 previous_mount_rider_value; /* 0x132 */
    u8 previous_mount_rider_id;    /* 0x133 */
    battle_stats_t* battle_data;      /* 0x134; battle_stats_t backlink */
    u16 used_ability_id;           /* 0x138 */
    u8 used_item_or_weapon_id;     /* 0x13a */
    u8 equipped_weapon_type;       /* 0x13b */
    u8 ability_ct_resolved;        /* 0x13c */
    u8 team_flags;                 /* 0x13d */
    u8 palette_modifier;           /* 0x13e */
    u8 horizontal_flip_flag;       /* 0x13f */
    u32 status_flags_1_4;          /* 0x140 */
    u32 status_flags_5_6;          /* 0x144 */
    /* 0x148..0x157: FFHacktics Miscellaneous Unit Data "Statuses to Add/Remove";
     * battle_update_float_and_jump_height tests 0x154 & 0x40 (Float). */
    u32 statuses_to_add_1_4;    /* 0x148 */
    u32 statuses_to_add_5_6;    /* 0x14c */
    u32 statuses_to_remove_1_4; /* 0x150 */
    u32 statuses_to_remove_5_6; /* 0x154 */
    u8 _unknown_158[0xc];       /* 0x158..0x163: AI decision word + destination/action scratch */
    s32 facing_hint;            /* 0x164: WAIT_DIRECTION facing directive (0..3) */
    /* Cursor target panel (Miscellaneous Unit Data 0x168/0x16a/0x16c);
     * free_cursor_selection_routine reads all three with lh. */
    s16 target_panel_x;        /* 0x168 */
    s16 target_map_level;      /* 0x16a */
    s16 target_panel_y;        /* 0x16c */
    u8 _unknown_16e[6];        /* 0x16e..0x173 */
    s32 ability_preview_phase; /* 0x174: ability preview branch selector */
    u8 _unknown_178[4];        /* 0x178..0x17b */
    s32 attack_phase_state;    /* 0x17c: 3 == commence, else pre-phase */
    s32 pending_attack_result; /* 0x180: attack result code; -1 signals death */
    /* Death-by-dismount destination (Miscellaneous Unit Data 0x184/0x186/
     * 0x188); battle_set_map_coords_after_death_dismount copies them to
     * map_x/map_z/map_y.  attack_result_animation_update passes &dismount_x. */
    u8 dismount_x; /* 0x184 */
    u8 _pad185;
    u8 dismount_z; /* 0x186 */
    u8 _pad187;
    u8 dismount_y; /* 0x188 */
    u8 _pad189[3];
    /* Current action data, FFHacktics Miscellaneous Unit Data 0x18c..0x1d7. */
    u8 action_18c;           /* 0x18c; "Reaction ID / Attacking unit ID? - Used Ability ID" */
    u8 target_count;         /* 0x18d; attacker_face_targets, update_anim_display_for_all_targets */
    u8 target_list[0x10];    /* 0x18e; misc ids, 0xff terminated */
    u8 animate_on_miss_flag; /* 0x19e; 1 when animate-on-miss is false, cleared on hit */
    u8 control_value_19f;    /* 0x19f; 0x01 math skill */
    u16 last_attack_id;      /* 0x1a0 */
    u8 ability_formula;      /* 0x1a2; can poach? */
    u8 reaction_occurred;    /* 0x1a3 */
    u8 continue_attack;      /* 0x1a4 */
    u8 current_hit_number;   /* 0x1a5 */
    u8 reaction_id_1a6;      /* 0x1a6 */
    u8 _unknown_1a7;
    u8 target_new_x;             /* 0x1a8; post-action knockback destination (transfer_target_coordinates) */
    u8 target_new_y;             /* 0x1a9 */
    u8 target_new_map_level;     /* 0x1aa */
    u8 used_weapon_id;           /* 0x1ab */
    u8 _unknown_1ac[3];          /* 0x1ac..0x1ae */
    u8 can_earn_experience;      /* 0x1af */
    u8 earned_experience;        /* 0x1b0; for display (post_action_xp_jp_ability) */
    u8 earned_jp;                /* 0x1b1 */
    u8 level_for_display;        /* 0x1b2; "Level UP!" */
    u8 job_level_for_display;    /* 0x1b3 */
    u8 _unknown_1b4[3];          /* 0x1b4..0x1b6 */
    u8 status_change_count;      /* 0x1b7; inflicted/removed status counter, max 0x1b */
    u8 display_flags[4];         /* 0x1b8..0x1bb; damage/heal/stat/message display flags */
    u8 status_change_list[0x1b]; /* 0x1bc..0x1d6; counts backwards, 0x80 = removal */
    u8 _pad1d7;
    /* Unit Sprite Data block starts at 0x1d8 (wiki); the trigger is written
     * as a halfword by animate_and_set_enemy_level_data_by_misc_id. */
    u16 sprite_graphic_trigger; /* 0x1d8 */
    u8 _pad1da[2];
    u16 encoded_animation;         /* 0x1dc: half-shifted animation id */
    u8 _unknown_1de[4];            /* 0x1de..0x1e1 */
    u16 animation_countdown;       /* 0x1e2: frames remaining in current attack state */
    u16 secondary_animation_state; /* 0x1e4 */
    u8 _unknown_1e6[0xe];          /* 0x1e6..0x1f3: unit animation / frame state */
    /* Unit sprite SHP/SEQ pointers (Miscellaneous Unit Data, wiki page
     * 00009560, 0x1f4/0x1f8); poach_morbol_transformation rewrites both for
     * the Malboro spritesheet. */
    u8* shp_data;              /* 0x1f4 */
    u8* seq_data;              /* 0x1f8 */
    u8 _unknown_1fc[0x9c];     /* 0x1fc..0x297: second SHP/SEQ pair, weapon and effect sprite data */
    u8 shadow_graphic_trigger; /* 0x298; set_/unset_shadow_graphic_trigger_by_misc_id */
    u8 _unknown_299[0x23];     /* 0x299..0x2bb */
    /*
     * Numerical display / status text (Miscellaneous Unit Data, wiki page
     * 00009560, 0x2bc..0x2d8).
     * prep_for_displaying_earned_exp_jp and activate_numerical_sprite_data test
     * the activation flag, zero the display type (sh) and poke field_04 of the
     * three numeric battle_sprite_display_data_t slots.
     */
    u8 numeric_display_active; /* 0x2bc */
    u8 _pad2bd;
    u16 numeric_display_message;            /* 0x2be; message/stat selector (wiki "Display Type") */
    u16 numeric_display_value;              /* 0x2c0; number to display */
    s16 numeric_display_type;               /* 0x2c2; 0 when inactive, capped at 0x15 */
    battle_sprite_display_data_t* numeric_displays[3]; /* 0x2c4, 0x2c8, 0x2cc */
    u16 _unknown_2d0;                       /* 0x2d0; item ability display */
    s8 item_get_x_offset;                   /* 0x2d2; setup_item_get_rendering reads (s8) */
    s8 item_get_y_offset;                   /* 0x2d3 */
    u8 _pad2d4[4];
    battle_sprite_display_data_t* item_display; /* 0x2d8; Item/Equip display pointer */
    /* Status bubble (Miscellaneous Unit Data, wiki page 00009560, 0x2dc..0x2e7);
     * battle_update_status_bubble_graphic_trigger sets the flag and clears the
     * timer with a halfword store, so the timer is declared u16 although the
     * wiki calls it a word. */
    u8 status_bubble_active; /* 0x2dc */
    u8 status_bubble_id;     /* 0x2dd */
    u8 status_bubble_x;      /* 0x2de */
    u8 status_bubble_y;      /* 0x2df */
    u16 status_bubble_timer; /* 0x2e0 */
    u8 _pad2e2[2];
    void* status_bubble_display; /* 0x2e4; pointer into the 0x410 status bubble data */
    u32 _unknown_2e8;            /* 0x2e8; battle_initialize_position_vector_copies sets 1 */
    /* "array of VECTOR[6] used during sprite rotation/scaling render" (wiki
     * page 00009560, 0x2ec); battle_initialize_position_vector_copies seeds
     * all six from screen_x/z/y. */
    battle_svector_t display_svectors[6]; /* 0x2ec..0x31b */
    u8 _unknown_31c[0x124];      /* 0x31c..0x43f: sprite display sections */
} battle_misc_data_t;

typedef char BattleMiscData_size_must_be_0x440[(sizeof(battle_misc_data_t) == 0x440) ? 1 : -1];

/* Kept while source files migrate to the more specific type name. */
typedef battle_misc_data_t battle_display_unit_t;

typedef struct battle_secondary_effect_init {
    s16 target_count;
    u8 _pad2[2];
    s16 animate_on_miss;
    u8 target_id;
    u8 _pad7[0x9d];
    s16 unknown_a4;
    u8 caster_id;
} battle_secondary_effect_init_t;

typedef struct battle_sprite_part_display_data {
    s8 x_shift;
    s8 y_shift;
    u8 width;
    u8 height;
    u8 u;
    u8 v;
    u8 flags;
} battle_sprite_part_display_data_t;

typedef char SpritePartDisplayData_size_must_be_7[(sizeof(battle_sprite_part_display_data_t) == 7) ? 1 : -1];

/*
 * Header of a 0x440-byte sprite display slot (unit, weapon, item, numeric and
 * status-bubble displays all share it).  The battle_sprite_part_display_data_t records
 * start at 0x0e; battle_initialize_*_sprite_display fill in the header.
 */
struct battle_sprite_display_data {
    u8 red;                         /* 0x00 */
    u8 green;                       /* 0x01 */
    u8 blue;                        /* 0x02 */
    u8 part_count;                  /* 0x03; graphics count passed to construct_polygon_data_for_units */
    s16 field_04;                   /* 0x04 */
    u16 clut;                       /* 0x06 */
    s16 field_08;                   /* 0x08; initialised to 0x1000 */
    s16 field_0a;                   /* 0x0a; initialised to 0x1000 */
    s16 field_0c;                   /* 0x0c */
    battle_sprite_part_display_data_t parts[1]; /* 0x0e; count depends on the display */
};

typedef struct battle_render_unit {
    u8 _pad0[0x12];
    u16 sprite_flags;
    u8 _pad14[0x10c];
    battle_svector_t camera_relative_position;
    u32 otag_depth;
    u8 _pad12c[0x1ac];
    battle_sprite_display_data_t* found_item_display;
    u8 _pad2dc[0x10];
    battle_svector_t display_svectors[6];
} battle_render_unit_t;

/* The battle renderer stores these fixed-point coordinates in X, Z, Y order. */
typedef struct battle_real_coords {
    s32 x;
    s32 z;
    s32 y;
} battle_real_coords_t;

/*
 * AI data block, 0x19c8 bytes at 0x8019f3c4 (g_ai_data_base).  The layout is
 * the FFHacktics "BATTLE.BIN Data Tables" listing (wiki page 00009373, the
 * "AI data" section) cross-checked against the annotated routines cited per
 * field; the pages cited are the ones whose disassembly reads or writes the
 * field.  Undocumented ranges stay explicit padding.  Scalar aliases such as
 * g_ai_map_max_x / g_ai_acting_unit_decision_ptr name the same bytes; a site
 * uses the alias when the target addresses the byte through %lo(sym) and the
 * struct when it goes through a base register.
 */

/* X / map level / Y / zero, written in that order by transfer_unit_coordinates_to_ai
 * (wiki page 00006771) and read as one word for equality tests (00003583, 00007017). */
typedef union battle_ai_coords {
    u32 word;
    struct {
        u8 x;
        u8 level;
        u8 y;
        u8 zero;
    } bytes;
} battle_ai_coords_t;

/* Ability AI behaviour flags 1..4 (wiki pages 00004571, 00007518 read all four as a word;
 * 00000627, 00000636, 00000868 read the bytes).  flags_1: 0x80 HP, 0x40 MP, 0x20 cancel
 * status, 0x10 add status, 0x08 stats, 0x04 unequip, 0x02 target enemies, 0x01 target
 * allies.  flags_3: 0x80 arc, 0x40 direct, 0x20 linear.  flags_4: 0x80 usable by AI. */
typedef union battle_ai_ability_flags {
    u32 word;
    struct {
        u8 flags_1;
        u8 flags_2;
        u8 flags_3;
        u8 flags_4;
    } bytes;
} battle_ai_ability_flags_t;

enum {
    BATTLE_AI_ABILITY_FLAG_1_TARGET_ENEMIES = 0x02, /* wiki page 00009373 */
    BATTLE_AI_ABILITY_FLAG_1_TARGET_ALLIES = 0x01,
};

/* Considered ability, base+0x00 (wiki page 00009373 "AI Ability Use Data"). */
typedef struct battle_ai_considered_ability {
    u8 skillset;                   /* 0x00; page 00010175 */
    u8 ct;                         /* 0x01; page 00004574 */
    s16 ability_id;                /* 0x02; page 00004555 reads lh, 00010175 lhu */
    u8 range;                      /* 0x04; page 00004561 */
    u8 aoe;                        /* 0x05; page 00004561 */
    u8 item_id;                    /* 0x06; page 00010175 */
    u8 status_infliction[5];       /* 0x07; page 00004571 */
    battle_ai_ability_flags_t ai_flags; /* 0x0c; pages 00004571, 00007518, 00000868 */
    u8 element;                    /* 0x10; page 00004571 */
    u8 mp_cost;                    /* 0x11; page 00000636 */
    u8 _pad12[2];
} battle_ai_considered_ability_t;

typedef char BattleAiConsideredAbility_size_must_be_0x14[(sizeof(battle_ai_considered_ability_t) == 0x14) ? 1 : -1];

/*
 * One considered/recorded action, 0x20 bytes.  The current action lives at
 * base+0x14, the best so far at +0x34, eight ranked outcomes at +0x54 (wiki
 * page 00003571 walks them with +0x20), the inverted-priority scratch at
 * +0x154 (00003562) and the selected action at +0x17fc (00000869, 00003572).
 */
typedef struct battle_ai_action_data {
    u8 target_flags_set; /* 0x00; page 00006799 sets 1 (00007017 disputes the name) */
    u8 _pad01[3];
    battle_ai_coords_t coords;     /* 0x04; pages 00003582, 00003583, 00007017 */
    u8 unit_id;                /* 0x08; page 00000804 "Acting Unit's ID" */
    u8 skillset;               /* 0x09; pages 00006799, 00010175 */
    u16 ability_id;            /* 0x0a; page 00010175 (sh) */
    u16 calculator_type;       /* 0x0c; page 00009373 */
    u16 calculator_multiplier; /* 0x0e; page 00009373 */
    u8 item_id;                /* 0x10; page 00010175 */
    u8 _pad11;
    u8 targeting_type; /* 0x12; pages 00009352, 00010175: 5 weapon, 6 follows unit */
    u8 target_id;      /* 0x13; page 00004563 */
    u16 target_x;      /* 0x14; page 00004563 (lhu) */
    u16 target_level;  /* 0x16; page 00004563 */
    u16 target_y;      /* 0x18; page 00004563 */
    u8 _pad1a[2];
    u8 mount_info;       /* 0x1c; page 00009373 */
    u8 base_hit_percent; /* 0x1d; pages 00004569, 00003572 */
    u16 priority;        /* 0x1e; pages 00003584, 00003583 */
} battle_ai_action_data_t;

typedef char BattleAiActionData_size_must_be_0x20[(sizeof(battle_ai_action_data_t) == 0x20) ? 1 : -1];

/* Unit AI ability list entry, 4 bytes, 0x22 per unit (wiki page 00009373). */
typedef struct battle_ai_ability_entry {
    u8 ability_id_low;   /* 0x00; low 8 bits of the ability/R/S/M/item id */
    u8 unit_and_id_high; /* 0x01; upper 6 bits unit id, low 2 bits id bits 9-10 */
    u8 skillset;         /* 0x02; 0xff terminates the list (chose_move_from_move_list) */
    u8 usage_flags;      /* 0x03; 0x80 usable, 0x40 allies only, 0x20 enemies only */
} battle_ai_ability_entry_t;

/*
 * Per-unit AI decision record, 0x10 bytes at base+0x182c (wiki page 00009373;
 * page 00000804 computes unit*16 + 0x182c).  g_ai_acting_unit_decision_ptr
 * points at the acting unit's record.
 */
typedef struct battle_ai_unit_decision {
    battle_ai_coords_t target; /* 0x00..0x03; page 00006771 (x, level, y, 0) */
    u8 flags;              /* 0x04; page 00003563, 00000636: 0x40 focus on target, 0x20 stay near, 0x10 aggressive, 0x08 coward */
    u8 main_target_id;     /* 0x05; page 00003564 */
    u8 targeting_flags_1;  /* 0x06; page 00000868: 0x08 charging, 0x04 most usable abilities */
    u8 targeting_flags_2;  /* 0x07; pages 00003568, 00003578: 0x80 critical, 0x40 dead w/ reraise, 0x20 dead, 0x10 untargetable */
    u8 enemy_flag;         /* 0x08; pages 00003564, 00003577, 00003584, 00004573, 00006764 */
    u8 highest_mp_cost;    /* 0x09; page 00000636 */
    u8 lowest_mp_cost;     /* 0x0a; pages 00000636, 00004571 */
    u8 mp_ability_mod;     /* 0x0b; page 00000636 */
    u8 silence_mod;        /* 0x0c; page 00004571 */
    u8 evade_mod;          /* 0x0d; pages 00004571, 00000636 */
    u8 lowest_range;       /* 0x0e; page 00000868 (+ unit move) */
    u8 highest_range;      /* 0x0f; page 00000868 (+ unit move) */
} battle_ai_unit_decision_t;

typedef char BattleAiUnitDecision_size_must_be_0x10[(sizeof(battle_ai_unit_decision_t) == 0x10) ? 1 : -1];

typedef struct battle_ai_data {
    battle_ai_considered_ability_t considered_ability; /* 0x0000 */
    battle_ai_action_data_t current_action;            /* 0x0014; pages 00003571, 00004566 */
    battle_ai_action_data_t best_action;               /* 0x0034; page 00004566 */
    battle_ai_action_data_t ranked_actions[8];         /* 0x0054; pages 00003571, 00003572 */
    battle_ai_action_data_t inverted_priority_action;  /* 0x0154; page 00003562 */
    u8 tile_foe_proximity[0x240];                 /* 0x0174; page 00003566 */
    u8 tile_target_distance[0x240];               /* 0x03b4; page 00003566 */
    u16 tile_priority[0x240];                     /* 0x05f4; page 00003566 */
    u16 reachable_tiles[3][0x24];                 /* 0x0a74; page 00003563, Y-row bitmaps per map level */
    u16 targetable_tiles[0x24];                   /* 0x0b4c; page 00004563 */
    u16 movable_tiles[0x24];                      /* 0x0b94; page 00004557 */
    u16 attack_origin_tiles[0x24];                /* 0x0bdc; page 00004563 */
    u16 walkable_tiles[0x24];                     /* 0x0c24; page 00007013 */
    u8 _pad0c6c;
    u8 initial_targeting_state; /* 0x0c6d; page 00004528 */
    u8 action_decided;          /* 0x0c6e; pages 00000869, 00003574 */
    u8 _pad0c6f;
    u8 outcome_evaluation_state; /* 0x0c70; page 00010175 */
    u8 movement_decision_state;  /* 0x0c71; page 00003563 */
    u8 can_move_to_target;       /* 0x0c72; pages 00003576, 00004563 */
    u8 _pad0c73;
    battle_ai_coords_t considered_unit_coords; /* 0x0c74; pages 00004561, 00009352 */
    u8 unit_active[0x15];                  /* 0x0c78; pages 00010175, 00009347 */
    u8 unit_targetable[0x15];              /* 0x0c8d; pages 00004573, 00004557, 00004570 */
    u8 unit_targetable_saved[0x10];        /* 0x0ca2; page 00010175 */
    u8 _pad0cb2[2];
    u32 target_setting_flags;         /* 0x0cb4; pages 00000868, 00006799, 00007044 */
    u16 total_hit_percent;            /* 0x0cb8; pages 00004569, 00003584 */
    u8 hit_counter;                   /* 0x0cba; pages 00004569, 00003584; 0xff = none */
    u8 attack_origin_tile_count;      /* 0x0cbb; page 00004557 */
    u8 movable_tile_count;            /* 0x0cbc; page 00004557 */
    u8 ability_counter;               /* 0x0cbd; page 00003573 */
    u8 ability_targets_enemies_or_mp; /* 0x0cbe; page 00000868 */
    u8 crystal_treasure_status;       /* 0x0cbf; page 00003582: 1 crystal, 2 treasure */
    u8 _pad0cc0[4];
    battle_ai_coords_t candidate_coords[3]; /* 0x0cc4; pages 00003563, 00004543, indexed by movement_scenario */
    u8 _pad0cd0[4];
    u8 unit_action_records[16][0x14]; /* 0x0cd4; page 00009373 */
    u16 throw_ability_id;             /* 0x0e14; pages 00000868, 00004548 */
    u8 throw_weapon_id;               /* 0x0e16; page 00000868 */
    u8 team_average_max_hp;           /* 0x0e17; page 00004548 */
    u8 unit_acts_before_me[0x14];     /* 0x0e18; page 00003584 */
    u8 _pad0e2c;
    u8 movement_scenario;                       /* 0x0e2d; pages 00003563, 00004529, 00004542: 0..2 */
    u8 acting_unit_id;                          /* 0x0e2e; page 00000804 */
    u8 acting_unit_battle_id;                   /* 0x0e2f; page 00000804 */
    battle_ai_coords_t acting_unit_coords;          /* 0x0e30; pages 00000804, 00007017 */
    battle_ai_unit_decision_t* acting_unit_decision; /* 0x0e34; pages 00000804, 00003563, 00003564 */
    u8 acting_unit_move;                        /* 0x0e38; page 00000804 */
    u8 acting_unit_team;                        /* 0x0e39; page 00000804 */
    u8 map_max_x;                               /* 0x0e3a; pages 00006768, 00004548 */
    u8 map_max_y;                               /* 0x0e3b; pages 00004533, 00004548 */
    u8 team_golem[8];                           /* 0x0e3c; page 00009373 */
    u8 status_to_cancel[5];                     /* 0x0e44; page 00000868 */
    u8 _pad0e49[3];
    u8 ability_effect_on_self;           /* 0x0e4c; page 00010175: 0 none, 1 usable, 2 adverse */
    u8 weapon_range_flag;                /* 0x0e4d; page 00003584 */
    u8 useful_on_caster_flag;            /* 0x0e4e; page 00003584 */
    u8 acting_unit_remaining_clockticks; /* 0x0e4f; pages 00000804, 00003577, 00000868 */
    u8 unit_status_records[16][8];       /* 0x0e50; page 00009373 */
    u8 saved_ability_ct;                 /* 0x0ed0; page 00007017 */
    u8 saved_current_status;             /* 0x0ed1; page 00007017 */
    u8 saved_inflicted_status;           /* 0x0ed2; page 00007017 */
    u8 _pad0ed3;
    u8 main_ai_state;             /* 0x0ed4; page 00000866 */
    u8 autobattle_state;          /* 0x0ed5; page 00004529 */
    u8 charging_state;            /* 0x0ed6; page 00007017 */
    u8 find_highest_target_state; /* 0x0ed7; not annotated in the wiki; check_if_map_allows_use_and_find_highest_target's progress variable */
    u8 _pad0ed8;
    u8 highest_priority_state; /* 0x0ed9; page 00004557 */
    u8 max_possibilities;      /* 0x0eda; page 00004557 */
    u8 y_counter;              /* 0x0edb; page 00004557 */
    u8 map_level_counter;      /* 0x0edc; page 00004557 */
    u8 _pad0edd[0x11];
    u8 progress_0eee; /* 0x0eee; page 00009373 */
    u8 _pad0eef;
    battle_ai_ability_entry_t ability_lists[16][0x22]; /* 0x0ef0; page 00009373, 0x88 bytes per unit */
    u16 hardcoded_status_abilities[3];            /* 0x1770; page 00004548: blood suck, frog, berserk */
    u8 _pad1776[2];
    u8 unit_weapon_data[16][8];         /* 0x1778; pages 00000627, 00000640 */
    battle_stats_t* acting_unit;           /* 0x17f8; page 00000804 */
    battle_ai_action_data_t selected_action; /* 0x17fc; pages 00000869, 00004529, 00003572 */
    u8 table_181c[3];                   /* 0x181c; page 00004548, 0xff filled */
    u8 _pad181f[0xd];
    battle_ai_unit_decision_t unit_decisions[0x15]; /* 0x182c; pages 00000804, 00009373 */
    u8 _pad197c[0x10];
    u8 unit_battle_ids[0x15];   /* 0x198c; pages 00009373, 00000627 */
    u8 unit_behaviour[0x15];    /* 0x19a1; page 00000636: 0x11 coward, 0x0e/0x0c aggressive */
    u8 autobattle_setting;      /* 0x19b6; pages 00007045, 00004535 */
    u8 decision_state;          /* 0x19b7; pages 00003563, 00003576, 00004548, 00004542 */
    u8 random_hits_mod;         /* 0x19b8; page 00010175 */
    u8 water_penalty;           /* 0x19b9; page 00007013 */
    u8 valuable_target_hit;     /* 0x19ba; page 00004569 (00009373: "0 if base hit = FF") */
    u8 targetable_override;     /* 0x19bb; pages 00007044, 00007045 */
    u8 ability_processing_done; /* 0x19bc; page 00004569 */
    u8 action_taken;            /* 0x19bd; page 00009373 */
    u8 movement_taken;          /* 0x19be; page 00009373 */
    u8 _pad19bf[8];
    u8 field_19c7; /* 0x19c7; page 00009373, last documented byte */
} battle_ai_data_t;

typedef char BattleAiData_size_must_be_0x19c8[(sizeof(battle_ai_data_t) == 0x19c8) ? 1 : -1];

#endif
