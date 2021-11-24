#include <monkey/components/mover.h>
#include <monkey/entity.h>
#include <monkey/math/geom.h>

Mover::Mover() : Component(), m_pause(false), m_hold(false) {}

void Mover::setPause(bool value) {
    m_pause = value;
}

PolygonalMover::PolygonalMover(const ITab& t) {
    auto pts = t.get<std::vector<float>>("points");
    glm::vec2 P0;
    glm::vec2 P1;
    for (size_t i = 0; i< pts.size(); i+=2) {
        P1 = glm::vec2(pts[i], pts[i+1]);
        m_points.push_back(P1);
        if (i > 0) {
            m_uvec.push_back(glm::normalize(P1 - P0));
            m_distances.push_back(glm::length(P1-P0));
        }
        P0 = P1;
    }
    m_speed = t.get<float>("speed");
    m_mode = t.get<int>("mode");
}

void PolygonalMover::Start() {

    m_entity->SetPosition(m_points.front());
    m_currentEdge = 0;
    m_next = 1;
    m_distance = 0.0f;
    // going forward
    m_direction = 1;
    m_done = false;
}

void PolygonalMover::Update(double dt) {
    if (m_done) {
        return;
    }
    glm::vec2 uvec = m_uvec[m_currentEdge] * static_cast<float>(m_direction);
    glm::vec2 delta = uvec * m_speed * static_cast<float>(dt);
    m_entity->MoveLocal(delta);
    m_distance += glm::length(delta);
    if (m_distance >= m_distances[m_currentEdge]) {
        m_entity->SetPosition(m_points[m_next]);
        m_distance = 0.0f;
        if (m_direction == 1) {
            m_currentEdge++;
            if (m_currentEdge >= m_uvec.size()) {
                // what to do depends on mode
                switch (m_mode) {
                    case 0:
                        m_done = true;
                        break;
                    case 1:
                        m_currentEdge--;
                        m_direction = -1;
                        m_next = m_currentEdge;
                        break;
                    case 2:
                        m_currentEdge = 0;
                        m_direction = 1;
                        m_next = 1;
                        break;
                }
            }
        } else {
            m_currentEdge--;
            if (m_currentEdge < 0) {
                m_currentEdge = 0;
                m_direction = 1;
                m_next = 1;
            }
        }
    }

}

