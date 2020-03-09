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

def write(b, large = False):
    i = b
    if type(i) is int:
        if large == True:
            i = i.to_bytes(2, byteorder='little', signed=False) # if integer, large integer
        else:
            i = i.to_bytes(1, byteorder='little', signed=False) # if integer, treat it as a single byte since max value is 255

    if type(i) is str:
        i = i.encode()           # if string, encode to bytes-like

    binout.write(bytes(i))

write("TMF") # "Magic Number" (header)

for i in sprs.getpalette():
    write(i) # write palette data to file

write(sprs.width, True)  # write width and height values
write(sprs.height, True)

for i in sprs.getdata():
    write(chr(i)) # write every pixel (one byte each for 256 color)

sprs.close()
binout.close()
