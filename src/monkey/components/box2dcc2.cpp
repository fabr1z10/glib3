#include <monkey/components/box2dcc2.h>
#include <monkey/engine.h>
#include <monkey/entity.h>
#include <monkey/components/box2dbody.h>


Box2DCharacterController2::Box2DCharacterController2(const ITab & t) : Box2DCharacterControllerBase(t) {
    m_maxSpeed = t.get<float>("max_speed");
    m_acceleration = t.get<float>("acceleration");
    m_friction = t.get<float>("friction");
    m_gravity = t.get<float>("gravity");


}

void Box2DCharacterController2::Start() {
    Box2DCharacterControllerBase::Start();
    m_xVel = 0.0f;
    m_yVel = 0.0f;

    m_entity->GetComponent<Box2DBody>()->registerCallback(this);

}

void Box2DCharacterController2::applyGravity(double dt) {
    m_yVel -= m_gravity *dt;
}

void Box2DCharacterController2::applyFriction(double dt) {
    if (m_xVel > 0) {
        if (m_xVel - m_friction * dt > 0) {
            m_xVel -= m_friction * dt;
        } else {
            m_xVel = 0.0f;
        }
    } else {
        if (m_xVel + m_friction * dt < 0) {
            m_xVel += m_friction * dt;
        } else {
            m_xVel = 0.0f;
        }
    }
}

void Box2DCharacterController2::Update(double dt) {
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    if (right) {
        if (m_xVel < m_maxSpeed) {
            if (m_xVel + m_acceleration * dt < m_maxSpeed) {
                m_xVel += m_acceleration * dt;
            } else {
                m_xVel = m_maxSpeed;
            }
        }
    } else if (left) {
        if (m_xVel > -m_maxSpeed) {
            if (m_xVel - m_acceleration * dt > -m_maxSpeed) {
                m_xVel -= m_acceleration * dt;
            } else {
                m_xVel = -m_maxSpeed;
            }
        }

    } else {
        applyFriction(dt);
    }
    applyGravity(dt);
    m_body->SetLinearVelocity(b2Vec2(m_xVel, m_yVel));
}

void Box2DCharacterController2::startContact(Box2DBody* other, b2Contact* contact, bool y) {
    auto normal = contact->GetManifold()->localNormal;
    std::cerr << normal.x << ", " << normal.y << ", " << y << "\n";
}

void Box2DCharacterController2::endContact(Box2DBody* other, b2Contact*, bool) {

}
