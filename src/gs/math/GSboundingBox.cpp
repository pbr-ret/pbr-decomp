#include "gs/GSmath.hpp"

#include "common.hpp"

static GSvec sActiveBox[8];

namespace GSmath {

static void calcBoundingBoxCorners(const GSboundingBox *aabb) {
    if (aabb->mTransform) {
        sActiveBox[0] = *aabb->mTransform * aabb->mMin;
        sActiveBox[1] = *aabb->mTransform * GSvec(aabb->mMin.x, aabb->mMin.y, aabb->mMax.z);
        sActiveBox[2] = *aabb->mTransform * GSvec(aabb->mMin.x, aabb->mMax.y, aabb->mMin.z);
        sActiveBox[3] = *aabb->mTransform * GSvec(aabb->mMin.x, aabb->mMax.y, aabb->mMax.z);
        sActiveBox[4] = *aabb->mTransform * GSvec(aabb->mMax.x, aabb->mMin.y, aabb->mMin.z);
        sActiveBox[5] = *aabb->mTransform * GSvec(aabb->mMax.x, aabb->mMin.y, aabb->mMax.z);
        sActiveBox[6] = *aabb->mTransform * GSvec(aabb->mMax.x, aabb->mMax.y, aabb->mMin.z);
        sActiveBox[7] = *aabb->mTransform * aabb->mMax;
    } else {
        sActiveBox[0] = aabb->mMin;
        sActiveBox[1] = GSvec(aabb->mMin.x, aabb->mMin.y, aabb->mMax.z);
        sActiveBox[2] = GSvec(aabb->mMin.x, aabb->mMax.y, aabb->mMin.z);
        sActiveBox[3] = GSvec(aabb->mMin.x, aabb->mMax.y, aabb->mMax.z);
        sActiveBox[4] = GSvec(aabb->mMax.x, aabb->mMin.y, aabb->mMin.z);
        sActiveBox[5] = GSvec(aabb->mMax.x, aabb->mMin.y, aabb->mMax.z);
        sActiveBox[6] = GSvec(aabb->mMax.x, aabb->mMax.y, aabb->mMin.z);
        sActiveBox[7] = aabb->mMax;
    }
}

void calcBoundingBoxCenter(GSvec *dst, const GSboundingBox *aabb) {
    GSvec center;
    VECAdd(&aabb->mMin, &aabb->mMax, &center);
    VECScale(&center, dst, 0.5f);

    if (aabb->mTransform) {
        MTXMultVec(*aabb->mTransform, dst, dst);
    }
}

void expandBoundingBox(GSboundingBox *dst, const GSboundingBox *src) {
    calcBoundingBoxCorners(src);

    for (s32 i = 0; i < 8; i++) {
        GSvec corner;
        corner = sActiveBox[i];

        if (dst->mTransform) {
            Mtx inv;
            MTXInverse(*dst->mTransform, inv);
            MTXMultVec(inv, &corner, &corner);
        }

        if (corner.x < dst->mMin.x) {
            dst->mMin.x = corner.x;
        }

        if (corner.x > dst->mMax.x) {
            dst->mMax.x = corner.x;
        }

        if (corner.y < dst->mMin.y) {
            dst->mMin.y = corner.y;
        }

        if (corner.y > dst->mMax.y) {
            dst->mMax.y = corner.y;
        }

        if (corner.z < dst->mMin.z) {
            dst->mMin.z = corner.z;
        }

        if (corner.z > dst->mMax.z) {
            dst->mMax.z = corner.z;
        }
    }
}

} // namespace GSmath
