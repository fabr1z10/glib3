#pragma once

#include <gfx/component.h>
#include <gfx/depth.h>

class Shadow : public Component {
public:
    Shadow();
    void Start() override;
    void Update(double) override {}
    using ParentClass = Shadow;
private:
    void ResetPosition(Entity *);
    DepthCalculator* m_depth;
};


