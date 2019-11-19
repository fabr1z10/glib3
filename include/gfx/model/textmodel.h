#include <gfx/model/basicmodel.h>
#include <gfx/textmesh.h>

class TextModel : public BasicModel {
public:
    TextModel (std::shared_ptr<TextMesh> mesh);
    ShaderType GetShaderType() const override;
    // specific to text model
    std::string GetText () const;
    void SetText(const std::string&);
    glm::vec2 GetOffset() const;
    int GetNumberOfLines() const;
private:
   TextMesh* m_textMesh;

};