#include <algorithm>
#include <gfx/textmesh.h>
#include <sstream>
#include <gfx/shader.h>

using namespace std;

TextMesh::TextMesh(Font* font, const std::string& message, float lineHeight, TextAlignment align, float maxLineWidth) : Mesh<VertexText>(TEXT_SHADER), m_font{font}, m_fontSize{lineHeight}, m_align{align}
{
    m_primitive = GL_TRIANGLES;
    m_texId = font->getTexId();
    UpdateText(message, maxLineWidth);
}

void TextMesh::UpdateText(const std::string& msg, float maxLineWidth) {
    m_text = msg;
    if (m_vb != INVALID_OGL_VALUE)
        glDeleteBuffers(1, &m_vb);
    if (m_ib != INVALID_OGL_VALUE)
        glDeleteBuffers(1, &m_ib);
    if (msg.length() == 0) {
        m_vb = INVALID_OGL_VALUE;
        m_ib = INVALID_OGL_VALUE;
        return;
    }

    vector <VertexText> vertices;
    vector <unsigned int> indices;
    vector <string> lines;

    float scalingFactor = m_fontSize / m_font->size(); //font.getMaxHeight();
    if (maxLineWidth == 0.0f)
        lines.push_back(msg);
    else
        splitIntoLines(m_font, msg, lines, scalingFactor, maxLineWidth);

    // now loop through each line
    float y = -m_fontSize;
    int letterCount = 0;

    m_bounds.min.x = 1000;
    m_bounds.min.y = 1000;
    m_bounds.max.x = m_bounds.max.y = -1000;
    m_lines = lines.size();

    // loop through lines
    for (size_t n = 0; n < lines.size(); n++) {

        float x = 0.0f;					// current cursor position
        for (size_t i = 0; i < lines[n].length(); i++) {
            char c = lines[n][i];
            //bool isLastCharacter = i == lines[n].length()-1;
            Glyph glyph = m_font->getGlyph(c);

            float scaledWidth = glyph.width * scalingFactor;
            float scaledHeight = glyph.height * scalingFactor;
            float scaledYOffset = glyph.heightOffset * scalingFactor;
            float scaleAdvance = glyph.advanceToNext * scalingFactor;

            float yTop = y + scaledYOffset;
            float yBottom = yTop - scaledHeight;
            float lastX = x + scaledWidth;


            vertices.push_back(VertexText(x, yTop, glyph.tx, glyph.ty, 1.0f, 1.0f, 1.0f, 1.0f));
            vertices.push_back(VertexText(lastX, yTop, glyph.tx + glyph.tw, glyph.ty, 1.0f, 1.0f, 1.0f, 1.0f));
            vertices.push_back(VertexText(lastX, yBottom, glyph.tx + glyph.tw, glyph.ty + glyph.th, 1.0f, 1.0f, 1.0f, 1.0f));
            vertices.push_back(VertexText(x, yBottom, glyph.tx, glyph.ty + glyph.th, 1.0f, 1.0f, 1.0f, 1.0f));

            m_bounds.min.x = min(m_bounds.min.x, x);
            m_bounds.max.x = max(m_bounds.max.x, lastX);
            m_bounds.min.y = min(m_bounds.min.y, yBottom);
            m_bounds.max.y = max(m_bounds.max.y, yTop);

            int ix = letterCount * 4;
            indices.push_back(ix);
            indices.push_back(ix + 1);
            indices.push_back(ix + 3);
            indices.push_back(ix + 3);
            indices.push_back(ix + 2);
            indices.push_back(ix + 1);
            letterCount++;
            x += scaleAdvance;

        }
        y -= m_fontSize;
    }

    //m_width = xMax - xMin;
    //m_height = yMax - yMin;
    //m_topLeft = glm::vec2 (xMin, yMax);
    //m_offsetY = yMax;
    //m_bottomRight = glm::vec2 (xMax, yMin);

    Init(vertices, indices);
    //material.texId = font.getTexId();
}

void TextMesh::splitIntoLines(Font* font, const string& msg, vector<string>& lines, float scalingFactor, float mll) {
    float spaceLength = font->getGlyph(' ').advanceToNext * scalingFactor;
    vector <string> words;
    vector <float> wlenghts;
    istringstream iss(msg);
    do {
        std::string word;
        iss >> word;
        words.push_back(word);
    } while (iss);

    for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
        float wordLength = 0;
        for (size_t i = 0; i < iter->length(); i++) {
            Glyph glyph = font->getGlyph((*iter)[i]);
            wordLength += ((i == iter->length() - 1) ? glyph.width : glyph.advanceToNext) * scalingFactor;
        }
        wlenghts.push_back(wordLength);
    }

    size_t nWords = words.size();
    float currentLength = 0;
    int wordsInLine = 0;

    stringstream currentLine;
    for (size_t i = 0; i < nWords; i++) {
        float newLength = currentLength + wlenghts[i] + (wordsInLine > 0 ? spaceLength : 0);
        if (newLength <= mll) {
            if (wordsInLine == 0)
                currentLine << words[i];
            else
                currentLine << " " << words[i];
            currentLength = newLength;
            wordsInLine++;
        }
        else {
            lines.push_back(currentLine.str());
            currentLine.str("");
            currentLine.clear();
            currentLine << words[i];
            currentLength = wlenghts[i];
            wordsInLine = 1;
        }

    }

    if (currentLine.str().length() > 0)
        lines.push_back(currentLine.str());

}

void TextMesh::Setup(Shader* shader, const std::string&, int) {
    auto texLoc = shader->GetUniformLocation(TEXTURE);
    glUniform1i(texLoc, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texId);
}

glm::vec2 TextMesh::getOffset() {
    glm::vec2 offset(0.0f);
    switch (m_align) {
        case BOTTOM_LEFT:
            offset = - glm::vec2(m_bounds.min.x, m_bounds.min.y);
            break;
        case BOTTOM_RIGHT:
            offset = - glm::vec2(m_bounds.max.x, m_bounds.min.y);
            break;
        case BOTTOM:
            offset = -glm::vec2(0.5f * (m_bounds.min.x + m_bounds.max.x), m_bounds.min.y);
            break;
        case TOP_LEFT:
            offset = -glm::vec2(m_bounds.min.x, m_bounds.max.y);
            break;
        case TOP_RIGHT:
            offset = -glm::vec2(m_bounds.max.x, m_bounds.max.y);
            break;
        case TOP:
            offset = -glm::vec2(0.5f * (m_bounds.min.x + m_bounds.max.x), m_bounds.max.y);
            break;
        case CENTER:
            offset =-glm::vec2(0.5f * (m_bounds.min.x + m_bounds.max.x), 0.5f*(m_bounds.min.y + m_bounds.max.y));
            break;
    }
    return offset;
}
