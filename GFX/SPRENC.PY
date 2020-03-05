#!/usr/bin/env python3

########################################
### PROJECT "THE MAN": IMAGE ENCODER ###
###         STINKY GAMES 2020        ###
########################################
### This file expects a paletted 256-###
### color PNG as input, and outputs a###
### .TMF file. Set the `f` variable  ###
### to change the .PNG it converts,  ###
### as of writing this comment, it's ###
### default is set to "BG", to take  ###
### "BG.PNG" as input and output to  ###
### "BG.TMF".                        ###
########################################

from PIL import Image

f = "BG"

sprs = Image.open(f+".PNG")
binout = open(f+".TMF", "wb")

def write(b):
    print("writing",b)
    i = b
    if type(i) is int: i = i.to_bytes(2, 'big') # if integer, convert to 2-byte integer
    if type(i) is str: i = i.encode()           # if string, encode to bytes-like
    binout.write(bytes(i))

write("TMF") # "Magic Number" (header)

write("\00T\00PAL'D-IMG") # TYPE "PALetteD-IMaGe"

write("\00P\00") # PALETTE
write(sprs.palette.getdata()[1]) # write palette data to file

write("\00S\00") # SIZE
write(sprs.width)  # write width and height values
write(sprs.height)

write("\00D\00") # DATA
write(sprs.getdata()) # write every pixel (one byte each for 256 color)

sprs.close()
binout.close()
