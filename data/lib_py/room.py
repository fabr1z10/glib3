import settings
import lib_py.entity as e
import lib_py.engine as engine

def toggle_pause():
    print ('toggling pause! ')

class Room:

	def __init__(self, width, height, collide = False):
		self.width = width
		self.height = height
		self.collide = collide
		self.ref = {}
		self.engines = []

		# add a key listener to the engine
		keyl = engine.KeyListener()
		keyl.addKey (32, toggle_pause)

		self.engines.append(keyl)
		self.scene = []

	def add(self, entity, ref):
		if ref in self.ref:
			self.ref[ref].append(entity)



