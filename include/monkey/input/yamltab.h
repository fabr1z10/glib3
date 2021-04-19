#pragma once

#include <monkey/itable.h>
#include <monkey/yaml.h>

class YAMLTab : public ITab {
public:
    YAMLTab(YAML::Node node) : m_node(node) {}
    std::unique_ptr<ITab> operator[](const std::string&) const override;

    void foreach(std::function<void(const ITab&)> f) const override;
    void foreach(const std::string& id, std::function<void(const ITab&)> f) const override;

    void foreach(std::function<void(const std::string&, const ITab&)> f) const override;
    void foreach(const std::string& id, std::function<void(const std::string&, const ITab&)> f) const override;

    bool has(const std::string& id) const override;
	std::shared_ptr<ITab> clone(const ITab&) const override;

private:
    int _asInt() const override;
    float _asFloat() const override;
    bool _asBool() const override;

    std::string _asString() const override;
    pybind11::function _asFunction() const override {throw;}
    pybind11::object _asPyObject() const override {throw;}

    // glm objects
    glm::vec2 _asVec2() const override;
    glm::vec3 _asVec3() const override;
    glm::vec4 _asVec4() const override;
    glm::mat4 _asMat4() const override;

    std::vector<int> _asVecInt() const override;
    std::vector<float> _asVecFloat() const override;
    std::vector<std::string> _asVecStr() const override;

    YAML::Node m_node;
};
