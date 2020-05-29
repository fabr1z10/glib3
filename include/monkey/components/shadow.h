#pragma once

#include <monkey/component.h>
#include <monkey/components/controller25.h>

class Shadow : public Component {
public:
    Shadow();
    Shadow (const Shadow&);
    Shadow (const ITable& t);
    std::shared_ptr<Component> clone() const override;
    void Start() override;
    void Update(double) override ;
    using ParentClass = Shadow;
private:
    bool m_yFix;
    float m_y;
    void ResetPosition(Entity *);
    Controller25* m_depth;
};

class ShadowX : public Component {
public:
    ShadowX();
    ShadowX (const ShadowX&);
    ShadowX (const ITable& t);
    std::shared_ptr<Component> clone() const override;
    void Start() override;
    void Update(double) override ;
    using ParentClass = Shadow;
private:
    float m_y;
    void ResetPosition(Entity *);
    Entity * m_followed;
    std::string m_target;
};


