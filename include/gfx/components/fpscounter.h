#pragma once

#include <gfx/component.h>
#include <gfx/textmesh.h>

class FPSCounter : public Component {

public:
    FPSCounter();
    void Start() override ;
    void Update(double) override;
private:
    int m_frameCount;
    double m_frameStart;
    TextMesh* m_textMesh;
};