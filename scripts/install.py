#!/usr/bin/python3
# -*- coding: utf-8 -*-
from sys import platform
import urllib.request
import os
import zipfile
import shutil


''' Установка зависимостей '''
def install():
    if platform == "linux" or platform == "linux2":
        print("Установка xorriso")
        os.system("sudo apt install xorriso")

        print("Установка limine")
        os.system("git clone https://github.com/limine-bootloader/limine.git --branch=v4.x-branch-binary --depth=1")
        os.system("make -C limine")
    elif platform == "darwin":
        return -1 
    elif platform == "win32":
        print("Установка xorriso")
        urllib.request.urlretrieve("https://github.com/PeyTy/xorriso-exe-for-windows/archive/master.zip", "xorriso.zip")

        with zipfile.ZipFile("xorriso.zip", 'r') as zip_ref:
            zip_ref.extractall(".")
        get_files = os.listdir("xorriso-exe-for-windows-master")

        print("Установка limine")
        os.system("git clone https://github.com/limine-bootloader/limine.git --branch=v4.x-branch-binary --depth=1")
        os.system("make -C limine")


if __name__ == '__main__':
    install()