extern int build_file_header(void*, int, int, void*, int);

int main_build_file_header_nnl(void* header, int sector, int sectors,
    void* destination) {
    return build_file_header(header, sector, sectors, destination, -1);
}
