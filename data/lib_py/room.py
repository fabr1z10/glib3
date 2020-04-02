import lib_py.engine as engine
import lib_py.entity as entity

def toggle_pause():
    print ('toggling pause! ')

class Room:

	def __init__(self, id:str, width, height, collide = False):
		self.id = id
		self.width = width
		self.height = height
		self.collide = collide
		self.ref = {}
		self.engines = []

		# add a key listener to the engine
		keyl = engine.runner.KeyListener()
		keyl.addKey (32, toggle_pause)
		#a = engine.entity.Entity()

		
		self.engines.append(keyl)
		self.scene = []

	def add(self, e : entity.Entity, ref):
		if ref in self.ref:
			self.ref[ref].append(e)
		if e.tag:
			self.ref[e.tag] = e.children


