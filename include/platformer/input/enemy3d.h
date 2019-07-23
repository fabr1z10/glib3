#pragma once

#include <gfx/components/inputmethod.h>
#include <map>

class Controller3D;

class Enemy3DInputMethod : public InputMethod {
public:
    Enemy3DInputMethod(bool left, bool flipIfPlatformEnds) : InputMethod(),
        m_left(left), m_flipIfPlatformEnds(flipIfPlatformEnds), m_controller(nullptr) {}
    Enemy3DInputMethod(const Enemy3DInputMethod& orig) : InputMethod(orig),
        m_left(orig.m_left), m_flipIfPlatformEnds(orig.m_flipIfPlatformEnds), m_controller(nullptr) {}
    std::shared_ptr<Component> clone() const override;
    void Start() override;
    void Update (double) override;
    bool isKeyDown(int) override;
    std::type_index GetType() override;
    using ParentClass = InputMethod;
private:
    Controller3D * m_controller;
    bool m_left;
    bool m_flipIfPlatformEnds;
};

inline std::type_index Enemy3DInputMethod::GetType() {
    return std::type_index(typeid(InputMethod));
}
