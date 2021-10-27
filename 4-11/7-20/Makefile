CFLAGS := -S
# CFLAGS += -Wall
# CFLAGS := -save-temps
save-cflags := $(CFLAGS)
# This is deplicated
# EXTRA_CFLAGS += -S
# cflags-y := -S

# CFILES = sample.c
# EXTRA_CFLAGS = -Wall -g
obj-m := sample.o
# EXTRA_CFLAGS+= -save-temps
# ccflags-y = -save-temps
# sample-y := -S
# CFLAGS_sample.o := -S
# ccflags-y := -O2
# sample-objs := $(CFILES:.c=.S)
# https://stackoverflow.com/questions/448910/what-is-the-difference-between-the-gnu-makefile-variable-assignments-a
# ccflags-y += -S
# https://www.kernel.org/doc/Documentation/kbuild/modules.txt
# KBUILD_AFLAGS := -D__ASSEMBLY__
# KBUILD_CFLAGS := -S
# sample: sample.c
# 	gcc -S -Wall sample.c
# obj-m := sample.S
# asflags-y := -ansi
# CFLAGS_sample.o = -s
# EXTRA_CFLAGS := -S -save-temps
# EXTRA_CFLAGS+= -S -save-temps
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
