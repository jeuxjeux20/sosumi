#include "../io.h"
#include "../main.h"
#include "string.h"
#include "stdbool.h"
#include "stdint.h"
unsigned char keymapqwertz[] = 
{
/*
Qwerty with y and z swapped
*/
    0, 27,
          '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, /* control here? */
          'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, /* left shift */
    '\\',
          'y', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
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
unsigned char keymapazerty[] =
{
    0, 27,
          '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, /* control here? */
          'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, /* left shift */
    '\\',
          'w', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
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
unsigned char keymapqwerty[] =
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


char getChar()
{
    unsigned char scancode;
    
    getchar_tryagain:
    scancode = inb(0x60);
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
/*
alias
*/
char getC() {
    getChar()
}

static bool print(const char* data, size_t length) {
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		if (vidPutchar(bytes[i]) == EOF)
			return false;
	return true;
}
int printf(const char* a) {
    print(a, sizeof(a))
	return 1;
}
 
