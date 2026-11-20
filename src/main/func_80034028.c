#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s16 x;
    /* 0x12 */ s16 y;
    /* 0x14 */ u8 unk_14[0x30];
    /* 0x44 */ s32 unk_44;
} Sprite;

typedef struct {
    /* 0x00 */ Sprite *sprite;
    /* 0x04 */ s32 frame;
    /* 0x08 */ s32 timer;
    /* 0x0C */ u8 unk_0C[0x4];
    /* 0x10 */ s32 count;
    /* 0x14 */ f32 x;
    /* 0x18 */ f32 y;
    /* 0x1C */ f32 vx;
    /* 0x20 */ f32 vy;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ State *state;
} Task;

struct n64dk_r12 func_80034028(s32 arg1) {
    struct n64dk_r12 ret;
    s32 event;
    s32 i;
    Sprite *sprite;

    sprite = ((Task *)arg1)->state->sprite;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            ((Task *)arg1)->state->timer = 0;
            ((Task *)arg1)->state->frame = 0;
            break;
        }
    }
    ((Task *)arg1)->state->timer += D_800B96B4;
    if (((Task *)arg1)->state->timer >= 4) {
        ((Task *)arg1)->state->timer %= 4;
        ((Task *)arg1)->state->frame++;
        if (((Task *)arg1)->state->frame >= 4) {
            ((Task *)arg1)->state->frame = 0;
            ((Task *)arg1)->state->count--;
            if (((Task *)arg1)->state->count < 0) {
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            }
        }
    }
    i = 0;
    while (i < D_800B96B4) {
        ((Task *)arg1)->state->vy += D_8005C958;
        ((Task *)arg1)->state->vx -= D_8005C95C;
        ((Task *)arg1)->state->x += ((Task *)arg1)->state->vx;
        ((Task *)arg1)->state->y += ((Task *)arg1)->state->vy;
        i++;
    }
    sprite->x = (s32)((Task *)arg1)->state->x;
    sprite->y = (s32)((Task *)arg1)->state->y;
    if (sprite->x < 0 || sprite->y < 0 || sprite->x >= 321 || sprite->y >= 201) {
        ret.w[1] = 0;
        ret.w[0] = 1;
        return ret;
    }
    sprite->unk_44 = D_8005C948[((Task *)arg1)->state->frame];
    ret.w[1] = 1;
    ret.w[0] = 0;
    return ret;
}
