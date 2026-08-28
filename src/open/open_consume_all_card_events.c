extern void open_consume_bios_card_events(void);
extern void open_consume_hardware_card_events(void);

void open_consume_all_card_events(void) {
    open_consume_bios_card_events();
    open_consume_hardware_card_events();
}
