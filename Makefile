CC=gcc
CFLAGS=-O2 -g -I/libc/ -nostdlib
ASFLAGS=
LD=ld
LDBASEFLAGS=-Ttext 100000 -nostdlib
LDFLAGS=

OBJS=\
 boot.o \
 io.o \
 main.o

all: kernel

kernel: $(OBJS)
	$(LD) $(LDBASEFLAGS) $(LDFLAGS) $(OBJS) -o kernel

.SUFFIXES: .c .S .o

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.S.o:
	$(CC) $(ASFLAGS) -c $< -o $@

clean:
	rm -f *.o kernel image
	-rmdir mnt

install: image

image: kernel grub-kernel.img
	cp -f grub-kernel.img image
	-mkdir mnt
	mount -o loop image mnt
	cp -f kernel mnt
	umount mnt
