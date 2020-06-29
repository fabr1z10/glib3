import lib_py.engine as engine
import lib_py.entity as entity
import lib_py.camera as cam

class Room:

	def __init__(self, id:str, width, height):
		self.id = id
		self.width = width
		self.height = height
		#self.collide = collide
		self.ref = {}
		self.engines = []
		self.init = []

		self.keyl = engine.runner.KeyListener()
		# add a key listener to the engine
		#self.keyl.addKey (32, toggle_pause)
		#a = engine.entity.Entity()	
		self.engines.append(self.keyl)
		self.scene = []



	def add(self, e : entity.Entity, ref:str = None):
		if ref:
			if ref in self.ref:
				self.ref[ref].append(e)
			else:
				raise
		else:
			self.scene.append(e)
		if e.tag:
			self.ref[e.tag] = e.children

	def addRunner (self, r):
		self.engines.append(r)


class RoomBasic(Room):
	def __init__(self, id: str, width, height):
		super().__init__(id, width, height)
		# add the main node     
		camWidth = engine.device_size[0]
		camHeight = engine.device_size[1]
		main = entity.Entity (tag='main')
		main.camera = cam.OrthoCamera(width, height, camWidth, camHeight, [0, 0, camWidth, camHeight], tag='maincam')
		self.ref['main'] = main.children
		self.scene.append(main)
