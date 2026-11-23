#pragma once

#include "gs/GSmath.hpp"
#include "gs/GSsceneData.hpp"
#include "gs/scene/GSnull.hpp"

#include <revolution.h>

// NOTE Name known from RTTI
// size: 0x264
class GScamera : public GSnull {
public: // TODO Make private
    /* 0x104 */ u32 _104;
    /* 0x108 */ GScameraData *mCameraData;
    /* 0x10C */ Mtx44 _10c;
    /* 0x14C */ f32 _14c[7];
    /* 0x168 */ f32 _168;
    /* 0x16C */ f32 _16c;
    /* 0x170 */ f32 _170;
    /* 0x174 */ f32 _174;
    /* 0x178 */ f32 _178;
    /* 0x17C */ f32 _17c;
    /* 0x180 */ f32 _180;
    /* 0x184 */ f32 _184;
    /* 0x188 */ GSvec3 _188;
    /* 0x194 */ GSvec3 _194;
    /* 0x1A0 */ GSvec3 _1a0;
    /* 0x1AC */ GSvec3 _1ac;
    /* 0x1B8 */ GSvec3 _1b8;
    /* 0x1C4 */ GSvec3 _1c4;
    /* 0x1D0 */ GSnull *_1d0;
    /* 0x1D4 */ GSmatrix _1d4;
    /* 0x204 */ GSmatrix _204;
    /* 0x234 */ GSmatrix _234;

    GScamera();
    GScamera(GSobject *parentObject, GSnodeData *data);

    // vtable pointer: 0x100
    /* 0x08 */ virtual ~GScamera();
    /* 0x0C */ virtual void update(f32 deltaTime);
    /* 0x10 */ virtual void initTransform(bool recursive);
    /* 0x14 */ virtual void updateTransform();

    void fn_801DE1F8();
    void fn_801DE524();
    Unk80491970 fn_801DEA3C(const GSmatrix &src, bool yawOnly) const;

    static void fn_801DEEF8(GSanimationObject *animObj, GSchannelData *channel, f32 cursor, bool blend);

    GSmatrix *get_1d4() {
        return &_1d4;
    }
};
