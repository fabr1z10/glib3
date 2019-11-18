#include <gfx/imodel.h>
#include <gfx/imesh.h>

// a model with only one mesh
class BasicModel : public IModel {
public:
    BasicModel (std::shared_ptr<IMesh> mesh);
    Bounds GetBounds() const override;
    void Draw (Shader*, int offset, int count);
    std::vector<std::string> GetAnimations() const override;
    std::string GetDefaultAnimation() const override ;
    ShaderType GetShaderType() const override;

private:
    std::shared_ptr<IMesh> m_mesh;

};