#include "psx/types.h"

typedef struct HeapNode {
    struct HeapNode* next;
    u16 size;
    u16 owner;
} HeapNode;

typedef struct HeapList {
    HeapNode* head;
    s32 unk4;
} HeapList;

extern HeapNode* D_801B69A8;
extern HeapList D_801B8968[];

void* battle_heap_allocate_block(u32 size, s32 kind) {
    HeapNode* prev;
    HeapNode* node;
    u32 blocks;

    blocks = (size + 15) >> 3;
    prev = D_801B69A8;
    node = prev->next;
    for (;;) {
        if (node->size >= blocks) {
            if (node->size == blocks) {
                prev->next = node->next;
            } else {
                node->size = node->size - blocks;
                node = (HeapNode*)((u8*)node + node->size * 8);
                node->size = blocks;
            }
            node->owner = kind;
            node->next = D_801B8968[kind].head;
            D_801B69A8 = prev;
            D_801B8968[kind].head = node;
            return node + 1;
        } else {
            prev = node;
            node = node->next;
        }
    }
}
