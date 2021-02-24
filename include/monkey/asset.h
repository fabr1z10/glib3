#pragma once

#include <monkey/object.h>
#include <monkey/yaml.h>


class Asset : public Object{
public:
    Asset (const YamlWrapper&);

};