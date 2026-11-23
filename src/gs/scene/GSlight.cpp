#include "gs/scene/GSlight.hpp"

#include "gs/GShierarchyModule.hpp"
#include "gs/GSmath.hpp"
#include "gs/GSsceneData.hpp"
#include "gs/render/GSrenderLight.hpp"

#include <revolution.h>

#include "common.hpp"

// TODO Names
#define LIGHT_FLAG_CREATE_130 (1 << 2)
#define LIGHT_FLAG_CREATE_134 (1 << 3)
#define LIGHT_FLAG_ENABLED (1 << 4)
#define LIGHT_FLAG_UPDATE_114 (1 << 5)

#define CHANNEL_COLOR 19

static inline void safeNormalize(Vec *vec) {
    f32 sqMag = VECSquareMag(vec);
    if (sqMag > EPSILON) {
        f32 mag = safe_sqrt(sqMag);
        VECScale(vec, vec, 1.f / ensure_nonzero(mag));
    }
}

static inline bool isZero(const Vec &vec) {
    if (!FLOAT_EQUAL(vec.x, 0.f) || !FLOAT_EQUAL(vec.y, 0.f) || !FLOAT_EQUAL(vec.z, 0.f)) {
        return false;
    }
    return true;
}

static inline GSvec getMtxColumn(const Mtx mtx, int col) {
    GSvec vec;
    vec.x = mtx[0][col];
    vec.y = mtx[1][col];
    vec.z = mtx[2][col];
    return vec;
}

static inline void negate(Vec *dst, const Vec &src) {
    dst->x = -src.x;
    dst->y = -src.y;
    dst->z = -src.z;
}

GSlight::GSlight(GSlightNodeType type, BOOL create130, BOOL create134, const GXColor &color)
    : GSnull(GS_NODE_LIGHT),
      _104(0),
      mType(type),
      mLightData(NULL),
      mColor(color.r, color.g, color.b, color.a),
      _118(0.f),
      mDistAttnFn(GX_DA_OFF),
      mRefDistance(100.f),
      mRefBrightness(0.5f),
      mSpotFn(GX_SP_OFF),
      mCutoff(90.f),
      _130(NULL),
      _134(NULL) {
    update_114();

    switch (mType) {
        case GS_LIGHT_NODE_DIRECTIONAL:
            if (create134) {
                _134 = new GSrenderLight();
            }
            if (create130) {
                if (_134) {
                    _130 = _134;
                } else {
                    _130 = new GSrenderLight();
                }
            }
            break;
        case GS_LIGHT_NODE_POINT:
        case GS_LIGHT_NODE_SPOT:
            if (create130) {
                _130 = new GSrenderLight();
            }
            if (create134) {
                _134 = new GSrenderLight();
            }
            break;
    }
}

GSlight::GSlight(GSobject *parentObject, GSnodeData *data)
    : GSnull(parentObject, data),
      _104(0),
      mLightData(static_cast<GSlightData *>(data)),
      mColor(255, 255, 255, 255),
      _114(0, 0, 0, 255),
      _118(0.f),
      mDistAttnFn(GX_DA_OFF),
      mRefDistance(100.f),
      mRefBrightness(0.5f),
      mSpotFn(GX_SP_OFF),
      mCutoff(90.f),
      _130(NULL),
      _134(NULL) {
    GSlightData *lightData = static_cast<GSlightData *>(data);
    mType = (GSlightNodeType)(lightData->mLightFlags & 3);

    switch (mType) {
        case GS_LIGHT_NODE_DIRECTIONAL:
            if (lightData->mLightFlags & LIGHT_FLAG_CREATE_134) {
                _134 = new GSrenderLight();
            }
            if (lightData->mLightFlags & LIGHT_FLAG_CREATE_130) {
                if (_134) {
                    _130 = _134;
                } else {
                    _130 = new GSrenderLight();
                }
            }
            break;
        case GS_LIGHT_NODE_POINT:
        case GS_LIGHT_NODE_SPOT:
            if (lightData->mLightFlags & LIGHT_FLAG_CREATE_130) {
                _130 = new GSrenderLight();
            }
            if (lightData->mLightFlags & LIGHT_FLAG_CREATE_134) {
                _134 = new GSrenderLight();
            }
            break;
    }
}

