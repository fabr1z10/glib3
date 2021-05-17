#include <monkey/itable.h>

template<> int ITab::as() const { return _asInt(); }
template<> float ITab::as() const { return _asFloat(); }
template<> bool ITab::as() const { return _asBool(); }
template<> std::string ITab::as() const { return _asString(); }

template<> glm::ivec2 ITab::as() const { return _asIVec2(); }
template<> glm::ivec3 ITab::as() const { return _asIVec3(); }
template<> glm::ivec4 ITab::as() const { return _asIVec4(); }
template<> glm::vec2 ITab::as() const { return _asVec2(); }
template<> glm::vec3 ITab::as() const { return _asVec3(); }
template<> glm::vec4 ITab::as() const { return _asVec4(); }
template<> glm::mat4 ITab::as() const { return _asMat4(); }
//template<> pybind11::function ITab::as() const { return _asFunction(); }

template<> std::vector<int> ITab::as() const { return _asVecInt(); }
template<> std::vector<float> ITab::as() const { return _asVecFloat(); }
template<> std::vector<std::string> ITab::as() const { return _asVecStr(); }

