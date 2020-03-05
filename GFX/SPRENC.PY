#!/usr/bin/env python3

### PROJECT "THE MAN": IMAGE ENCODER ###
###         STINKY GAMES 2020        ###

from PIL import Image

sprs = Image.open("SPRITES.PNG")
binout = open("SPRITES.TMF", "wb")

def write(b):
    print("writing",b)
    i = b
    if type(i) is int: i = i.to_bytes(2, 'big')
    if type(i) is str: i = i.encode()
    binout.write(bytes(i))

write("TMF")

write("\00T\00PAL'D-IMG") # TYPE "PALetteD-IMaGe"

write("\00P\00") # PALETTE
write(sprs.palette.getdata()[1])

write("\00S\00") # SIZE
write(sprs.width)
write(sprs.height)

write("\00D\00") # DATA
write(sprs.getdata())

sprs.close()
binout.close()