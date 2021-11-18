#include <monkey/components/icontroller.h>
#include <monkey/entity.h>

IController::IController(const ITab& t) : m_debugShape(nullptr) {
	auto size = t.get<glm::vec3>("size");
	m_halfSize = 0.5f * size;
	m_shift = t.get<glm::vec3>("offset",glm::vec3(0.0f));
    m_debug = t.get<bool>("debug", false);

}

void IController::setBounds(glm::vec3 size, glm::vec3 shift) {
    m_halfSize = 0.5f * size;
    m_shift = shift;
    if (m_debug) {
        if (m_debugShape != nullptr) {
            m_entity->Remove(m_debugShape);
        }
        drawShape();
    }
}