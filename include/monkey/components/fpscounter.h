#pragma once

#include <monkey/component.h>
#include <monkey/textmesh.h>

class FPSCounter : public Component {

public:
    FPSCounter();
    FPSCounter(const FPSCounter&);
    void Start() override ;
    void Update(double) override;
    std::shared_ptr<Component> clone() const override;
private:
    int m_frameCount;
    double m_frameStart;
    TextMesh* m_textMesh;
};
