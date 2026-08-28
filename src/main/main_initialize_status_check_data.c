typedef unsigned char u8;

extern void main_clear_byte_data(u8*, int);
extern u8 found[0x80];
extern u8 checks[11][5];
extern u8 properties[];

void main_initialize_status_check_data(void) {
    int status;
    int offset;
    u8 flags4;
    u8 flags5;
    int byte;
    u8 mask;

    main_clear_byte_data(found, 0x80);
    main_clear_byte_data(&checks[0][0], 0x37);
    status = 0;
    offset = 0;
    do {
        flags4 = properties[offset];
        flags5 = properties[offset + 1];
        byte = status / 8;
        mask = 0x80 >> (status & 7);
        if (flags4 & 1)
            checks[0][byte] |= mask;
        if (flags4 & 2)
            checks[1][byte] |= mask;
        if (flags4 & 4)
            checks[2][byte] |= mask;
        if (flags4 & 0x80)
            checks[3][byte] |= mask;
        if (flags5 & 0x80)
            checks[4][byte] |= mask;
        if (flags5 & 1)
            checks[5][byte] |= mask;
        if (flags5 & 2)
            checks[6][byte] |= mask;
        if (flags5 & 4)
            checks[7][byte] |= mask;
        if (flags5 & 8)
            checks[8][byte] |= mask;
        if (flags5 & 0x10)
            checks[9][byte] |= mask;
        offset += 0x10;
        status++;
    } while (status < 40);
    checks[10][0] = 0x60;
    checks[10][1] = 0x85;
    checks[10][2] = 0x0e;
    checks[10][4] = 0x20;
}
