class Camera:
    def __init__(self, viewport, tag: str = None):
        self.tag = tag
        self.viewport = viewport


class OrthoCamera(Camera):
    def __init__(self, world_width, world_height, cam_width, cam_height, viewport, tag: str = None):
        super().__init__(viewport, tag)
        self.type = 'cam.ortho'
        self.tag = tag
        self.size = [cam_width, cam_height]
        self.bounds = [0, 0, world_width, world_height]
        self.viewport = viewport
        self.world_width = world_width
        self.world_height = world_height
        self.cam_width = cam_width
        self.cam_height = cam_height


