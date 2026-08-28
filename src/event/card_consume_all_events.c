extern void card_consume_bios_events(void);
extern void card_consume_hardware_events(void);

void card_consume_all_events(void) {
    card_consume_bios_events();
    card_consume_hardware_events();
}
