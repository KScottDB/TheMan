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

def write(b, big=False):
    i = b
    if type(i) is list or type(i) is tuple:
        write(len(i), True)
        for j in i: write(j, big)
        return

    print("Writing",b)
    if type(i) is int:
        if big:
            i = i.to_bytes(2, byteorder='little', signed=False) # if integer, larg
        else:
            i = i.to_bytes(1, byteorder='little', signed=False)

    if type(i) is str:
        i = i.encode()           # if string, encode to bytes-like

    binout.write(bytes(i))

write("TMF\0") # "Magic Number" (header)

write( sprs.getpalette(), False ) # write palette data to file

write(sprs.width, True)  # write width and height values
write(sprs.height, True)

write( sprs.getdata(), False ) # write every pixel (one byte each for 256 color)

sprs.close()
binout.close()
