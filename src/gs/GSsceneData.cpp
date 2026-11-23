#include "gs/GSsceneData.hpp"

#include ".unsorted/80205954.hpp"
#include ".unsorted/80220DC4.hpp"
#include "gs/GShierarchyModule.hpp"
#include "gs/GSmenuModule.hpp"
#include "gs/GSrender.hpp"
#include "gs/render/GSrenderTarget.hpp"
#include "gs/render/GStexture.hpp"
#include "gs/scene/GScamera.hpp"
#include "gs/scene/GSlight.hpp"
#include "gs/scene/GSmaterial.hpp"
#include "gs/scene/GSmodel.hpp"
#include "gs/scene/GSnull.hpp"

#include <revolution/gx/GXEnum.h>
#include <string.h>

#include "common.hpp"

/* 0x80491870 */ static GSmeshRenderSettings lbl_80491870(false);
/* 0x8049188C */ static GSmeshRenderSettings lbl_8049188C(true);
/* 0x804918A8 */ static _UnkObjectData_1 lbl_804918A8;
/* 0x804918B4 */ static _UnkObjectData_1 lbl_804918B4;

// TODO(samm) #define the start of logical memory somewhere
template <typename T>
static inline void fixPointer(T **pointer, u32 baseAddr) {
    if (baseAddr && *pointer && (u32)*pointer < 0x80000000) {
        *pointer = (T *)((u32)*pointer + baseAddr);
    }
}

template <typename T>
static inline void initTextureList(T *data, u32 baseAddr) {
    GStexture **texList;
    u16 texCount;
    u16 texIndex;

    texCount = data->mTextureCount;
    texList = data->mTextureList;

    for (texIndex = 0; texIndex < texCount; texIndex++, texList++) {
        if (!*texList) {
            continue;
        }

        fixPointer(texList, baseAddr);
        *texList = fn_8023D6CC(*texList);

        if (GSrender::sInstance->get_7a()) {
            GXTexFilter magFilter = (*texList)->mMagFilter;
            if (magFilter < GX_NEAR_MIP_NEAR) {
                magFilter = GX_NEAR_MIP_NEAR;
            }

            GXTexFilter minFilter = (*texList)->mMinFilter;
            if (minFilter < GX_NEAR_MIP_NEAR) {
                minFilter = GX_NEAR_MIP_NEAR;
            }

            u32 filterFlags = (*texList)->mFilterFlags;
            fn_8023E3C8(*texList, minFilter, magFilter, filterFlags);
        }
    }

    GSrender::sInstance->invalidateTextureCache();
}

static inline void releaseTextureList(GSsceneData *sceneData) {
    u16 texCount;
    u16 texIndex;
    GStexture **texList;

    texCount = sceneData->mTextureCount;
    texList = sceneData->mTextureList;

    for (texIndex = 0; texIndex < texCount; texIndex++, texList++) {
        if (*texList) {
            (*texList)->fn_8023E2D0();
        }
    }
}

template <typename T>
static inline void initRenderSettingsList(T *data, u32 baseAddr) {
    u16 rsCount;
    u16 rsIndex;
    GSmeshRenderSettings **rsList;

    rsCount = data->mRenderSettingsCount;
    rsList = data->mRenderSettingsList;

    for (rsIndex = 0; rsIndex < rsCount; rsIndex++, rsList++) {
        if (!*rsList) {
            continue;
        }

        fixPointer(rsList, baseAddr);
        fn_801E1714(*rsList, &data->mVersion, baseAddr);
    }
}

static inline void releaseRenderSettingsList(GSsceneData *sceneData) {
    u16 rsCount;
    u16 rsIndex;
    GSmeshRenderSettings **rsList;

    rsCount = sceneData->mRenderSettingsCount;
    rsList = sceneData->mRenderSettingsList;

    for (rsIndex = 0; rsIndex < rsCount; rsIndex++, rsList++) {
        if (*rsList) {
            fn_801E1740(*rsList);
        }
    }
}

template <typename T>
static inline void initMaterialList(T *data, u32 baseAddr) {
    u16 matCount;
    u16 matIndex;
    GSmaterialData **matList;

    matCount = data->mMaterialCount;
    matList = data->mMaterialList;

    for (matIndex = 0; matIndex < matCount; matIndex++, matList++) {
        if (!*matList) {
            continue;
        }

        fixPointer(matList, baseAddr);
        fn_801E18F8(*matList, &data->mVersion, baseAddr);
    }
}

static inline void releaseMaterialList(GSsceneData *sceneData) {
    u16 matCount;
    u16 matIndex;
    GSmaterialData **matList;

    matCount = sceneData->mMaterialCount;
    matList = sceneData->mMaterialList;

    for (matIndex = 0; matIndex < matCount; matIndex++, matList++) {
        if (*matList) {
            fn_801E1C78(*matList);
        }
    }
}

static inline void initObjectList(GSsceneData *sceneData, u32 baseAddr) {
    u16 objCount;
    u16 objIndex;
    GSobjectData **objList;

    objCount = sceneData->mObjectCount;
    objList = sceneData->mObjectList;

    for (objIndex = 0; objIndex < objCount; objIndex++, objList++) {
        if (!*objList) {
            continue;
        }

        fixPointer(objList, baseAddr);
        fn_801E2F60(*objList, &sceneData->mVersion, baseAddr, (bool)sceneData->mEnvData);
    }
}

static inline void releaseObjectList(GSsceneData *sceneData) {
    GSobjectData **objList;
    u16 objCount;
    u16 objIndex;

    objCount = sceneData->mObjectCount;
    objList = sceneData->mObjectList;

    for (objIndex = 0; objIndex < objCount; objIndex++, objList++) {
        if (*objList) {
            fn_801E31EC(*objList, (bool)sceneData->mEnvData);
        }
    }
}

// TODO: Relocates a channel using this file's version
void fn_801E0A54(GSchannelData *channelData, u32 baseAddr) {
    fn_801E0A60(channelData, &version, baseAddr);
}

