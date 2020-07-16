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
        inv_unselected = [170, 0, 170, 255]
        inv_selected = [255, 85, 255, 255]
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




# initialize the scumm engine
# it requires a player list, and an initial player
def init(players: list, current_player : str):
    # initialize inventories
    for player in players:
        State.inventory[player] = {}
    State.player = current_player
    
import yaml
import example
import sys
class Data:
    items = {}
    locator = {}
    @staticmethod
    def makeRoom (roomid: str):
        filename = example.dir +'/rooms/'+ roomid+ '.yaml'
        from lib_py.scumm.room import RoomUI
        try:
            with open(filename) as f:
                room = yaml.load(f, Loader=yaml.FullLoader)
                r = RoomUI(id= room['id'], width = ['width'], height = ['height'])
                if roomid in Data.locator:
                    for key, value in Data.locator[roomid].items():
                        print ('found item: ' + key)
                return r
        except EnvironmentError as error:
            print (error)
            sys.exit(1)


    @staticmethod
    def putItem (id: str, room: str, pos, parent: str = 'main'):
        # locate an item in a room at a certain pos
        # check if item is in another room
        item = Data.items[id]
        if 'room' in item and item['room'] != room:
            Data.locator[item['room']].pop(id)
        Data.items[id]['room'] = room
        Data.items[id]['pos'] = pos
        if room not in Data.locator:
            Data.locator[room] = {}
        Data.locator[room][id] = (id, pos, parent)


    @staticmethod
    def loadItems():
        print ('ciaomerd')
        filename = example.dir +'/items.yaml'
        with open(filename) as f:
            Data.items = yaml.load(f, Loader=yaml.FullLoader)
        print ('loaded items')
        for k, v in Data.items.items():
            if 'room' in v:
                parent = 'main' if 'parent' not in v else v['parent']
                Data.putItem (k, v['room'], v['pos'], parent)
                
        print (Data.items)
        print (Data.locator)
    
class State:
    # map that associate room with dynamic items to create on the fly
    items = {}
    dialogues = {}
    room_items = {}
    items_room = {}
    variables = {}
    player = ''
    md = None
    # we can have more than one inventory for each player
    inventory = {}

    @staticmethod
    def getCurrentInventory():
        return State.inventory[State.player]

    @staticmethod
    def has (id: str, qty: int = 1):
        return State.player in State.inventory and id in State.inventory[State.player] and State.inventory[State.player][id] >= qty

    @staticmethod
    def addItem (item):
        if item.id in State.items:
            raise BaseException('Duplicate item ' + item.id)
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




