from lib_py.entity import Entity
from lib_py.components import HotSpot
from lib_py.shape import Rect
from lib_py.scumm.dialogue import Dialogue


class Verb:
    # bear in mind the difference between callback and handler
    # callback is called when you click on the verb, handler is used when you run an action
    # for this verb
    def __init__(self, id : str, text: str, items: int, callback: callable, handler : callable, default_action : callable = None):
        self.text = text
        self.id = id
        self.items = items
        self.callback = callback
        self.handler = handler
        self.default_action = default_action

class VerbSet:
    def __init__(self, verbs : list, defaultVerb : str):
        self.verbs = verbs
        self.defaultVerb = defaultVerb

class Config:
    class Colors:
        current_action = [0, 170, 170, 255]
        verb_selected = [255, 255, 85, 255]
        verb_unselected = [0, 170, 0, 255]
    ui_height : int
    verb: str = ''
    item1 : str = ''
    item2 : str = ''
    __verbs = {}
    verbSets = []
    @staticmethod
    def resetVerb():
        Config.verb = Config.verbSets[0].defaultVerb
        Config.item1 = ''
        Config.item2 = ''

    @staticmethod
    def addVerb(v : Verb):
        Config.__verbs[v.id] = v
    @staticmethod
    def getVerb(id : str) -> Verb:
        return Config.__verbs[id]



# # a char item
# class CharacterItem(Item):
#     def __init__(self, text: str = None, model: str = None,
#         width: float = None, height: float = None, walkto: tuple = (), dir: str = '',
#         offset = [0,0], priority=1, actions : dict = {}):
#         self.text = text
#         self.width = width
#         self.height  =height
#         self.offset = offset
#         self.walkto = walkto
#         self.dir = dir
#         self.priority = priority
#         self.actions = actions
#         self.model = model



# class DynamicItem:
#     def __init__(self, id : str, params : dict = {}, parent: str = 'main'):
#         self.id = id
#         self.params = params
#         self.parent = parent

# new item
# an item can have 
# model ... optional, if this is provided the item will have a gfx
# -- a hotspot 
# if the item has an hotspot, it means the player can iteract with it. In order to have
# a hotspot, you must provide: text, width, height, walkto, dir
# optionally, you can provide an actions table to specify the script attached to each action
def ni (id: str, model: str, text: str, width: float, height: float, walkto: tuple, dir: str, actions: dict = {}):
    State.addItem(
        id = id, 
        item = Item(
            model = model,
            text = text, 
            width = 30, 
            height = 10, 
            walkto = walkto,
            dir = dir,
            actions = actions
        ))

    
class State:
    # map that associate room with dynamic items to create on the fly
    items = {}
    dialogues = {}
    room_items = {}
    items_room = {}
    variables = {}
    player = ''
    md = None

    @staticmethod
    def addItem (item):
        State.items[item.id]= item
    
    
    @staticmethod
    def addDialogue (dialogue : Dialogue):
        State.dialogues[dialogue.id] = dialogue
    
    @staticmethod
    def getDialogue (id: str):
        if id not in State.dialogues:
            print ('*** unknown dialogue: ' + id)
        return State.dialogues[id]

    @staticmethod
    def setDynamicItem(id: str, room : str, **kwargs):
        if room not in State.room_items:
            State.room_items[room] = {}
        # if item is already somewhere, remove it from current location
        if id in State.items_room:
            current_room = State.items_room[id]
            del State.room_items[current_room][id]
        State.room_items[room][id] = kwargs

# def print_msg(msg):
#     def h(e : example.Wrap1):
#         print(msg)
#     return h



# #    example.


# # scumm.func.set_verb = function(verb)
# #     local v = engine.config.verbs[verb]
# #     if v.objects > 0 then
# #         ai.verb = verb
# #         ai.obj1 = nil
# #         ai.obj2 = nil
# #         ai.selectSecond = false
# #         scumm.func.updateVerb()
# #     else
# #         v.callback()

# #     end
# # end
# # entities
# # button