// TODO: Relocates a channel and picks its step callback
void fn_801E0A60(GSchannelData *channelData, const Version *version, u32 baseAddr) {
    fixPointer(&channelData->mKeyframes, baseAddr);

    if (!channelData->mKeyframes) {
        return;
    }

    GSkeyframe *keyframes = NULL;
    u16 keyframeCount = 0;
    f32 *pDuration = NULL;

    switch (channelData->mChannel) {
        case 0:
        case 1:
        case 2:
        case 3:
            channelData->_0 = false;
            channelData->mStepCallback = GSnull::fn_801F3D44;
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
            channelData->_0 = false;
            channelData->mStepCallback = GScamera::fn_801DEEF8;
            break;
        case 17:
        case 18:
            channelData->_0 = false;
            channelData->mStepCallback = GSmodel::fn_801F1554;
            break;
        case 19:
            channelData->_0 = false;
            channelData->mStepCallback = GSlight::fn_801E6BB0;
            break;
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
            channelData->_0 = true;
            channelData->mStepCallback = GSmaterial::fn_801EC9AC;
            break;
    }

    GSanimTrackData *trackData;
    switch (channelData->mDataType) {
        // NOTE(samm) There is no difference between any of the cases
        case 0:
            trackData = channelData->mKeyframes;
            fixPointer(&trackData->mValues, baseAddr);
            fixPointer(&trackData->mControls, baseAddr);
            fixPointer(&trackData->mKeyframes, baseAddr);
            keyframeCount = trackData->mKeyframCount;
            pDuration = &trackData->mDuration;
            keyframes = trackData->mKeyframes;
            break;
        case 1:
            trackData = channelData->mKeyframes;
            fixPointer(&trackData->mValues, baseAddr);
            fixPointer(&trackData->mControls, baseAddr);
            fixPointer(&trackData->mKeyframes, baseAddr);
            keyframeCount = trackData->mKeyframCount;
            pDuration = &trackData->mDuration;
            keyframes = trackData->mKeyframes;
            break;
        case 2:
            trackData = channelData->mKeyframes;
            fixPointer(&trackData->mValues, baseAddr);
            fixPointer(&trackData->mControls, baseAddr);
            fixPointer(&trackData->mKeyframes, baseAddr);
            keyframeCount = trackData->mKeyframCount;
            pDuration = &trackData->mDuration;
            keyframes = trackData->mKeyframes;
            break;
        case 3:
            trackData = channelData->mKeyframes;
            fixPointer(&trackData->mValues, baseAddr);
            fixPointer(&trackData->mControls, baseAddr);
            fixPointer(&trackData->mKeyframes, baseAddr);
            keyframeCount = trackData->mKeyframCount;
            pDuration = &trackData->mDuration;
            keyframes = trackData->mKeyframes;
            break;
        case 4:
            trackData = channelData->mKeyframes;
            fixPointer(&trackData->mValues, baseAddr);
            fixPointer(&trackData->mControls, baseAddr);
            fixPointer(&trackData->mKeyframes, baseAddr);
            keyframeCount = trackData->mKeyframCount;
            pDuration = &trackData->mDuration;
            keyframes = trackData->mKeyframes;
            break;
        case 5:
            trackData = channelData->mKeyframes;
            fixPointer(&trackData->mValues, baseAddr);
            fixPointer(&trackData->mControls, baseAddr);
            fixPointer(&trackData->mKeyframes, baseAddr);
            keyframeCount = trackData->mKeyframCount;
            pDuration = &trackData->mDuration;
            keyframes = trackData->mKeyframes;
            break;
        case 6:
            trackData = channelData->mKeyframes;
            fixPointer(&trackData->mValues, baseAddr);
            fixPointer(&trackData->mControls, baseAddr);
            fixPointer(&trackData->mKeyframes, baseAddr);
            keyframeCount = trackData->mKeyframCount;
            pDuration = &trackData->mDuration;
            keyframes = trackData->mKeyframes;
            break;
        case 7:
            trackData = channelData->mKeyframes;
            fixPointer(&trackData->mValues, baseAddr);
            fixPointer(&trackData->mControls, baseAddr);
            fixPointer(&trackData->mKeyframes, baseAddr);
            keyframeCount = trackData->mKeyframCount;
            pDuration = &trackData->mDuration;
            keyframes = trackData->mKeyframes;
            break;
        case 8:
            trackData = channelData->mKeyframes;
            fixPointer(&trackData->mValues, baseAddr);
            fixPointer(&trackData->mControls, baseAddr);
            fixPointer(&trackData->mKeyframes, baseAddr);
            keyframeCount = trackData->mKeyframCount;
            pDuration = &trackData->mDuration;
            keyframes = trackData->mKeyframes;
            break;
    }

    if (pDuration && keyframes && keyframeCount) {
        *pDuration = 0.f;
        for (u16 i = 0; i < keyframeCount; i++, keyframes++) {
            if (*pDuration < keyframes->mTime) {
                *pDuration = keyframes->mTime;
            }
        }
    }
}

// TODO: Release counterpart of fn_801E0A60 (empty)
void fn_801E10BC(GSchannelData *channelData) {}

// TODO: Samples a channel into a float
void fn_801E10C0(GSchannelData *channelData, f32 cursor, f32 *dst) {
    switch (channelData->mDataType) {
        case 0: *dst = GSmath::fn_80221B2C(cursor, channelData->mKeyframes, 0); break;
        case 5: {
            u8 result = GSmath::animSampleU8(cursor, channelData->mKeyframes, channelData->mScaleExp);
            *dst = (f32)result / (1 << channelData->mScaleExp);
        } break;
        case 6: {
            s8 result = GSmath::animSampleS8(cursor, channelData->mKeyframes, channelData->mScaleExp);
            *dst = (f32)result / (1 << channelData->mScaleExp);
        } break;
        case 7: {
            u16 result = GSmath::animSampleU16(cursor, channelData->mKeyframes, channelData->mScaleExp);
            *dst = (f32)result / (1 << channelData->mScaleExp);
        } break;
        case 8: {
            s16 result = GSmath::animSampleS16(cursor, channelData->mKeyframes, channelData->mScaleExp);
            *dst = (f32)result / (1 << channelData->mScaleExp);
        } break;
    }
}

