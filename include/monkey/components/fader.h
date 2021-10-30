#pragma once

#include "monkey/components/ianimator.h"
#include <glm/glm.hpp>

class Renderer;

class Fader : public IAnimator {
public:
    Fader (const ITab&);
    virtual ~Fader() {}
    bool IsComplete() const override;
    void Start() override;
    void Update(double dt) override;
    std::type_index GetType() override;
    void setModel (std::shared_ptr<Model> model) override { throw; }
    void SetAnimation (const std::string& anim, bool forward = true) override { throw; }
    virtual Model* getModel() const { return nullptr;}
	std::shared_ptr<IShape> getShapeCast() override { return nullptr;}
private:
    std::vector<glm::vec4> m_colors;
    std::vector<float> m_times;
    float m_T;
    float m_t;
    int m_index;
    Renderer* m_renderer;

};

inline bool Fader::IsComplete() const {
    return false;
}

inline std::type_index Fader::GetType() {
    return std::type_index(typeid(IAnimator));
}