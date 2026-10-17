#pragma once

#include "gs/GScolor.hpp"
#include "gs/GSmath.hpp"
#include "gs/GSrender.hpp"
#include "gs/scene/GSanimationObject.hpp"

class GScamera;
struct GSmeshRenderSettings;
class GSchannelData;

// size: 0x30
struct Unk80491970 : public GSmatrix {
    Unk80491970();

    Unk80491970(GSvec3 scale, GSvec3 trans) {
        MTXScale(*this, scale.x, scale.y, scale.z);
        MTXTransApply(*this, *this, trans.x, trans.y, trans.z);
    }
};

// size: 0x6
struct Unk8063D768 {
    /* 0x0 */ u8 _0;
    /* 0x1 */ bool _1;
    /* 0x2 */ u8 mTexMapId;
    /* 0x3 */ u8 mTexCoordId;
    /* 0x4 */ u8 _4;
    /* 0x5 */ u8 _5;
};

// NOTE(samm) Name known from RTTI
// size: 0x38
class GSmaterial : public GSanimationObject {
protected:
    /* 0x08 */ const GSmaterialData *mOrigMatData;
    /* 0x0C */ GSmaterialData *mMatData;
    /* 0x10 */ GSmeshRenderSettings *mRenderSettings;
    /* 0x14 */ GStexture *_14;
    /* 0x18 */ Unk80491970 *_18;
    /* 0x1C */ u8 _1c;
    /* 0x1D */ u8 mTexGenCount;
    /* 0x1E */ u8 mChannelCount;
    /* 0x1F */ u8 mCurrTevStage;
    /* 0x20 */ u8 _20;
    /* 0x21 */ u8 _21;
    /* 0x22 */ u8 _22;
    /* 0x23 */ u8 _23;
    /* 0x24 */ u8 _24;
    /* 0x25 */ u8 _25;
    /* 0x26 */ u8 _26;
    /* 0x27 */ u8 _27;
    /* 0x28 */ u32 _28;
    /* 0x2C */ GScolor _2c;
    /* 0x30 */ GScolor mBaseColor;

    void releaseTexture() {
        if (mOrigMatData->_50) {
            if (_14 && (_28 & (1 << 0))) {
                _14->fn_8023E2D0();
                _28 &= ~(1 << 0);
            }
            _14 = NULL;
        }
    }

public:
    GSmaterial(GSmaterialData *data, GSmeshRenderSettings *arg1);

    // vtable pointer: 0x34
    /* 0x8 */ virtual ~GSmaterial();

    void fn_801E6F78(GStexture *baseTex, GStexture *spotTex, u32 spotOffsets, const bool *darken);
    void fn_801E74B0(_UnkMaterialData_1 *arg0);
    void fn_801E7FA4(GScamera *arg0, GSmatrix *arg1, u32 arg2);
    void fn_801E8858(bool useTexture);
    void fn_801E8BA4(bool useTexture);
    void fn_801E9114(GScamera *arg0, bool useTexture);
    void fn_801E98E0();
    void fn_801E9C18(GScamera *arg0);
    GSmatrix *fn_801E9C74(u8 arg0, _UnkMaterialData_2 *arg1);
    void fn_801E9DCC(const GScamera *arg0, GSmatrix *arg1);
    void fn_801EA44C();
    void fn_801EAA94();
    void fn_801EABE8(bool inverted);
    void fn_801EB044(bool inverted, bool blend, bool zComp);
    void fn_801EB668(bool inverted);
    void fn_801EB87C(GScamera *arg0, GSmatrix *arg1);
    bool fn_801EC050(GScamera *arg0, GSmatrix *arg1, bool arg2);
    bool fn_801EC538(GScamera *arg0, GSmatrix *arg1, bool arg2, bool arg3, u32 arg4);
    void fn_801ECBA8();

    GSmeshRenderSettings *getRenderSettings() const {
        return mRenderSettings;
    }

    u8 getAlpha() const {
        return mBaseColor.a;
    }

    static void fn_801EC9AC(GSanimationObject *animObj, GSchannelData *channel, f32 cursor, bool blend);
};
