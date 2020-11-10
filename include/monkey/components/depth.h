#ifndef __depth_compononent_hpp
#define __depth_compononent_hpp

#include <monkey/component.h>
#include <monkey/math/funcs.h>

class Renderer;

class DepthCalculator : public Component {
public:
    DepthCalculator() : Component(), m_depthFunc(nullptr), m_scaleFunc(nullptr) {}
    void Start() override;
    void Update(double) override;
    float GetFloorY (float x, float z);
    void SetDepthFunction (std::shared_ptr<Function2D> func);
    void SetScalingFunction (std::shared_ptr<Function2D> func);
    using ParentClass = DepthCalculator;
private:
    void UpdateDepthAndScale();
    std::shared_ptr<Function2D> m_depthFunc;
    std::shared_ptr<Function2D> m_scaleFunc;
    //Renderer* m_renderer;
    glm::vec2 m_pos;
};



inline void DepthCalculator::SetDepthFunction (std::shared_ptr<Function2D> func) {
    m_depthFunc = func;
}
inline void DepthCalculator::SetScalingFunction (std::shared_ptr<Function2D> func) {
    m_scaleFunc = func;
}

#endif
