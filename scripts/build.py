#!/usr/bin/python3
# -*- coding: utf-8 -*-
import os
import glob
import shutil


SRC_TARGETS = []
BIN_TARGETS = []
ARCH = "i686" # "x86_64", "arm", "e2k"
CC = f"{ARCH}-elf-gcc"
DEBUG_FLAGS = ""
if 1:
    DEBUG_FLAGS = "-ggdb -DDEBUG=1"
CC_FLAGS = f"-fno-builtin -fno-stack-protector -ffreestanding {DEBUG_FLAGS} -Wall -Wextra -w  -O0 -I include/ -c "
LD_FLAGS = f"-T src/arch/{ARCH}/link.ld -nostdlib -O0 -ggdb -lgcc "


''' Сборка ядра '''
def build_kernel():
    files = glob.glob(f"src/arch/{ARCH}/**/*.s", recursive=True) + \
        glob.glob("src/**/*.c", recursive=True) + \
        glob.glob(f"src/arch/{ARCH}/**/*.c", recursive=True)

    for i in range(len(files)):
        SRC_TARGETS.append(files[i])
        BIN_TARGETS.append(os.path.join("bin/kernel/", os.path.basename(SRC_TARGETS[i]) + '.o '  ))
    shutil.rmtree("bin", ignore_errors=True)
    os.mkdir("bin")
    os.mkdir("bin/kernel")

    for i in range(0, len(SRC_TARGETS)):
        os.system(f"{CC} {DEBUG_FLAGS} {CC_FLAGS} {SRC_TARGETS[i]} -o {BIN_TARGETS[i]}")
        print(f"{CC} {CC_FLAGS} {SRC_TARGETS[i]} -o {BIN_TARGETS[i]}")
    #print(f"{CC} {LD_FLAGS} -o isodir/boot/kernel.elf {' '.join(str(x) for x in BIN_TARGETS)}")
    os.system(f"{CC} {LD_FLAGS} -o isodir/boot/kernel.elf {' '.join(str(x) for x in BIN_TARGETS)}")


''' Сборка документации '''
def build_docs():
    os.system("doxygen scripts/Doxyfile")


''' Сборка модулей '''
def build_modules():
    pass


''' Сборка драйверов '''
def build_drivers():
    pass


''' Сборка программ '''
def build_programms():
    pass


if __name__ == '__main__':
    build_kernel()
    build_docs()