QEMU_FLAGS = -m 1024M -sd image.bin -M vexpress-a9
CC = gcc-arm-none-eabi
C_FLAGS = -Wall -Wextra -pedantic 

all: run

run: image.bin
	qemu-system-arm ${QEMU_FLAGS}
