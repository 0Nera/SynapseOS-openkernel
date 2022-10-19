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
if 0:
    DEBUG_FLAGS = "-ggdb -DDEBUG=1"
CC_FLAGS = f"-fno-builtin -fno-stack-protector -ffreestanding {DEBUG_FLAGS} -Wall -Wextra -O0 -I include// -c "
LD_FLAGS = f"-T src//arch//{ARCH}//link.ld -nostdlib -O0 "


''' Сборка ядра '''
def build_kernel():
    print("Сборка ядра")

    files = glob.glob("src//kernel//**//*.c", recursive=True) + \
        glob.glob(f"src//arch//{ARCH}//**//*.s", recursive=True) + \
        glob.glob(f"src//arch//{ARCH}//**//*.c", recursive=True)

    for i in range(len(files)):
        SRC_TARGETS.append(files[i])
        BIN_TARGETS.append(os.path.join("bin//kernel//", os.path.basename(SRC_TARGETS[i]) + '.o '  ))
    print(SRC_TARGETS)
    print(BIN_TARGETS)
    shutil.rmtree("bin", ignore_errors=True)

    if not os.path.exists("bin//"):
        os.mkdir("bin//")

    if not os.path.exists("bin//kernel//"):
        os.mkdir("bin//kernel//")

    for i in range(0, len(SRC_TARGETS)):
        os.system(f"{CC} {DEBUG_FLAGS} {CC_FLAGS} {SRC_TARGETS[i]} -o {BIN_TARGETS[i]}")
        print(f"{CC} {CC_FLAGS} {SRC_TARGETS[i]} -o {BIN_TARGETS[i]}")

    print(f"{CC} {LD_FLAGS} -o isodir//boot//kernel.elf {' '.join(str(x) for x in BIN_TARGETS)}")
    os.system(f"{CC} {LD_FLAGS} -o isodir//boot//kernel.elf {' '.join(str(x) for x in BIN_TARGETS)}")


''' Генерация документации '''
def build_docs():
    print("Генерация документации")

    os.system("doxygen scripts//Doxyfile")


''' Сборка модулей '''
def build_modules():
    pass


''' Сборка драйверов '''
def build_drivers():
    pass


''' Сборка программ '''
def build_programms():
    pass


''' Сборка ISO limine '''
def build_iso_limine():
    print("Сборка ISO limine")
    
    os.system("""xorriso -as mkisofs -b limine-cd.bin \
          -no-emul-boot -boot-load-size 4 -boot-info-table \
          --efi-boot limine-cd-efi.bin \
          -efi-boot-part --efi-boot-image --protective-msdos-label \
          isodir -o SynapseOS-limine.iso""")
    
    os.system("limine-deploy SynapseOS-limine.iso")
    
    #print(f"Сборка ISO//Limine образа заняла: {(time.time() - start_time):2f} сек.")


''' Сборка ISO grub legasy bios'''
def build_iso_grub_bios():
    pass


''' Сборка ISO grub EFI'''
def build_iso_grub_efi():
    pass


if __name__ == '__main__':
    build_kernel()
    
    build_iso_limine()

    #build_docs()

    os.system("qemu-system-i386 -cdrom SynapseOS-limine.iso -serial file:serial.log")