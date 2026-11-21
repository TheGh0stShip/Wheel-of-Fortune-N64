// DrawImage.c -- draws a picture where it is

#include "wof.h"

/*
=====================
DrawImage

Draws a picture where it is.
=====================
*/
void DrawImage(image_t *image, s32 lit) {
    DrawImageAt(image, lit, 0, 0);
}
