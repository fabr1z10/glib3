from mopy.engine import Engine
import scripts
import factories.items
import data

engine = Engine(data=data, scripts=scripts)



engine.add_item_factory('brick', factories.items.brick)