#include <gfx/activities/cambounds.h>
#include <gfx/engine.h>


ChangeCamBounds::ChangeCamBounds(const std::string &camId, float xMin, float xMax, float yMin, float yMax)
: Activity(), m_camId(camId), m_xMin(xMin), m_xMax(xMax), m_yMin(yMin), m_yMax(yMax) {


}

void ChangeCamBounds::Start() {
    auto camera = Engine::get().GetRef<OrthographicCamera>(m_camId);
    std::cout << "Setting camera bounds to " << m_xMin << ", " << m_xMax << ", " << m_yMin << ", " << m_yMax << "\n";
    camera->SetBounds(m_xMin, m_xMax, m_yMin, m_yMax);
    SetComplete();


}