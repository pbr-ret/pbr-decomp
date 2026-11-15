#include ".unsorted/80254260.hpp"

#include "common.hpp"

// TODO Name: called by fn_80253DF0 on lbl_804FDAB0; sets the value arg2 of element arg1 to arg3
void fn_80254260(Unk80250F18 *arg0, s32 arg1, u32 arg2, u32 arg3) {
    // Ids 3 to 7 carry an f32 in the bits of arg3.
    f32 value = *(f32 *)&arg3;
    if (arg1 < 0 || arg1 >= arg0->_00) {
        return;
    }

    Unk80250F18_08 *element = &arg0->_08[arg1];
    switch (arg2) {
        case 1: element->_06 = arg3; break;
        case 2:
            element->_20 = arg3 >> 24;
            element->_21 = arg3 >> 16;
            element->_22 = arg3 >> 8;
            element->_23 = arg3;
            break;
        case 3:  element->_24 = value; break;
        case 4:  element->_28 = value; break;
        case 5:  element->_2C = value; break;
        case 6:  element->_30 = value; break;
        case 7:  element->_34 = value; break;
        case 8:  element->_9F = arg3 != 0; break;
        case 9:  element->_07 = arg3; break;
        case 10: element->_A1 = arg3 != 0; break;
    }
}

// TODO Name: called by fn_80253E4C and fn_80253E6C on lbl_804FDAB0; reads the value arg2 of element arg1 into arg3
void fn_80254334(Unk80250F18 *arg0, s32 arg1, u32 arg2, u32 *arg3) {
    if (arg1 < 0 || arg1 >= arg0->_00) {
        return;
    }

    Unk80250F18_08 *element = &arg0->_08[arg1];
    switch (arg2) {
        case 1:  *arg3 = element->_06; break;
        case 13: *arg3 = element->_12; break;
        case 11: *arg3 = element->_08; break;
        case 2:  *arg3 = (element->_20 << 24) | (element->_21 << 16) | (element->_22 << 8) | element->_23; break;
        case 12: *arg3 = element->_0C; break;
        case 8:  *arg3 = element->_9F; break;
        case 9:  *arg3 = element->_07; break;
        case 10: *arg3 = element->_A1; break;
        // The f32 values go out in the bits of *arg3, the way fn_80254260 takes them.
        case 3:  *arg3 = *(u32 *)&element->_24; break;
        case 4:  *arg3 = *(u32 *)&element->_28; break;
        case 5:  *arg3 = *(u32 *)&element->_2C; break;
        case 6:  *arg3 = *(u32 *)&element->_30; break;
        case 7:  *arg3 = *(u32 *)&element->_34; break;
        case 14: return;
        case 15: *arg3 = 8; break;
    }
}
