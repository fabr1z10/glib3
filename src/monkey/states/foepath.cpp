#include <monkey/states/foepath.h>
#include <monkey/components/controller3d.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/entity.h>
#include <monkey/engine.h>
#include <monkey/components/icollider.h>
#include <monkey/random.h>

FoePath::FoePath(const ITab& t) : Base3D(t) {
    t.foreach("moves", [&] (const ITab& u) {
       PathSeg seg;
       seg.direction = glm::normalize(u.get<glm::vec3>("direction"));
       seg.distance = u.get<float>("distance");
       seg.anim = u.get<std::string>("anim");
       seg.oe = u.get<int>("on_end", 0);
       m_segments.push_back(seg);
    });
}

void FoePath::AttachStateMachine(StateMachine * sm) {
    Base3D::AttachStateMachine(sm);
}

void FoePath::Init(const ITab& d) {
    m_currentIndex = 0;
    initSeg(m_currentIndex);
}

void FoePath::initSeg(unsigned i) {
	m_dist = 0.0f;
	m_renderer->setAnimation(m_segments[i].anim);
}

void FoePath::Run(double dt) {
	if (m_currentIndex == -1) {
		return;
	}
    m_dist += dt * m_maxSpeed;
    auto& seg = m_segments[m_currentIndex];
    if (m_dist >= seg.distance) {
    	if (seg.oe == 0) {
    		// go to next seg
    		m_currentIndex++;
    		if (m_currentIndex >= m_segments.size()) {
    			m_currentIndex = -1;
    		} else {
    			initSeg(m_currentIndex);
    		}
		} else if (seg.oe == 1) {
    		m_renderer->setAnimation("idle");
    	}
    } else {
		glm::vec3 delta = seg.direction * m_maxSpeed * static_cast<float>(dt);
		m_controller->Move(delta);

    }


}

void FoePath::End() {

}