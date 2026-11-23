#include ".unsorted/803739E4.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_806404E0;
void fn_80373BB0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80374360(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_803743B4(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_8037536C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_80374C1C(void) {}
void fn_80374C20(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80373BB0(a0 - 0x74, a1, a2, a3, a4, a5, a6, a7);
}
void fn_80374C28(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80373BB0(a0 - 0x80, a1, a2, a3, a4, a5, a6, a7);
}
void fn_803750E4(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80374360(a0 + 0xd8, a1, a2, a3, a4, a5, a6, a7);
}
void fn_803750EC(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_803743B4(a0 + 0xd8, a1, a2, a3, a4, a5, a6, a7);
}
BOOL fn_803751DC(u8 *p) {
    return *(u32 *)(p + 0x20c) != 0;
}
void fn_803751F0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_8037536C(*(u32 *)(a0 + 0x20c), a1, a2, a3, a4, a5, a6, a7);
}
u8 *fn_80375340(u8 *p) {
    return p + 0xd8;
}
u8 *fn_80375348(u8 *p) {
    return p + 0xd8;
}
u8 fn_80375350(u8 *p) {
    return *(u8 *)(p + 0x221);
}
u32 *fn_80375358(void) {
    return &lbl_806404E0;
}
}
