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
    COLOR_SHADER
};

enum ShaderUniform {
    PROJECTION, MODELVIEW, TEXTURE, TINT
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
