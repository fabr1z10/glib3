#pragma once

#include <monkey/assets/model.h>
#include <monkey/spritemesh.h>
#include <monkey/components/renderer.h>
#include <monkey/yaml.h>

class SpriteRenderer;


struct FrameInfo {
    float time;
    int offset;
    int count;
};

struct AnimationInfo {
    bool loop;
    int loopFrame;
    std::vector<FrameInfo> frames;
};


class __attribute__ ((visibility ("default"))) SpriteModel : public Model {
public:
    explicit SpriteModel (const ITab&);
    std::string getDefaultAnimation() const ;
    std::shared_ptr<Renderer> makeRenderer(std::shared_ptr<Model>, const ITab& t = PyTab()) override;
    AnimationInfo* getAnimationInfo(const std::string&);
protected:
    std::string m_defaultAnimation;
    std::unordered_map<std::string, AnimationInfo> m_animInfos;
};

inline std::string SpriteModel::getDefaultAnimation() const {
    return m_defaultAnimation;
}


