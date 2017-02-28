#pragma once

#include "BufferObject.h"

class ElementBuffer final : public BufferObject {
public:
    ElementBuffer();
    ~ElementBuffer();

    static void Reset();
private:
};