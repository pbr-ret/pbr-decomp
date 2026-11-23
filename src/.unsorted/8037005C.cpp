#include ".unsorted/8037005C.hpp"

#include <nw4r/snd/snd_AxfxImpl.h>

#include "common.hpp"

extern "C" {

bool fn_803706E0(u8 *p, void *buffer, u32 size) {
    return reinterpret_cast<nw4r::snd::detail::AxfxImpl *>(p + 0xc)->CreateHeap(buffer, size);
}
void fn_803706E8(u8 *p) {
    reinterpret_cast<nw4r::snd::detail::AxfxImpl *>(p + 0xc)->DestroyHeap();
}
bool fn_80370B20(u8 *p, void *buffer, u32 size) {
    return reinterpret_cast<nw4r::snd::detail::AxfxImpl *>(p + 0xc)->CreateHeap(buffer, size);
}
void fn_80370B28(u8 *p) {
    reinterpret_cast<nw4r::snd::detail::AxfxImpl *>(p + 0xc)->DestroyHeap();
}
bool fn_80370E78(u8 *p, void *buffer, u32 size) {
    return reinterpret_cast<nw4r::snd::detail::AxfxImpl *>(p + 0xc)->CreateHeap(buffer, size);
}
void fn_80370E80(u8 *p) {
    reinterpret_cast<nw4r::snd::detail::AxfxImpl *>(p + 0xc)->DestroyHeap();
}
bool fn_80371260(u8 *p, void *buffer, u32 size) {
    return reinterpret_cast<nw4r::snd::detail::AxfxImpl *>(p + 0xc)->CreateHeap(buffer, size);
}
void fn_80371268(u8 *p) {
    reinterpret_cast<nw4r::snd::detail::AxfxImpl *>(p + 0xc)->DestroyHeap();
}
bool fn_80371648(u8 *p, void *buffer, u32 size) {
    return reinterpret_cast<nw4r::snd::detail::AxfxImpl *>(p + 0xc)->CreateHeap(buffer, size);
}
void fn_80371650(u8 *p) {
    reinterpret_cast<nw4r::snd::detail::AxfxImpl *>(p + 0xc)->DestroyHeap();
}
}
