#pragma once

#include <monkey/component.h>
#include "btBulletDynamicsCommon.h"

class BulletRigidBody : public Component {
public:
    BulletRigidBody(const ITab&);
    void Start() override {}
    void Update(double) override;
private:
    glm::mat4 bulletToGlm(const btTransform& t);

    btTransform m_transform;
    btCollisionShape* m_shape;
    btRigidBody* m_body;

};