// TODO: Samples a channel into a vector
void fn_801E1278(GSchannelData *channelData, f32 cursor, GSvec *dst) {
    switch (channelData->mComponent) {
        case 0: {
            GSvec result;
            GSmath::animSampleVec3(&result, cursor, channelData->mKeyframes, 0);
            *dst = result;
        } break;
        case 1: {
            fn_801E10C0(channelData, cursor, &dst->x);
        } break;
        case 2: {
            fn_801E10C0(channelData, cursor, &dst->y);
        } break;
        case 3: {
            fn_801E10C0(channelData, cursor, &dst->z);
        } break;
        // NOTE(samm) These appear bugged, since the function they call also switches on mComponent, but uses 0-2
        case 4: {
            GSvec2 result;
            fn_801E13B8(channelData, cursor, &result);
            dst->x = result.x;
            dst->y = result.y;
        } break;
        case 5: {
            GSvec2 result;
            fn_801E13B8(channelData, cursor, &result);
            dst->x = result.x;
            dst->z = result.y;
        } break;
        case 6: {
            GSvec2 result;
            fn_801E13B8(channelData, cursor, &result);
            dst->y = result.x;
            dst->z = result.y;
        } break;
    }
}

// TODO: Samples a channel into a quaternion
void fn_801E1360(GSchannelData *channelData, f32 cursor, GSquat *dst) {
    GSquat result;
    GSmath::animSampleQuat(&result, cursor, channelData->mKeyframes, 0);
    *dst = result;
}

// TODO: Samples a channel into a 2D vector
void fn_801E13B8(GSchannelData *channelData, f32 cursor, GSvec2 *dst) {
    switch (channelData->mComponent) {
        case 0: *dst = GSmath::fn_80221F8C(cursor, channelData->mKeyframes, 0); break;
        case 1: fn_801E10C0(channelData, cursor, &dst->x); break;
        case 2: fn_801E10C0(channelData, cursor, &dst->y); break;
    }
}

// TODO: Samples a channel into a colour
void fn_801E1440(GSchannelData *channelData, f32 cursor, GScolor<u8> *dst) {
    switch (channelData->mComponent) {
        case 0: {
            u32 result = GSmath::fn_80223164(cursor, channelData->mKeyframes, 0);
            GScolor<u8> color(result >> 24, result >> 16, result >> 8, result);
            dst->r = color.r;
            dst->g = color.g;
            dst->b = color.b;
            dst->a = color.a;
        } break;
        case 1: fn_801E1504(channelData, cursor, &dst->r); break;
        case 2: fn_801E1504(channelData, cursor, &dst->g); break;
        case 3: fn_801E1504(channelData, cursor, &dst->b); break;
        case 4: fn_801E1504(channelData, cursor, &dst->a); break;
    }
}

// TODO: Samples a channel into a byte
void fn_801E1504(GSchannelData *channelData, f32 cursor, u8 *dst) {
    *dst = GSmath::animSampleU8(cursor, channelData->mKeyframes, channelData->mScaleExp);
}

// TODO: Relocates a keyframe data list
void fn_801E1540(GSkeyframeData *keyframeData, const Version *version, u32 baseAddr) {
    fixPointer(&keyframeData->mChannels, baseAddr);

    GSchannelData *channelData = keyframeData->mChannels;
    for (u16 i = 0; i < keyframeData->mChannelCount; i++, channelData++) {
        fn_801E0A60(channelData, version, baseAddr);
    }

    fixPointer(&keyframeData->mNext, baseAddr);

    if (keyframeData->mNext) {
        fn_801E1540(keyframeData->mNext, version, baseAddr);
    }
}

// TODO: Release counterpart of fn_801E1540
void fn_801E1614(GSkeyframeData *keyframeData) {
    if (keyframeData->mNext) {
        fn_801E1614(keyframeData->mNext);
    }

    GSchannelData *channelData = keyframeData->mChannels;
    for (u16 i = 0; i < keyframeData->mChannelCount; i++, channelData++) {
        fn_801E10BC(channelData);
    }
}

GSmeshRenderSettings::GSmeshRenderSettings(bool arg0) {
    mBlend = true;
    mColorUpdateEnable = true;
    mAlphaUpdateEnable = true;
    mZUpdateEnable = true;
    mZCompareFunc = GX_LEQUAL;
    mAlphaCompEnable = false;
    mAlphaComp = GX_ALWAYS;
    mAlphaRef = 0;
    mCullMode = GX_CULL_BACK;
    mDstAlphaEnable = false;
    mDstAlpha = 0xff;
    mZTexOp = GX_ZT_DISABLE;
    mZTexBias = 0;
    mZTexture = NULL;

    if (arg0) {
        mBlendMode = GX_BM_BLEND;
        mBlendSrcFactor = GX_BL_SRCALPHA;
        mBlendDstFactor = GX_BL_INVSRCALPHA;
    } else {
        mBlendMode = GX_BM_NONE;
        mBlendSrcFactor = GX_BL_ONE;
        mBlendDstFactor = GX_BL_ZERO;
    }
    mBlendOp = GX_LO_NOOP;
}

// TODO: Relocates mesh render settings
void fn_801E1714(GSmeshRenderSettings *renderSettings, const Version *version, u32 baseAddr) {
    fixPointer(&renderSettings->mZTexture, baseAddr);
}

// TODO: Release counterpart of fn_801E1714 (empty)
void fn_801E1740(GSmeshRenderSettings *renderSettings) {}

