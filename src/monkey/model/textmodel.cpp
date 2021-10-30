#include <monkey/model/textmodel.h>
#include <string>
#include <locale>
#include <codecvt>

void TextModel::updateText() {
    m_meshes.clear();

    auto mesh = std::make_shared<Mesh<VertexText>>();

    std::vector <VertexText> vertices;
    std::vector <unsigned int> indices;
    std::vector <std::string> lines;

    float scalingFactor = size / m_font->size(); //font.getMaxHeight();
    if (maxLineWidth == 0.0f)
        lines.push_back(msg);
    else
        splitIntoLines(m_font, m_text, lines, scalingFactor, maxLineWidth);

    // now loop through each line
    float y = -size;
    unsigned int letterCount = 0;

    m_bounds.min = glm::vec3(std::numeric_limits<float>::infinity());
    m_bounds.max = glm::vec3(-std::numeric_limits<float>::infinity());
    m_lines = lines.size();

    // loop through lines
    for (size_t n = 0; n < lines.size(); n++) {
        //std::u32string sss(lines[n].c_str());
        //auto sss = std::wstring_convert<std::codecvt_utf8<char32_t >>().from_bytes(lines[n].c_str());

        auto sss = std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t >().from_bytes(lines[n].c_str());
        //std::string sss = lines[n];
        float x = 0.0f;					// current cursor position
        for (const auto& w : sss) {

            //char c = lines[n][i];
            //bool isLastCharacter = i == lines[n].length()-1;
            Glyph glyph = font->getGlyph(w);

            float scaledWidth = glyph.width * scalingFactor;
            float scaledHeight = glyph.height * scalingFactor;
            float scaledYOffset = glyph.heightOffset * scalingFactor;
            float scaleAdvance = glyph.advanceToNext * scalingFactor;

            float yTop = y + scaledYOffset;
            float yBottom = yTop - scaledHeight;
            float lastX = x + scaledWidth;


            vertices.emplace_back(VertexText(x, yTop, glyph.tx, glyph.ty, 1.0f, 1.0f, 1.0f, 1.0f));
            vertices.emplace_back(VertexText(lastX, yTop, glyph.tx + glyph.tw, glyph.ty, 1.0f, 1.0f, 1.0f, 1.0f));
            vertices.emplace_back(VertexText(lastX, yBottom, glyph.tx + glyph.tw, glyph.ty + glyph.th, 1.0f, 1.0f, 1.0f, 1.0f));
            vertices.emplace_back(VertexText(x, yBottom, glyph.tx, glyph.ty + glyph.th, 1.0f, 1.0f, 1.0f, 1.0f));

            m_bounds.min.x = std::min(m_bounds.min.x, x);
            m_bounds.max.x = std::max(m_bounds.max.x, lastX);
            m_bounds.min.y = std::min(m_bounds.min.y, yBottom);
            m_bounds.max.y = std::max(m_bounds.max.y, yTop);

            unsigned int ix = letterCount * 4;
            indices.push_back(ix);
            indices.push_back(ix + 1);
            indices.push_back(ix + 3);
            indices.push_back(ix + 3);
            indices.push_back(ix + 2);
            indices.push_back(ix + 1);
            letterCount++;
            x += scaleAdvance;

        }
        y -= size;
    }
    //glm::vec2 offset = getOffset();
    //m_localTransform = glm::translate(glm::mat4(1.0f), glm::vec3(offset.x, offset.y, 0.0f));
    //m_width = xMax - xMin;
    //m_height = yMax - yMin;
    //m_topLeft = glm::vec2 (xMin, yMax);
    //m_offsetY = yMax;
    //m_bottomRight = glm::vec2 (xMax, yMin);

    mesh->Init(vertices, indices);
    addMesh(mesh);
    //material.texId = font.getTexId();


}

TextModel::TextModel(Font* font,
    const std::string& msg,
    float size,
    TextAlignment align,
    float maxLineWidth) : m_font(font), m_text(msg), m_size(size)
{
    updateText();
}


void TextModel::splitIntoLines(const std::string& msg, std::vector<std::string>& lines,
                               float scalingFactor, float mll) {
    float spaceLength = m_font->getGlyph(' ').advanceToNext * scalingFactor;
    std::vector<std::string> words;
    std::vector<float> wlenghts;

    std::string current = "";
    std::unordered_set<int> newLines;
    for (auto& c : msg) {
        if (c == ' ' || c == '\n') {
            if (!current.empty()) {
                words.push_back(current);
            }
            current = "";
            if (c == '\n') {
                newLines.insert(words.size()-1);
            }
        } else {
            current.push_back(c);
        }
    }
    if (!current.empty()) {
        words.push_back(current);
    }

    for (const auto& word : words) {

        float wordLength = 0;
        int charcount = 0;
        auto sss = std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t >().from_bytes(word.c_str());
        for (const auto& ch : sss) {
            Glyph glyph = m_font->getGlyph(ch);
            wordLength += ((charcount == word.size()-1) ? glyph.width : glyph.advanceToNext) * scalingFactor;
            charcount += 1;
        }
        wlenghts.push_back(wordLength);
    }

    size_t nWords = words.size();
    float currentLength = 0;
    int wordsInLine = 0;

    std::stringstream currentLine;
    for (size_t i = 0; i < nWords; i++) {
        float newLength = currentLength + wlenghts[i] + (wordsInLine > 0 ? spaceLength : 0);
        bool added = false;
        if (newLength <= mll) {
            if (wordsInLine == 0)
                currentLine << words[i];
            else
                currentLine << " " << words[i];
            currentLength = newLength;
            wordsInLine++;
            added = true;
        }

        if (newLength > mll || (newLines.count(i) > 0)) {
            lines.push_back(currentLine.str());
            currentLine.str("");
            currentLine.clear();
            wordsInLine = 0;
            if (!added) {
                currentLine << words[i];
                currentLength = wlenghts[i];
                wordsInLine = 1;
            }
        }

    }

    if (currentLine.str().length() > 0)
        lines.push_back(currentLine.str());

}


std::string TextModel::getText () const {
    return m_text;

}

void TextModel::setText(const std::string&) {
    m_text = text;
    updateText();

}

Bounds TextModel::getBounds() const {
	return m_textMesh->GetBounds();
}

int TextModel::GetNumberOfLines() const {
    return m_textMesh->getNumberOfLines();
}

glm::vec2 TextModel::GetOffset() const {
    return m_textMesh->getOffset();
}