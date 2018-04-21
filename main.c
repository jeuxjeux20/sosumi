/* main.c - the basic initializer for the esokernel
 * 
 * Copyright (c) 2006 Gregor Richards
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "brainfuck.h"
#include "dev.h"
#include "multiboot.h"

#define COLS 80
#define ROWS 24
#define VIDEO 0xB8000
#define BLANKATTR 7
#define NULL ((void *) 0)

void vidPutchar(char p);
char kbGetchar();

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

unsigned char keymap[] =
{
    0, 27,
          '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, /* control here? */
          'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, /* left shift */
    '\\',
          'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    0, /* right shift */
    '*',
    0, /* alt */
    ' ',
    0, /* caps lock */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* F1-10 */
    0, /* num lock */
    0, /* scroll lock */
    0, /* home */
    0, /* up */
    0, /* pgup */
    '-',
    0, /* left */
    0,
    0, /* right */
    '+',
    0, /* end */
    0, /* down */
    0, /* pgdown */
    0, /* insert */
    0, /* delete */
    0, 0, 0,
    0, 0, /* F11-12 */
    0
};

/* a simple getchar */
char kbGetchar()
{
    unsigned char scancode;
    
    getchar_tryagain:
    scancode = inportb(0x60);
    if (scancode & 0x80) {
        /* just released the key - ignored ATM */
        goto getchar_tryagain;
    } else {
        /* convert it to a character */
        char cret;
        cret = keymap[scancode];
        /* ignore null */
        if (!cret) goto getchar_tryagain;
        
        return cret;
    }
}
