#include "c3d.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <monkey/entity.h>

Controller3Db::Controller3Db(const Controller3Db & orig) : Component(orig) {}

Controller3Db::Controller3Db(const LuaTable &t) : Component(t){}

void Controller3Db::Start() {

    // requires an input component and a rigid body comp
    m_input = m_entity->GetComponent<InputMethod>();
    m_rigidBody = m_entity->GetComponent<RigidBody>();
}

void Controller3Db::Update(double) {
    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
    bool up = m_input->isKeyDown(GLFW_KEY_UP);
    auto body = m_rigidBody->getRigidBody();
    float vx = (left ? -5.0f : (right ? 5.0f : 0.0f));
    body->applyForce(btVector3(vx, 0, 0), btVector3(0,0,0));
}

std::shared_ptr<Component> Controller3Db::clone() const {
    return std::make_shared<Controller3Db>(*this);
}