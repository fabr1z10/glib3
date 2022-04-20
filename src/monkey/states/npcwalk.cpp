#include <monkey/states/npcwalk.h>
#include <GLFW/glfw3.h>
#include <monkey/math/geom.h>
#include <monkey/entity.h>
#include <monkey/components/controller3d.h>
#include <monkey/python/wrap1.h>

NPCWalk::NPCWalk(const ITab& t) : State(t) {
    m_walkAnim = t.get<std::string>("walk_anim", "walk");
    // direction specifies whether is facing right (1) or left (-1)
    // if none is specified the direction is given by the current flip
    m_direction = t.get<int>("direction", -1);
    m_fliph = t.get<bool>("flip_hor", true);
    m_flipIfPlatformEnds = t.get<bool>("flip_on_edge", false);
    m_collisionMaskOverride = t.get<int>("collision_mask", -1);
	m_gravity = t.get<float>("gravity");
	m_maxSpeed = t.get<float>("max_speed");
	if (t.has("on_land")) {
        m_onLand = t.get<pybind11::function>("on_land");
    }
	m_bounce = t.get<float>("bounce", 0.0f);
}

void NPCWalk::AttachStateMachine(StateMachine * sm) {

	State::AttachStateMachine(sm);
	m_entity = sm->GetObject();

	m_dynamics = m_entity->GetComponent<Dynamics>();
	if (m_dynamics == nullptr) {
		GLIB_FAIL("player jump state requires a dynamics component!");
	}

	m_controller = dynamic_cast<Controller2D*>(m_entity->GetComponent<IController>());
	if (m_controller == nullptr) {
		GLIB_FAIL("Platformer state requires a <Controller2D> component!");
	}

	m_renderer = dynamic_cast<AnimationRenderer*>(m_entity->GetComponent<Renderer>());
}

void NPCWalk::Init(const ITab &d) {
    m_entity->SetFlipX(m_direction == -1);
    m_direction = d.get<int>("direction", m_entity->GetFlipX() ? -1 : 1);

    //m_collider->setCollisionFlag(0);
    m_renderer->setAnimation(m_walkAnim);
}

void NPCWalk::Run(double dt) {
    auto dtf = static_cast<float>(dt);

    if (m_controller->grounded() && m_dynamics->m_velocity.y <= 0.0f) {
        if (m_bounce > 0.0f && fabs(m_dynamics->m_velocity.y)> 5.0f) {
            m_dynamics->m_velocity.y = fabs(m_dynamics->m_velocity.y) * m_bounce;
        } else {
            m_dynamics->m_velocity.y = 0.0f;
            if (m_onLand) {
                m_onLand(Wrap1::create(m_entity));
            }
        }
    }

    glm::vec2 a(0.0f);
    a.y = -m_gravity;
    m_dynamics->m_velocity += a * dtf;
    if (m_fliph) {
        m_dynamics->m_velocity.x = m_maxSpeed;
        m_entity->SetFlipX(m_direction == -1);
    } else {
        m_dynamics->m_velocity.x = (m_direction == -1 ? -m_maxSpeed : m_maxSpeed);
    }
    if (m_controller->m_details.left && m_direction == -1) {
        m_direction = 1;
    } else if (m_controller->m_details.right && m_direction == 1) {
        m_direction = -1;
    }
    if (m_flipIfPlatformEnds) {
        // check if I reached the end of the platform
        if (m_controller->m_details.below && m_controller->IsFalling((m_direction == -1) ? -1 : 1 )) {
            m_direction = (m_direction == -1) ? 1 : -1;
            return;
        }
    }
    auto delta = glm::vec3(m_dynamics->m_velocity * dtf, 0.0f);
    m_controller->Move(delta);

//    if (m_renderer != nullptr) {
//        if (m_controller->grounded()) {
//            m_renderer->setAnimation(m_walkAnim);
//        } else {
//            if (m_dynamics->m_velocity.y >= 0) {
//                m_renderer->setAnimation(m_jUpAnim);
//            } else {
//                m_renderer->setAnimation(m_jDownAnim);
//            }
//        }
//    }
}

void NPCWalk::End() {

}