#include "gfx/mesh.h"

struct Quad {
    float x, y, z;
    float width, height;
    float anchorx, anchory;
};

struct Frame {
    std::vector<Quad> quads;
    float time;
};

struct Animation {
    std::string name;
    bool loop;
    std::vector<Frame> frames;
};


// An animation is a vector of frame. A frame is a vector of quads. A quad is defined by
// the texture position and size and the anchor point. A sprite mesh is a collection of named animations.
class SpriteMesh : public Mesh<Vertex3D> {
public:
    SpriteMesh (float ppu, const std::string& filename, std::vector<Animation>& data);
    void Setup(Shader*, const std::string&, int) override;
private:
    //std::unordered_map<std::string, std::vector<AnimInfo>> m_info;
    GLuint m_texId;
};



