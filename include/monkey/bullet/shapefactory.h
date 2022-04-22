#pragma once

#include "btBulletDynamicsCommon.h"
#include <monkey/itable.h>

class ShapeFactory {
public:
    ShapeFactory();
    virtual ~ShapeFactory();
    btCollisionShape* getShape(const ITab&);
private:
    std::unordered_map<std::string, btCollisionShape*> m_shapes;
    btAlignedObjectArray<btCollisionShape*> m_collisionShapes;

    btCollisionShape* makeBox(const ITab&);

    std::unordered_map<std::string, std::function<btCollisionShape*(const ITab&)>> m_factories;

};