#ifndef __depth_compononent_hpp
#define __depth_compononent_hpp

#include <gfx/component.h>
#include <gfx/math/funcs.h>

class Renderer;

class DepthCalculator : public Component {
public:
    DepthCalculator() : Component(), m_depthFunc(nullptr), m_scaleFunc(nullptr) {}
    void Start() override;
    void Update(double) override {}
    float GetFloorY (float x, float z);
    void SetDepthFunction (std::unique_ptr<Function2D> func);
    void SetScalingFunction (std::unique_ptr<Function2D> func);
    using ParentClass = DepthCalculator;
private:
    void UpdateDepthAndScale(Entity*);
    std::unique_ptr<Function2D> m_depthFunc;
    std::unique_ptr<Function2D> m_scaleFunc;
    Renderer* m_renderer;
};



inline void DepthCalculator::SetDepthFunction (std::unique_ptr<Function2D> func) {
    m_depthFunc = std::move(func);
}
inline void DepthCalculator::SetScalingFunction (std::unique_ptr<Function2D> func) {
    m_scaleFunc = std::move(func);
}

#endif
