#pragma once

#include <monkey/component.h>
#include <monkey/model/textmodel.h>

class FPSCounter : public Component {

public:
    FPSCounter();
    FPSCounter(const ITable&);
    void Start() override ;
    void Update(double) override;
private:
    int m_frameCount;
    double m_frameStart;
    TextModel* m_textMesh;
};
