from lib_py.entity import Entity
from lib_py.components import HotSpot
from lib_py.scumm.dialogue import Dialogue, DialogueNode
import lib_py.engine as engine

class Verb:
    # bear in mind the difference between callback and handler
    # callback is called when you click on the verb, handler is used when you run an action
    # for this verb
    def __init__(self, id : str, text: str, items: int, callback: callable, handler : callable, default_action : callable = None, prep = ''):
        self.text = text
        self.id = id
        self.items = items
        self.prep = prep
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
    wait_for_second_item = False
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

class Data:
    items = {}
    dialogues = {}
    locator = {}

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
        filename = example.dir +'/items.yaml'
        with open(filename) as f:
            Data.items = yaml.load(f, Loader=yaml.FullLoader)
        print ('loaded items')
        for k, v in Data.items.items():
            if 'room' in v:
                parent = 'main' if 'parent' not in v else v['parent']
                Data.putItem (k, v['room'], v['pos'], parent)
        print ('--- items ---')
        print (Data.items)
        print (Data.locator)
        Data.loadDialogues()

    @staticmethod
    def loadDialogues():
        filename = example.dir +'/dialogues.yaml'
        with open(filename) as f:
            dial = yaml.load(f, Loader=yaml.FullLoader)
            for k, v in dial.items():
                print ('making dialog ' + k)
                stringset = v['stringset']
                a = Dialogue(k, stringset)
                for nodeId, value in v['nodes'].items():
                    nex = value.get('next', None)
                    status = value['status']
                    parent = value.get('parent', None)
                    print ('adding node ' + nodeId)
                    closeThis = value.get('once', False)
                    closeNodes = value.get('close_nodes', [])
                    actNodes = value.get('activate_nodes', [])
                    if closeThis:
                        closeNodes.append(nodeId)
                    node = a.add(nodeId, status, nex, parent = parent, closeNodes = closeNodes, actNodes = actNodes)
                Data.dialogues[k] = a
    
    @staticmethod
    def loadRooms():
        # create one room builder for each yaml in rooms
        dir = example.dir +'/rooms'
        import os, glob
        if os.path.exists(dir):
            for file in glob.glob(dir+"/*.yaml"):
                roomName = os.path.splitext(os.path.basename(file))[0]
                engine.addRoom (roomName, builder(roomName))

class State:
    # map that associate room with dynamic items to create on the fly
    #items = {}
    dialogues = {}
    room_items = {}
    items_room = {}
    variables = {}
    player = ''
    collision_enabled = False
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
        return Data.dialogues[id]

def init(players: list, current_player : str):
    # initialize inventories
    for player in players:
        State.inventory[player] = {}
    State.player = current_player

