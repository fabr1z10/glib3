from mopy.engine import Engine
from data.scripts.factory import *
import data

engine = Engine(data=data)

engine.add_room_factory('default_room', default_room)
