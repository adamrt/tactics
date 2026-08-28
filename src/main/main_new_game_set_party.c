enum {
    NEW_GAME_GENERATE_DEFAULT_UNIT = 0,
    NEW_GAME_LOAD_EVENT_PARTY = 2,
    STARTING_UNIT_ID = 2,
    STARTING_EVENT_ID = 0xfe,
    SCRIPT_VARIABLE_WAR_FUNDS = 0x2c,
    STARTING_WAR_FUNDS = 2000,
};

extern void initialize_world_new_game(int mode);
extern void main_clear_party(void);
extern void generate_party_unit_in_empty_slot(int unit_id);
extern void main_event_start_initialize_unit_data(int event_id);
extern void main_new_game_set_inventory(void);
extern void set_script_variable(int variable_id, int value);

void main_new_game_set_party(int mode) {
    initialize_world_new_game(mode);
    main_clear_party();

    if (mode == NEW_GAME_GENERATE_DEFAULT_UNIT) {
        generate_party_unit_in_empty_slot(STARTING_UNIT_ID);
    } else if (mode == NEW_GAME_LOAD_EVENT_PARTY) {
        main_event_start_initialize_unit_data(STARTING_EVENT_ID);
    }

    main_new_game_set_inventory();
    set_script_variable(SCRIPT_VARIABLE_WAR_FUNDS, STARTING_WAR_FUNDS);
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
