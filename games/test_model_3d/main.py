from mopy.engine import Engine
import factories.items
import data

engine = Engine(data=data)



engine.add_item_factory('brick', factories.items.brick)
engine.add_item_factory('goomba', factories.items.goomba)
engine.add_item_factory('mario', factories.items.mario)