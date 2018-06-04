#include <gfx/component.h>
#include <gfx/camera.h>


class Follow : public Component {
public:
    Follow (const std::string& cam) : Component(), m_camId{cam} {}
    void Start() override;
    void Update(double) override;
    using ParentClass = Follow;
private:
    std::string m_camId;
    Camera* m_cam;
    glm::vec3 m_previousPosition;
};