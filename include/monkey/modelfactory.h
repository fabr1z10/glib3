#pragma once

#include <monkey/model/spritemodel.h>
#include <monkey/compositemodel.h>
#include <monkey/visitor.h>

// generates an entity from a imodel (can be simple mesh, or a complex model with  multiple meshes)

class ModelFactory : 
    public AcyclicVisitor,
    public Visitor<SpriteModel>,
    public Visitor<CompositeModel>
{
public:
    static std::shared_ptr<Entity> CreateMesh (IModel& s);
    void visit(SpriteModel&) override;
    void visit(CompositeModel&) override;
};
