#pragma once

#include <monkey/components/renderer.h>
#include <monkey/model/basicmodel.h>

class __attribute__ ((visibility ("default"))) BasicRenderer : public Renderer {
public:
    BasicRenderer (std::shared_ptr<IModel> model);
    BasicRenderer (const ITab&);

    void Draw(Shader*) override;
    void Start() override {}
    std::type_index GetType() override;
    void SetModel(std::shared_ptr<IModel> mesh) override;
private:
    std::shared_ptr<IModel> m_model;
};