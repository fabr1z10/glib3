#pragma once

#include <monkey/yaml.h>
#include <monkey/object.h>

// create a mesh with dynamic joint ids
std::shared_ptr<Object> makeDynamicSkeletalMesh(const YAML::Node& node, const YAML::Node& args);
