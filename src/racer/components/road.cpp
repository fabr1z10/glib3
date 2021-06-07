#include "road.h"
#include <GLFW/glfw3.h>
#include <monkey/scheduler.h>

#include <monkey/engine.h>
#include <iostream>
#include <monkey/dynamicmesh.h>
#include <monkey/math/algo/closest.h>
#include <monkey/math/algo/shortestpath.h>
#include <monkey/properties.h>
#include <monkey/meshfactory.h>
#include <monkey/components/basicrenderer.h>

//WalkArea::WalkArea(std::shared_ptr<IShape> shape, int priority) : ScriptHotSpot(shape, priority) {}

Road::Road(const ITab& t) : Component(t) {
}


void Road::Start() {
    // init mesh
    std::cerr << "qu]m";

    auto mesh = std::make_shared<DynamicMesh<VertexColor>>();
}

void Road::Update(double) {
    // update mesh vertices
}

