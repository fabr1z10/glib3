#pragma once

#include <monkey/model/basicmodel.h>
#include <memory>

// primitives 3d (color and tex)

class Box3D : public BasicModel {
public:
    Box3D (const LuaTable&);
};

class Sphere3D : public BasicModel {
public:
    Sphere3D (const LuaTable&);
};
