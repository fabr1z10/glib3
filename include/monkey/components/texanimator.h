#pragma once

#include "monkey/components/ianimator.h"
#include <glm/glm.hpp>
class Renderer;

class TexAnimator : public IAnimator {
public:
    TexAnimator (const ITab&);
    virtual ~TexAnimator() {}
    bool IsComplete() const override;
    void Start() override;
    void Update(double dt) override;
    std::type_index GetType() override;
    void setModel (std::shared_ptr<IModel> model) override { throw; }
    void SetAnimation (const std::string& anim, bool forward = true) override { throw; }
    virtual IModel* getModel() const { return nullptr;}
	std::shared_ptr<IShape> getShapeCast() override { return nullptr;}

private:
    // sawtooth
    // offset goes from 0 to 1 in time T
    glm::vec2 m_T;
    glm::vec2 m_t;
    glm::vec2 m_sgn;
    glm::vec2 m_offset;
    Renderer* m_renderer;

};

inline bool TexAnimator::IsComplete() const {
    return false;
}

inline std::type_index TexAnimator::GetType() {
    return std::type_index(typeid(IAnimator));
}