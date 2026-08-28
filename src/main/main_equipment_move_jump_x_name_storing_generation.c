extern void equipment_stat_setting(void* unit);
extern void equipment_attribute_setting(void* unit, int mode);
extern void move_jump_x_calculation(void* unit, int mode);
extern void store_generate_character_names(void* unit);

void main_equipment_move_jump_x_name_storing_generation(void* unit) {
    equipment_stat_setting(unit);
    equipment_attribute_setting(unit, 1);
    move_jump_x_calculation(unit, 0);
    store_generate_character_names(unit);
}
