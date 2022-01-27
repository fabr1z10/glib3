from mopy.engine import Engine
import data
import data.factories as f


engine = Engine(data=data)

engine.add_room_factory('3d', f.ciao)
