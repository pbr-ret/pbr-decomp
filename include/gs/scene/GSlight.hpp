#pragma once

#include "gs/GScolor.hpp"
#include "gs/GSmath.hpp"
#include "gs/GSsceneData.hpp"
#include "gs/scene/GSnull.hpp"

#include <revolution.h>

class GSrenderLight;

static inline f32 getLuminance(const GScolor<u8> &color) {
    return 0.3f * u8tof32(color.r) + 0.59f * u8tof32(color.g) + 0.11f * u8tof32(color.b);
}

enum GSlightNodeType {
    GS_LIGHT_NODE_DIRECTIONAL,
    GS_LIGHT_NODE_POINT,
    GS_LIGHT_NODE_SPOT
};

// NOTE(samm) Name known from RTTI
// size: 0x138
class GSlight : public GSnull {
public: // TODO(samm) Make private
    /* 0x104 */ u32 _104;
    /* 0x108 */ GSlightNodeType mType;
    /* 0x10C */ GSlightData *mLightData;
    /* 0x110 */ GScolor<u8> mColor;
    /* 0x114 */ GScolor<u8> _114;
    /* 0x118 */ f32 _118;
    /* 0x11C */ GXDistAttnFn mDistAttnFn;
    /* 0x120 */ f32 mRefDistance;
    /* 0x124 */ f32 mRefBrightness;
    /* 0x128 */ GXSpotFn mSpotFn;
    /* 0x12C */ f32 mCutoff;
    /* 0x130 */ GSrenderLight *_130;
    /* 0x134 */ GSrenderLight *_134;

private:
    // TODO Name. Sets _114 to a grey that gets darker as mColor gets brighter.
    void update_114() {
        u8 grey = f32tou8(255.5f - getLuminance(mColor) / 2.f);
        _114.r = grey;
        _114.g = grey;
        _114.b = grey;
        _114.a = 255;
    }

public:
    GSlight(GSlightNodeType type, BOOL create130, BOOL create134, const GXColor &color);
    GSlight(GSobject *parentObject, GSnodeData *data);

    // vtable pointer: 0x100
    /* 0x08 */ virtual ~GSlight();
    /* 0x0C */ virtual void update(f32 deltaTime);
    /* 0x10 */ virtual void initTransform(bool recursive);

    void fn_801E64DC(const GSvec3 *target);
    GSvec3 fn_801E6944() const;
    GSvec3 fn_801E69D8() const;
    GSvec3 fn_801E6A94(const GSvec3 *point) const;

    // TODO(samm) Names

    u32 checkLightFlag(u32 flag) const {
        return (_104 & flag) == flag;
    }

    u32 isEnabled() const {
        return _104 & (1 << 0);
    }

    GSlightData *getLightData() const {
        return mLightData;
    }

    GSrenderLight *get_130() const {
        return _130;
    }

    GSrenderLight *get_134() const {
        return _134;
    }

    static void fn_801E6BB0(GSanimationObject *animObj, GSchannelData *channel, f32 cursor, bool blend);
};
