#!/bin/bash

ARCH="i686"
CC="${ARCH}-elf-gcc"
CC_FLAGS="-fno-builtin -fno-stack-protector -ffreestanding -Wall -Wextra -O0 -I include/ -c"
LD_FLAGS="-T src/arch/${ARCH}/link.ld -nostdlib -O0"

mkdir -p bin/kernel

declare -a SRC_TARGETS
declare -a BIN_TARGETS

# *.c
for file in $(find src/ -type f -name "*c")
do
	SRC_TARGETS+=($file)
done

# *.s
for file in $(find src/ -type f -name "*s"); do
	SRC_TARGETS+=($file)
done

for i in ${!SRC_TARGETS[@]}; do
	file=$( basename ${SRC_TARGETS[$i]} )
	${CC} ${CC_FLAGS} ${SRC_TARGETS[$i]} -o bin/kernel/${file}.o
done

for file in $(find bin/kernel/ -type f -name "*o"); do
	BIN_TARGETS+=($file)
done

${CC} ${LD_FLAGS} -o isodir/boot/kernel.elf ${BIN_TARGETS[@]}

xorriso -as mkisofs -b limine-cd.bin \
          -no-emul-boot -boot-load-size 4 -boot-info-table \
          --efi-boot limine-cd-efi.bin \
          -efi-boot-part --efi-boot-image --protective-msdos-label \
          isodir -o SynapseOS-limine.iso

qemu-system-i386 -cdrom SynapseOS-limine.iso -serial file:serial.log
