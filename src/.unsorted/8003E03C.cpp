#include ".unsorted/8003E03C.hpp"

#include "common.hpp"

extern Unk8063EA80 *lbl_8063EA80;

// TODO Name: callback registered with fn_8023EB58 by fn_8003E03C, next to fn_8003E124
void fn_8003E158() {}

// TODO Name: returns the object that fn_8003E03C allocates
Unk8063EA80 *fn_8003E15C() {
    return lbl_8063EA80;
}

// TODO Name: the object read by fn_80032EEC when the file of unit 80036F88 is not cached
Unk80032E60 *fn_8003E42C(Unk8063EA80 *arg0) {
    return arg0->_c;
}
