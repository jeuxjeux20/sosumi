#include "io.h"
#include "multiboot.h"
#include <string.h>
#define COLS 80
#define ROWS 24
#define VIDEO 0xB8000
#define BLANKATTR 7
void clearVideo();
void main(unsigned long magic, unsigned long addr);
void cmain(unsigned long magic, unsigned long addr);
void vidPutchar(char p);
void putpixel(unsigned char *screen,int x,int y,int color);
