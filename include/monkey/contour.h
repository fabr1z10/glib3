#pragma once

#include <monkey/mesh.h>
#include <monkey/math/shapes/rect.h>
//#include <monkey/math/shapes/box3d.h>
#include <monkey/math/shapes/line.h>
#include <monkey/math/shapes/poly.h>
#include <monkey/math/shapes/polyline.h>
#include <monkey/math/shapes/circle.h>
#include <monkey/math/shapes/ellipse.h>
#include <monkey/math/compound.h>
#include <memory>

class Contour :
    public AcyclicVisitor,
    public Visitor<Rect>,
    public Visitor<Segment>
    //public Visitor<Box3D>
//    public Visitor<Polygon>,
//    public Visitor<Poly>,
//    public Visitor<PolyLine>,
//    public Visitor<Circle>,
//    public Visitor<Ellipse>,
//    public Visitor<CompoundShape>
{
public:
    void visit(Rect&) override;
    void visit(Segment&) override;
    //void visit(Box3D&) override;
    static std::vector<glm::vec3> CreateContour (IShape*);
private:
    std::vector<glm::vec3> m_result;
    Contour () {}
};

