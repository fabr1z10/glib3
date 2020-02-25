#pragma once

#include <monkey/component.h>
#include "btBulletDynamicsCommon.h"

/// A Bullet rigid body. If you want your entity to be handled by Bullet Dynamics world,
/// then you need to add it a RigidBody component!
class RigidBody : public Component {
public:
    RigidBody(const LuaTable&);
    RigidBody(const RigidBody&);
    void Start() override;
    void Update(double) override;
    std::shared_ptr<Component> clone() const override;
private:
    std::shared_ptr<btRigidBody> m_rigidBody;
    std::shared_ptr<btCollisionShape> m_collisionShape;
};