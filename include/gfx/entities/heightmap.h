#pragma once

#include <gfx/entity.h>
#include <gfx/keyboard.h>
#include <gfx/engine.h>
#include <gfx/collisionengine.h>

class HeightMap : public Entity
{
public:
    HeightMap (const std::string& file, const std::string& texture, float width, float height, float zMin, float zMax);

    float getHeight (float x, float y);
    glm::vec3 getNormal (float x, float y);
private:
    float m_width;
    float m_height;
    float m_zMin, m_zMax;
    std::string m_file;
    std::vector<std::vector<float>> m_heightInfo;
};