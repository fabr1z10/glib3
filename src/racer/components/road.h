#pragma once

#include <monkey/components/hotspot.h>
#include <monkey/math/funcs.h>
#include <monkey/math/geom.h>
#include <monkey/components/scripthotspot.h>
#include <monkey/math/algo/shortestpath.h>

class Scheduler;

class Road : public Component {
public:
    //WalkArea (std::shared_ptr<IShape> shape, int priority);
    Road(const ITab&);
    void Update(double) override;
    void Start() override;
    using ParentClass = Road;
    std::type_index GetType() override;

};



inline std::type_index Road::GetType() {
    return std::type_index(typeid(Road));
}

