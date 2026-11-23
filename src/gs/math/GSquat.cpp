#include "gs/GSmath.hpp"

#include "common.hpp"

// TODO(samm) Is a namespace really appropriate?
namespace GSmath {
GSvec sXAxis(1.f, 0.f, 0.f);
GSvec sYAxis(0.f, 1.f, 0.f);
GSvec sZAxis(0.f, 0.f, 1.f);
} // namespace GSmath

// TODO(samm) Name these variables
GSvec lbl_8049362C(0.f, 0.f, 0.f);
GSvec lbl_80493638(1.f, 1.f, 1.f);

GSvec2 lbl_8063F5B0(0.f, 0.f);
GSvec2 lbl_8063F5B8(1.f, 1.f);

void GSmath::rotateVec3ByQuat(GSvec *p, GSquat *r) {
    f32 rw;
    f32 rz;
    f32 ry;
    f32 rx;

    rx = r->x;
    ry = r->y;
    rz = r->z;
    rw = r->w;

    f32 px = p->x;
    f32 py = p->y;
    f32 pz = p->z;

    f32 rx2 = rx * rx;
    f32 ry2 = ry * ry;
    f32 rz2 = rz * rz;
    f32 rw2 = rw * rw;

    f32 rxry = rx * ry;
    f32 rxrz = rx * rz;
    f32 rxrw = rx * rw;
    f32 ryrz = ry * rz;
    f32 ryrw = ry * rw;
    f32 rzrw = rz * rw;

    p->x = px * (rw2 + rx2 - rz2 - ry2) + 2.f * (pz * (ryrw + rxrz) + py * (rxry - rzrw));
    p->y = py * (ry2 - rz2 + rw2 - rx2) + 2.f * (px * (rxry + rzrw) + pz * (ryrz - rxrw));
    p->z = pz * (rz2 - ry2 - rx2 + rw2) + 2.f * (py * (ryrz + rxrw) + px * (rxrz - ryrw));
}
