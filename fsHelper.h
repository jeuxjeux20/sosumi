extern inline unsigned char get_fs_byte(const char * addr)
extern inline unsigned short get_fs_word(const unsigned short *addr)
extern inline unsigned long get_fs_long(const unsigned long *addr)
extern inline void put_fs_byte(char val,char *addr)
extern inline void put_fs_word(short val,short * addr)
extern inline void put_fs_long(unsigned long val,unsigned long * addr)
extern inline void memcpy_tofs(void * to, void * from, unsigned long n)
extern inline void memcpy_fromfs(void * to, void * from, unsigned long n)
/*
 * Someone who knows GNU asm better than I should double check the followig.
 * It seems to work, but I don't know if I'm doing something subtly wrong.
 * --- TYT, 11/24/91
 * [ nothing wrong here, Linus: I just changed the ax to be any reg ]
 */
 extern inline unsigned long get_fs() 
 extern inline unsigned long get_ds()
 extern inline void set_fs(unsigned long val)
