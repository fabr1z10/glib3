#pragma once

#include <string>
#include "yaml-cpp/yaml.h"
#include <monkey/error.h>

class YamlWrapper {
public:
    YamlWrapper (const YAML::Node& node) : m_node(node) {}

    template <typename T>
    T as(YAML::Node node) const {
        return node.as<T>();
    }

    template <typename T>
    T get(const std::string& key) const {
        if (m_node[key]) {
            return as<T>(m_node[key]);
        } else {
            GLIB_FAIL("Cannot find key " << key);
        }
    }

    template <typename T>
    T get(const std::string& key, T defaultValue) const {
        if (m_node[key]) {
            return as<T>(m_node[key]);
        } else {
            return defaultValue;
        }
    }
private:
    const YAML::Node& m_node;
};