GSmaterialData::GSmaterialData()
    : mName(),
      mTextureSlots(),
      _2c(),
      _40(),
      _50(),
      _54(),
      _58(),
      _59(),
      mTextureCount(),
      _5b(),
      _5c(),
      _5d(1),
      _5e(),
      _5f(),
      _60(0, 0, 0, 0),
      _64(0x80, 0x80, 0x80, 0xff),
      _68(0.0f),
      _6c(-1),
      _6d(),
      _6e(-1),
      _6f(),
      _70(0, 0, 0, 0),
      _74(-1),
      _75(),
      _76(-1),
      _77(-1),
      _78(0, 0, 0, 0),
      _7c(50.0f),
      _80(0xff, 0xff, 0xff, 0xff),
      mKeyframes(),
      _88() {
    memset(_4, 0, sizeof(_4));

    for (u32 i = 0; i < 3; i++) {
        _c[i][0] = 0;
        _c[i][1] = 1;
        _c[i][2] = 2;
        _c[i][3] = 3;
    }

    memset(mTextureSlots, 0, sizeof(mTextureSlots));
    memset(_2c, 0, sizeof(_2c));
    memset(_40, 0, sizeof(_40));
}

// TODO: Relocates material data
void fn_801E18F8(GSmaterialData *materialData, const Version *version, u32 baseAddr) {
    if (*version < VERSION(1, 3, 0)) {
        materialData->_54 = 0;
    }
    if (*version < VERSION(1, 4, 0)) {
        materialData->_50 = NULL;
    }

    fixPointer(&materialData->mName, baseAddr);
    fixPointer(&materialData->_50, baseAddr);

    GStexture **texSlots = materialData->mTextureSlots;
    for (u32 i = 0; i < MATERIAL_MAX_TEXTURE_SLOTS; i++, texSlots++) {
        fixPointer(texSlots, baseAddr);
    }

    _UnkMaterialData_2 **_unkVar1 = materialData->_2c;
    for (u32 i = 0; i < MATERIAL_MAX_TEXTURE_SLOTS; i++, _unkVar1++) {
        fixPointer(_unkVar1, baseAddr);
    }

    // TODO(samm) Clean up these types!!!
    u32 _unkVar3 = 0;
    _UnkMaterialData_1 *(*_unkVar2)[2] = (_UnkMaterialData_1 * (*)[2]) materialData->_40;
    for (u32 i = 0; i < 2; i++, _unkVar2++) {
        for (u32 j = 0; j < 2; j++) {
            fixPointer(&(*_unkVar2)[j], baseAddr);

            if (_unkVar3 == 0 && (*_unkVar2)[j] && !materialData->_50) {
                switch ((*_unkVar2)[j]->_0) {
                    case 0:
                    case 2: materialData->_50 = materialData->mTextureSlots[(*_unkVar2)[j]->_4]; break;
                }
            }
            _unkVar3++;
        }
    }

    fixPointer(&materialData->mKeyframes, baseAddr);

    if (materialData->mKeyframes) {
        fn_801E1540(materialData->mKeyframes, version, baseAddr);
    }
}

// TODO: Release counterpart of fn_801E18F8
void fn_801E1C78(GSmaterialData *materialData) {
    if (materialData->mKeyframes) {
        fn_801E1614(materialData->mKeyframes);
    }
}

GSnodeData::GSnodeData()
    : mNodeType(GS_NODE_NULL),
      mName(),
      mIndex(),
      mFlags((1 << 3) | (1 << 4)),
      mTranslation(),
      mRotation(),
      mScale(),
      mTransformPivots(),
      _1c(0.0f),
      mAnimData(),
      mFirstChild(),
      mNextSibling(),
      _2c() {}

// TODO: Relocates a node tree
void fn_801E1CD0(GSnodeData *nodeData, const Version *version, u32 baseAddr) {
    switch (nodeData->mNodeType) {
        case GS_NODE_JOINT:    fn_801E2A90(static_cast<GSjointData *>(nodeData), version, baseAddr); break;
        case GS_NODE_MODEL:    fn_801E2878(static_cast<GSmodelNodeData *>(nodeData), version, baseAddr); break;
        case GS_NODE_CAMERA:   fn_801E2AE8(static_cast<GScameraData *>(nodeData), version, baseAddr); break;
        case GS_NODE_LIGHT:    fn_801E2A60(static_cast<GSlightData *>(nodeData), version, baseAddr); break;
        case GS_NODE_PARTICLE: fn_801E2B40(static_cast<GSparticleData *>(nodeData), version, baseAddr); break;
        case GS_NODE_VOLUME:   fn_801E2D88(static_cast<GSvolumeData *>(nodeData), version, baseAddr); break;
    }

    fixPointer(&nodeData->mName, baseAddr);
    fixPointer(&nodeData->mTranslation, baseAddr);
    fixPointer(&nodeData->mRotation, baseAddr);
    fixPointer(&nodeData->mScale, baseAddr);
    fixPointer(&nodeData->mTransformPivots, baseAddr);
    fixPointer(&nodeData->mAnimData, baseAddr);
    fixPointer(&nodeData->mNextSibling, baseAddr);
    fixPointer(&nodeData->mFirstChild, baseAddr);
    fixPointer(&nodeData->_2c, baseAddr);

    _TransformPivots *pivots = nodeData->mTransformPivots;
    if (pivots) {
        if (*version < VERSION(1, 3, 0)) {
            if (pivots->_24_0 != 0xfefefefe || pivots->_24_1 != 0xfefefefe || pivots->_24_2 != 0xfefefefe) {
                GSvec _unk1, _unk2, _unk3;

                _unk1 = -pivots->mScalePivot;
                _unk2 = pivots->mScalePivot;

                VECAdd(&_unk2, &pivots->mScaleToRot, &_unk2);
                VECSubtract(&_unk2, &pivots->mRotToTrans, &_unk2);

                _unk3 = pivots->mRotToTrans;
                VECAdd(&_unk3, &pivots->_24, &_unk3);

                nodeData->mTransformPivots->mScalePivot = _unk1;
                nodeData->mTransformPivots->mScaleToRot = _unk2;
                nodeData->mTransformPivots->mRotToTrans = _unk3;

                pivots->_24_0 = 0xfefefefe;
                pivots->_24_1 = 0xfefefefe;
                pivots->_24_2 = 0xfefefefe;
            };
        }
    }

    if (nodeData->mAnimData) {
        fn_801E1540(nodeData->mAnimData, version, baseAddr);
    }

    if (nodeData->mFirstChild) {
        fn_801E1CD0(nodeData->mFirstChild, version, baseAddr);
    }

    if (nodeData->mNextSibling) {
        fn_801E1CD0(nodeData->mNextSibling, version, baseAddr);
    }
}

