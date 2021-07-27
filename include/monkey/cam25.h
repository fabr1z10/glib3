#pragma once

#include <monkey/camera.h>

class Camera25 : public OrthographicCamera {
public:
	Camera25(const ITab&);
	void SetPosition(glm::vec3 eye, glm::vec3 direction, glm::vec3 up = glm::vec3(0, 1, 0), bool alwaysUpdate = false) override;
	void Init() override;

private:
	float m_angle;
	float m_cosAngle;
	float m_sinAngle;
};