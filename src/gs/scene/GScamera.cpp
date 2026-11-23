#include "gs/scene/GScamera.hpp"

#include ".unsorted/80223694.hpp"
#include "gs/GSmath.hpp"
#include "gs/GSsceneData.hpp"
#include "gs/GSvideo.hpp"

#include <revolution.h>

#include "common.hpp"

// TODO Names
#define CAMERA_PROJECTION_MASK 3
#define CAMERA_FLAG_WIDESCREEN_APPLIED (1 << 2)
#define CAMERA_FLAG_PROJECTION_DIRTY (1 << 3)
#define CAMERA_FLAG_UP_DIRTY (1 << 4)
#define CAMERA_FLAG_VIEW_DIRTY (1 << 5)
#define CAMERA_FLAG_40 (1 << 6)
#define CAMERA_FLAG_80 (1 << 7)
#define CAMERA_FLAG_WIDESCREEN (1 << 8)

#define RAD_TO_DEG(rad) (57.29578f * (rad))

#define CAMERA_DATA_FLAG_40 (1 << 2)

enum GScameraProjection {
    GS_CAMERA_PERSPECTIVE = 1,
    GS_CAMERA_ORTHO       = 2,
    GS_CAMERA_FRUSTUM     = 3
};

#define CHANNEL_168 5
#define CHANNEL_16C 6
#define CHANNEL_17C 7
#define CHANNEL_180 8
#define CHANNEL_184 9
#define CHANNEL_188 10
#define CHANNEL_1A0 11
#define CHANNEL_194 12

// TODO Defined in an unsplit unit
extern GSmatrix lbl_804932E0;

static inline bool isZero(const Vec &vec) {
    if (!FLOAT_EQUAL(vec.x, 0.f) || !FLOAT_EQUAL(vec.y, 0.f) || !FLOAT_EQUAL(vec.z, 0.f)) {
        return false;
    }
    return true;
}

static inline bool isEqual(const Vec &a, const Vec &b) {
    if (!FLOAT_EQUAL(a.x, b.x) || !FLOAT_EQUAL(a.y, b.y) || !FLOAT_EQUAL(a.z, b.z)) {
        return false;
    }
    return true;
}

static inline GSvec3 getMtxColumn(const Mtx mtx, int col) {
    GSvec3 vec;
    vec.x = mtx[0][col];
    vec.y = mtx[1][col];
    vec.z = mtx[2][col];
    return vec;
}

static inline f32 safe_acos(f32 x) {
    if (x >= 1.f) {
        return 0.f;
    } else if (x <= -1.f) {
        return PI;
    }
    return acos(x);
}

GScamera::GScamera()
    : GSnull(GS_NODE_CAMERA),
      _104(CAMERA_FLAG_WIDESCREEN | CAMERA_FLAG_PROJECTION_DIRTY | GS_CAMERA_PERSPECTIVE),
      mCameraData(NULL),
      _14c(),
      _168(60.f),
      _16c(1.28f),
      _178(1.f),
      _17c(0.1f),
      _180(100000.f),
      _184(10.f),
      _188(0.f, 0.f, -1.f),
      _194(0.f, 1.f, 0.f),
      _1a0(0.f, 0.f, 0.f),
      _1ac(0.f, 0.f, -1.f),
      _1b8(0.f, 1.f, 0.f),
      _1c4(0.f, 0.f, 0.f),
      _1d0(NULL) {
    _184 = 10.f;
    MTXIdentity(_1d4);
    MTXIdentity(_204);
    MTXIdentity(_234);
}

GScamera::GScamera(GSobject *parentObject, GSnodeData *data)
    : GSnull(parentObject, data),
      _104(CAMERA_FLAG_WIDESCREEN | CAMERA_FLAG_PROJECTION_DIRTY | GS_CAMERA_PERSPECTIVE),
      mCameraData(static_cast<GScameraData *>(data)),
      _14c(),
      _168(60.f),
      _16c(1.28f),
      _178(1.f),
      _17c(0.1f),
      _180(100000.f),
      _184(10.f),
      _188(0.f, 0.f, -1.f),
      _194(0.f, 1.f, 0.f),
      _1a0(0.f, 0.f, 0.f),
      _1ac(0.f, 0.f, 0.f),
      _1b8(0.f, 1.f, 0.f),
      _1c4(0.f, 0.f, -1.f),
      _1d0(NULL) {
    _16c = 1.28f;
    _184 = 10.f;
    MTXIdentity(_1d4);
    MTXIdentity(_204);
    MTXIdentity(_234);
}

