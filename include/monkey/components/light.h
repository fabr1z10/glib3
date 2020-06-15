#pragma once

#include "monkey/component.h"
#include <glm/glm.hpp>

class LightShader;


class Light : public Component {
public:
    Light () : Component() {}
    Light(const Light& orig) : Component(orig) {}
    virtual ~Light() ;
    void Start() override;
    void Update(double) override {}
    virtual void setUp(LightShader*) = 0;
};


//class AmbientLight : public Light {
//public:
//    AmbientLight (glm::vec3 color) : Light(), m_color(color) {}
//    AmbientLight (const AmbientLight&);
//    void setUp(Shader*) override ;
//    std::shared_ptr<Component> clone() const override;
//private:
//    glm::vec3 m_color;
//};

class DirectionalLight : public Light {
public:
    //DirectionalLight (glm::vec3 direction, glm::vec3 color) ;
    DirectionalLight (const DirectionalLight&);
    void setUp(LightShader*) override ;
    std::shared_ptr<Component> clone() const override;
private:
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_direction;
};

