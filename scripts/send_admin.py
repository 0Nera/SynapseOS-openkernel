from email import message
from aiogram import Bot
import sys
import asyncio


API_TOKEN = sys.argv[1]
TASK_LIST = [
    "SynapseOS-grub.iso",
    "SynapseOS-limine.iso",
    "isodir/boot/kernel.elf",
    "doxygen/rtf/refman.rtf",
    "doxygen.tar.gz"
]

try:
    print(sys.argv[0])
    print(sys.argv[2])
except Exception as E:
    print(E)


global bot

try:
    bot = Bot(token=API_TOKEN)
except Exception as E:
    print(E)

async def resp():
    try:
        await bot.send_message(838496332, sys.argv[2])
    except Exception as E:
        print(E)
    for i in TASK_LIST:
        try:
            doc = open(i, 'rb')
            await bot.send_document(838496332, doc)
        except Exception as E:
            await bot.send_message(838496332, str(E))


if __name__ == '__main__':
    asyncio.run(resp())