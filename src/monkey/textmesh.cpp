//#include <algorithm>
//#include <monkey/textmesh.h>
//#include <sstream>
//#include <monkey/shader.h>
//#include <glm/gtc/matrix_transform.hpp>
//#include <unordered_set>
//#include <limits>
//#include <string>
//#include <locale>
//#include <codecvt>
//
//using namespace std;
//
//TextMesh::TextMesh(Font* font, const std::string& message, float lineHeight, TextAlignment align, float maxLineWidth) :
//        Mesh<VertexText>(TEXT_SHADER), m_font{font}, m_fontSize{lineHeight}, m_align{align}
//{
//    m_primitive = GL_TRIANGLES;
//    m_texId = font->getTexId();
//    UpdateText(message, maxLineWidth);
//}
//
//void TextMesh::UpdateText(const std::string& msg, float maxLineWidth) {
//    m_text = msg;
//    if (m_vb != INVALID_OGL_VALUE)
//        glDeleteBuffers(1, &m_vb);
//    if (m_ib != INVALID_OGL_VALUE)
//        glDeleteBuffers(1, &m_ib);
//    if (msg.length() == 0) {
//        m_vb = INVALID_OGL_VALUE;
//        m_ib = INVALID_OGL_VALUE;
//        return;
//    }
//
//    vector <VertexText> vertices;
//    vector <unsigned int> indices;
//    vector <string> lines;
//
//    float scalingFactor = m_fontSize / m_font->size(); //font.getMaxHeight();
//    if (maxLineWidth == 0.0f)
//        lines.push_back(msg);
//    else
//        splitIntoLines(m_font, msg, lines, scalingFactor, maxLineWidth);
//
//    // now loop through each line
//    float y = -m_fontSize;
//    unsigned int letterCount = 0;
//
//    m_bounds.min = glm::vec3(std::numeric_limits<float>::infinity());
//    m_bounds.max = glm::vec3(-std::numeric_limits<float>::infinity());
//    m_lines = lines.size();
//
//    // loop through lines
//    for (size_t n = 0; n < lines.size(); n++) {
//        //std::u32string sss(lines[n].c_str());
//        //auto sss = std::wstring_convert<std::codecvt_utf8<char32_t >>().from_bytes(lines[n].c_str());
//
//        auto sss = std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t >().from_bytes(lines[n].c_str());
//        //std::string sss = lines[n];
//        float x = 0.0f;					// current cursor position
//        for (const auto& w : sss) {
//
//            //char c = lines[n][i];
//            //bool isLastCharacter = i == lines[n].length()-1;
//            Glyph glyph = m_font->getGlyph(w);
//
//            float scaledWidth = glyph.width * scalingFactor;
//            float scaledHeight = glyph.height * scalingFactor;
//            float scaledYOffset = glyph.heightOffset * scalingFactor;
//            float scaleAdvance = glyph.advanceToNext * scalingFactor;
//
//            float yTop = y + scaledYOffset;
//            float yBottom = yTop - scaledHeight;
//            float lastX = x + scaledWidth;
//
//
//            vertices.emplace_back(VertexText(x, yTop, glyph.tx, glyph.ty, 1.0f, 1.0f, 1.0f, 1.0f));
//            vertices.emplace_back(VertexText(lastX, yTop, glyph.tx + glyph.tw, glyph.ty, 1.0f, 1.0f, 1.0f, 1.0f));
//            vertices.emplace_back(VertexText(lastX, yBottom, glyph.tx + glyph.tw, glyph.ty + glyph.th, 1.0f, 1.0f, 1.0f, 1.0f));
//            vertices.emplace_back(VertexText(x, yBottom, glyph.tx, glyph.ty + glyph.th, 1.0f, 1.0f, 1.0f, 1.0f));
//
//            m_bounds.min.x = min(m_bounds.min.x, x);
//            m_bounds.max.x = max(m_bounds.max.x, lastX);
//            m_bounds.min.y = min(m_bounds.min.y, yBottom);
//            m_bounds.max.y = max(m_bounds.max.y, yTop);
//
//            unsigned int ix = letterCount * 4;
//            indices.push_back(ix);
//            indices.push_back(ix + 1);
//            indices.push_back(ix + 3);
//            indices.push_back(ix + 3);
//            indices.push_back(ix + 2);
//            indices.push_back(ix + 1);
//            letterCount++;
//            x += scaleAdvance;
//
//        }
//        y -= m_fontSize;
//    }
//    //glm::vec2 offset = getOffset();
//    //m_localTransform = glm::translate(glm::mat4(1.0f), glm::vec3(offset.x, offset.y, 0.0f));
//    //m_width = xMax - xMin;
//    //m_height = yMax - yMin;
//    //m_topLeft = glm::vec2 (xMin, yMax);
//    //m_offsetY = yMax;
//    //m_bottomRight = glm::vec2 (xMax, yMin);
//
//    Init(vertices, indices);
//    //material.texId = font.getTexId();
//}
//
//
//
//void TextMesh::Setup(Shader* shader) {
//    shader->setInt("Tex1", 0);
////    auto texLoc = shader->GetUniformLocation(TEXTURE);
//  //  glUniform1i(texLoc, 0);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, m_texId);
//}
//
//glm::vec2 TextMesh::getOffset() {
//
//}
//
