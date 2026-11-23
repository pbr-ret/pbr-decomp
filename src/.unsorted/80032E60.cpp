#include ".unsorted/80032E60.hpp"

#include ".unsorted/8003E03C.hpp"

#include "common.hpp"

// TODO Name: called by fn_80025390 (a constructor) on its member at 0x998
void fn_80032E60(Unk80032E60 *arg0) {}

// TODO Name: called by fn_800255A8 on the body of the "MTBL" chunk of a loaded file
void fn_80032E64(Unk80032E60 *arg0, Unk80032E64 *arg1) {
    arg0->_0 = arg1->_0;
    arg0->_4 = arg1->_8;
    // The pointer fields of the chunk hold offsets from the start of its body until they are turned into pointers
    // here.
    for (s32 i = 0; arg0->_4[i] != NULL; i++) {
        arg0->_4[i] = (Unk80032EEC **)((u32)arg1 + (u32)arg0->_4[i]);
        for (Unk80032EEC **entry = arg0->_4[i]; *entry != NULL; entry++) {
            *entry = (Unk80032EEC *)((u32)arg1 + (u32)*entry);
        }
    }
}

// TODO Name: only called by fn_80032EEC
Unk80032EEC **fn_80032EC0(Unk80032E60 *arg0, s32 arg1) {
    if (arg1 < 0 || arg1 >= arg0->_0) {
        return NULL;
    }
    return arg0->_4[arg1];
}

// TODO Name: called by fn_8003967C of unit 80036F88; the kind of each entry (0 to 3) decides how its id is checked
s8 *fn_80032EEC(Unk80032E60 *arg0, s32 arg1, s32 arg2, u16 arg3) {
    Unk80032EEC **list = fn_80032EC0(arg0, arg1);
    if (list == NULL) {
        return NULL;
    }

    for (s32 i = 0; list[i] != NULL; i++) {
        Unk80032EEC *item = list[i];
        u16 id = (item->_1 << 8) | item->_2;
        switch (item->_0) {
            case 0: break;
            case 1: return item->_3;
            case 2:
                if (id == arg2) {
                    return item->_3;
                }
                break;
            case 3:
                if (fn_8003E434(fn_8003E15C(), arg3, id) != 0xFFFF) {
                    return item->_3;
                }
                break;
        }
    }
    return NULL;
}
