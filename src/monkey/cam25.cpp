#include <monkey/cam25.h>
#include <monkey/math/geom.h>

Camera25::Camera25(const ITab& tab) : OrthographicCamera(tab) {
	m_angle = glm::radians(tab.get<float>("angle", 45.0f));
	m_cosAngle = cos(m_angle);
	m_sinAngle = sin(m_angle);
}

void Camera25::Init() {
	SetPosition(m_eye, m_fwd, m_up, true);

}

void Camera25::SetPosition(glm::vec3 eye, glm::vec3 dir, glm::vec3 up, bool alwaysUpdate) {
	eye.x = Clamp(eye.x, m_xMin, m_xMax);
	eye.y = Clamp(eye.y, m_yMin, m_yMax);
	eye.z = Clamp(eye.z, m_zMin, m_zMax);

	if (alwaysUpdate || !isEqual(eye.x, m_eye.x) || !isEqual(eye.y, m_eye.y) || !isEqual(eye.z, m_eye.z)) {
		m_fwd = dir;
		m_up = up;
		m_eye = eye;

		m_viewMatrix = glm::mat4(1.0f);
		m_viewMatrix[1][1] = 1.0f;
		m_viewMatrix[2][1] = -m_sinAngle;
		m_viewMatrix[3][0] = -m_eye.x;
		m_viewMatrix[3][1] = -m_eye.y;
		m_viewMatrix[3][2] = -m_eye.z;
		OnMove.Fire(this);
	}

}