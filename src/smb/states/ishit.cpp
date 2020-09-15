#include "ishit.h"
#include <monkey/components/dynamics2d.h>
#include <monkey/components/controller2d.h>
#include <monkey/components/ianimator.h>

IsHit::IsHit(const ITable & t) : PlatformerState(t) {
	m_acceleration = t.get<float>("acceleration");
	m_anim = t.get<std::string>("anim");
	m_dist = t.get<float>("dist");
}

IsHit::IsHit(const IsHit & orig) : PlatformerState(orig) {
}

std::shared_ptr<State> IsHit::clone() const {
	return std::make_shared<IsHit>(*this);
}

void IsHit::Init(pybind11::dict & d) {
	m_animator->SetAnimation(m_anim);
	m_sgn = d["sign"].cast<float>();
	m_distanceTravelled = 0.0f;
}
void IsHit::Run(double dt) {
	if (m_controller->grounded()) {
		m_dynamics->m_velocity.y = 0.0f;
	}
	glm::vec3 delta = m_dynamics->step(dt, m_sgn *m_acceleration, 0.0f, 0.0f);
	glm::vec3 deltaH(delta.x, delta.y, delta.z);

	m_controller->Move(deltaH);
	m_distanceTravelled += deltaH.x;
	std::cerr << "aa:" << deltaH.x;
	if (fabs(m_distanceTravelled) > m_dist || fabs(deltaH.x) <0.01f) {
		// if (abs(m_dynamics->m_velocity.x) < 20.0f) {
		m_sm->SetState("walk");
	}
}

void IsHit::End() {
}