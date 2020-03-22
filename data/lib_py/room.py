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


class RoomUI(Room):
	def __init__(self, width, height, collide = False):
		super().__init__(width, height, collide)
		uisize = settings.monkey.uiHeight
		print ('uisize is '+str(uisize))
		camWidth = settings.monkey.deviceSize[0]
		camHeight = settings.monkey.deviceSize[1] - uisize

		# add the main node     
		main = e.Entity (tag='main')
		main.camera = e.cam.OrthoCamera(width, height, camWidth, camHeight, [0, uisize, camWidth, camHeight], tag='maincam')

		# add the ui node
		ui = e.Entity (tag='ui')
		ui.camera = e.cam.OrthoCamera(camWidth, uisize, camWidth, uisize, [0, 0, camWidth, uisize], tag = 'uicam')
		ui.add (e.Text(font='ui', text='ciao', color = [255, 255, 255, 255], align = e.TextAlignment.bottom, tag=None, pos = [camWidth/2, 0]))
		

		self.scene.append(main)
		self.scene.append(ui)
