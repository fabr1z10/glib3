 #include <monkey/funcs.h>


 float PatchwiseLinear2D::operator() (float x, float y) {
    int i{0};
    for (auto& d : m_domains) {
        if (!(x < d[0] || x > d[1] || y < d[2] || y > d[3])) {
            return m_functions[i](m_varX[i] ? x : y);
        }
        // found the right patch
        ++i;
    }
 }


 void PatchwiseLinear2D::AddFunction (glm::vec4 domain , bool isX, float value0, float value1) {
     m_domains.push_back(domain);
     m_varX.push_back(isX);
     float p0 = isX ? domain[0] : domain[2];
     float p1 = isX ? domain[1] : domain[3];
     m_functions.push_back(LinearFunction(p0,value0,p1,value1));
 }