#include ".unsorted/80384F4C.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_80640568;

void fn_803852C0(u8 *p) {
    *(u32 *)(p + 0x0) = -0x1;
}
void fn_803852CC(void) {}
void fn_803852F4(void) {}
void fn_8038531C(void) {}
s32 fn_80385320(void) {
    return 255;
}
void fn_80385328(void) {}
void fn_8038580C(void) {}
u32 fn_80385E04(u8 *p) {
    return *(u32 *)(p + 0x28);
}
u32 *fn_80385E0C(void) {
    return &lbl_80640568;
}
void fn_80385E14(void) {
    lbl_80640568 = 0x0;
}
}
