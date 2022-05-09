import mopy
import data.scripts.factories as f

def init():
	# put here your initialization code
	engine = mopy.monkey.engine
	engine.add_item_factory('box', f.box)
	engine.add_item_factory('ramp', f.ramp)
	pass
