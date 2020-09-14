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
    TEXTURE_SHADER_UNLIT,
    TEXT_SHADER,
    COLOR_SHADER,
    TEXTURE_SHADER_LIGHT,
    COLOR_SHADER_LIGHT,
    SKELETAL_SHADER,
    NONE
};

enum ShaderUniform {
    PROJECTION,
    MODELVIEW,
    MODEL,
    VIEW,
    TEXTURE,
    MULTCOLOR,
    ADDCOLOR,
    LIGHTDIR,
    LIGHTCOLOR,
    AMBIENT,
    BONES
};

enum TextAlignment {
    TOP_LEFT,
    TOP,
    TOP_RIGHT,
    LEFT,
    CENTER,
    RIGHT,
    BOTTOM_LEFT,
    BOTTOM,
    BOTTOM_RIGHT
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
