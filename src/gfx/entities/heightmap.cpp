#include <gfx/entities/heightmap.h>
#define cimg_use_jpeg
#define cimg_use_png
#define cimg_display 0
#include <gfx/CImg.h>
#include <gfx/assetman.h>
#include <gfx/engine.h>
#include <gfx/quadmesh.h>
#include <gfx/components/renderer.h>

using namespace cimg_library;

HeightMap::HeightMap(const std::string &file, const std::string& texture, float width, float height, float zMin, float zMax) : Entity(), m_file(file),
m_width(width), m_height(height), m_zMin(zMin), m_zMax(zMax) {
    std::string f =  Engine::get().GetAssetManager().GetDirectory() + m_file;
    CImg<unsigned char> data (f.c_str());
    int w = data.width();
    int h = data.height();
    for (int j = 0; j < w; ++j) {
        std::vector <float> col;
        for (int i = h-1; i >= 0; i--) {
            unsigned char ciao = *(data.data(j, i, 0, 0));
            float z = m_zMin + ((255.0f - ciao) / 255.0f) * (m_zMax - m_zMin);
            col.push_back(z);
        }
        m_heightInfo.push_back(col);
    }

    auto mesh = std::make_shared<TexturedMesh<Vertex3DN>>(TEXTURE_SHADER_LIGHT, GL_TRIANGLES, texture);
    std::vector<Vertex3DN> vertices;
    std::vector<unsigned int> indices;
    int k = 0;
    for (int i = 0; i < h-1; ++i) {
        for (int j = 0; j < w-1; ++j) {

            // for each point draw two triangles, which represent the quad
            // having the current point as bottom left corner.
            float hbl = m_heightInfo[j][i];
            float hbr = m_heightInfo[j+1][i];
            float htl = m_heightInfo[j][i+1];
            float htr = m_heightInfo[j+1][i+1];

            // lower triangle normal
            glm::vec3 Pbl { j*width, i*height, hbl };
            glm::vec3 Pbr { (j+1)*width, i*height, hbr };
            glm::vec3 Ptl { j*width, (i+1)*height, htl };
            glm::vec3 Ptr { (j+1)*width, (i+1)*height, htr };
            glm::vec3 nl = glm::normalize (glm::cross(Pbr - Pbl, Ptl - Pbl));
            glm::vec3 nu = glm::normalize (glm::cross(Ptl - Ptr, Pbr - Ptr));
            //nl = glm::vec3(0,0,1);
            //nu = glm::vec3(0,0,1);
            vertices.push_back( { Pbl.x, Pbl.y, Pbl.z, 0.0f, 0.0f, nl.x, nl.y, nl.z });
            vertices.push_back( { Pbr.x, Pbr.y, Pbr.z, 1.0f, 0.0f, nl.x, nl.y, nl.z });
            vertices.push_back( { Ptl.x, Ptl.y, Ptl.z, 0.0f, 1.0f, nl.x, nl.y, nl.z });

            vertices.push_back( { Pbr.x, Pbr.y, Pbr.z, 1.0f, 0.0f, nu.x, nu.y, nu.z });
            vertices.push_back( { Ptr.x, Ptr.y, Ptr.z, 1.0f, 1.0f, nu.x, nu.y, nu.z });
            vertices.push_back( { Ptl.x, Ptl.y, Ptl.z, 0.0f, 1.0f, nu.x, nu.y, nu.z });

            indices.push_back(k);
            indices.push_back(k+1);
            indices.push_back(k+2);
            indices.push_back(k+3);
            indices.push_back(k+4);
            indices.push_back(k+5);
            k += 6;

        }
    }
    mesh->Init(vertices, indices);
    auto renderer = std::make_shared<Renderer>();
    renderer->SetMesh(mesh);
    AddComponent(renderer);

}

glm::vec3 HeightMap::getNormal (float x, float y) {
    int icol = static_cast<int>(x/m_width);
    int irow = static_cast<int>(y/m_height);
    float dx = x- m_width*icol;
    float dy = y - m_height*irow;
    bool lowerTri = dy <= (m_height-dx);
    if (lowerTri) {
        float h_bl = m_heightInfo[icol][irow];
        float h_br = m_heightInfo[icol+1][irow];
        float h_tl = m_heightInfo[icol][irow+1];
        return (glm::normalize (glm::cross(
                glm::vec3(1.0f, 0.0f, h_br - h_bl), glm::vec3(0.0f, 1.0f, h_tl - h_bl))));
    } else {
        float h_tr = m_heightInfo[icol+1][irow+1];
        float h_br = m_heightInfo[icol+1][irow];
        float h_tl = m_heightInfo[icol][irow+1];
        return (glm::normalize (glm::cross(
                glm::vec3(1.0f, 0.0f, h_tr - h_tl), glm::vec3(0.0f, 1.0f, h_tr - h_br))));

    }
}

float HeightMap::getHeight (float x, float y) {
    int icol = static_cast<int>(x/m_width);
    int irow = static_cast<int>(y/m_height);
    float dx = x- m_width*icol;
    float dy = y - m_height*irow;
    bool lowerTri = dy <= (m_height-dx);
    glm::vec2 grad;
    float xInc = 0.0f;
    float yInc = 0.0f;
    float h0 = 0.0f;
    if (lowerTri) {
        xInc = x - m_width*icol;
        yInc = y - m_height*irow;
        float h_bl = m_heightInfo[icol][irow];
        float h_br = m_heightInfo[icol+1][irow];
        float h_tl = m_heightInfo[icol][irow+1];
        grad= glm::vec2 ((h_br-h_bl)/m_width, (h_tl-h_bl)/m_height);
        std::cout << "Get height @ (" << x << ", " << y << ")\n";
        h0 = h_bl;
        std::cout << "Lower tri: grad is = " << grad.x << ", " << grad.y << " h_bl = " << h0 << "\n";
    } else {
        xInc = m_width*(icol+1)-x;
        yInc = m_height*(irow+1)-y;
        float h_tr = m_heightInfo[icol+1][irow+1];
        float h_br = m_heightInfo[icol+1][irow];
        float h_tl = m_heightInfo[icol][irow+1];
        grad =glm::vec2((h_tl-h_tr)/m_width, (h_br-h_tr)/m_height);
        h0 = h_tr;
        std::cout << "Get height @ (" << x << ", " << y << ")\n";
        std::cout << "Up tri: grad is = " << grad.x << ", " << grad.y << "h_tr = " << h0 << "\n";

    }
    float h = h0 + glm::dot(grad, glm::vec2(xInc, yInc));
    std::cout << "h = " << h << "\n";
    return h;

}