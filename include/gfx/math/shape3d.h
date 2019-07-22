#pragma once

#include <gfx/bounds.h>

class Shape3D {
public:
    virtual ~Shape3D();
    virtual Bounds getBounds () const = 0;
};