// TODO: Release counterpart of fn_801E1CD0
void fn_801E2090(GSnodeData *nodeData) {
    if (nodeData->mNextSibling) {
        fn_801E2090(nodeData->mNextSibling);
    }

    if (nodeData->mFirstChild) {
        fn_801E2090(nodeData->mFirstChild);
    }

    if (nodeData->mAnimData) {
        fn_801E1614(nodeData->mAnimData);
    }

    // NOTE The particle and volume cases are swapped compared to fn_801E1CD0
    switch (nodeData->mNodeType) {
        case GS_NODE_JOINT:    fn_801E2AE4(static_cast<GSjointData *>(nodeData)); break;
        case GS_NODE_MODEL:    fn_801E2938(static_cast<GSmodelNodeData *>(nodeData)); break;
        case GS_NODE_CAMERA:   fn_801E2B3C(static_cast<GScameraData *>(nodeData)); break;
        case GS_NODE_LIGHT:    fn_801E2A8C(static_cast<GSlightData *>(nodeData)); break;
        case GS_NODE_PARTICLE: fn_801E2E20(static_cast<GSvolumeData *>(nodeData)); break;
        case GS_NODE_VOLUME:   fn_801E2D84(static_cast<GSparticleData *>(nodeData)); break;
    }
}

// TODO: Relocates a mesh list and builds its display lists
void fn_801E2168(GSmeshData *meshData, const Version *version, u32 baseAddr, GSmodelData *modelData) {
    if (meshData->_c == 0) {
        meshData->_c = 1;
    }

    fixPointer(&meshData->mRenderSettings, baseAddr);
    fixPointer(&meshData->mMaterial, baseAddr);
    fixPointer(&meshData->_10, baseAddr);
    fixPointer(&meshData->mDisplayList, baseAddr);
    fixPointer(&meshData->mNext, baseAddr);

    if (meshData->mNext) {
        fn_801E2168(meshData->mNext, version, baseAddr, modelData);
    }

    fixPointer(&meshData->_20, baseAddr);

    switch (meshData->_0) {
        case 0: break;
        case 1: meshData->mRenderSettings = &lbl_80491870; break;
        case 2: meshData->mRenderSettings = &lbl_8049188C; break;
    }

    if (meshData->_10 && !meshData->_10->mDisplayList) {
        Unk801E2168 *displayList = new Unk801E2168;
        if (displayList) {
            for (Unk801E2168Attr *attr = meshData->_10->mAttrs; attr->mAttr != 0xff; attr++) {
                u32 size = 0;
                switch (attr->mAttr) {
                    case GX_VA_PNMTXIDX:
                    case GX_VA_TEX0MTXIDX:
                    case GX_VA_TEX1MTXIDX:
                    case GX_VA_TEX2MTXIDX:
                    case GX_VA_TEX3MTXIDX:
                    case GX_VA_TEX4MTXIDX:
                    case GX_VA_TEX5MTXIDX:
                    case GX_VA_TEX6MTXIDX:
                    case GX_VA_TEX7MTXIDX: break;
                    case GX_VA_POS:        size = attr->mStride * modelData->mVertexCount; break;
                    case GX_VA_NRM:        size = attr->mStride * modelData->mVertexCount; break;
                    case GX_VA_NBT:        size = attr->mStride * modelData->mVertexCount; break;
                    case GX_VA_CLR0:       size = attr->mStride * modelData->_4; break;
                    case GX_VA_TEX0:
                    case GX_VA_TEX1:
                    case GX_VA_TEX2:
                    case GX_VA_TEX3:
                    case GX_VA_TEX4:
                    case GX_VA_TEX5:
                    case GX_VA_TEX6:
                    case GX_VA_TEX7:
                        if (modelData->_14) {
                            size = attr->mStride * modelData->_14[attr->mAttr - GX_VA_TEX0].mCount;
                        }
                        break;
                }

                if (size) {
                    displayList->mVertexFormat.fn_8023CAD8(attr->mAttr, attr->mCompCount, attr->mCompType, attr->mFrac);
                    displayList->mVertexFormat.fn_8023CC30(attr->mAttr, attr->_4, -1, attr->mStride, size);
                }
            }

            displayList->mDisplayList.fn_80232988(&displayList->mVertexFormat,
                                                  meshData->mDisplayList,
                                                  meshData->mDisplayListSize,
                                                  meshData->_c);
            meshData->_10->mDisplayList = displayList;
        }
    }
}

// TODO: Release counterpart of fn_801E2168
void fn_801E2444(GSmeshData *meshData) {
    switch (meshData->_0) {
        case 0: break;
        case 1: meshData->mRenderSettings = NULL; break;
        case 2: meshData->mRenderSettings = NULL; break;
    }

    if (meshData->_10->mDisplayList) {
        delete meshData->_10->mDisplayList;
        meshData->_10->mDisplayList = NULL;
    }

    if (meshData->mNext) {
        fn_801E2444(meshData->mNext);
    }
}

