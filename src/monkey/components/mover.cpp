#include <monkey/components/mover.h>
#include <monkey/entity.h>
#include <monkey/math/geom.h>

Mover::Mover() : Component(), m_pause(false), m_hold(false) {}

void Mover::setPause(bool value) {
    m_pause = value;
}


PolygonalMover::Movement::Movement(glm::vec2 delta, float speed, float hold) : speed(speed), hold(hold) {
    length = glm::length(delta);
    dir = glm::normalize(delta);
}
PolygonalMover::PolygonalMover(int loopType, glm::vec2 origin) : Mover(), m_O(origin), m_startIndex(0), m_pctComplete(0.0f) {}


PolygonalMover::PolygonalMover(const ITable & t) : Mover(), m_O(glm::vec2(0.0f)), m_startIndex(0), m_pctComplete(0.0f), m_hasSinX(false), m_hasSinY(false) {
	m_O = t.get<glm::vec2>("origin");
	//m_loopType = t.get<int>("loop");
	m_pctComplete = t.get<float>("pct", 0.0f);
	if (t.hasKey("sinx")) {
	    m_hasSinX = true;
	    m_sinx = t.get<glm::vec3>("sinx");
	    // convert period to freq
	    m_sinx[1] = 2 * M_PI / m_sinx[1];
	}
    if (t.hasKey("siny")) {
        m_hasSinY = true;
        m_siny = t.get<glm::vec3>("siny");
        m_siny[1] = 2 * M_PI / m_siny[1];
    }
	t.foreach<PyDict>("moves", [&] (const PyDict& d) {
		auto delta = d.get<glm::vec2>("delta");
		auto speed = d.get<float>("speed");
		auto hold = d.get<float>("hold");
		this->addMovement(delta, speed, hold);
	});

}



void PolygonalMover::addMovement(glm::vec2 delta, float speed, float hold) {

    m_movements.push_back(Movement(delta, speed, hold));
}

void PolygonalMover::Start() {

    glm::vec2 P = m_O;
    for ( auto& m : m_movements) {
        m.startPosition = P;
        m.endPosition = P + m.dir * m.length;
        m.time = m.length / m.speed;
        P = m.endPosition;
    }
    //m_entity->SetPosition(m_O);
    m_currentMovement = m_startIndex;
    const auto& im = m_movements[m_currentMovement];
    m_cumulatedLength = im.length * m_pctComplete;
    glm::vec2 startPos = im.startPosition + im.dir * m_cumulatedLength;
    m_entity->SetPosition(startPos);
    m_fwd = true;
    m_t = m_pctComplete * im.time;
}

void PolygonalMover::Update(double dt) {
    if (m_pause || m_movements.empty()) return;
    m_t += dt;
    if (m_hold) {
        m_holdTimer += dt;
        if (m_holdTimer >= m_holdTime) {
            m_hold = false;
        }
        return;
    }
    Movement& cm = m_movements[m_currentMovement];
    glm::vec2 dir = cm.dir;
    if (!m_fwd) dir *= -1.0f;
    glm::vec2 translation = (cm.speed * static_cast<float>(dt)) * dir;
    m_cumulatedLength += cm.speed*dt;
    if (m_cumulatedLength >= cm.length) {
        m_cumulatedLength = 0.0f;
        if (m_fwd) {
            m_currentMovement++;
			m_entity->SetPosition(cm.endPosition);
            if (m_currentMovement >= m_movements.size()) {
            	m_currentMovement = 0;
            }
        } else {
            m_currentMovement--;
            if (m_currentMovement < 0) {
                m_entity->SetPosition(cm.startPosition);
                m_currentMovement = 0;
                m_fwd = true;
                m_t = 0;
            } else {
                m_entity->SetPosition(cm.startPosition);
            }
        }
        if (cm.hold > 0) {
            m_hold = true;
            m_holdTime = cm.hold;
            m_holdTimer = 0.0f;
        }
    } else {
        glm::vec2 currentPos = cm.startPosition + cm.dir * m_cumulatedLength;
        // apply sinusoidal component
        if (m_hasSinX) {
            currentPos.x += m_sinx[0] * sin(m_sinx[1] * m_t + m_sinx[2]);
        }
        if (m_hasSinY) {
            currentPos.y += m_sinx[0] * sin(m_sinx[1] * m_t + m_sinx[2]);
        }
        m_entity->SetPosition(currentPos);
        // m_entity->MoveLocal(translation);
    }
    auto pos = m_entity->GetPosition();
}

void PolygonalMover::setStartPosition(int si, float pct) {
    m_startIndex = si;
    m_pctComplete = pct;
}

void PolygonalMover::setCompleteCallback(pybind11::function f) {
    m_hook = std::make_shared<pybind11::function>(f);
}

AcceleratedMover::AcceleratedMover(const ITable& t) {
	m_angularSpeed = t.get<float>("angular_speed", 0.0f);
	m_initialVelocity = t.get<glm::vec2>("v0");
	m_acceleration = t.get<glm::vec2>("acceleration");
	m_velocity = m_initialVelocity;
	m_angle = 0.0f;
}

void AcceleratedMover::Update(double dt) {
	float step = dt;
	m_angle += m_angularSpeed * dt;
	glm::vec2 dpos = m_velocity * step;
	glm::vec2 dvel = m_acceleration * step;
	m_velocity += dvel;
	m_entity->MoveOrigin(dpos);
	m_entity->SetAngle(m_angle);
}