#pragma once

#include <monkey/mesh.h>
#include <monkey/math/rect.h>
#include <monkey/math/box.h>
#include <monkey/math/line.h>
#include <monkey/math/poly.h>
#include <monkey/math/polyline.h>
#include <monkey/math/circle.h>
#include <monkey/math/ellipse.h>
#include <monkey/math/compound.h>
#include <memory>

class Contour :
    public AcyclicVisitor,
    public Visitor<Rect>,
    public Visitor<Line>,
    public Visitor<Box>
//    public Visitor<Polygon>,
//    public Visitor<Poly>,
//    public Visitor<PolyLine>,
//    public Visitor<Circle>,
//    public Visitor<Ellipse>,
//    public Visitor<CompoundShape>
{
public:
    void visit(Rect&) override;
    void visit(Line&) override;
    void visit(Box&) override;
    static std::vector<glm::vec3> CreateContour (Shape*);
private:
    std::vector<glm::vec3> m_result;
    Contour () {}
};