def startUp():
    a = engine.startUp()
    print ('icicici')
    ac = a['custom']
    Config.ui_height = ac['ui_height']
    players = ac['players']
    cp = ac['current_player']
    init (players = players, current_player= cp)

    import lib_py.scumm.helper as helper

    import lib_py.scumm.functions as func
    print ('icicici')

    for key, verb in ac['verbs'].items():
        print ('adding verb ' + key)
        text = engine.getString (verb['text'])
        print ('text = ' + text)
        nitems = int(verb['items'])
        # get the default action
        def_act = verb.get('default_action', None)
        f = None
        if def_act:
            f = engine.getFunc (def_act)
        # check if 
        handler = func.handler1 if nitems == 1 else func.handler2
        prep =  engine.getString(verb.get('prep',None))
        #print ('AAA='+prep)
        Config.addVerb (Verb (id = key, text = text, items = nitems, callback = helper.set_verb(key), handler = handler, default_action=f, prep = prep))
    for verbset in ac['verbsets']:
        Config.verbSets.append (VerbSet (verbs = verbset['verbs'], defaultVerb=verbset['default_verb'] ))
    Data.loadItems()

    Data.loadRooms()
    import importlib
    engine.scripts = importlib.import_module('scripts', package=None)    
    from inspect import getmembers, isfunction
    #print (getmembers(engine.scripts.actions))
    functions_list = [o for o in getmembers(engine.scripts) if isfunction(o[1])]#State.setDynamicItem (id='guybrush', room='lookout', pos=[200,30,0], dir='s', parent='walkarea')
    print ('-- functions')

    Data.putItem (id=cp, room=engine.room, pos=[0,0], parent='walkarea')
    #State.setDynamicItem (id=cp, room=engine.room, pos = [0,0,0], dir='s', parent='walkarea')
    #print (functions_list)    
    #exit(1)

    # #scumm.State.inventory['guybrush']['rubber.chicken'] = 1


    # t = engine.data['strings']


    # # # add verbs and verb sets
    # scumm.Config.addVerb (scumm.Verb (id = 'open', text = t['ui']['open'], items=1, callback=helper.set_verb('open'), handler = func.handler1,
    #     default_action = sscripts.say( lines = [t['defaultactions'][1]])))
    # scumm.Config.addVerb (scumm.Verb (id = 'close', text = t['ui']['close'], items=1, callback=helper.set_verb('close'), handler = func.handler1,
    #     default_action = sscripts.say( lines = [t['defaultactions'][2]])))
    # scumm.Config.addVerb (scumm.Verb (id = 'push', text = t['ui']['push'], items=1, callback=helper.set_verb('push' ), handler = func.handler1,
    #     default_action = sscripts.say( lines = [t['defaultactions'][3]])))
    # scumm.Config.addVerb (scumm.Verb (id = 'pull', text = t['ui']['pull'], items=1, callback=helper.set_verb('pull' ), handler = func.handler1,
    #     default_action = sscripts.say( lines = [t['defaultactions'][3]])))
    # scumm.Config.addVerb (scumm.Verb (id = 'walkto', text = t['ui']['walkto'], items=1, callback=helper.set_verb('walkto' ), handler = func.handler1))
    # scumm.Config.addVerb (scumm.Verb (id = 'pickup', text = t['ui']['pickup'], items=1, callback=helper.set_verb('pickup' ), handler = func.handler1,
    #     default_action = sscripts.say( lines = [t['defaultactions'][5]])))
    # scumm.Config.addVerb (scumm.Verb (id = 'talkto', text = t['ui']['talkto'], items=1, callback=helper.set_verb('talkto' ), handler = func.handler1,
    #     default_action = sscripts.say( lines = [t['defaultactions'][2]])))
    # scumm.Config.addVerb (scumm.Verb (id = 'give', text = t['ui']['give'], items=1, callback=helper.set_verb('give' ), handler = func.handler1))
    # scumm.Config.addVerb (scumm.Verb (id = 'use', text = t['ui']['use'], items=1, callback=helper.set_verb('use' ), handler = func.handler1,
    #     default_action = sscripts.say( lines = [t['defaultactions'][2]])))
    # scumm.Config.addVerb (scumm.Verb (id = 'look', text = t['ui']['lookat'], items=1, callback=helper.set_verb('look' ), handler = func.handler1,
    #     default_action = sscripts.say( lines = [t['defaultactions'][4]])))
    # scumm.Config.addVerb (scumm.Verb (id = 'turnon', text = t['ui']['turnon'], items=1, callback=helper.set_verb('turnon' ), handler = func.handler1,
    #     default_action = sscripts.say( lines = [t['defaultactions'][2]])))
    # scumm.Config.addVerb (scumm.Verb (id = 'turnoff', text = t['ui']['turnoff'], items=1, callback=helper.set_verb('turnoff' ), handler = func.handler1,
    #     default_action = sscripts.say( lines = [t['defaultactions'][2]])))



    # scumm.Config.verbSets.append (scumm.VerbSet(verbs= ['open', 'close', 'push', 'pull', 'walkto', 'pickup', 'talkto', 'give', 'use', 'look', 'turnon', 'turnoff'],
    #     defaultVerb='walkto'))

    # # sets door to closed

    # scumm.State.variables['door.village.scummbar'] = 'closed'

    # scumm.State.md = variables

    # #from mi1_py.data import *
    # #from mi1_py.data.dialogues import *
    # #from mi1_py.rooms import *

    # # load all rooms

    # # initialize room
    # #engine.room = 'village1'
    # # scumm.State.setDynamicItem (
    # #     id = 'guybrush', 
    # #     room = engine.room, 
    # #     pos = variables.village1_door_pos,
    # #     state = 'idle',
    # #     chardir = 's', parent = 'walkarea')

    # #inv = scumm.State.getCurrentInventory()
    # #inv['pieces.of.eight'] = 10
    # scumm.Data.loadItems()
    # scumm.Data.loadRooms()

    # import importlib
    # engine.scripts = importlib.import_module('scripts', package=None)







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





    
import yaml
import example
import sys


def builder(id):
    def f():
        from lib_py.scumm.builder.room import makeRoom
        return makeRoom(id)
    return f        


