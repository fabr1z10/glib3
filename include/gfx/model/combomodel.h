#include <gfx/imodel.h>
#include <gfx/imesh.h>

// a model with only one mesh
class ComboModel : public IModel {
public:
    ComboModel ();
    Bounds GetBounds() const override;
    void Draw (Shader*, int offset, int count);
    std::vector<std::string> GetAnimations() const override;
    std::string GetDefaultAnimation() const override ;
    ShaderType GetShaderType() const override;
    void AddMesh (std::shared_ptr<IMesh>);
private:
    std::vector<std::shared_ptr<IMesh>> m_meshes;

};