QEMU_FLAGS = -m 1024M
CC = gcc-arm-none-eabi
C_FLAGS = -Wall -Wextra -pedantic 

all: run

run: image.bin
	qemu-system-arm ${QEMU_FLAGS}