// TODO: Relocates model data
void fn_801E24F8(GSmodelData *modelData, const Version *version, u32 baseAddr) {
    fixPointer(&modelData->mVertices, baseAddr);
    fixPointer(&modelData->mWeights, baseAddr);

    if (modelData->mWeights) {
        fixPointer(&modelData->mWeights->_4, baseAddr);
        fixPointer(&modelData->mWeights->_c, baseAddr);
        fixPointer(&modelData->mWeights->_10, baseAddr);
        fixPointer(&modelData->mWeights->_18, baseAddr);
    }

    fixPointer(&modelData->mVertexColors, baseAddr);
    fixPointer(&modelData->_14, baseAddr);

    _UnkModelData_2 *texCoords = modelData->_14;
    if (texCoords) {
        u32 count = modelData->_6;
        for (u32 i = 0; i < count; i++, texCoords++) {
            fixPointer(&texCoords->mTexCoords, baseAddr);
        }
    }

    fixPointer(&modelData->mFirstMesh, baseAddr);

    if (modelData->mFirstMesh) {
        fn_801E2168(modelData->mFirstMesh, version, baseAddr, modelData);
    }

    fixPointer(&modelData->_1c, baseAddr);

    if (modelData->_1c) {
        fn_801E294C(modelData->_1c, baseAddr);
    }

    fixPointer(&modelData->_20, baseAddr);

    if (modelData->_20) {
        fixPointer(&modelData->_20->_0, baseAddr);
        fixPointer(&modelData->_20->_8, baseAddr);
    } else {
        modelData->_20 = &lbl_804918A8;
    }

    if ((modelData->mFlags & (1 << 9))) {
        GSrenderTarget::_unkFunc_1(GShierarchyModule::getInstance()->get_134());
    }
}

// TODO: Release counterpart of fn_801E24F8
void fn_801E2810(GSmodelData *modelData) {
    if (modelData->mFirstMesh) {
        fn_801E2444(modelData->mFirstMesh);
    }

    if ((modelData->mFlags & (1 << 9))) {
        GSrenderTarget::_unkFunc_2(GShierarchyModule::getInstance()->get_134());
    }
}

// TODO: Relocates model node data
void fn_801E2878(GSmodelNodeData *nodeData, const Version *version, u32 baseAddr) {
    fixPointer(&nodeData->mModelData, baseAddr);

    if (nodeData->mModelData) {
        fn_801E24F8(nodeData->mModelData, version, baseAddr);
    }

    fixPointer(&nodeData->_34, baseAddr);
    fixPointer(&nodeData->_38, baseAddr);
}

// TODO: Release counterpart of fn_801E2878
void fn_801E2938(GSmodelNodeData *nodeData) {
    if (nodeData->mModelData) {
        fn_801E2810(nodeData->mModelData);
    }
}

// TODO: Relocates the table at _UnkModelData_1::_1c
void fn_801E294C(_UnkModelData_1 *arg0, u32 baseAddr) {
    fixPointer(&arg0->_1c, baseAddr);

    for (u16 i = 0; i < arg0->_18; i++) {
        fixPointer(&arg0->_1c[i]._4, baseAddr);
    }
}

GSlightData::GSlightData() {
    mLightFlags = (1 << 2) | (1 << 3) | (1 << 4);
    mColor.r = 0xff;
    mColor.g = 0xff;
    mColor.b = 0xff;
    mColor.a = 0xff;
    _38.r = 0x80;
    _38.g = 0x80;
    _38.b = 0x80;
    _38.a = 0xff;
    _3c = 0.0f;
    mDistAttnFn = GX_DA_OFF;
    mRefDistance = 100.0f;
    mRefBrightness = 0.5f;
    mSpotFn = GX_SP_OFF;
    mCutoff = 90.0f;
    _54 = NULL;
    mNodeType = GS_NODE_LIGHT;
}

// TODO: Relocates light node data
void fn_801E2A60(GSlightData *nodeData, const Version *version, u32 baseAddr) {
    fixPointer(&nodeData->_54, baseAddr);
}

// TODO: Release counterpart of fn_801E2A60 (empty)
void fn_801E2A8C(GSlightData *nodeData) {}

// TODO: Relocates joint node data
void fn_801E2A90(GSjointData *nodeData, const Version *version, u32 baseAddr) {
    fixPointer(&nodeData->_40, baseAddr);
    fixPointer(&nodeData->_74, baseAddr);
}

// TODO: Release counterpart of fn_801E2A90 (empty)
void fn_801E2AE4(GSjointData *nodeData) {}

// TODO: Relocates camera node data
void fn_801E2AE8(GScameraData *nodeData, const Version *version, u32 baseAddr) {
    fixPointer(&nodeData->_48, baseAddr);
    fixPointer(&nodeData->_4c, baseAddr);
}

// TODO: Release counterpart of fn_801E2AE8 (empty)
void fn_801E2B3C(GScameraData *nodeData) {}

// TODO: Relocates particle node data
void fn_801E2B40(GSparticleData *nodeData, const Version *version, u32 baseAddr) {
    fixPointer(&nodeData->_38, baseAddr);
    fixPointer(&nodeData->_3c, baseAddr);
    fixPointer(&nodeData->_40, baseAddr);
    fixPointer(&nodeData->_44, baseAddr);
    fixPointer(&nodeData->_4c, baseAddr);
    fixPointer(&nodeData->_54, baseAddr);
    fixPointer(&nodeData->_58, baseAddr);
    fixPointer(&nodeData->_60, baseAddr);
    fixPointer(&nodeData->_64, baseAddr);

    Unk801E294C *entry = nodeData->_40;
    u16 count = nodeData->_34;
    while (count--) {
        fixPointer(&entry->_4, baseAddr);
        entry++;
    }

    fixPointer(&nodeData->_68, baseAddr);

    if (nodeData->_68) {
        fn_801E294C(nodeData->_68, baseAddr);
    }

    fixPointer(&nodeData->_6c, baseAddr);
}

// TODO: Release counterpart of fn_801E2B40 (empty)
void fn_801E2D84(GSparticleData *nodeData) {}

