#pragma once

#include <monkey/mesh.h>
#include <monkey/math/rect.h>
#include <monkey/math/line.h>
#include <monkey/math/poly.h>
#include <monkey/math/polyline.h>
#include <monkey/math/circle.h>
#include <monkey/math/ellipse.h>
#include <monkey/math/compound.h>
#include <monkey/math/plane3d.h>
#include <monkey/math/box.h>
#include <monkey/fill.h>
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
    public Visitor<CompoundShape>,
    public Visitor<Plane3D>,
    public Visitor<Box>
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
    void visit(Plane3D&) override;
    void visit(Box&) override;


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
    //public Visitor<Plane3D>
{
public:
    static std::shared_ptr<IMesh> CreateMesh (
        Shape& s,
        std::shared_ptr<Fill> fill,
        float z = 0.0f);
    void visit(Rect&) override;
    void visit(Ellipse&) override;
    //void visit(Plane3D&) override;

private:
    void addPoint (std::vector<VertexColor>& v, float x, float y);
    std::shared_ptr<IMesh> m_mesh;
    std::shared_ptr<Fill> m_fill;
    float m_z;
    MeshFactorySolid(float z, std::shared_ptr<Fill> fill) : m_fill{fill}, m_z{z} {}
};


class MeshFactoryTextured :
    public AcyclicVisitor,
    public Visitor<Poly>
{
public:
    // you can provide colors (r, g, b, a) as functions of x and y
    // each channel (red, green, blue, alpha) is a linear func ax + by + c
    static std::shared_ptr<IMesh> CreateMesh (
        Shape& s,
        const std::string& texture,
        float x0,
        float y0,
        float repx,
        float repy,
        float slantx,
        float slanty,
        std::shared_ptr<Fill> fill);
    void visit(Poly&) override;
private:
    MeshFactoryTextured(const std::string& texture, float x0, float y0, float repx, float repy, float slantx, float slanty, std::shared_ptr<Fill>);
    float m_x0;
    float m_y0;
    float m_rx;
    float m_ry;
    float m_a;
    float m_b;
    std::shared_ptr<Fill> m_fill;
    //glm::vec3 m_red;
    //glm::vec3 m_green;
    //glm::vec3 m_blue;
    //glm::vec3 m_alpha;
    std::string m_texId;
    std::shared_ptr<IMesh> m_mesh;

};