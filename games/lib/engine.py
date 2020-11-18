import example


class Engine:
    def __init__(self):
        example.init(example.what)

    def add_shader(self, shader):
        self.shaders.append(shader)

    shaders = []