// TODO: Relocates volume node data
void fn_801E2D88(GSvolumeData *nodeData, const Version *version, u32 baseAddr) {
    fixPointer(&nodeData->_34, baseAddr);
    fixPointer(&nodeData->_3c, baseAddr);

    nodeData->_38 = NULL;
    if (nodeData->_34) {
        nodeData->_38 = fn_80206D8C(nodeData->_34);
    }
}

// TODO: Release counterpart of fn_801E2D88
void fn_801E2E20(GSvolumeData *nodeData) {
    if (nodeData->_38) {
        fn_80206DF4(nodeData->_38);
    }
}

// TODO: Relocates animation data
void fn_801E2E34(GSanimationData *animationData, const Version *version, u32 baseAddr) {
    fixPointer(&animationData->mName, baseAddr);
    fixPointer(&animationData->_10, baseAddr);
    fixPointer(&animationData->_14, baseAddr);
    fixPointer(&animationData->_1c, baseAddr);
    fixPointer(&animationData->_20, baseAddr);
    fixPointer(&animationData->_2c, baseAddr);
}

// TODO: Release counterpart of fn_801E2E34 (empty)
void fn_801E2F28(GSanimationData *animationData) {}

GSobjectData::GSobjectData()
    : mName(),
      mId(),
      mNodeCount(),
      mAnimCount(),
      _a(),
      mAnimList(),
      mRootNode(),
      mBoundingBox(),
      _18(&lbl_804918B4) {}

// TODO: Relocates object data
void fn_801E2F60(GSobjectData *objectData, const Version *version, u32 baseAddr, bool arg3) {
    fixPointer(&objectData->mName, baseAddr);
    fixPointer(&objectData->mRootNode, baseAddr);
    fixPointer(&objectData->mAnimList, baseAddr);
    fixPointer(&objectData->mBoundingBox, baseAddr);
    fixPointer(&objectData->_18, baseAddr);

    GSanimationData *animData = objectData->mAnimList;
    for (u16 i = 0; i < objectData->mAnimCount; i++, animData++) {
        fn_801E2E34(animData, version, baseAddr);
    }

    if (objectData->mRootNode) {
        fn_801E1CD0(objectData->mRootNode, version, baseAddr);
    }

    if (objectData->_18) {
        // TODO(samm) Fix regswap here
        fixPointer(&objectData->_18->_0, baseAddr);
        fixPointer(&objectData->_18->_8, baseAddr);
    } else {
        objectData->_18 = &lbl_804918B4;
    }

    if (arg3) {
        GSrenderTarget::_unkFunc_1(GShierarchyModule::getInstance()->get_138());
        GSrenderTarget::_unkFunc_1(GShierarchyModule::getInstance()->get_144());
    } else {
        GSrenderTarget::_unkFunc_1(GShierarchyModule::getInstance()->get_140());
        GSrenderTarget::_unkFunc_1(GShierarchyModule::getInstance()->get_144());
        GSrenderTarget::_unkFunc_1(GSmenuModule::getInstance()->get_10c());
        GSrenderTarget::_unkFunc_1(GSmenuModule::getInstance()->get_110());
    }
}

// TODO: Release counterpart of fn_801E2F60
void fn_801E31EC(GSobjectData *objectData, bool arg1) {
    if (arg1) {
        GSrenderTarget::_unkFunc_2(GShierarchyModule::getInstance()->get_138());
        GSrenderTarget::_unkFunc_2(GShierarchyModule::getInstance()->get_144());
    } else {
        GSrenderTarget::_unkFunc_2(GShierarchyModule::getInstance()->get_140());
        GSrenderTarget::_unkFunc_2(GShierarchyModule::getInstance()->get_144());
        GSrenderTarget::_unkFunc_2(GSmenuModule::getInstance()->get_10c());
        GSrenderTarget::_unkFunc_2(GSmenuModule::getInstance()->get_110());
    }

    if (objectData->mRootNode) {
        fn_801E2090(objectData->mRootNode);
    }

    GSanimationData *animData = objectData->mAnimList;
    for (u16 i = 0; i < objectData->mAnimCount; i++, animData++) {
        fn_801E2F28(animData);
    }
}

GSenvData::GSenvData() : _10(), _14(), _18(), _1c(), _20(), _24() {
    mFogEnable = false;
    mFogType = GX_FOG_LIN;
    mFogRangeAdjEnable = false;
    mFogStartZ = 0.0f;
    mFogEndZ = 1000.0f;
    mFogColor.r = 0xff;
    mFogColor.g = 0xff;
    mFogColor.b = 0xff;
    mFogColor.a = 0xff;
}

// TODO: Relocates environment data
void fn_801E3380(GSenvData *envData, const Version *version, u32 baseAddr) {
    fixPointer(&envData->_14, baseAddr);
    fixPointer(&envData->_10, baseAddr);
    fixPointer(&envData->_18, baseAddr);
    fixPointer(&envData->_1c, baseAddr);
    fixPointer(&envData->_20, baseAddr);

    if (!envData->_20) {
        envData->_20 = envData->_1c;
    }

    fixPointer(&envData->_24, baseAddr);
}

// TODO: Release counterpart of fn_801E3380 (empty)
void fn_801E3488(GSenvData *envData) {}

GSsceneData::GSsceneData()
    : mVersion(version),
      mObjectList(),
      mTextureList(),
      mRenderSettingsList(),
      mMaterialList(),
      mObjectCount(),
      mTextureCount(),
      mRenderSettingsCount(),
      mMaterialCount(),
      _20(),
      mEnvData(),
      _28() {}

// TODO: Relocates a loaded .sdr scene file
void fn_801E34DC(GSsceneData *sceneData, u32 baseAddr) {
    fixPointer(&sceneData->mObjectList, baseAddr);
    fixPointer(&sceneData->mTextureList, baseAddr);
    fixPointer(&sceneData->mRenderSettingsList, baseAddr);
    fixPointer(&sceneData->mMaterialList, baseAddr);
    fixPointer(&sceneData->mEnvData, baseAddr);
    fixPointer(&sceneData->_28, baseAddr);

    initTextureList(sceneData, baseAddr);

    if (sceneData->mEnvData) {
        fn_801E3380(sceneData->mEnvData, &sceneData->mVersion, baseAddr);
    }

    initRenderSettingsList(sceneData, baseAddr);
    initMaterialList(sceneData, baseAddr);

    initObjectList(sceneData, baseAddr);
}

