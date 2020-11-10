#pragma once

#include "monkey/components/ianimator.h"

class Renderer;

class Fader : public IAnimator {
public:
    Fader (const ITable&);
    virtual ~Fader() {}
    bool IsComplete() const override;
    void Start() override;
    void Update(double dt) override;
    std::type_index GetType() override;
    void setModel (std::shared_ptr<IModel> model) override { throw; }
    void SetAnimation (const std::string& anim, bool forward = true) override { throw; }
    virtual IModel* getModel() const { return nullptr;}
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