#include <monkey/input/pytab.h>
#include <glm/gtc/type_ptr.hpp>

PyTab::PyTab(pybind11::object obj) : m_obj(obj) {
    //std::cerr << obj.get_type() << "\n";
    m_dict = (pybind11::type::of(obj) == pybind11::type::of(pybind11::dict()));

}

pybind11::object PyTab::_get(const std::string & key) const {
    if (m_dict)
        return m_obj[key.c_str()];
    return m_obj.attr(key.c_str());
}

int PyTab::_asInt() const {
    return m_obj.cast<int>();
}

float PyTab::_asFloat() const {
    return m_obj.cast<float>();
}

bool PyTab::_asBool() const {
    return m_obj.cast<bool>();
}

std::string PyTab::_asString() const {
    return m_obj.cast<std::string>();
}

pybind11::function PyTab::_asFunction() const {
    return m_obj.cast<pybind11::function>();
}

pybind11::object PyTab::_asPyObject() const {
    return m_obj;
}

glm::vec2 PyTab::_asVec2() const {
    auto vec = m_obj.cast<std::vector<float>>();
    return glm::vec2(vec[0], vec[1]);
}

glm::vec3 PyTab::_asVec3() const {
    auto vec = m_obj.cast<std::vector<float>>();
    return glm::vec3(vec[0], vec[1], vec[2]);
}

glm::vec4 PyTab::_asVec4() const {
    auto vec = m_obj.cast<std::vector<float>>();
    return glm::vec4(vec[0], vec[1], vec[2], vec[3]);
}

glm::mat4 PyTab::_asMat4() const {
    auto vec = m_obj.cast<std::vector<float>>();
    return glm::make_mat4(&vec[0]);
}

std::vector<int> PyTab::_asVecInt() const {
    return m_obj.cast<std::vector<int>>();
}

std::vector<float> PyTab::_asVecFloat() const {
    return m_obj.cast<std::vector<float>>();
}

std::vector<std::string> PyTab::_asVecStr() const {
    return m_obj.cast<std::vector<std::string>>();
}

std::unique_ptr<ITab> PyTab::operator[] (const std::string & key) const {
    return std::make_unique<PyTab>(_get(key));
}

bool PyTab::has(const std::string &id) const {
    try {
        auto obj = _get(id);
        return !obj.is_none();
    } catch (...) {
        return false;
    }
}

void PyTab::foreach(std::function<void(const ITab &)> f) const {
    for (auto &i : m_obj) {
        PyTab o(i.cast<pybind11::object>());
        f(o);
    }

}

void PyTab::foreach(const std::string &id, std::function<void(const ITab &)> f) const {
    try {
        auto l = _get(id);
        auto list = l.cast<pybind11::list>();
        for (auto &i : list) {
            PyTab o(i.cast<pybind11::object>());
            f(o);
        }
    } catch (Error& err) {
        std::cerr << err.what() ;
        exit(1);

    }
}

void PyTab::foreach(std::function<void(const std::string &, const ITab &)> f) const {
    auto dict = m_obj.cast<pybind11::dict>();
    for (const auto& item : dict) {
        f(item.first.cast<std::string>(), PyTab(item.second.cast<pybind11::object>()));
    }
}

void PyTab::foreach(const std::string &id, std::function<void(const std::string &, const ITab &)> f) const {
    try {
        auto dict = _get(id).cast<pybind11::dict>();
        for (const auto & item : dict) {
            f(item.first.cast<std::string>(), PyTab(item.second.cast<pybind11::object>()));
        }
    } catch (...) {

    }
}