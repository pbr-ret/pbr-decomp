#pragma once

#include <revolution/types.h>

struct Unk80032E60;

// size: 0x90
struct Unk8063EA80 {
    /* 0x00 */ u8 _unk0[0xC];
    /* 0x0C */ Unk80032E60 *_c;
    /* 0x10 */ u8 _unk10[0x80];
};

void fn_8003E158();
Unk8063EA80 *fn_8003E15C();
Unk80032E60 *fn_8003E42C(Unk8063EA80 *arg0);
u16 fn_8003E434(Unk8063EA80 *arg0, u32 arg1, u16 arg2);
