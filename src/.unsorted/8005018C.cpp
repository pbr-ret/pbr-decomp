#include ".unsorted/8005018C.hpp"

#include ".unsorted/80032FE8.hpp"
#include ".unsorted/801FB42C.hpp"
#include "gs/GScache.hpp"

#include "common.hpp"

// TODO Name: called with 1 or 2 by six units; sets up the object of lbl_8063F410 and starts it with fn_801FEE2C
void fn_8005018C(s32 arg0, f32 arg1) {
    if (lbl_8063F410->_468) {
        fn_801FEF68(lbl_8063F410);
    }

    // Each group of stores reads lbl_8063F410 again, as if the original wrote it through four inline accessors.
    switch (arg0) {
        case 1: {
            Unk8063F410 *object = lbl_8063F410;
            object->_458 = arg1;
            object->_460 = 0;
            object->_461 = 0;
            object = lbl_8063F410;
            object->_462 = 0x17;
            object->_45c = arg1;
            object = lbl_8063F410;
            object->_494 = 0;
            object->_495 = 0;
            object->_496 = 0;
            object->_497 = 0xFF;
            void *file = GScache::getCachedFile(10, 0x1B7A0C00);
            object = lbl_8063F410;
            object->_49c = 0;
            object->_4a0 = file;
            break;
        }
        case 2: {
            Unk8063F410 *object = lbl_8063F410;
            object->_458 = arg1;
            object->_460 = 1;
            object->_461 = 1;
            object = lbl_8063F410;
            object->_462 = 0x17;
            object->_45c = arg1;
            object = lbl_8063F410;
            object->_494 = 0;
            object->_495 = 0;
            object->_496 = 0;
            object->_497 = 0xFF;
            void *file = GScache::getCachedFile(10, 0x1B7A0C00);
            object = lbl_8063F410;
            object->_49c = 0;
            object->_4a0 = file;
            break;
        }
        default: return;
    }

    fn_801FEE2C(lbl_8063F410, 1);
}

// TODO Name: polled by six units; true while the object of lbl_8063F410 is active and its floats at 0x474 and
// 0x478 are equal
BOOL fn_800502BC() {
    if (lbl_8063F410->_468) {
        f32 diff = lbl_8063F410->_474 - lbl_8063F410->_478;
        return diff < 1e-5f && diff > -1e-5f;
    }
    return FALSE;
}