//PolygonalMover::Movement::Movement(glm::vec2 delta, float speed, float hold) : speed(speed), hold(hold) {
//    length = glm::length(delta);
//    dir = glm::normalize(delta);
//}
//PolygonalMover::PolygonalMover(int loopType, glm::vec2 origin) : Mover(), m_O(origin), m_startIndex(0), m_pctComplete(0.0f) {}
//
//
//PolygonalMover::PolygonalMover(const ITab & t) : Mover(), m_O(glm::vec2(0.0f)), m_startIndex(0), m_pctComplete(0.0f), m_hasSinX(false), m_hasSinY(false) {
//	m_O = t.get<glm::vec2>("origin");
//	//m_loopType = t.get<int>("loop");
//	m_pctComplete = t.get<float>("pct", 0.0f);
//	if (t.has("sinx")) {
//	    m_hasSinX = true;
//	    m_sinx = t.get<glm::vec3>("sinx");
//	    // convert period to freq
//	    m_sinx[1] = 2 * M_PI / m_sinx[1];
//	}
//    if (t.has("siny")) {
//        m_hasSinY = true;
//        m_siny = t.get<glm::vec3>("siny");
//        m_siny[1] = 2 * M_PI / m_siny[1];
//    }
//	t.foreach("moves", [&] (const ITab& d) {
//		auto delta = d.get<glm::vec2>("delta");
//		auto speed = d.get<float>("speed");
//		auto hold = d.get<float>("hold");
//		this->addMovement(delta, speed, hold);
//	});
//
//}
//
//
//
//void PolygonalMover::addMovement(glm::vec2 delta, float speed, float hold) {
//
//    m_movements.push_back(Movement(delta, speed, hold));
//}
//
//void PolygonalMover::Start() {
//
//    glm::vec2 P = m_O;
//    for ( auto& m : m_movements) {
//        m.startPosition = P;
//        m.endPosition = P + m.dir * m.length;
//        m.time = m.length / m.speed;
//        P = m.endPosition;
//    }
//    //m_entity->SetPosition(m_O);
//    m_currentMovement = m_startIndex;
//    const auto& im = m_movements[m_currentMovement];
//    m_cumulatedLength = im.length * m_pctComplete;
//    glm::vec2 startPos = im.startPosition + im.dir * m_cumulatedLength;
//    m_entity->SetPosition(startPos);
//    m_fwd = true;
//    m_t = m_pctComplete * im.time;
//}
//
//void PolygonalMover::Update(double dt) {
//    if (m_pause || m_movements.empty()) return;
//    m_t += dt;
//    if (m_hold) {
//        m_holdTimer += dt;
//        if (m_holdTimer >= m_holdTime) {
//            m_hold = false;
//        }
//        return;
//    }
//    Movement& cm = m_movements[m_currentMovement];
//    glm::vec2 dir = cm.dir;
//    if (!m_fwd) dir *= -1.0f;
//    glm::vec2 translation = (cm.speed * static_cast<float>(dt)) * dir;
//    m_cumulatedLength += cm.speed*dt;
//    if (m_cumulatedLength >= cm.length) {
//        m_cumulatedLength = 0.0f;
//        if (m_fwd) {
//            m_currentMovement++;
//			m_entity->SetPosition(cm.endPosition);
//            if (m_currentMovement >= m_movements.size()) {
//            	m_currentMovement = 0;
//            }
//        } else {
//            m_currentMovement--;
//            if (m_currentMovement < 0) {
//                m_entity->SetPosition(cm.startPosition);
//                m_currentMovement = 0;
//                m_fwd = true;
//                m_t = 0;
//            } else {
//                m_entity->SetPosition(cm.startPosition);
//            }
//        }
//        if (cm.hold > 0) {
//            m_hold = true;
//            m_holdTime = cm.hold;
//            m_holdTimer = 0.0f;
//        }
//    } else {
//        glm::vec2 currentPos = cm.startPosition + cm.dir * m_cumulatedLength;
//        // apply sinusoidal component
//        if (m_hasSinX) {
//            currentPos.x += m_sinx[0] * sin(m_sinx[1] * m_t + m_sinx[2]);
//        }
//        if (m_hasSinY) {
//            currentPos.y += m_sinx[0] * sin(m_sinx[1] * m_t + m_sinx[2]);
//        }
//        m_entity->SetPosition(currentPos);
//        // m_entity->MoveLocal(translation);
//    }
//    auto pos = m_entity->GetPosition();
//}
//
//void PolygonalMover::setStartPosition(int si, float pct) {
//    m_startIndex = si;
//    m_pctComplete = pct;
//}
//
//void PolygonalMover::setCompleteCallback(pybind11::function f) {
//    m_hook = std::make_shared<pybind11::function>(f);
//}
//
//AcceleratedMover::AcceleratedMover(const ITab& t) {
//	m_angularSpeed = t.get<float>("angular_speed", 0.0f);
//	m_initialVelocity = t.get<glm::vec2>("v0");
//	m_acceleration = t.get<glm::vec2>("acceleration");
//	m_velocity = m_initialVelocity;
//	m_angle = 0.0f;
//}
//
//void AcceleratedMover::Update(double dt) {
//	float step = dt;
//	m_angle += m_angularSpeed * dt;
//	glm::vec2 dpos = m_velocity * step;
//	glm::vec2 dvel = m_acceleration * step;
//	m_velocity += dvel;
//	m_entity->MoveOrigin(dpos);
//	m_entity->SetAngle(m_angle);
//}
ConstrainedDynamicMover::ConstrainedDynamicMover(const ITab &t) : Mover() {
    m_tMin = t.get<float>("min", std::numeric_limits<float>::lowest());
    m_tMax = t.get<float>("max", std::numeric_limits<float>::max());
}

void ConstrainedDynamicMover::Start() {
    m_dynamics = m_entity->GetComponent<Dynamics>();
    if (m_dynamics == nullptr) {
        GLIB_FAIL("Constrained dynamics component requires a dynamics component");
    }
}

void ConstrainedDynamicMover::Update(double dt) {
    // only consider the component of velocity along the line
    auto t = tangent(m_t);
    float speed = glm::dot(m_dynamics->m_velocity, t);
    m_dynamics->m_velocity = speed * t;


    // update position
    glm::vec2 p0 = getPosition();
    m_t += speed * dt;
    if (m_t <= m_tMin) {
        m_t = m_tMin;
    } else if (m_t >= m_tMax) {
        m_t = m_tMax;
    }
    auto delta = getPosition() - p0;
    m_entity->MoveLocal(delta);

}

LineDynamicMover::LineDynamicMover(const ITab& t) : ConstrainedDynamicMover(t) {
    m_u = glm::normalize(t.get<glm::vec2>("direction"));


}


void LineDynamicMover::Start() {
    ConstrainedDynamicMover::Start();
    m_origin = m_entity->GetPosition();
    m_t = 0.0f;

}

glm::vec2 LineDynamicMover::getPosition() {
    return m_origin + m_t * m_u;
}

glm::vec2 LineDynamicMover::tangent(float) {
    return m_u;
}