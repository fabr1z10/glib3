#pragma once

#include <gfx/components/inputmethod.h>

class Controller2D;

class EnemyInputMethod : public InputMethod {
public:
    EnemyInputMethod(bool left, bool flipIfPlatformEnds) : InputMethod(),
        m_left(left), m_flipIfPlatformEnds(flipIfPlatformEnds), m_controller(nullptr) {}
    EnemyInputMethod(const EnemyInputMethod& orig) : InputMethod(orig),
        m_left(orig.m_left), m_flipIfPlatformEnds(orig.m_flipIfPlatformEnds), m_controller(nullptr) {}
    std::shared_ptr<Component> clone() const override;
    void Start() override;
    void Update (double) override;
    bool isKeyDown(int) override;
    std::type_index GetType() override;
    using ParentClass = InputMethod;
private:
    Controller2D * m_controller;
    bool m_left;
    bool m_flipIfPlatformEnds;
};

inline std::type_index EnemyInputMethod::GetType() {
    return std::type_index(typeid(InputMethod));
}
