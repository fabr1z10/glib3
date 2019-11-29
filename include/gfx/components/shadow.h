#pragma once

#include <gfx/component.h>
#include <gfx/components/depth25.h>

class Shadow : public Component {
public:
    Shadow();
    Shadow (const Shadow&);
    std::shared_ptr<Component> clone() const override;
    void Start() override;
    void Update(double) override ;
    using ParentClass = Shadow;
private:
    void ResetPosition(Entity *);
    Depth25* m_depth;
};


