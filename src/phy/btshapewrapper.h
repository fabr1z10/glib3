#pragma once

#include <monkey/asset.h>
#include "bullet/btBulletDynamicsCommon.h"
#include <memory>
#include <monkey/lua/luatable.h>

class btShapeWrapper : public Object {
public:
    btShapeWrapper() : Object() {}
    std::shared_ptr<btCollisionShape> get();
protected:
    std::shared_ptr<btCollisionShape> m_shape;
};

inline std::shared_ptr<btCollisionShape> btShapeWrapper::get() {
    return m_shape;
}

class btBoxWrapper : public btShapeWrapper {
public:
    btBoxWrapper (const LuaTable&);

};

class btSphereWrapper : public btShapeWrapper {
public:
    btSphereWrapper (const LuaTable&);

};