#pragma once

#include <monkey/itable.h>

class PyTab : public ITab {
public:
    PyTab(pybind11::object obj);
    std::unique_ptr<ITab> operator[](const std::string&) const override;
    void foreach(std::function<void(const ITab&)> f) const override;
    void foreach(const std::string& id, std::function<void(const ITab&)> f) const override;
    void foreach(std::function<void(const std::string&, const ITab&)> f) const override;
    void foreach(const std::string& id, std::function<void(const std::string&, const ITab&)> f) const override;
    bool has(const std::string& id) const override;

private:
    pybind11::object _get(const std::string&) const;
    bool m_dict;
    int _asInt() const override;
    float _asFloat() const override;
    bool _asBool() const override;
    std::string _asString() const override;
    pybind11::function _asFunction() const override;

    // glm objects
    glm::vec2 _asVec2() const override;
    glm::vec3 _asVec3() const override;
    glm::vec4 _asVec4() const override;
    glm::mat4 _asMat4() const override;

    // shortcut for vecs
    std::vector<int> _asVecInt() const override;
    std::vector<float> _asVecFloat() const override;
    std::vector<std::string> _asVecStr() const override;

    pybind11::object m_obj;
};
