#include <monkey/states/foewalk25.h>
#include <monkey/monkey.h>
#include <monkey/entity.h>
#include <monkey/math/geom.h>
#include <monkey/components/controller25.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/animator.h>
#include <monkey/random.h>

namespace py = pybind11;

FoeWalk25::FoeWalk25(const ITable & t) : State(t) {
    m_speed = t.get<float>("speed");
    m_acceleration = t.get<float>("acceleration");
    m_flipHorizontal = t.get<bool>("flipH");
    //m_sdelta = t.get<float>("delta",0);

    m_probAttack = t.get<float>("prob_attack");
    m_attacks = t.get<std::vector<std::string>>("attacks", std::vector<std::string>());
    m_attackCount = m_attacks.size();
}

FoeWalk25::FoeWalk25(const FoeWalk25 & orig) : State(orig) {

}

std::shared_ptr<State> FoeWalk25::clone() const {
    return std::make_shared<FoeWalk25>(*this);
}


void FoeWalk25::computeDirection() {
    // the difference between this and foechase and here
    // the foe should also move in the y direction
    auto targetPos = m_target->GetPosition();
    float attackPos = m_attackPos * m_entity->GetScale();
    float td = m_pc->getDepth();
//    std::cerr << "player depth = " <<playerDepth << "\n";
    float md = m_controller->getDepth();
    auto mePos = m_entity->GetPosition();
    float ex = mePos.x;
    float ey = mePos.y;
    float x = targetPos.x;
    float y = targetPos.y;
    float x0 = x - attackPos;
    float x1 = x + attackPos;
    // y is the easiest
    m_targetVelocityY = 0.0f;
    float eps = 0.01f;
    float dy = 0.0f;
    float dx = 0.0f;
    float dt = 1.0f/60.0f;
    float max_vel_x = 0.0f;
    float max_vel_y = 0.0f;
    bool ry = false;
    bool rx = false;
    if (!isZero(td-md, 0.01f)) {
        // this is the distance to target depth
        // I need to make sure not to overshoot
        dy =-(md-td);
        max_vel_y = std::min(m_speed, fabs(dy) / dt);
    } else {
        ry = true;
    }
    if (ex > x1 + eps) {
        // go left, face left
        m_entity-> SetFlipX(true);
        dx = (ex-x1);
        // m_targetVelocityX = m_speed;
    } else if (ex < x0 - eps) {
        // go right, face right
        m_entity->SetFlipX(false);
        dx = (x0-ex);
        //m_targetVelocityX = m_speed;
    } else if (ex >= x0+eps && ex < x) {
        // go left, face right
        dx = -(ex-x0);
        m_entity->SetFlipX(false);
        //m_targetVelocityX = -m_speed;
    } else if (ex >=x && ex < x1-eps) {
        // go right, face left
        dx = (ex-x1);
        m_entity->SetFlipX(true);
        //m_targetVelocityX = -m_speed;
    } else {
        rx = true;
    }
    max_vel_x = std::min(m_speed, fabs(dx)/dt);
    //std::cerr << "dx = " << dx;
    //std::cerr << "dy = " << dy;
    glm::vec2 vel(sign(dx) * max_vel_x, sign(dy) * max_vel_y);
    // normalize, making sure the length is
    float absvel = glm::length(vel);
    if (absvel > m_speed) {
        vel = glm::normalize(vel) * m_speed;
    }
    m_inRange =rx and ry;
    //std::cout << abs(ex-x) << ", " << m_attackPos << abs(abs(ex-x)-m_attackPos) << "\n";
    m_targetVelocityX = vel.x;
    m_targetVelocityY = vel.y;
    //std::cerr << m_targetVelocityX << ", " << m_targetVelocityY<<"\n";
    if (m_inRange) {
        // TODO make tem params
        m_animator->SetAnimation("idle");
        m_targetVelocityX = 0.0f;
    } else {
        m_animator->SetAnimation("walk");
    }


}

