#pragma once

#include "BufferObject.h"

class ArrayBuffer final : public BufferObject {
public:
    ArrayBuffer(GLenum);
    ~ArrayBuffer();

    static void Reset();
private:
};