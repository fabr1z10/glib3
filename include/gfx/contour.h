#pragma once

#include <gfx/mesh.h>
#include <gfx/math/rect.h>
#include <gfx/math/line.h>
#include <gfx/math/poly.h>
#include <gfx/math/polyline.h>
#include <gfx/math/circle.h>
#include <gfx/math/ellipse.h>
#include <gfx/math/compound.h>
#include <memory>

class Contour :
    public AcyclicVisitor,
    public Visitor<Rect>,
    public Visitor<Line>
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
    static std::vector<glm::vec3> CreateContour (Shape*);
private:
    std::vector<glm::vec3> m_result;
    Contour () {}
};