void GSlight::initTransform(bool recursive) {
    GSnull::initTransform(recursive);

    if (mLightData) {
        if (mLightData->mLightFlags & LIGHT_FLAG_ENABLED) {
            _104 |= (1 << 0);
        } else {
            _104 &= ~(1 << 0);
        }

        mColor.r = mLightData->mColor.r;
        mColor.g = mLightData->mColor.g;
        mColor.b = mLightData->mColor.b;
        mColor.a = mLightData->mColor.a;
        _114.r = mLightData->_38.r;
        _114.g = mLightData->_38.g;
        _114.b = mLightData->_38.b;
        _114.a = mLightData->_38.a;
        _118 = mLightData->_3c;
        mDistAttnFn = mLightData->mDistAttnFn;
        mRefDistance = mLightData->mRefDistance;
        mRefBrightness = mLightData->mRefBrightness;
        mSpotFn = mLightData->mSpotFn;
        mCutoff = mLightData->mCutoff;
    }
}

GSlight::~GSlight() {
    GShierarchyModule::unregisterLight(this);

    if (_130 && _130 != _134) {
        delete _130;
    }
    if (_134) {
        delete _134;
    }
}

// TODO Points the specular light from the light's position towards target
void GSlight::fn_801E64DC(const GSvec *target) {
    if (!_134 || _134 == _130) {
        return;
    }

    GSvec dir = *target - getMtxColumn(mTransform, 3);

    if (isZero(dir)) {
        dir.set(0.f, -1.f, 0.f);
    } else {
        dir.normalize();
    }

    _134->setDirection(dir);
}

void GSlight::update(f32 deltaTime) {
    if (fn_801F3C7C()) {
        deltaTime = 0.f;
    }

    GSnull::update(deltaTime);

    if (checkLightFlag(1 << 0)) {
        GSvec position;
        GSvec dir;

        switch (mType) {
            case GS_LIGHT_NODE_POINT:
                if (_130) {
                    position = getMtxColumn(mTransform, 3);
                    _130->initPointLight(mColor, position, mDistAttnFn, mRefDistance, mRefBrightness);
                }
            case GS_LIGHT_NODE_DIRECTIONAL:
                if (_134) {
                    negate(&dir, getMtxColumn(mTransform, 2));
                    safeNormalize(&dir);
                    _134->initSpecLight(mColor, dir, 50.f);
                }
                break;
            case GS_LIGHT_NODE_SPOT: {
                negate(&dir, getMtxColumn(mTransform, 2));
                safeNormalize(&dir);
                if (_130) {
                    position = getMtxColumn(mTransform, 3);
                    _130->initSpotLight(mColor,
                                        position,
                                        dir,
                                        mDistAttnFn,
                                        mRefDistance,
                                        mRefBrightness,
                                        mSpotFn,
                                        mCutoff);
                }
                if (_134) {
                    _134->initSpecLight(mColor, dir, 50.f);
                }
                break;
            }
        }
    }

    if (mLightData && (mLightData->mLightFlags & LIGHT_FLAG_UPDATE_114)) {
        update_114();
    }
}

// TODO Position of the light; directional lights are placed far away against their direction
GSvec GSlight::fn_801E6944() const {
    GSvec position;
    switch (mType) {
        case GS_LIGHT_NODE_DIRECTIONAL: position = fn_801E69D8() * -1e18f; break;
        case GS_LIGHT_NODE_POINT:
        case GS_LIGHT_NODE_SPOT:
        default:                        position = getMtxColumn(mTransform, 3); break;
    }
    return position;
}

// TODO Direction the light points in
GSvec GSlight::fn_801E69D8() const {
    const Mtx &mtx = mTransform;
    GSvec dir;
    dir.x = -mtx[0][2];
    dir.y = -mtx[1][2];
    dir.z = -mtx[2][2];
    safeNormalize(&dir);
    return dir;
}

// TODO Direction of the light at point
GSvec GSlight::fn_801E6A94(const GSvec *point) const {
    GSvec dir;
    if (mType == GS_LIGHT_NODE_DIRECTIONAL) {
        negate(&dir, getMtxColumn(mTransform, 2));
    } else {
        dir = *point - getMtxColumn(mTransform, 3);
    }
    safeNormalize(&dir);
    return dir;
}

void GSlight::fn_801E6BB0(GSanimationObject *animObj, GSchannelData *channel, f32 cursor, bool blend) {
    GSlight *light = static_cast<GSlight *>(animObj);

    if (blend) {
        return;
    }

    switch (channel->mChannel) {
        case CHANNEL_COLOR: fn_801E1440(channel, cursor, &light->mColor); break;
    }
}
