#include <gfx/component.h>
#include <gfx/camera.h>


class Follow : public Component {
public:
    Follow (const std::string& cam, glm::vec3 relativePos, glm::vec3 up);
    void Start() override;
    void Update(double) override;
    void fixZ(float);
    using ParentClass = Follow;
private:
    // relative position of camera w.r.t. target
    bool m_fixZ;
    glm::vec3 m_relativePos;
    glm::vec3 m_dir;
    glm::vec3 m_up;
    std::string m_camId;
    Camera* m_cam;
    glm::vec3 m_previousPosition;
    float m_z;
};
