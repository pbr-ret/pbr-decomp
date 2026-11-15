#pragma once

#include <revolution/types.h>

struct Unk80250F18;
typedef void (*Unk80250F18Callback)(Unk80250F18 *obj);

struct Unk80250F18_04 {
    /* 0x00 */ u8 unk00[0xE];
    /* 0x0E */ u16 _0E;
    /* 0x10 */ u8 unk10[0x1C];
    // size: 0x2C
};

struct Unk80250F18_08 {
    /* 0x00 */ u8 unk00[6];
    /* 0x06 */ u8 _06;
    /* 0x07 */ u8 _07;
    /* 0x08 */ u32 _08;
    /* 0x0C */ u32 _0C;
    /* 0x10 */ s16 _10;
    /* 0x12 */ u16 _12;
    /* 0x14 */ u8 unk14[0xA];
    /* 0x1E */ s16 _1E;
    /* 0x20 */ u8 _20;
    /* 0x21 */ u8 _21;
    /* 0x22 */ u8 _22;
    /* 0x23 */ u8 _23;
    /* 0x24 */ f32 _24;
    /* 0x28 */ f32 _28;
    /* 0x2C */ f32 _2C;
    /* 0x30 */ f32 _30;
    /* 0x34 */ f32 _34;
    /* 0x38 */ u8 unk38[0x67];
    /* 0x9F */ u8 _9F;
    /* 0xA0 */ u8 unkA0;
    /* 0xA1 */ u8 _A1;
    /* 0xA2 */ u8 unkA2[0x1E];
    // size: 0xC0
};

struct Unk80250F18 {
    /* 0x000 */ u16 _00;
    /* 0x002 */ u16 _02;
    /* 0x004 */ Unk80250F18_04 *_04;
    /* 0x008 */ Unk80250F18_08 *_08;
    /* 0x00C */ void *_0C;
    /* 0x010 */ u8 unk010[0x14];
    /* 0x024 */ u32 _24;
    /* 0x028 */ u32 _28;
    /* 0x02C */ u32 _2C[32];
    /* 0x0AC */ u32 _AC[32];
    /* 0x12C */ u8 _12C[32];
    /* 0x14C */ u32 _14C;
    /* 0x150 */ u32 _150;
    /* 0x154 */ Unk80250F18Callback _154;
    /* 0x158 */ u8 unk158[0x18];
    // size: 0x170
};

/* lbl_804FDAB0 */ extern Unk80250F18 lbl_804FDAB0;

extern "C" {
// TODO Replace with proper imports
void fn_80250FF8(Unk80250F18 *obj, u16 count);
void fn_80251AF8(Unk80250F18 *obj, s16 a);
}
