#pragma once

#include <string>

class SceneFactory;

class DynamicLoader {
public:

    static void load(const std::string& file, SceneFactory*);

};