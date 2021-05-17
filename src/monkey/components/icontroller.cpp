#include <monkey/components/icontroller.h>

IController::IController(const ITab& t) {
	auto size = t.get<glm::vec3>("size");
	m_halfSize = 0.5f * size;
	m_shift = t.get<glm::vec3>("shift",glm::vec3(0.0f, m_halfSize.y, 0.0f));
}