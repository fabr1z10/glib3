#include <monkey/entitywrapper.h>
#include <gfx/renderer.h>
#include <glm/glm.hpp>

float EntityWrapper::GetX() const {
    return m_underlying->GetPosition().x;
}

EntityWrapper EntityWrapper::GetParent() {
    return EntityWrapper(m_underlying->GetParent());
}

void EntityWrapper::SetColor(int r, int g, int b, int a) {
    m_underlying->GetComponent<Renderer>()->SetTint(glm::vec4(r/255.0f, g/255.0f, b/255.0f, a/255.0f));
}