#pragma once

#include <monkey/components/renderer.h>
#include <monkey/model/basicmodel.h>

class BasicRenderer : public Renderer {
public:
    BasicRenderer (std::shared_ptr<IModel> model);
    BasicRenderer (const BasicRenderer&);
    std::shared_ptr<Component> clone() const override;

    void Draw(Shader*) override;
    void Start() override {}
    std::type_index GetType() override;
    void SetModel(std::shared_ptr<IModel> mesh) override;
private:
    std::shared_ptr<BasicModel> m_model;
};