// TODO: Release counterpart of fn_801E34DC
void fn_801E37F0(GSsceneData *sceneData) {
    releaseObjectList(sceneData);

    releaseMaterialList(sceneData);
    releaseRenderSettingsList(sceneData);

    if (sceneData->mEnvData) {
        fn_801E3488(sceneData->mEnvData);
    }

    releaseTextureList(sceneData);
}

// TODO: Relocates a loaded single-object file
void fn_801E3920(Unk801E3920 *data, u32 baseAddr) {
    fixPointer(&data->mObject, baseAddr);
    fixPointer(&data->mTextureList, baseAddr);
    fixPointer(&data->mRenderSettingsList, baseAddr);
    fixPointer(&data->mMaterialList, baseAddr);
    fixPointer(&data->_20, baseAddr);

    initTextureList(data, baseAddr);
    initRenderSettingsList(data, baseAddr);
    initMaterialList(data, baseAddr);

    if (data->mObject) {
        fn_801E2F60(data->mObject, &data->mVersion, baseAddr, false);
    }
}

// TODO: Release counterpart of fn_801E3920
void fn_801E3BA0(Unk801E3920 *data) {
    u16 matIndex;
    u16 matCount;
    GSmaterialData **matList;
    GSmeshRenderSettings **rsList;
    u16 rsIndex;
    u16 rsCount;
    GStexture **texList;
    u16 texIndex;
    u16 texCount;

    if (data->mObject) {
        fn_801E31EC(data->mObject, false);
    }

    matCount = data->mMaterialCount;
    matList = data->mMaterialList;

    for (matIndex = 0; matIndex < matCount; matIndex++, matList++) {
        if (*matList) {
            fn_801E1C78(*matList);
        }
    }

    rsCount = data->mRenderSettingsCount;
    rsList = data->mRenderSettingsList;

    for (rsIndex = 0; rsIndex < rsCount; rsIndex++, rsList++) {
        if (*rsList) {
            fn_801E1740(*rsList);
        }
    }

    texCount = data->mTextureCount;
    texList = data->mTextureList;

    for (texIndex = 0; texIndex < texCount; texIndex++, texList++) {
        if (*texList) {
            (*texList)->fn_8023E2D0();
        }
    }
}

// TODO: Relocates a loaded single-material file
void fn_801E3C94(Unk801E3C94 *data, u32 baseAddr) {
    fixPointer(&data->mTextureList, baseAddr);
    fixPointer(&data->mRenderSettings, baseAddr);
    fixPointer(&data->mMaterial, baseAddr);
    fixPointer(&data->_1c, baseAddr);

    initTextureList(data, baseAddr);

    switch (data->mRenderSettingsType) {
        case 0: fn_801E1714(data->mRenderSettings, &data->mVersion, baseAddr); break;
        case 1: data->mRenderSettings = &lbl_80491870; break;
        case 2: data->mRenderSettings = &lbl_8049188C; break;
    }

    if (data->mMaterial) {
        fn_801E18F8(data->mMaterial, &data->mVersion, baseAddr);
    }
}

// TODO: Release counterpart of fn_801E3C94
void fn_801E3E80(Unk801E3C94 *data) {
    u16 texIndex;
    u16 texCount;
    GStexture **texList;

    if (data->mMaterial) {
        fn_801E1C78(data->mMaterial);
    }

    switch (data->mRenderSettingsType) {
        case 0: fn_801E1740(data->mRenderSettings); break;
        case 1: data->mRenderSettings = NULL; break;
        case 2: data->mRenderSettings = NULL; break;
    }

    texCount = data->mTextureCount;
    texList = data->mTextureList;

    for (texIndex = 0; texIndex < texCount; texIndex++, texList++) {
        if (*texList) {
            (*texList)->fn_8023E2D0();
        }
    }
}

// TODO: Relocates a loaded single-model file
void fn_801E3F48(Unk801E3F48 *data, u32 baseAddr) {
    fixPointer(&data->mTextureList, baseAddr);
    fixPointer(&data->mRenderSettingsList, baseAddr);
    fixPointer(&data->mMaterialList, baseAddr);
    fixPointer(&data->mModel, baseAddr);
    fixPointer(&data->_20, baseAddr);

    initTextureList(data, baseAddr);
    initRenderSettingsList(data, baseAddr);
    initMaterialList(data, baseAddr);

    if (data->mModel) {
        fn_801E24F8(data->mModel, &data->mVersion, baseAddr);
    }
}

// TODO: Release counterpart of fn_801E3F48
void fn_801E41C4(Unk801E3F48 *data) {
    u16 matIndex;
    u16 matCount;
    GSmaterialData **matList;
    GSmeshRenderSettings **rsList;
    u16 rsIndex;
    u16 rsCount;
    GStexture **texList;
    u16 texIndex;
    u16 texCount;

    if (data->mModel) {
        fn_801E2810(data->mModel);
    }

    matCount = data->mMaterialCount;
    matList = data->mMaterialList;

    for (matIndex = 0; matIndex < matCount; matIndex++, matList++) {
        if (*matList) {
            fn_801E1C78(*matList);
        }
    }

    rsCount = data->mRenderSettingsCount;
    rsList = data->mRenderSettingsList;

    for (rsIndex = 0; rsIndex < rsCount; rsIndex++, rsList++) {
        if (*rsList) {
            fn_801E1740(*rsList);
        }
    }

    texCount = data->mTextureCount;
    texList = data->mTextureList;

    for (texIndex = 0; texIndex < texCount; texIndex++, texList++) {
        if (*texList) {
            (*texList)->fn_8023E2D0();
        }
    }
}
