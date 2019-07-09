#include <gfx/imodel.h>
#include <gfx/textmesh.h>

// a model with only one mesh
class TextModel : public IModel {
public:
    TextModel (std::shared_ptr<TextMesh> mesh);
    Bounds3D GetBounds() const override;
    void Draw (Shader*, int offset, int count) override;
    std::vector<std::string> GetAnimations() const override;
    std::string GetDefaultAnimation() const override ;
    ShaderType GetShaderType() const override;
    std::string GetText () const;
    void SetText(const std::string&);
    glm::vec2 GetOffset() const;
    int GetNumberOfLines() const;
private:
    std::shared_ptr<TextMesh> m_mesh;

};