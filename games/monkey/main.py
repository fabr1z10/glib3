import sys
import yaml
from pathlib import Path
import example
import vars

# add folder
path = Path(__file__)
sys.path.append(str(path.parent.parent / 'lib'))

import engine as eng
import factories


import factories.room
import factories.items
import shader

engine = eng.Engine()
engine.add_shader(shader.ShaderType.unlit_textured)
engine.add_shader(shader.ShaderType.unlit_color)
engine.add_shader(shader.ShaderType.text)
engine.add_room_factory('default', factories.room.default_room)
engine.add_item_factory('bg', factories.items.bg)
engine.add_item_factory('walkarea', factories.items.walkarea)


# load adventure items. fill up the items_in_room structure
with open(example.dir+  '/items.yaml') as f:
    vars.items = yaml.load(f, Loader=yaml.FullLoader)
print('# loaded ' + str(len(vars.items)) + ' items')
for k, v in vars.items.items():
    if 'room' in v:
        if v['room'] not in vars.items_in_room:
            vars.items_in_room[v['room']] = set()
        vars.items_in_room[v['room']].add(k)
#         parent = 'main' if 'parent' not in v else v['parent']
#         Data.putItem(k, v['room'], v['pos'], parent)
# print('--- items ---')
# print(Data.items)
# print(Data.locator)
# Data.loadDialogues()