GScamera::~GScamera() {}

// TODO Recomputes the projection matrix when it is dirty, widening it on a widescreen display
void GScamera::fn_801DE1F8() {
    f32 zoom;
    f32 widescreen;
    if (GSvideo::getInstance()->get_7a() && (_104 & CAMERA_FLAG_WIDESCREEN)) {
        if (!(_104 & CAMERA_FLAG_WIDESCREEN_APPLIED)) {
            _104 |= CAMERA_FLAG_WIDESCREEN_APPLIED | CAMERA_FLAG_PROJECTION_DIRTY;
        }
        widescreen = 1.334375f;
    } else {
        if (_104 & CAMERA_FLAG_WIDESCREEN_APPLIED) {
            _104 = (_104 | CAMERA_FLAG_PROJECTION_DIRTY) & ~CAMERA_FLAG_WIDESCREEN_APPLIED;
        }
        widescreen = 1.f;
    }

    if (_104 & CAMERA_FLAG_PROJECTION_DIRTY) {
        zoom = _178;
        switch (_104 & CAMERA_PROJECTION_MASK) {
            case GS_CAMERA_ORTHO: {
                f32 invZoom;
                f32 offset = 0.5f * ((1.f - widescreen) * (_174 - _170));
                if (zoom > 1.f) {
                    invZoom = 1.f / zoom;
                    fn_80223698(_10c,
                                _168 * invZoom,
                                _16c * invZoom,
                                offset + _170 * widescreen,
                                offset + _174 * widescreen,
                                _17c,
                                _180);
                } else {
                    zoom *= widescreen;
                    fn_80223698(_10c, _168, _16c, offset + _170 * zoom, offset + _174 * zoom, _17c, _180);
                }
                _14c[0] = 1.f;
                _14c[1] = _10c[0][0];
                _14c[2] = _10c[0][3];
                _14c[3] = _10c[1][1];
                _14c[4] = _10c[1][3];
                _14c[5] = _10c[2][2];
                _14c[6] = _10c[2][3];
                break;
            }
            case GS_CAMERA_FRUSTUM: {
                f32 invZoom;
                f32 offset = 0.5f * ((1.f - widescreen) * (_174 - _170));
                if (zoom > 1.f) {
                    invZoom = 1.f / zoom;
                    fn_80223694(_10c,
                                _168 * invZoom,
                                _16c * invZoom,
                                offset + _170 * widescreen,
                                offset + _174 * widescreen,
                                _17c,
                                _180);
                } else {
                    zoom *= widescreen;
                    fn_80223694(_10c, _168, _16c, offset + _170 * zoom, offset + _174 * zoom, _17c, _180);
                }
                _14c[0] = 0.f;
                _14c[1] = _10c[0][0];
                _14c[2] = _10c[0][2];
                _14c[3] = _10c[1][1];
                _14c[4] = _10c[1][2];
                _14c[5] = _10c[2][2];
                _14c[6] = _10c[2][3];
                break;
            }
            case GS_CAMERA_PERSPECTIVE:
            default:
                if ((_104 & CAMERA_FLAG_80) && zoom > 1.f) {
                    f32 fovY = 2.f * atan2f(tanf(0.017453292f * (0.5f * _168)) / zoom, 1.f);
                    fovY = RAD_TO_DEG(fovY);
                    zoom *= widescreen;
                    fn_8022369C(_10c, fovY, _16c * zoom, _17c, _180);
                } else {
                    zoom *= widescreen;
                    fn_8022369C(_10c, _168, _16c * zoom, _17c, _180);
                }
                _14c[0] = 0.f;
                _14c[1] = _10c[0][0];
                _14c[2] = _10c[0][2];
                _14c[3] = _10c[1][1];
                _14c[4] = _10c[1][2];
                _14c[5] = _10c[2][2];
                _14c[6] = _10c[2][3];
                break;
        }
        _104 &= ~CAMERA_FLAG_PROJECTION_DIRTY;
    }
}

