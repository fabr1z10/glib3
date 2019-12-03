#pragma once

#include <gfx/components/inputmethod.h>
#include <map>

class Controller2D;

class BasicEnemyInputMethod : public InputMethod {
public:

    BasicEnemyInputMethod(int status, bool flipIfPlatformEnds) : InputMethod(),
        m_left(status==1), m_flipIfPlatformEnds(flipIfPlatformEnds), m_controller(nullptr) {}

    BasicEnemyInputMethod(const BasicEnemyInputMethod& orig) : InputMethod(orig),
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
    Entity* m_target;
};

inline std::type_index BasicEnemyInputMethod::GetType() {
    return std::type_index(typeid(InputMethod));
}
