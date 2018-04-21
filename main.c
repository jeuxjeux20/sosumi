#include "io.h"
#include "multiboot.h"
#include <string.h>
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

//use screen as (unsigned char *) VIDEO by casting to it x)
void putpixel(unsigned char *screen,int x,int y,int color){
	memset((char *)screen,color,(320 * 200));
	unsigned pos = y * 320 + x * 80;
	memset(screen, + (y *320 + 80) +x,160);
	int pos = x + y * 320;
	screen[pos] = color & 255;
	screen[pos] = (color >> 8) & 255;
	screen[pos + 2] = (color >> 16) & 255;
}
