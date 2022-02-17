#include <monkey/states/jumpattack.h>
#include <monkey/monkey.h>
#include <monkey/engine.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/controller3d.h>
#include <monkey/math/shapes3d/aabb.h>

JumpAttack::JumpAttack(const ITab &t) : Base3D(t) {
//    m_speed = t.get<float>("speed");
//    m_accTimeAir = t.get<float>("acceleration");
//    m_flipHorizontally = t.get<bool>("flipH");
//
//    m_anim = t.get<std::string>("anim");
    m_peakHeight = t.get<float>("peak_height");
    m_downSpeed = t.get<float>("down_speed");
    m_castMask = t.get<int>("cast_mask");
    m_castTag = t.get<int>("cast_tag");

}

void JumpAttack::AttachStateMachine(StateMachine * sm) {
    Base3D::AttachStateMachine(sm);
    m_target = Monkey::get().Get<Entity>("player");
    m_engine = Engine::get().GetRunner<ICollisionEngine>();

}

void JumpAttack::Run(double dt) {
    auto dtf = static_cast<float>(dt);

    glm::vec3 a(0.0f);
    a.y = -m_gravity;

    m_dynamics->m_velocity += a * dtf;
    auto delta = m_dynamics->m_velocity * dtf;
    m_controller->Move(delta);
    if (m_dynamics->m_velocity.y <= 0.0f) {
        m_renderer->setAnimation("jumpdown");
        m_dynamics->m_velocity.x = 0.0f;
        m_dynamics->m_velocity.z = 0.0f;
        m_dynamics->m_velocity.y = -m_downSpeed;
    }
    if (m_controller->grounded()) {
        // test collision
        auto r = AABB(glm::vec3(10.0f, 1.0f, 10.0f), glm::vec3(-5.0f, 0.0f, -5.0f));
        auto t = m_entity->GetWorldTransform();
        auto e = m_engine->ShapeCast(&r, t, m_castMask);
        if (e.report.collide) {
            std::cerr << "FUCKING HIT!!!!\n";
            auto rm = m_engine->GetResponseManager();
            if (rm == nullptr) {
                std::cerr << "no handler!\n";
            } else {
                auto object = e.entity->GetObject();
                auto handler = rm->GetHandler(m_castTag, e.entity->GetCollisionTag());
                if (handler.response != nullptr) {
                    std::cerr << "FOUND RESPONSE\n";
                    //m_stateMachine->getCurrentState()->onCollide();
                    if (handler.flip) {
                        handler.response->onStart(object, m_entity, e.report);
                    } else {
                        handler.response->onStart(m_entity, object, e.report);
                    }
                }
            }
        }
        m_sm->SetState("walk");
    }
}

void JumpAttack::Init(const ITab &) {
    auto entityPos = m_entity->GetPosition();
    auto targetPos = m_target->GetPosition();
    auto delta = targetPos - entityPos;
    delta.y = 0.0f;
    auto dx = glm::length(delta);
    std::cerr << " horizontal spacing = " << dx << "\n";
    // vertical speed
    float vy = sqrt(2.0f * m_gravity * m_peakHeight);
    // horizontal speed
    float vx = (dx * m_gravity) / vy;
    glm::vec3 velocity = vx * glm::normalize(delta);
    velocity.y = vy;
    velocity.x = fabs(velocity.x);
    m_renderer->setAnimation("jumpup");
    m_dynamics->m_velocity = velocity;
    m_entity->SetFlipX(delta.x < 0);

}

void JumpAttack::End() {

}