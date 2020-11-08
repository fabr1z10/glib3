#pragma once

#include <monkey/components/renderer.h>
#include <monkey/model/basicmodel.h>


class MultiRenderer : public Renderer {
public:
    MultiRenderer ();
    MultiRenderer (const MultiRenderer&);
    ~MultiRenderer() override;
    std::shared_ptr<Component> clone() const override;
    void Draw(Shader*) override;
    void Start() override {}
    std::type_index GetType() override;
    void setVisible(int);
    void clearVisible();
    void setAllVisible();
    void SetModel(std::shared_ptr<IModel> mesh) override;
    void addModel (std::shared_ptr<BasicModel>);
private:
    std::vector<std::pair<bool, std::shared_ptr<BasicModel>>> m_models;
};