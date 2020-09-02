from lib_py.entity import Entity
from lib_py.engine import read
from lib_py.components import HotSpot, Info, Follow, Collider
from lib_py.scumm.components import Character
from lib_py.scumm.actions import Walk
from lib_py.shape import Rect
from lib_py.scumm.scumm import Data, State
from lib_py.scumm.entity import hoverOn, hoverOff
from lib_py.scumm.functions import run_action
from lib_py.scumm.helper import gv
from lib_py.script import Script
from lib_py.actions import ChangeRoom
import example

def updateText(text: str):
    def f(id):
        a : example.Wrap1 = example.get('cursor')
        a.setText (text)
    return f

def clearText(id):
    a : example.Wrap1 = example.get('cursor')
    a.setText ('')

def gotohotspot(id):
    def f(x,y,obj):
        desc = Data.items[id]   
        pos = desc.get ('pos', [0, 0, 0])
        goto = desc.get ('goto')
        dir = goto.get('dir', None)
        gnode = goto.get('node', 'walkarea')
        Data.putItem (State.player, goto['room'], gv(goto['pos']), gnode)
        if dir is not None:
            Data.items[State.player]['dir'] = dir
        s = Script('_main')
        s.addAction(Walk(pos = pos, tag='player'))
        s.addAction (ChangeRoom(room = goto['room']))
        example.play(s)
    return f


def mapHotSpotItem (id: str):
    desc = Data.items[id]   
    tag = desc.get ('tag', id)            
    pos = desc.get ('pos', [0, 0, 0])
    e = Entity (tag, pos)
    width = desc.get ('width', 10)
    height = desc.get ('height', 10)
    textid = desc['text']
    from lib_py.engine import data
    text = data['strings']['objects'][textid]
    e.addComponent(HotSpot(
        shape = Rect(width = width, height = height, offset = (-width/2, -height/2)),
        priority= 0,
        onenter = updateText(text),
        onleave = clearText,
        onclick = gotohotspot(id)))
    return e
    #onenter = hoverOn(id),
    #onleave = hoverOff,
    #onclick = run_action))


def basicItem (id: str):
    desc = Data.items[id]   
    # create the entity
    tag = read (desc, 'tag', default_value = id)# desc.get ('tag', id)
        
    pos = read (desc, 'pos', default_value = [0, 0, 0])
    e = Entity (tag, pos)
    
    # if the item has model
    model = read(desc,'model', default_value = None)
    if model is not None:
        e.type = 'sprite'
        e.model = model
        if 'anim' in desc:
            e.anim =read(desc, 'anim')
    
    # check if hotspot is to be added
    text = read(desc, 'text', default_value = None)
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

    if State.collision_enabled and 'collision' in desc:
        coll = desc['collision']
        box = read (coll, 'size')
        offset = read (coll, 'offset', default_value=[0,0])
        flag = read (coll, 'flag')
        mask = read (coll, 'mask')
        tag = read (coll, 'tag')
        e.addComponent (Collider (flag, mask, tag, Rect(box[0], box[1], offset = offset)))
        
    return e
item_factories = {
    'basic': basicItem,
    'maphotspot': mapHotSpotItem
}
# create an entity from an item description
def buildItem (id: str = None):
    desc = Data.items[id]   
    itype = desc.get('type', 'basic')
    return item_factories[itype](id)
