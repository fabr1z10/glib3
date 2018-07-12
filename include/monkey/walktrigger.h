#pragma once

#include <gfx/component.h>
#include <graph/shape.h>
#include <memory>

class Entity;

class WalkTrigger : public Component {
public:
    WalkTrigger (std::shared_ptr<Shape> shape, const std::string& target);
    void Start() override;
    void Update(double) override ;
    virtual void onEnter() = 0;
    virtual void onLeave() = 0;
    virtual void onStay() = 0;
    void SetParent(Entity*) override;
private:
    void onTargetMove(Entity*);
    std::shared_ptr<Shape> m_shape;
    std::string m_target;
    bool m_isInside;
};