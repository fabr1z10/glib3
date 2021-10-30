#include <monkey/assets/model.h>
#include <monkey/textmesh.h>

class TextModel : public Model {
public:
    TextModel(Font* font,
        const std::string& message,
        float size,
        TextAlignment align,
        float maxLineWidth = 0.0f);
    //ShaderType GetShaderType() const override;
    // specific to text model
    std::string getText () const;
    void setText(const std::string&);
    glm::vec2 GetOffset() const;
    Bounds getBounds() const;
    int GetNumberOfLines() const;
private:
    std::string m_text;
    Font* m_font;
    float m_size;
    void splitIntoLines(const std::string&, std::vector<std::string>& lines, float scalingFactor, float mll);
    void updateText();
};