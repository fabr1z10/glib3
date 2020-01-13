//
//  enums.h
//  glib
//
//  Created by Fabrizio Venturini on 06/05/2018.
//
//

#ifndef enums_h
#define enums_h

enum ShaderType {
    TEXTURE_SHADER,
    TEXT_SHADER,
    COLOR_SHADER,
    TEXTURE_SHADER_LIGHT,
    COLOR_SHADER_LIGHT,
    NONE
};

enum ShaderUniform {
    PROJECTION, MODELVIEW, TEXTURE, TINT, LIGHTDIR, LIGHTCOLOR, AMBIENT
};

enum TextAlignment {
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
    BOTTOM,
    TOP_LEFT,
    TOP_RIGHT,
    TOP,
    CENTER
};

struct EnumClassHash
{
    template <typename T>
    size_t operator()(T t) const
    {
        return static_cast<size_t>(t);
    }
};

#endif /* enums_h */
