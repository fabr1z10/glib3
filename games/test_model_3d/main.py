from mopy.engine import Engine
import scripts
import factories.items


engine = Engine(scripts=scripts)



engine.add_item_factory('brick', factories.items.brick)