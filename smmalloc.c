#ifndef SMMALLOC_HERE
#define SMMALLOC_HERE

#define SMMALLOC_BLOCK_COUNT_MAX 512
int SMMALLOC_BLOCK_CURRECT = -1;
void *SMMALLOC_BLOCKS [SMMALLOC_BLOCK_COUNT_MAX]; // blocks are separated memory blocks


void _zero_all_blocks (int forceUnsafe) {
    for (int i=0; i<SMMALLOC_BLOCK_COUNT_MAX; ++i) {
        if (forceUnsafe == 0 && SMMALLOC_BLOCKS[i] != 0) {
            free(SMMALLOC_BLOCKS[i]);
        }
        SMMALLOC_BLOCKS[i] = 0;
    }
    SMMALLOC_BLOCK_CURRECT = 0;
}

void _prepare_blocks (void) {
    if (SMMALLOC_BLOCK_CURRECT < 0) {
        _zero_all_blocks(1);
    }
    if (SMMALLOC_BLOCK_CURRECT >= SMMALLOC_BLOCK_COUNT_MAX) {
        SMMALLOC_BLOCK_CURRECT = 0;
    }
}

void* smmalloc (size_t size) { // implementation with named blocks is also possible, but common unnamed is here
    _prepare_blocks();
    if (SMMALLOC_BLOCKS[SMMALLOC_BLOCK_CURRECT] != 0) { // warning: unsafe reusing of memory
        free(SMMALLOC_BLOCKS[SMMALLOC_BLOCK_CURRECT]);
        SMMALLOC_BLOCKS[SMMALLOC_BLOCK_CURRECT] = 0;
    }
    return SMMALLOC_BLOCKS[SMMALLOC_BLOCK_CURRECT++] = malloc(size);
}

void smfreeall (void) {
    _prepare_blocks();
    _zero_all_blocks(0);
}

#endif
