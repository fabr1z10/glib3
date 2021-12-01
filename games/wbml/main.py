from mopy.engine import Engine
import data
import data.factories

engine = Engine(data=data)


engine.add_item_factory('player', data.factories.player)
engine.add_item_factory('rect', data.factories.rect)
engine.add_item_factory('bg', data.factories.bg)
