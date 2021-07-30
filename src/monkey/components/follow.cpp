#include <monkey/components/follow.h>
#include <monkey/engine.h>
#include <iostream>

Follow::Follow (const std::string& cam, glm::vec3 relativePos, glm::vec3 up) :
Component(), m_camId{cam}, m_relativePos(relativePos), m_up(up), m_fixZ{false}
{
    //m_dir = -glm::normalize(m_relativePos);
    m_dir = glm::vec3(0,0, -1);
}

void Follow::Begin() {
	glm::vec3 pos = m_entity->GetPosition();
	glm::vec3 eye = pos + m_relativePos;
	if (m_fixZ) {
		eye.z = m_z;
	}
	m_cam->SetPosition(eye, m_dir, m_up);
	m_previousPosition = pos;

}

Follow::Follow(const ITab & t) : Component(t), m_fixZ{false} {
    m_dir = glm::vec3(0,0, -1);

    m_camId = t.get<std::string>("cam");
    m_relativePos = t.get<glm::vec3>("relativepos");
    m_up = t.get<glm::vec3>("up");
    if (t.has("z")) {
        float z = t.get<float>("z");
        fixZ(z);
    }
}

DynamicFollow::DynamicFollow(const ITab& t) : Follow(t) {
	auto camWidth = t.get<float>("cam_width");
	auto camHeight = t.get<float>("cam_height");
	m_camHalfWidth = camWidth * 0.5f;
	m_camHalfHeight = camHeight * 0.5f;
	m_worldWidth = t.get<float>("world_width");
	m_x0 = m_camHalfWidth;
	m_x1 = m_worldWidth - m_camHalfWidth;
	auto camPos = t.get<std::vector<float>>("bounds");

	float previousSize = 0.0f;
	float x{0.0f};
	for (size_t i = 0; i < camPos.size(); i+=3) {
		float currentSize = camPos[i+2] - camPos[i+1];
		if (currentSize >= previousSize) {
			x = (i == 0 ? 0.0f : camPos[i] + m_camHalfWidth);

		} else {
			x = camPos[i] - m_camHalfWidth;
		}
		float yMin = camPos[i+1] + m_camHalfHeight;
		float yMax = std::max(camPos[i+2] - m_camHalfHeight, yMin);
		m_dynamicCamBounds[x] = glm::vec2(yMin, yMax);
	}


}

void Follow::Start() {

    m_cam = Monkey::get().Get<Camera>(m_camId);


}

void Follow::fixZ(float z) {
    m_fixZ = true;
    m_z = z;
}

void Follow::Update (double dt) {
    if (!m_active) return;
    glm::vec3 pos = m_entity->GetPosition();
    if (m_previousPosition - pos != glm::vec3(0.0f)) {
        glm::vec3 eye = pos + m_relativePos;
        if (m_fixZ) {
            eye.z = m_z;
        }
        // eye.y = 10;
        //std::cout << "Update cam pos to " << pos.x << ", " << pos.y << "\n";
        m_cam->SetPosition(eye, m_dir, m_up);

    }
	m_previousPosition = pos;
}

//         |  cw			 if x_player <= cw
// x_cam = |  ww - cw		 if x_player >= ww - cw
//         |  x_player		 otherwise

void DynamicFollow::Update (double dt) {
	if (!m_active) return;
	glm::vec3 pos = m_entity->GetPosition();

	if (m_previousPosition - pos != glm::vec3(0.0f)) {
		float yplayer = pos.y -0.707106781186548 * pos.z;
		float xCam = Clamp(pos.x, m_x0, m_x1);
		auto it = m_dynamicCamBounds.upper_bound(xCam);
		it--;
		float yCam = Clamp(yplayer, it->second.x, it->second.y);
		float zCam = 0.01*pos.z;

		glm::vec3 eye = glm::vec3(xCam, yCam, zCam) + m_relativePos;
		if (m_fixZ) {
			eye.z = m_z;
		}
		m_cam->SetPosition(eye, m_dir, m_up);

	}
	m_previousPosition = pos;
}