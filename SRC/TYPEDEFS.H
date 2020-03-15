#ifndef TYPEDEFS_H
#define TYPEDEFS_H

typedef unsigned char  byte;
typedef unsigned short word;

struct Image {
    char* data;
    char* palette;
    word width;
    word height;
};

#endif