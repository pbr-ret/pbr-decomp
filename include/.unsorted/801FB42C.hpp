#pragma once

#include <revolution/types.h>

struct Unk8063F410;

// size: 0x8
struct Unk801FB80C {
    /* 0x0 */ u8 _0;
    /* 0x1 */ bool _1;
    /* 0x2 */ u8 _2;
    /* 0x3 */ bool _3;
    /* 0x4 */ u32 _4;
};

// TODO role: returns the first entry of module->_3ec whose _1 is clear, or NULL
Unk801FB80C *fn_801FB80C(Unk8063F410 *module);

void fn_801FEE2C(Unk8063F410 *arg0, u8 arg1);
void fn_801FEF68(Unk8063F410 *arg0);
