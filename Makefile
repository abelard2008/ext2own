#
# Makefile for the linux ext2-filesystem routines.
#

obj-m += ext2.o

ext2-objs := balloc.o dir.o file.o ialloc.o inode.o \
	  ioctl.o namei.o super.o symlink.o

ext2-m += xattr_user.o xattr_trusted.o

all: ko 

ko:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