// TODO Makes the up vector perpendicular to the view direction
void GScamera::fn_801DE524() {
    if (_104 & CAMERA_FLAG_UP_DIRTY) {
        GSvec3 forward;
        GSvec3 right;
        forward = _1c4 - _1ac;
        forward.normalize();
        right = forward.cross(&_1b8);
        right.normalize();
        _1b8 = right.cross(&forward);
        _104 = (_104 & ~CAMERA_FLAG_UP_DIRTY) | CAMERA_FLAG_VIEW_DIRTY;
    }
}

void GScamera::updateTransform() {
    bool transformDirty = mFlags & 1;

    if (_1d0) {
        if (_1d0->checkFlag(1)) {
            _1d0->updateTransform();
        }
        _1c4 = getMtxColumn(*_1d0->getTransform(), 3);

        GSvec3 forward;
        GSvec3 right;
        forward = _1c4 - _1ac;
        forward.normalize();
        right = forward.cross(&GSmath::sYAxis);
        if (isZero(right)) {
            right = forward.cross(&GSmath::sZAxis);
        }
        right.normalize();
        _1b8 = right.cross(&forward);
        _104 = (_104 & ~CAMERA_FLAG_UP_DIRTY) | CAMERA_FLAG_VIEW_DIRTY;
    }

    if (_104 & CAMERA_FLAG_UP_DIRTY) {
        fn_801DE524();
    }

    if ((_104 & CAMERA_FLAG_VIEW_DIRTY) || transformDirty) {
        GSmatrix inv;
        GSmatrix viewInv;
        GSmatrix viewInvXpose;
        MTXInverse(mTransform, inv);
        _188 = inv * _1ac;
        _194 = inv.multVecSR(_1b8);
        _1a0 = inv * _1c4;

        if (transformDirty) {
            GSnull::updateTransform();
        }

        _1ac = mTransform * _188;
        _1b8 = mTransform.multVecSR(_194);
        _1c4 = mTransform * _1a0;

        if (isZero(_1b8)) {
            _1b8 = GSmath::sYAxis;
        }
        if (isEqual(_1ac, _1c4)) {
            _1c4 = _1ac + GSmath::sZAxis;
        }

        MTXLookAt(_1d4, &_1ac, &_1b8, &_1c4);
        MTXInverse(_1d4, viewInv);
        _204 = viewInv;
        MTXTranspose(_204, viewInvXpose);
        _234 = viewInvXpose;
        _104 &= ~CAMERA_FLAG_VIEW_DIRTY;
    }
}

// TODO Turns src to face the camera, keeping its scale and position; with yawOnly, only around the Y axis
Unk80491970 GScamera::fn_801DEA3C(const GSmatrix &src, bool yawOnly) const {
    GSmatrix mtx;
    Mtx rotMtx;
    GSvec3 position;
    GSvec3 dir;
    GSvec3 scale;
    Quaternion rotQuat;

    const Mtx &m = src;
    scale.x = safe_sqrt(m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0]);
    scale.y = safe_sqrt(m[0][1] * m[0][1] + m[1][1] * m[1][1] + m[2][1] * m[2][1]);
    scale.z = safe_sqrt(m[0][2] * m[0][2] + m[1][2] * m[1][2] + m[2][2] * m[2][2]);
    MTXScale(mtx, scale.x, scale.y, scale.z);

    position.x = m[0][3];
    position.y = m[1][3];
    position.z = m[2][3];

    if (yawOnly) {
        VECSubtract(&_1ac, &position, &dir);
        dir.y = 0.f;
        if (isZero(dir)) {
            return lbl_804932E0;
        }
        dir.normalize();
        f32 angle = safe_acos(dir.z);
        if (dir.x < 0.f) {
            angle = -angle;
        }
        QUATRotAxisRad(&rotQuat, &GSmath::sYAxis, angle);
        MTXQuat(rotMtx, &rotQuat);
        MTXConcat(rotMtx, mtx, mtx);
    } else {
        MTXConcat(_204, mtx, mtx);
    }

    mtx(0, 3) = position.x;
    mtx(1, 3) = position.y;
    mtx(2, 3) = position.z;
    return mtx;
}

