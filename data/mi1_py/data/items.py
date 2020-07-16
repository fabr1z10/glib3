
from lib_py.scumm.scumm import State
import lib_py.engine as engine
#from lib_py.scumm.scumm import DynamicItem
import lib_py.scumm.entity as se
import lib_py.components as compo

st = engine.data['strings']

# guybrush
State.addItem (se.CharItem (
    id = 'guybrush',
    model = 'guybrush',
    speed = 500,
    text_color = [255, 255, 255, 255],
	text_offset = [0, 60]))

State.addItem(se.Item(
    id = 'pieces.of.eight',
    text = st['objects']['pieceofeight'],
    plural= st['objects']['piecesofeight']
))

# engine.addEntity(
#     id = 'guybrush',
#     e = se.Character(
#         model = 'guybrush', 
#         speed = 100, 
#         dir = 'e', 
#         state = 'idle',
#         text_color = [255, 255, 255, 255],
# 	    text_offset = [0, 60]
#     ))

# make guybrush!
# def makeGuybrush(**kwargs):
#     print (kwargs)
#     state = kwargs['state'] if 'state' in kwargs else 'idle'
#     dir = kwargs['dir'] if 'dir' in kwargs else 'e'
#     e = se.Character (model='guybrush', speed=100, dir=dir, state=state, text_color = [255,255,255,255], text_offset=[0,60])
#     if 'pos' in kwargs:
#         e.pos = kwargs['pos']
#         print ('found pos ' + str(e.pos[0]))
#     if State.player == 'guybrush':
#         e.tag = 'player'
#         e.addComponent (compo.Follow())
#     else:
#         e.tag = 'guybrush'
#     return e

#engine.data['factories']['guybrush'] = makeGuybrush

# a dynamic item is created ON THE FLY. It is simply a callable that creates an entity
