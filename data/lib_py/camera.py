class Camera:
    def __init__(self, viewport, tag = None):
        self.tag = tag
        self.viewport = viewport


class OrthoCamera(Camera):
    def __init__(self, worldwidth, worldheight, camwidth, camheight, viewport, tag = None):
        super().__init__(viewport, tag)
        self.type = 'cam.ortho'
        self.tag = tag
        self.size = [camwidth, camheight]
        self.bounds = [0, 0, worldwidth, worldheight]
        self.viewport = viewport
        self.worldwidth = worldwidth
        self.worldheight = worldheight
        self.camwidth = camwidth
        self.camheight = camheight


