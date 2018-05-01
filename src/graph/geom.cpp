#include "graph/geom.h"
#include "graph/poly.h"
#include "graph/graph.h"

void FindPathInPoly (const Poly& poly, glm::vec2 Start, glm::vec2 End) {
    int nHoles = poly.GetHoleCount();
    int nVertices = poly.GetVertexCount();
    Graph<int, glm::vec2> g;
    int n = 0;
    for (int i = 0; i < nVertices; ++i) {
        if (poly.isVertexConcave(i)) {
            g.AddNode(n++, poly.GetVertex(i));
        }
    }

    // add hole points
    for (int h = 0; h < nHoles; ++h) {
        int nvh = poly.GetVertexCount(h+1);
        for (int j = 0; j < nvh; ++j) {
            if (!poly.isVertexConcave(j, h+1)) {
                g.AddNode(n++, poly.GetVertex(j, h+1));
            }
        }
    }

    g.AddNode(n++, Start);
    g.AddNode(n++, End);

    // now you need to set up the edges

}

bool inLineOfSight (const Poly& p, glm::vec2 start, glm::vec2 end) {
    
   	float epsilon = 0.5;
    
    // Not in LOS if any of the ends is outside the polygon
    if ( !p.isPointInside(start) || !p.isPointInside(end)) {
        return false;
    }
    
    // In LOS if it's the same start and end location
    if (glm::length(end - start) < epsilon) {
        return false;
    }
    
    // Not in LOS if any edge is intersected by the start-end line segment
    bool inSight = true;
    int n = p.GetHoleCount() + 1;
    for (int i = 0; i < n; ++i) {
        int m = p.GetVertexCount(i);
        glm::vec2 v1 = p.GetVertex(m-1, i);
        for (int j = 1; j < m; ++j) {
            glm::vec2 v2 = p.GetVertex(j);
            if (LineSegmentCross(start, end, v1, v2)) {
                
            }
            v1 = v2;
        }
    }
    
//        for (i in 0...polygon.vertices.length) {
//            var v1:Vector = polygon.vertices[i];
//            var v2:Vector = polygon.vertices[(i + 1) % polygon.vertices.length];
//            if (LineSegmentsCross(start, end, v1, v2)) {
//                //In some cases a 'snapped' endpoint is just a little over the line due to rounding errors. So a 0.5 margin is used to tackle those cases.
//                if (polygon.distanceToSegment(start.x, start.y, v1.x, v1.y, v2.x, v2.y ) &gt; 0.5 &amp;&amp; polygon.distanceToSegment(end.x, end.y, v1.x, v1.y, v2.x, v2.y ) &gt; 0.5) {
//                    return false;
//                }
//            }
//        }
    //}
        bool inside;
    // Finally the middle point in the segment determines if in LOS or not
//    var v:Vector = Vector.Add(start, end);
//    var v2:Vector = new Vector(v.x / 2, v.y / 2);
//    var inside:Bool = polygons[0].pointInside(v2);
//    for (i in 1...polygons.length) {
//        if (polygons[i].pointInside(v2, false)) {
//            inside = false;
//        }
//    }
    return inside;
}
