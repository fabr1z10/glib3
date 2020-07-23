from lib_py.entity import Entity
from lib_py.components import HotSpot, Info, Follow
from lib_py.scumm.components import Character
from lib_py.shape import Rect
from lib_py.scumm.scumm import Data, State
from lib_py.scumm.entity import hoverOn, hoverOff
from lib_py.scumm.functions import run_action
from lib_py.scumm.helper import gv

# create an entity from an item description
def buildItem (id: str = None):
    desc = Data.items[id]
    # create the entity
    tag = desc.get ('tag', id)    
        
    pos = desc.get ('pos', [0, 0, 0])
    e = Entity (tag, pos)
    
    # if the item has model
    model = desc.get ('model', None)
    if model is not None:
        e.type = 'sprite'
        e.model = model
        if 'anim' in desc:
            e.anim = gv(desc['anim'])
    
    # check if hotspot is to be added
    text = desc.get ('text', None)
    if text is not None:
        width = desc.get('width', None)
        height = desc.get('height', None)
        offset = desc.get('offset', (0, 0))
        priority = desc.get('priority', 1)
        if width is None or height is None:
            raise BaseException('you need to specify width & height for hotspots!')
        e.addComponent(HotSpot(
            shape = Rect(width = width, height = height, offset = offset),
            priority= priority,
            onenter = hoverOn(id),
            onleave = hoverOff,
            onclick = run_action))
    
    # if speed is set --> item is a character
    speed = desc.get ('speed', None)
    # add the character stuff
    if speed is not None:
        direction = desc.get('dir')
        state = desc.get('state', 'idle')
        text_color = desc.get ('text_color')
        text_offset = desc.get ('text_offset')
        e.addComponent (Character(speed, direction, state))
        e.addComponent (Info(text_color = text_color, text_offset = text_offset))
        # check if this is the current player
        # if so, I tag it as player, and make the camera follow him
        if State.player == id:
            e.tag = 'player'
            e.addComponent (Follow())
             
    return e