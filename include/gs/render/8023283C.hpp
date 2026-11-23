#pragma once

#include <revolution.h>

struct GSvertexFormat;

// size: 0x10
class GSdisplayList {
private:
    /* 0x00 */ u16 mFlags;
    /* 0x02 */ u16 _2;
    /* 0x04 */ void *mDisplayList;
    /* 0x08 */ u32 mDisplayListSize;
    /* 0x0C */ GSvertexFormat *mVertexFormat;

public:
    GSdisplayList();
    ~GSdisplayList();

    void fn_802328AC();
    void call();
    void flush();
    void fn_80232988(GSvertexFormat *vertexFormat, void *data, u32 size, u16 arg3);

    GSvertexFormat *getVertexFormat() const {
        if ((mFlags & (1 << 0))) {
            return mVertexFormat;
        }
        return NULL;
    }
};
