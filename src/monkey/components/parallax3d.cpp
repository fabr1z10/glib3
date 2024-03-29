#include <monkey/components/parallax3d.h>
#include <monkey/engine.h>
#include <monkey/components/renderer.h>
#include <monkey/quadmesh.h>
#include <monkey/assets/model.h>
#include <monkey/model/factory.h>

Parallax3D::Parallax3D(const std::string &camId, float z, const std::string &img) : m_camId(camId), m_img(img), m_z(z) {}



void Parallax3D::Start() {
    m_cam = Monkey::get().Get<PerspectiveCamera>(m_camId);
    m_cam->OnMove.Register(this, [&] (Camera* cam) { this->onCameraMove(cam); });

    // create the panel
    auto tex = Engine::get().GetAssetManager().get<Tex>(m_img);
    auto w = tex->GetWidth();
    auto h = tex->GetHeight();

    float fov = m_cam->getFieldOfView();
    auto entity = std::make_shared<Entity>();
    float panelHeight = 2.0*m_z * tan(fov*0.5f);
    //f<loat horizontalCamWidth = panelHeight * m_cam->getAspectRatio();
    m_panelWidth = panelHeight * (static_cast<float>(w)/h);
    m_halfPanelHeight = 0.5*panelHeight;
    //auto mesh = std::make_shared<QuadMesh>(m_img, 3*m_panelWidth, panelHeight, 3, 1);
    //auto model = std::make_shared<BasicModel>(mesh);
    auto model = ModelFactory::quad(m_img, 3 * m_panelWidth, panelHeight, 3, 1);
    auto renderer = std::make_shared<Renderer>(model);

    glm::vec3 camPos = m_cam->GetPosition();
    camPos += glm::vec3(0, -m_halfPanelHeight, -m_z);
    m_camPos = 0;
    entity->SetPosition(glm::vec3(-m_panelWidth*1.5f, -m_halfPanelHeight, camPos.z-m_z));
    entity->AddComponent(renderer);
    m_entity->AddChild(entity);
    m_bg = entity.get();

}

void Parallax3D::onCameraMove(Camera * cam) {
    glm::vec3 pos = cam->GetPosition();
    glm::vec3 bgPos = m_bg->GetPosition();

    int camPos = static_cast<int>(pos.x / m_panelWidth);
    float newX = bgPos.x;
    if (camPos != m_camPos) {
        // shift by
        glm::vec3 translation = static_cast<float>(camPos-m_camPos) * glm::vec3(m_panelWidth, 0.0f, 0.0f);
        newX += translation.x;
        m_camPos = camPos;
    }
    m_bg->SetPosition(glm::vec3(newX, pos.y-m_halfPanelHeight, pos.z-m_z));
}