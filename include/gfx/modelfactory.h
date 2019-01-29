#pragma once

#include <gfx/simplemodel.h>
#include <gfx/compositemodel.h>
#include <gfx/visitor.h>

// generates an entity from a imodel (can be simple mesh, or a complex model with  multiple meshes)

class ModelFactory : 
    public AcyclicVisitor,
    public Visitor<SimpleModel>,
    public Visitor<CompositeModel>
{
public:
    static std::shared_ptr<Entity> CreateMesh (IModel& s);
    void visit(SimpleModel&) override;
    void visit(CompositeModel&) override;
};
