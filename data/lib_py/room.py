import lib_py.engine as engine
import lib_py.entity as entity

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
