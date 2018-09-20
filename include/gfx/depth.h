#ifndef __depth_compononent_hpp
#define __depth_compononent_hpp

#include <gfx/component.h>
#include <monkey/funcs.h>

class Renderer;

class DepthCalculator : public Component {
public:
    DepthCalculator();
    void Start() override;
    void Update(double) override {}
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