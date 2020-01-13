//#include <phy/road.h>
//#include <lapacke.h>
//#include <iostream>
//#include <monkey/math/integral.h>
//
//glm::vec3 RoadArc::operator() (double t) {
//    return glm::vec3( a*t*t + b*t + c, d*t*t+ e*t+f, g*t+h);
//
//};
//
//// get the tangent vector to the curve
//glm::vec3 RoadArc::tangent(double t) {
//    return glm::normalize(glm::vec3 (2*a*t + b, 2*d*t + e, g));
//}
//float RoadArc::GetArcLength() const {
//
//    return Integral::IntegrateTrapezoidal(0.0, 1.0, [&] (double t) { return sqrt ( (2*a*t+b) * (2*a*t+b) + (2*d*t+e)*(2*d*t+e) + g*g); }, 10);
//
//}
//
//Road::Road(std::unordered_map<int, glm::vec3> & points, std::vector<Edge> &edges){
//    for (auto& p: points) {
//        VertexInfo info;
//        info.P = p.second;
//        m_connections[p.first] = info;
//
//    }
//    // the road is made of connecting edges
//    // each edge is a quadratic 2D function
//    // t -> (at^2 + bt + c, dt^2 + et + f, gt + h)
//    // the third component is the height function
//    // we want to have:
//    // P(0) = P0 --> (c, f, h) = (P0.x, P0.y, P0.height)
//    // P(1) = P1 --> (a+b+c, d+e+f, g+h) = (P1.x, P1.y, P1.height)
//    // Next, we know the angles
//    // the angle formed by the road with the x-axis is, in general
//    // arctan ( 2at+b / 2dt + e), if 2dt+e is not zero. If it's zero, then
//    // the angle is 90 or 180, depending pn whether d>0.
//    for (auto& e : edges) {
//        glm::vec3 P0 = m_connections.at(e.id0).P;
//        glm::vec3 P1 = m_connections.at(e.id1).P;
//        float h = P0.z;
//        float g = P1.z - P0.z;
//        if (e.angle1 != e.angle0) {
//            double c = P0.x;
//            double f = P0.y;
//            bool vertical0 = (e.angle0 == 90.0f);
//            bool vertical1 = (e.angle1 == 90.0f);
//            double k0 = vertical0 ? 1.0 : tan(e.angle0);
//            double k1 = vertical1 ? 1.0 : tan(e.angle1);
//            double a23 = vertical1 ? 0.0 : -2.0;
//            double ex0 = vertical0 ? 0.0 : -1.0;
//            double ex1 = vertical1 ? 0.0 : -1.0;
//            //double a12 = k;
//            double a[16] = {
//                    1.0, 0.0, 0.0, 2.0 * k1,
//                    1.0, 0.0, k0, k1,
//                    0.0, 1.0, 0.0, a23,
//                    0.0, 1.0, ex0, ex1
//            };
//            double b[4] = {
//                    P1.x - P0.x, P1.y - P0.y, 0.0, 0.0
//            };
//            int ipiv[4];
//            int info = LAPACKE_dgesv(LAPACK_COL_MAJOR, 4, 1, a, 4, ipiv, b, 4);
//            m_edgeParams.insert(std::make_pair(
//                    std::make_pair(e.id0, e.id1), RoadArc(b[0], b[1], c, b[2], b[3], f,g,h)));
//        } else {
//            m_edgeParams.insert(std::make_pair(
//                    std::make_pair(e.id0, e.id1), RoadArc(0.0, (P1.x - P0.x), P0.x, 0.0, (P1.y - P0.y), P0.y,g,h)));
//        }
//
//    }
//}
