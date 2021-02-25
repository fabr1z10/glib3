#pragma once

#include <string>
#include "yaml-cpp/yaml.h"
#include <monkey/error.h>
#include "glm/glm.hpp"

class YamlWrapper {
public:

    template <typename T>
    static T as(const YAML::Node& node, const std::string& key) {
    	if (node["Key"])
    		return YamlWrapper::cast<T>(node[key]);
    	else
    		throw;
    }

    template <typename T>
	static T as(const YAML::Node& node, const std::string& key, T defaultValue) {
		if (node["Key"])
			return YamlWrapper::cast<T>(node[key]);
		else
			return defaultValue;

	}
private:
	template <typename T>
	static T cast(const YAML::Node& node) {
		throw;
	}

};

template <>
inline glm::vec2 YamlWrapper::cast(const YAML::Node& node) {
	auto v = node.as<std::vector<float>>();
	return glm::vec2(v[0], v[1]);
}

template <>
inline glm::vec3 YamlWrapper::cast(const YAML::Node& node) {
	auto v = node.as<std::vector<float>>();
	return glm::vec3(v[0], v[1], v[2]);
}

template <>
inline glm::vec4 YamlWrapper::cast(const YAML::Node& node) {
	auto v = node.as<std::vector<float>>();
	return glm::vec4(v[0], v[1], v[2], v[3]);
}
