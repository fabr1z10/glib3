#include <monkey/itable.h>

int PyTab::_getInt() const {
    return m_obj.cast<int>();
}

float PyTab::_getFloat() const {
    return m_obj.cast<float>();
}

std::string PyTab::_getString() const {
    return m_obj.cast<std::string>();
}