void FoeWalk25::Run(double dt) {
    if (!m_target->isActive())
        return;

    computeDirection();
    // if I'm at the right position, go to idle

    // randomly attack if within range
    if (m_inRange) {
        float u = Random::get().GetUniformReal(0.0f, 1.0f);
        if (u < m_probAttack) {
            // choose random attack
            int chosenAttack = Random::get().GetUniform(0, m_attackCount-1);
            m_sm->SetState(m_attacks[chosenAttack]);
        }
//
    }
    glm::vec3 delta =m_dynamics->step(dt, m_targetVelocityX, m_targetVelocityY, 0.0f);
    //if (m_speed < 30.0f) std::cout << delta.x << "\n";
    m_controller->Move(delta);

    //UpdateAnimation();

//    auto playerPos = m_target->GetPosition();
//    auto pos = m_entity->GetPosition();
//    bool rightOfPlayer = playerPos.x < pos.x;
//    float targetX = playerPos.x + (rightOfPlayer ? m_delta : -m_delta);
//
//    float playerDepth = m_pc->getDepth();
//    std::cerr << "player depth = " <<playerDepth << "\n";
//    float meDepth = m_controller->getDepth();
//    float dx = targetX - pos.x;
//    float dd = playerDepth - meDepth;
//
//
//    m_entity->SetFlipX(rightOfPlayer);
//
//    float targetVelocityX = (abs(dx) < 1.0f) ? 0.0f : m_speed;
//    float targetVelocityZ = (abs(dd) < 1.0f) ? 0.0f : sign(dd) * m_speed;

//    if (targetVelocityX != 0.0f or targetVelocityZ != 0.0f) {
//        glm::vec3 delta = m_dynamics->step(dt, targetVelocityX, targetVelocityZ, m_acceleration);
//        glm::vec3 deltaH(delta.x, delta.y, delta.z);
//        m_controller->Move(deltaH);
//        m_animator->SetAnimation("walk");
//    } else {
//        m_animator->SetAnimation("idle");
//        if (m_attackCount > 0) {
//            float f = Random::get().GetUniformReal(0.0f, 1.0f);
//            if (f < 0.02f) {
//                // choose a random attack
//                int n = Random::get().GetUniform(0, m_attackCount-1);
//                py::dict d;
//                d["anim"] = m_attacks[n];
//                m_sm->SetState("attack", d);
//
//                //m_sm->SetState("attack");
//            }
//        }
//    }
    //std::cerr << "new z = " << m_entity->GetPosition().z << "\n";
    //UpdateAnimation();
    //std::cerr << deltaH.x << " " << deltaH.y << deltaH.z << "\n";
//    if (m_controller->grounded()) {
//        if (glm::length(glm::vec2(delta.x, delta.z)) > 0.2f) {
//            m_animator->SetAnimation("walk");
//        } else {
//            m_animator->SetAnimation("idle");
//        }
//    } else {
//        m_animator->SetAnimation("jump");
//    }

}


void FoeWalk25::Init(pybind11::dict &) {
}

void FoeWalk25::End() {
}

void FoeWalk25::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    m_entity = sm->GetObject();

    m_target = Monkey::get().Get<Entity>("player");

    // here I will get the skeletal model or sprite model
    auto animator = sm->GetObject()->GetComponent<IAnimator>();
    auto shapes = animator->getModel()->getAttackShapes();
    float am = std::numeric_limits<float>::infinity();
    float aM = -std::numeric_limits<float>::infinity();
    float scale = m_entity->GetScale();
    for (const auto& shape : shapes) {
        auto sb = shape->getBounds();
        am = std::min(am, sb.min.x);
        aM = std::max(aM, sb.max.x);
    }
    m_attackPos = 0.5f* (am + aM);


    m_pc = dynamic_cast<Controller25*>(m_target->GetComponent<IController>());
    m_dynamics = m_entity->GetComponent<Dynamics2D>();
    m_controller = dynamic_cast<Controller25*>(m_entity->GetComponent<IController>());
    m_animator = m_entity->GetComponent<IAnimator>();
    //m_delta = m_sdelta* m_entity->GetScale();
}