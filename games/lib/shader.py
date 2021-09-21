import enum


class ShaderType(enum.Enum):
    unlit_textured = 0,
    unlit_color = 1,
    text = 2,
    skeletal = 3
    skeletal_color = 4
    textured_light = 5

