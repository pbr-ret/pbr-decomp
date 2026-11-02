#pragma once

#include <revolution.h>

// Name and template arguments known from RTTI: the original has
// eftseq::AnimNode<GScolor<float>> and eftseq::AnimNode<GScolor<unsigned char>>.
// size: 4 * sizeof(T)
template <typename T>
struct GScolor {
    T r;
    T g;
    T b;
    T a;

    GScolor() {}

    GScolor(T r, T g, T b, T a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    GScolor &operator-=(const GScolor &other) {
        r -= other.r;
        g -= other.g;
        b -= other.b;
        a -= other.a;
        return *this;
    }

    GScolor &operator+=(const GScolor &other) {
        r += other.r;
        g += other.g;
        b += other.b;
        a += other.a;
        return *this;
    }

    GScolor &operator*=(f32 scale) {
        r = r * scale;
        g = g * scale;
        b = b * scale;
        a = a * scale;
        return *this;
    }

    bool operator!=(const GScolor &other) const {
        return r != other.r || g != other.g || b != other.b || a != other.a;
    }
};
