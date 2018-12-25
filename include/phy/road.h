#pragma once

#include <unordered_map>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <gfx/hashpair.h>

class RoadArc {
public:
    RoadArc(double a, double b, double c, double d, double e, double f, double g, double h) :
    a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h){}
    glm::vec3 operator()(double) ;
    glm::vec3 tangent(double);
    float GetArcLength() const;
private:
    double a,b,c,d,e,f,g,h;

};


class Road {
public:
    struct Edge {
        int id0;
        int id1;
        float angle0;
        float angle1;
        float width0;
        float width1;
    };
    struct EdgeParams {

    };
    Road(std::unordered_map<int, glm::vec3> &, std::vector<Edge> &edges);
    std::unordered_map< std::pair<int, int>, RoadArc>& GetArcs() ;
private:
    struct VertexInfo {
        glm::vec3 P;
        float width;
        std::map<float, int> conn;
    };
    std::unordered_map <int, VertexInfo> m_connections;
    std::unordered_map< std::pair<int, int>, RoadArc> m_edgeParams;
};

inline std::unordered_map< std::pair<int, int>, RoadArc>& Road::GetArcs() {
    return m_edgeParams;
};
