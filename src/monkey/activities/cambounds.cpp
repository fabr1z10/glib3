#include <monkey/activities/cambounds.h>
#include <monkey/engine.h>
#include <monkey/monkey.h>


ChangeCamBounds::ChangeCamBounds(const std::string &camId, float xMin, float xMax, float yMin, float yMax)
: Activity(), m_camId(camId), m_xMin(xMin), m_xMax(xMax), m_yMin(yMin), m_yMax(yMax) {


}


ChangeCamBounds::ChangeCamBounds(const ITable& t) : Activity() {
    m_camId = t.get<std::string>("cam");

    m_xMin = t.get<float>("xmin");
    m_xMax = t.get<float>("xmax");
    m_yMin = t.get<float>("ymin");
    m_yMax = t.get<float>("ymax");

}


void ChangeCamBounds::Start() {
    auto camera = Monkey::get().Get<OrthographicCamera>(m_camId);
    std::cout << "Setting camera bounds to " << m_xMin << ", " << m_xMax << ", " << m_yMin << ", " << m_yMax << "\n";
    camera->SetBounds(m_xMin, m_xMax, m_yMin, m_yMax);
    SetComplete();


}