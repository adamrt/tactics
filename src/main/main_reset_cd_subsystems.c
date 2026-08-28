extern void CdReset(int mode);

void main_reset_cd_subsystems(void) {
    CdReset(0);
}
