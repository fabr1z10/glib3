#include "bubble.h"
#include <gfx/entity.h>
#include <gfx/engine.h>
#include <gfx/components/controller2d.h>
#include <gfx/components/smartcollider.h>
#include <gfx/components/ianimator.h>
#include <gfx/components/luahook.h>


Bubble::Bubble(bool left, float speed, float speedUp) : State(), m_left(left), m_speed(speed),
    m_speedUp(speedUp) {}

Bubble::Bubble(const Bubble &orig) : State(orig) {}

std::shared_ptr<State> Bubble::clone() const {
    return std::make_shared<Bubble>(*this);
}

void Bubble::shoot(float dt) {
    glm::vec3 pos = m_entity->GetPosition();
    glm::vec3 delta(0.0f);

    // check if I reachead the range or if I hit a wall
    if ((m_left && m_controller2D->m_details.left) || (!m_left && m_controller2D->m_details.right) || (fabs(m_x0-pos.x) >= 64)) {
        // I bumped into a wall
        m_currentBehavior = 1;
        m_collider->setCollisionMask(1);
        // now generate the path
        if (pos.x <= 112 || pos.x >= 144) {
            float x = (pos.x <=112 ? 112 : 144);
            m_moves.push_back(BubbleMove{glm::vec2(pos.x, 160)});
            m_moves.push_back(BubbleMove{glm::vec2(x, 160)});
            m_moves.push_back(BubbleMove{glm::vec2(x, 176)});
            m_next = {1, 2, 1};
        } else {
            m_moves.push_back(BubbleMove{glm::vec2(pos.x, 160)});
            m_moves.push_back(BubbleMove{glm::vec2(pos.x, 176)});
            m_next = {1, 0};
        }

        initMove(0);

    } else {
        delta.x = m_left ? -m_speed*dt : m_speed*dt;
    }
    m_controller2D->Move(delta);
}

void Bubble::rise(float dt) {
    glm::vec3 delta(0.0f);

    glm::vec2 d = m_direction * (m_speedUp * dt);
    m_lengthTraversed += glm::length(d);
    if (m_lengthTraversed >= m_lengthToCover) {
        m_entity->SetPosition(m_goal);
        initMove(m_next[m_currentMove]);
    } else {
        delta.x = d.x;
        delta.y = d.y;
        m_entity->MoveLocal(delta);
    }


}

void Bubble::blowup(float) {

    if (m_animator->IsComplete()) {
        Engine::get().Remove(m_entity->GetId());
    }
}

void Bubble::pop() {
    if (m_currentBehavior ==1) {
        m_animator->SetAnimation("blowingup4");
        // bubble with enemies might play an enemy kill script

        m_currentBehavior = 2;
    }
}



void Bubble::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    m_entity = m_sm->GetObject();
    m_animator = m_entity->GetComponent<IAnimator>();
    m_collider = dynamic_cast<SmartCollider*>(m_entity->GetComponent<ICollider>());
    m_controller2D = dynamic_cast<Controller2D*>(m_entity->GetComponent<IController>());
    m_timedEvents.push_back(TimedEvent{3, [&] () { m_animator->SetAnimation("blowingup1"); }});
    m_timedEvents.push_back(TimedEvent{6, [&] () { m_animator->SetAnimation("blowingup2"); }});
    m_timedEvents.push_back(TimedEvent{9, [&] () { m_animator->SetAnimation("blowingup3"); }});
    m_timedEvents.push_back(TimedEvent{12, [&] () {
        m_animator->SetAnimation("blowingup4");
        // bubble with enemies might create a new enemy here!

        m_currentBehavior=2;
    }});

    m_behaviors.push_back([&] (float dt) { shoot(dt); });
    m_behaviors.push_back([&] (float dt) { rise(dt); });
    m_behaviors.push_back([&] (float dt) { blowup(dt); });

    auto* luaHook = m_entity->GetComponent<LuaHook>();
    if (luaHook== nullptr) {
        GLIB_FAIL("Bubble component requires a LuaHook comp!");
    }
    luaHook->addHook("pop", [&] (luabridge::LuaRef) { pop(); });
}

void Bubble::Init() {
    m_x0 = m_entity->GetPosition().x;
    m_timer = 0.0f;
    m_currentBehavior = 0;
}


void Bubble::initMove(int i) {
    glm::vec2 pos(m_entity->GetPosition());

    m_currentMove = i;
    // get current entity position
    const auto& cm = m_moves[i];
    glm::vec2 delta = cm.toPoint - pos;
    m_lengthToCover = glm::length(delta);
    m_direction = delta/m_lengthToCover;
    m_lengthTraversed = 0.0f;
    m_goal = cm.toPoint;
    //std::cerr << "init " << i << ", currentpos = " << pos.x << ", " << pos.y << ", ltc=" << m_lengthToCover<<
      //  " goal = " << m_goal.x << ", " << m_goal.y << ", dir = " << m_direction.x << ", " << m_direction.y << "\n";
}

void Bubble::Run(double dt) {
    float ft = static_cast<float>(dt);
    m_behaviors[m_currentBehavior].operator()(ft);

    if (!m_timedEvents.empty()) {
        m_timer+=dt;
        const auto& nextTimeEvent = m_timedEvents.front();
        if (m_timer >= nextTimeEvent.t) {
            nextTimeEvent.func();
            m_timedEvents.pop_front();
        }
    }
}