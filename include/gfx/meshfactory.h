#pragma once

#include <gfx/mesh.h>
#include <graph/rect.h>
#include <graph/line.h>
#include <graph/poly.h>
#include <graph/polyline.h>
#include <graph/circle.h>
#include <graph/ellipse.h>
#include <graph/compound.h>
#include <memory>


class MeshFactory :
    public AcyclicVisitor,
    public Visitor<Rect>,
    public Visitor<Line>,
    public Visitor<Polygon>,
    public Visitor<Poly>,
    public Visitor<PolyLine>,
    public Visitor<Circle>,
    public Visitor<Ellipse>,
    public Visitor<CompoundShape>
{
public:
    static std::shared_ptr<IMesh> CreateLineMesh (glm::vec2 A, glm::vec2 B, glm::vec4 color, float z= 0.0f);
    static std::shared_ptr<IMesh> CreateLineMesh (glm::vec2 A, glm::vec2 B);
    static std::shared_ptr<IMesh> CreateBoxMesh (float width, float height, glm::vec4 color);
    static std::shared_ptr<IMesh> CreateMesh (const Polygon& p, float z);
    static std::shared_ptr<IMesh> CreateMesh (Shape& s, float z = 0.0f, glm::vec4 color = glm::vec4(1.0f));
    void visit(Rect&) override;
    void visit(Line&) override;
    void visit(Polygon&) override;
    void visit(Poly&) override;
    void visit(PolyLine&) override;
    void visit(Circle&) override;
    void visit(Ellipse&) override;
    void visit(CompoundShape&) override;
private:
    std::shared_ptr<IMesh> m_mesh;
    glm::vec4 m_color;
    float m_z;
    MeshFactory(float z, glm::vec4 color) : m_color{color}, m_z{z} {}
};

class MeshFactorySolid :
        public AcyclicVisitor,
        public Visitor<Rect>,
        public Visitor<Ellipse>
{
public:
    static std::shared_ptr<IMesh> CreateMesh (Shape& s, float z = 0.0f, glm::vec4 color = glm::vec4(1.0f));
    void visit(Rect&) override;
    void visit(Ellipse&) override;
private:
    std::shared_ptr<IMesh> m_mesh;
    glm::vec4 m_color;
    float m_z;
    MeshFactorySolid(float z, glm::vec4 color) : m_color{color}, m_z{z} {}
};
