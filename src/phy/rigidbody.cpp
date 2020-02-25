#include "rigidbody.h"
#include "bulletengine.h"
#include "btshapewrapper.h"
#include <monkey/engine.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

RigidBody::RigidBody(const LuaTable & t) : Component(t) {

    btScalar mass = t.Get<btScalar>("mass");
    bool isDynamic = (mass != 0.0f);

    luabridge::LuaRef sref = t.Get<luabridge::LuaRef>("shape");
    LuaTable st(sref);
    auto factory = Engine::get().GetSceneFactory();
    auto shape = factory->make<btShapeWrapper>(st);
    m_collisionShape = shape->get();

    btVector3 localIntertia (0, 0, 0);
    if (isDynamic) {
        shape->get()->calculateLocalInertia(mass, localIntertia);
    }
    btRigidBody::btRigidBodyConstructionInfo rbInfo (mass, nullptr, m_collisionShape.get(), localIntertia);
    m_rigidBody = std::make_shared<btRigidBody>(rbInfo);
    //btRigidBody::btRigidBodyConstructionInfo rbInfo (mass, nullptr,
    //m_rigidBody = std::make_unique<btRigidBody>();
}

RigidBody::RigidBody(const RigidBody & other) : m_collisionShape(other.m_collisionShape) {

    btScalar mass = other.m_rigidBody->getMass();
    btVector3 localInertia;
    if (mass != 0.0f) {
        m_collisionShape->calculateLocalInertia(mass, localInertia);
    }
    btRigidBody::btRigidBodyConstructionInfo rbInfo (mass, nullptr, m_collisionShape.get(), localInertia);
}


void RigidBody::Start() {
//    btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
//
//    //collisionShapes.push_back(groundShape);
//
//    btTransform groundTransform;
//    groundTransform.setIdentity();
//    groundTransform.setOrigin(btVector3(0, -56, 0));
//
//    btScalar mass(0.);
//
//    //rigidbody is dynamic if and only if mass is non zero, otherwise static
//    bool isDynamic = (mass != 0.f);
//
//    btVector3 localInertia(0, 0, 0);
//    if (isDynamic)
//        groundShape->calculateLocalInertia(mass, localInertia);
//
//    //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
//    btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
//    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
//    btRigidBody* body = new btRigidBody(rbInfo);

    //add the body to the dynamics world


    glm::dmat4 wt = m_entity->GetWorldTransform();
    btTransform transform;
    transform.setFromOpenGLMatrix(glm::value_ptr(wt));
    btDefaultMotionState* motionState = new btDefaultMotionState(transform);
    m_rigidBody->setMotionState(motionState);

    auto be = Engine::get().GetRunner<BulletEngine>();
    std::cerr << "is static = " << m_rigidBody->isStaticObject();
    std::cerr << "aa = " << m_rigidBody->getLocalInertia().x();
     //be->addBody(body);
    be->addBody(m_rigidBody.get());
}

void RigidBody::Update(double dt) {
    // the movement of this entity is handled by the dynamics world.
    // therefore I need to make sure that

    const auto& transform = m_rigidBody->getWorldTransform();
    glm::dmat4 wt;

    transform.getOpenGLMatrix(glm::value_ptr(wt));

    // associate this transform to entity
    // ...

    std::cerr << m_entity->GetTag() << " --> " << wt[3][0] << ", " << wt[3][1] << ", " << wt[3][2] << "\n";

}

std::shared_ptr<Component> RigidBody::clone() const {
    return std::make_shared<RigidBody>(*this);
}
