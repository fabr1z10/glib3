import mopy.engine as engine
import mopy.entity as entity


class Room:
    def __init__(self, uid: str, width, height):
        self.id = uid
        self.width = width
        self.height = height
        self.ref = {}
        self.engines = []
        self.init = []
        self.dims = 2
        # collection of entities
        self.scene = []
        # method to call before room is created
        self.on_start = None

    # add an entity. If you provide a parent, the entity will be added to the parent,
    # otherwise it will be added to the scene
    def add(self, e: entity.Entity, parent: str = None):
        if parent and parent in self.ref:
            self.ref[parent].add(e)
        else:
            if parent:
                print ('WARNING! ' + parent +' + not found!')
            self.scene.append(e)
        if e.tag:
            self.ref[e.tag] = e

    def add_runner(self, r):
        self.engines.append(r)

