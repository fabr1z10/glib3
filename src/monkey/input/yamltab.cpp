#include <monkey/input/yamltab.h>

int YAMLTab::_asInt() const {
    return m_node.as<int>();
}

float YAMLTab::_asFloat() const {
    return m_node.as<float>();
}

bool YAMLTab::_asBool() const {
    return m_node.as<bool>();
}

std::string YAMLTab::_asString() const {
    return m_node.as<std::string>();
}

glm::vec2 YAMLTab::_asVec2() const {
    throw;
}

glm::vec3 YAMLTab::_asVec3() const {

}

glm::vec4 YAMLTab::_asVec4() const {

}

glm::mat4 YAMLTab::_asMat4() const {
    
}

std::unique_ptr<ITab> YAMLTab::operator[] (const std::string & key) const {
    auto node = m_node[key.c_str()];
    if (node) {
        return std::make_unique<YAMLTab>(m_node[key.c_str()]);
    }
    return nullptr;
}

void YAMLTab::foreach(std::function<void(const ITab &)> f) const {
    for (auto &i : m_node) {
        f(YAMLTab(i));
    }
}

void YAMLTab::foreach(const std::string &id, std::function<void(const ITab &)> f) const {
    auto l = m_node[id.c_str()];
    if (l) {
        auto list = l.as<std::vector<YAML::Node>>();
        for (auto &i : list) {
            f(YAMLTab(i));
        }
    }
}

void YAMLTab::foreach(std::function<void(const std::string &, const ITab &)> f) const {
    for (const auto& node : m_node) {
        auto key = node.first.as<std::string>();
        f(key, YAMLTab(node.second));
    }
}

void YAMLTab::foreach(const std::string &id, std::function<void(const std::string &, const ITab &)> f) const {
    auto l = m_node[id.c_str()];
    if (l) {
        for (const auto &node : l) {
            auto key = node.first.as<std::string>();
            f(key, YAMLTab(node.second));
        }
    }
}

bool YAMLTab::has(const std::string &id) const {
    return m_node[id];
}

std::vector<int> YAMLTab::_asVecInt() const {
    return m_node.as<std::vector<int>>();
}

std::vector<float> YAMLTab::_asVecFloat() const {
    return m_node.as<std::vector<float>>();
}

std::vector<std::string> YAMLTab::_asVecStr() const {
    return m_node.as<std::vector<std::string>>();
}