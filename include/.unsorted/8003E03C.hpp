#pragma once

#include <revolution/types.h>

struct Unk80032E64;

// size: >= 0x10
struct Unk8063EA80 {
    /* 0x0 */ u8 _unk0[0xC];
    /* 0xC */ Unk80032E64 *_c;
};

void fn_8003E158();
Unk8063EA80 *fn_8003E15C();
Unk80032E64 *fn_8003E42C(Unk8063EA80 *arg0);
u16 fn_8003E434(Unk8063EA80 *arg0, u32 arg1, u16 arg2);
