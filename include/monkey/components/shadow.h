#pragma once

#include <monkey/component.h>
#include <monkey/components/depth25.h>

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


