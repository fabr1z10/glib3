#include <monkey/assets/imodel.h>
#include <monkey/imesh.h>

// a model with only one mesh
class ComboModel : public IModel {
public:
    ComboModel ();
    Bounds GetBounds() const override;
    void draw (Shader*, int offset = 0, int count = 0) override;
    std::vector<std::string> GetAnimations() const override;
    std::string GetDefaultAnimation() const override ;
    ShaderType GetShaderType() const override;
    void addModel (std::shared_ptr<IModel>);
private:
    std::vector<std::shared_ptr<IModel>> m_models;
    //std::vector<std::shared_ptr<IMesh>> m_meshes;

};