void GScamera::update(f32 deltaTime) {
    if (fn_801F3C7C()) {
        deltaTime = 0.f;
    }

    GSblendObject::update(deltaTime);
    updateTransform();
    fn_801DE1F8();
    updateChildren(deltaTime);
}

void GScamera::initTransform(bool recursive) {
    GSnull::initTransform(recursive);

    if (mCameraData) {
        _104 = (mCameraData->mCameraFlags & CAMERA_PROJECTION_MASK) | CAMERA_FLAG_WIDESCREEN;
        if (mCameraData->mCameraFlags & CAMERA_DATA_FLAG_40) {
            _104 |= CAMERA_FLAG_40;
        }

        switch (_104 & CAMERA_PROJECTION_MASK) {
            case GS_CAMERA_ORTHO:
                _168 = 0.f;
                _170 = 0.f;
                _174 = mCameraData->_34;
                _16c = mCameraData->_34 / mCameraData->_38;
                break;
            case GS_CAMERA_FRUSTUM: {
                f32 halfWidth = 0.5f * mCameraData->_34;
                _174 = halfWidth;
                _170 = -halfWidth;
                f32 halfHeight = halfWidth / mCameraData->_38;
                _16c = halfHeight;
                _168 = -halfHeight;
                break;
            }
            case GS_CAMERA_PERSPECTIVE:
            default:
                _168 = RAD_TO_DEG(mCameraData->_34);
                _16c = mCameraData->_38;
                break;
        }

        _17c = mCameraData->_3c;
        _180 = mCameraData->_40;
        _184 = mCameraData->_44;

        if (mCameraData->_48) {
            _188 = mCameraData->_48->_0;
            _194 = mCameraData->_48->_c;
            _1a0 = mCameraData->_48->_18;
        } else {
            _188.set(0.f, 0.f, 0.f);
            _194.set(0.f, 1.f, 0.f);
            _1a0.set(0.f, 0.f, -1.f);
        }

        _1d0 = NULL;
        _104 |= CAMERA_FLAG_VIEW_DIRTY | CAMERA_FLAG_PROJECTION_DIRTY;
    }
}

void GScamera::fn_801DEEF8(GSanimationObject *animObj, GSchannelData *channel, f32 cursor, bool blend) {
    GScamera *camera = static_cast<GScamera *>(animObj);

    if (blend) {
        return;
    }

    switch (channel->mChannel) {
        case CHANNEL_168:
            fn_801E10C0(channel, cursor, &camera->_168);
            camera->_104 |= CAMERA_FLAG_PROJECTION_DIRTY;
            break;
        case CHANNEL_16C:
            fn_801E10C0(channel, cursor, &camera->_16c);
            camera->_104 |= CAMERA_FLAG_PROJECTION_DIRTY;
            break;
        case CHANNEL_17C:
            fn_801E10C0(channel, cursor, &camera->_17c);
            camera->_104 |= CAMERA_FLAG_PROJECTION_DIRTY;
            break;
        case CHANNEL_180:
            fn_801E10C0(channel, cursor, &camera->_180);
            camera->_104 |= CAMERA_FLAG_PROJECTION_DIRTY;
            break;
        case CHANNEL_184: fn_801E10C0(channel, cursor, &camera->_184); break;
        case CHANNEL_188:
            fn_801E1278(channel, cursor, &camera->_188);
            camera->_104 |= CAMERA_FLAG_VIEW_DIRTY;
            break;
        case CHANNEL_1A0:
            fn_801E1278(channel, cursor, &camera->_1a0);
            camera->_104 |= CAMERA_FLAG_VIEW_DIRTY;
            break;
        case CHANNEL_194:
            fn_801E1278(channel, cursor, &camera->_194);
            camera->_104 |= CAMERA_FLAG_VIEW_DIRTY;
            break;
    }
}
