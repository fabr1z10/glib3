#pragma once

#include <monkey/factories.h>
#include <monkey/entitywrapper.h>

class SceneFactory;

class Extension {
public:
    void extend(SceneFactory*);
    void extendLua();
};

