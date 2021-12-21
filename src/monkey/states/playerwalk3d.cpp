#include <monkey/states/playerwalk3d.h>
#include <monkey/math/geom.h>

#include <monkey/entity.h>
#include <monkey/engine.h>
#include <monkey/components/controller3d.h>
#include <monkey/components/inputmethod.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/animator.h>
#include <monkey/components/statemachine.h>
#include <GLFW/glfw3.h>

//PlayerWalk3D::PlayerWalk3D(float speed, float acceleration, bool fliph, float jumpSpeed) :
//        m_speed(speed), m_acceleration(acceleration), m_flipHorizontally(fliph), m_velocitySmoothing(0.0f), m_jumpSpeed(jumpSpeed) {}

PlayerWalk3D::PlayerWalk3D(const ITab& t) : State(t), m_renderer(nullptr)  {
    //auto factory = Engine::get().GetSceneFactory();

    m_maxSpeed = t.get<float>("max_speed");
    auto tmax = t.get<float>("time_acc");
    m_acceleration = m_maxSpeed / tmax;
	//m_flipHorizontally = t.get<bool>("flipH");
	m_jumpSpeed = t.get<float>("jump_speed");
	//auto pi = t["animator"];
	m_gravity = t.get<float>("gravity");
	m_jumpKey = t.get<int>("jump_key", GLFW_KEY_A);
    //m_walkAnimator = factory->make2<WalkAnim>(*pi);
    m_jumpState = t.get<std::string>("jump_state", "jump");
    m_idleAnim = t.get<std::string>("idle_anim", "idle");
	m_walkAnim = t.get<std::string>("walk_anim", "walk");
}

void PlayerWalk3D::Init(const ITab&) {
    m_controller->m_details.below= true;
    m_dynamics->m_velocity = glm::vec3(0.0f);
}

void PlayerWalk3D::End() {

}

void PlayerWalk3D::Run(double dt) {
    auto dtf = static_cast<float>(dt);

    if (!m_controller->grounded()) {
        m_sm->SetState(m_jumpState);
        return;
    } else {
        m_dynamics->m_velocity.y = 0.0f;
    }

    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
    bool up = m_input->isKeyDown(GLFW_KEY_UP);
    bool down = m_input->isKeyDown(GLFW_KEY_DOWN);
    bool jmp = m_input->isKeyDown(m_jumpKey);

    if (jmp) {
        m_dynamics->m_velocity.y = m_jumpSpeed;
        m_sm->SetState(m_jumpState);
        return;
    }

    glm::vec3 a(0.0f);
    a.y = - m_gravity;

    if (left || right) {
        a.x = m_acceleration;
        m_entity->SetFlipX(left);
    } else {
        // apply deceleration only if velocity above theshold
        if (fabs(m_dynamics->m_velocity.x) > 0.1f) {
            a.x = -m_acceleration;
        } else {
            a.x = 0.0f;
            m_dynamics->m_velocity.x = 0.0f;
        }
    }
    if (up || down) {
        a.z = (down ? 1.0f : -1.0f) * m_acceleration;
    } else {
        // apply deceleration only if velocity above theshold
        if (fabs(m_dynamics->m_velocity.z) > 0.1f) {
            a.z = -signf(m_dynamics->m_velocity.z) * m_acceleration;
        } else {
            a.z = 0.0f;
            m_dynamics->m_velocity.z = 0.0f;
        }
    }
    m_dynamics->m_velocity += a * dtf;

    // cap horizontal vel to max speed
    if (left || right) {
        if (fabs(m_dynamics->m_velocity.x) > m_maxSpeed) {
            m_dynamics->m_velocity.x = sign(m_dynamics->m_velocity.x) * m_maxSpeed;
        }
    }
	if (up || down) {
		if (fabs(m_dynamics->m_velocity.z) > m_maxSpeed) {
			m_dynamics->m_velocity.z = sign(m_dynamics->m_velocity.z) * m_maxSpeed;
		}
	}

    auto delta = m_dynamics->m_velocity * dtf;
    m_controller->Move(delta);

    // TODO restore anim handle

    if (m_renderer != nullptr) {
        if ((fabs(m_dynamics->m_velocity.x) > 1.0f) || (fabs(m_dynamics->m_velocity.z) > 1.0f)) {
            m_renderer->setAnimation(m_walkAnim);
        } else {
            m_renderer->setAnimation(m_idleAnim);
        }
    }
}




void PlayerWalk3D::AttachStateMachine(StateMachine * sm) {
	State::AttachStateMachine(sm);
	m_entity = sm->GetObject();
	m_controller = dynamic_cast<Controller3D*>(m_entity->GetComponent<IController>());
	if (m_controller == nullptr) {
		GLIB_FAIL("Platformer state requires a <Controller3D> component!");
	}
    m_renderer = dynamic_cast<AnimationRenderer*>(m_entity->GetComponent<Renderer>());
	m_dynamics = m_entity->GetComponent<Dynamics3D>();
	if (m_dynamics == nullptr) {
		GLIB_FAIL("Platormer state requires a <Dynamics2D> component!");
	}
	//m_animator = m_entity->GetComponent<Animator>();
	m_input = m_entity->GetComponent<InputMethod>();
	//if (m_input == nullptr) {
	//    GLIB_FAIL("Walk state requires an <InputMethod> component!");
	//}
	// TODO set animator
	//m_animator = m_entity->GetComponent<IAnimator>();


}