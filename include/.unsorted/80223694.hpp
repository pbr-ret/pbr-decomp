#pragma once

#include <revolution.h>

// TODO Thin wrappers around MTXFrustum, MTXOrtho and MTXPerspective
void fn_80223694(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void fn_80223698(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void fn_8022369C(Mtx44 m, f32 fovY, f32 aspect, f32 n, f32 f);
