#pragma once

#include <revolution/types.h>

// size: >= 0x3
struct Unk80032EEC {
    /* 0x0 */ u8 _0;
    /* 0x1 */ u8 _1;
    /* 0x2 */ u8 _2;
    /* 0x3 */ s8 _3[];
};

// size: >= 0x8
struct Unk80032E64File {
    /* 0x0 */ u16 _0;
    /* 0x2 */ u8 _unk2[0x6];
    /* 0x8 */ Unk80032EEC **_8[];
};

// size: 0x8
struct Unk80032E64 {
    /* 0x0 */ u32 _0;
    /* 0x4 */ Unk80032EEC ***_4;
};

void fn_80032E60();
void fn_80032E64(Unk80032E64 *arg0, Unk80032E64File *arg1);
Unk80032EEC **fn_80032EC0(Unk80032E64 *arg0, s32 arg1);
s8 *fn_80032EEC(Unk80032E64 *arg0, s32 arg1, s32 arg2, u16 arg3);
