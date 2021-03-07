#pragma once

#include <monkey/model/basicmodel.h>
#include <monkey/math/shape.h>
//#include <monkey/mesh.h>
//#include <monkey/math/shapes/rect.h>
//#include <monkey/math/shapes/line.h>
//#include <monkey/math/shapes/poly.h>
//#include <monkey/math/shapes/polyline.h>
//#include <monkey/math/shapes/circle.h>
//#include <monkey/math/shapes/ellipse.h>
//#include <monkey/math/compound.h>
//#include <monkey/math/shapes/polytri.h>
//#include <monkey/fill.h>

// creates a model from a shape
class MeshFactory {
public:
    MeshFactory ();
    std::shared_ptr<BasicModel> createWireframe (IShape*, glm::vec4 color);
private:
    std::unordered_map<ShapeType, std::function<void(IShape*, glm::vec4, std::vector<VertexColor>&, std::vector<unsigned>&)>> m_plotters;
//    std::shared_ptr<BasicModel> drawConvexPoly(IShape*, glm::vec4);
//	std::shared_ptr<BasicModel> drawCircle(IShape*, glm::vec4);

	void drawConvexPoly (IShape*, glm::vec4, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices, bool closeLoop);
    void drawCircle (IShape*, glm::vec4, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices);
    void drawCompound (IShape*, glm::vec4, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices);
    void drawPoly (IShape*, glm::vec4, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices);

    // 3d shapes
	void drawAABB (IShape*, glm::vec4, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices);
	void drawPlane (IShape*, glm::vec4, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices);
};
//    public AcyclicVisitor,
//    public Visitor<Rect>,
//    public Visitor<Segment>,
//    //public Visitor<Polygon>,
//    //public Visitor<Poly>,
//    //public Visitor<PolyLine>,
//    //public Visitor<PolyTri>,
//    public Visitor<Circle>
//    //public Visitor<Ellipse>,
//    //public Visitor<CompoundShape>,
//{
//public:
//    //static std::shared_ptr<IMesh> CreateMesh (const Polygon& p, float z);
//    static std::shared_ptr<IMesh> CreateMesh (IShape& s, float z = 0.0f, glm::vec4 color = glm::vec4(1.0f));
//    void visit(Rect&) override;
//    void visit(Segment&) override;
//    //void visit(Polygon&) override;
//    //void visit(Poly&) override;
//    //void visit(PolyLine&) override;
//    //void visit(PolyTri&) override;
//    void visit(Circle&) override;
//    //void visit(Ellipse&) override;
//    //void visit(CompoundShape&) override;
//    //void visit(Plane3D&) override;
//    //void visit(Box3D&) override;
//
//
//private:
//    std::shared_ptr<IMesh> m_mesh;
//    glm::vec4 m_color;
//    float m_z;
//    MeshFactory(float z, glm::vec4 color) : m_color{color}, m_z{z} {}
//};
//
//class MeshFactorySolid :
//    public AcyclicVisitor,
//    public Visitor<Rect>
//    //public Visitor<Ellipse>
//    //public Visitor<Plane3D>
//{
//public:
//    static std::shared_ptr<IMesh> CreateMesh (
//        IShape& s,
//        std::shared_ptr<Fill> fill,
//        float z = 0.0f);
//    void visit(Rect&) override;
//    //void visit(Ellipse&) override;
//    //void visit(Plane3D&) override;
//
//private:
//    void addPoint (std::vector<VertexColor>& v, float x, float y);
//    std::shared_ptr<IMesh> m_mesh;
//    std::shared_ptr<Fill> m_fill;
//    float m_z;
//    MeshFactorySolid(float z, std::shared_ptr<Fill> fill) : m_fill{fill}, m_z{z} {}
//};
//
//
//class MeshFactoryTextured :
//    public AcyclicVisitor
//    //public Visitor<Poly>
//{
//public:
//    // you can provide colors (r, g, b, a) as functions of x and y
//    // each channel (red, green, blue, alpha) is a linear func ax + by + c
//    static std::shared_ptr<IMesh> CreateMesh (
//        IShape& s,
//        const std::string& texture,
//        float x0,
//        float y0,
//        float repx,
//        float repy,
//        float slantx,
//        float slanty,
//        std::shared_ptr<Fill> fill);
//    //void visit(Poly&) override;
//private:
//    MeshFactoryTextured(const std::string& texture, float x0, float y0, float repx, float repy, float slantx, float slanty, std::shared_ptr<Fill>);
//    float m_x0;
//    float m_y0;
//    float m_rx;
//    float m_ry;
//    float m_a;
//    float m_b;
//    std::shared_ptr<Fill> m_fill;
//    //glm::vec3 m_red;
//    //glm::vec3 m_green;
//    //glm::vec3 m_blue;
//    //glm::vec3 m_alpha;
//    std::string m_texId;
//    std::shared_ptr<IMesh> m_mesh;
//
//};
