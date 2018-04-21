#include "io.h"
#include "multiboot.h"

#define COLS 80
#define ROWS 24
#define VIDEO 0xB8000
#define BLANKATTR 7
#define NULL ((void *) 0)

void vidPutchar(char p);

void clearVideo() {
	for (i = (char *) VIDEO;
         i < (char *) VIDEO + COLS * ROWS * 2;
         i++) {
        *i = 0;
    }
}
void main(unsigned long magic, unsigned long addr) {
}
void writeCharacter(unsigned char c, unsigned char forecolour, unsigned char backcolour, int x, int y)
{
     uint16_t attrib = (backcolour << 4) | (forecolour & 0x0F);
     volatile uint16_t * where;
     where = (volatile uint16_t *)0xB8000 + (y * 80 + x) ;
     *where = c | (attrib << 8);
}
/* main multiboot entrance */
void cmain(unsigned long magic, unsigned long addr)
{
    multiboot_info_t *mbi;
    memory_map_t *mmap;
    void *heap;
    unsigned long heapSize;
    char *i;
    
    mbi = (multiboot_info_t *) addr;
    
    /* get our heap by simply finding the largest available space (lame) */
    heap = NULL;
    heapSize = 0;
    for (mmap = (memory_map_t *) mbi->mmap_addr;
         (unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length;
         mmap = (memory_map_t *)((unsigned long) mmap + 
                                 mmap->size +
                                 sizeof(mmap->size))) {
         if (mmap->type == 1 &&
             mmap->length_low > heapSize) {
             heap = (void *) mmap->base_addr_low;
             heapSize = mmap->length_low;
         }
    }
    
    /* clear out video */
    clearVideo();
    
    /* start our BF interp */
    main(magic, addr);
}

/* a ridiculously simple putchar */
void vidPutchar(char p)
{
    static int pcloc = 0;
    
    char *pchar = (char *) VIDEO + pcloc * 2;
    *pchar = p;
    *(pchar + 1) = BLANKATTR;
    
    pcloc++;
    if (pcloc >= COLS * ROWS) pcloc = 0; // stupid
}

