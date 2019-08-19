#include <gfx/component.h>
#include <gfx/math/shape.h>


class WalkStop : public Component {
public:
    WalkStop (std::shared_ptr<Shape> shape);
    WalkStop (const WalkStop&);
    std::shared_ptr<Component> clone() const override;
    void Start() override;
    void Update(double) override {}

private:
    std::shared_ptr<Shape> m_shape;

};