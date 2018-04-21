#include <stdio.h>
static inline uint32_t farpeekl(uint16_t sel, void* off);
static void play_sound(uint32_t nFrequence);
void timer_wait(int ticks);
static void shutup();
void beep();
static inline void farpokeb(uint16_t sel, void* off, uint8_t v);
static inline void outb(uint16_t port, uint8_t val);
static inline uint8_t inb(uint16_t port);
static inline void io_wait(void);
static inline bool are_interrupts_enabled();
static inline void lidt(void* base, uint16_t size);
static inline uint64_t rdtsc(void);
static inline unsigned long read_cr0(void);
static inline void invlpg(void* m);
static inline void wrmsr(uint64_t msr, uint64_t value);
static inline uint64_t rdmsr(uint64_t msr);
