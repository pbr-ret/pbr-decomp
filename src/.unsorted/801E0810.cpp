#include ".unsorted/801E0810.hpp"

#include ".unsorted/80032FE8.hpp"
#include "gs/render/GSrenderTarget.hpp"

#include <string.h>

#include "common.hpp"

// TODO role: takes a free entry from lbl_8063F410 and sets its color
Unk801FB80C *fn_801E0810(GXColor *color, u32 arg1, u8 arg2, bool arg3) {
    if (lbl_8063F410 == NULL) {
        return NULL;
    }

    Unk801FB80C *entry = fn_801FB80C(lbl_8063F410);
    if (entry == NULL) {
        return NULL;
    }

    entry->_1 = true;
    entry->_2 = arg2;
    entry->_3 = arg3;
    entry->_4 = arg1;
    if (arg3) {
        GSrenderTarget::_unkFunc_1(lbl_8063F410->_10);
    }
    *lbl_8063F410->getColor(entry) = *color;
    return entry;
}

// TODO role: gives an entry from fn_801E0810 back
void fn_801E0904(Unk801FB80C *entry) {
    if (entry->_1) {
        if (entry->_3) {
            GSrenderTarget::_unkFunc_2(lbl_8063F410->_10);
        }
        entry->_1 = false;
        entry->_4 = 0;
    }
}

// TODO role: reads the color of an entry from fn_801E0810
void fn_801E0978(Unk801FB80C *entry, GXColor *color) {
    if (entry->_1) {
        *color = *lbl_8063F410->getColor(entry);
    } else {
        memset(color, 0, sizeof(GXColor));
    }
}

// TODO role: sets the color of an entry from fn_801E0810
void fn_801E09DC(Unk801FB80C *entry, GXColor *color) {
    if (entry->_1) {
        GXColor *dst = lbl_8063F410->getColor(entry);
        *dst = *color;
        DCFlushRange(dst, sizeof(GXColor));
    }
}
