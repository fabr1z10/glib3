#pragma once

#include <monkey/components/renderer.h>
#include <monkey/model/basicmodel.h>


class MultiRenderer : public Renderer {
public:
    MultiRenderer ();
    ~MultiRenderer() override;
    void Draw(Shader*) override;
    void Start() override {}
    std::type_index GetType() override;
    void setVisible(int);
    void clearVisible();
    void setAllVisible();
    void SetModel(std::shared_ptr<IModel> mesh) override;
    void addModel (std::shared_ptr<BasicModel>);
    void clear();
private:
    std::vector<std::pair<bool, std::shared_ptr<BasicModel>>> m_models;
};