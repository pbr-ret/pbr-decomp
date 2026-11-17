#pragma once

#include <revolution/types.h>

// Only the fields used by the decompiled functions are named; the roles are not established yet.

// An entry of the table at 0x96C of an Unk80035CB0.
// size: 0x1C
struct Unk8000EC58 {
    /* 0x00 */ u8 _00;
    /* 0x01 */ u8 unk01[3];
    /* 0x04 */ u16 _04;
    /* 0x06 */ u8 unk06[6];
    /* 0x0C */ int _0c[2];
    /* 0x14 */ u16 _14;
    /* 0x16 */ u16 _16;
    /* 0x18 */ u8 unk18[4];
};

struct Unk80035CB0Sub {
    /* 0x00 */ u8 unk00[2];
    /* 0x02 */ u16 _02;
    /* 0x04 */ u8 _04;
    /* 0x05 */ u8 _05;
    /* 0x06 */ u8 _06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ u16 _08;
    /* 0x0A */ u16 _0A;
    /* 0x0C */ u16 _0C;
    /* 0x0E */ u8 unk0E[0x0A];
    /* 0x18 */ u16 _18;
    /* 0x1A */ u8 unk1A[0x0A];
    /* 0x24 */ u8 _24;
    /* 0x25 */ u8 _25;
    /* 0x26 */ u8 _26;
    /* 0x27 */ u8 _27;
    // size: unknown
};

struct Unk80035CB0 {
    /* 0x000 */ u32 _00;
    /* 0x004 */ u32 _04;
    /* 0x008 */ u32 _08;
    /* 0x00C */ u32 _0C;
    /* 0x010 */ u32 _10;
    /* 0x014 */ u32 _14;
    /* 0x018 */ u8 unk18[0x14];
    /* 0x02C */ u32 _2C;
    /* 0x030 */ u8 unk30[0x300];
    /* 0x330 */ u8 _330;
    /* 0x331 */ u8 unk331[3];
    /* 0x334 */ u32 mFlags;
    /* 0x338 */ u8 unk338[0x634];
    /* 0x96C */ Unk8000EC58 *_96c;
    /* 0x970 */ Unk80035CB0Sub *_970;
    // size: 0x974 (allocation size in fn_80035D58)
};

Unk80035CB0 *fn_80035D9C();
int fn_80035E38(Unk80035CB0 *p);
void fn_80035E40(Unk80035CB0 *p, u32 v);
u32 fn_80035E48(Unk80035CB0 *p);
void fn_80035E50(Unk80035CB0 *p, u32 v);
int fn_80035E58(Unk80035CB0 *p);
void fn_80035E60(Unk80035CB0 *p, u32 v);
int fn_80035E68(Unk80035CB0 *p);
void fn_80035E70(Unk80035CB0 *p, u32 v);
u32 fn_80035E78(Unk80035CB0 *p);
void fn_80035E80(Unk80035CB0 *p, u32 v);
u32 fn_80035E88(Unk80035CB0 *p);
void fn_80035E90(Unk80035CB0 *p, u32 v);
void fn_80035E98(Unk80035CB0 *p, u32 v);
u32 fn_80035EA0(Unk80035CB0 *p);
int fn_80035EA8(Unk80035CB0 *p);
void fn_80035EB4(Unk80035CB0 *p, u16 v);
u8 fn_80035EC0(Unk80035CB0 *p);
void fn_80035ECC(Unk80035CB0 *p, u8 v);
int fn_80035ED8(Unk80035CB0 *p);
void fn_80035EE4(Unk80035CB0 *p, u8 v);
u8 fn_80035EF0(Unk80035CB0 *p);
u16 fn_80035EFC(Unk80035CB0 *p);
void fn_80035F08(Unk80035CB0 *p, u16 v);
u16 fn_80035F14(Unk80035CB0 *p);
void fn_80035F20(Unk80035CB0 *p, u16 v);
u16 fn_80035F2C(Unk80035CB0 *p);
void fn_80035F38(Unk80035CB0 *p, u16 v);
u16 fn_80035F44(Unk80035CB0 *p);
u8 fn_80035F50(Unk80035CB0 *p);
void fn_80035F5C(Unk80035CB0 *p, u8 v);
int fn_80035F68(Unk80035CB0 *p);
void fn_80035F74(Unk80035CB0 *p, u8 v);
u8 fn_80035F80(Unk80035CB0 *p);
u8 fn_80035F8C(Unk80035CB0 *p);
BOOL fn_80035F98(Unk80035CB0 *p);
int fn_800360D0(Unk80035CB0 *arg0);
int fn_80036554(Unk80035CB0 *arg0, int arg1, int arg2, int arg3);
s32 fn_80036844();
u8 fn_80036E6C(Unk80035CB0 *arg0, u8 arg1, u32 arg2);
u8 fn_80036E94(Unk80035CB0 *arg0, u8 arg1, u32 arg2);
u8 fn_80036F18(Unk80035CB0 *p);
void fn_80036F20(Unk80035CB0 *p, u8 v);
BOOL fn_80036F50(Unk80035CB0 *p, u32 mask);
