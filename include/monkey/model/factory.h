#pragma once

#include <monkey/assets/model.h>
#include <string>


class ModelFactory {

public:
    // create a rectangular image, having given width and height. If width or height are both zero, the image size
    // matches that of the image in pixel. If only one has a value, and the other is 0, the other is computed in order
    // to maintain the aspect ratio of the image. Repx and repy give how many texture repetition you want along x and y axis. 1 is default.
    static std::shared_ptr<Model> quad(const std::string& imagePath, float width = 0.0f, float height = 0.0f,
                                 float repx = 1.0f, float repy = 1.0f);
    static std::shared_ptr<Model> polygon(const ITab&);
};