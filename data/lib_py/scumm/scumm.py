
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
    def addVerb(v : Verb):
        Config.__verbs[v.id] = v
    @staticmethod
    def getVerb(id : str) -> Verb:
        return Config.__verbs[id]

# a interactive item
class Item:
    def __init__(self, text: str, width: float, height: float, walkto: list, dir: str, priority=1, actions : dict = {}):
        self.text = text
        self.width = width
        self.height  =height
        self.walkto = walkto
        self.dir = dir
        self.priority = priority
        self.actions = actions



class DynamicItem:
    def __init__(self, id : str, params : dict = {}, parent: str = 'main'):
        self.id = id
        self.params = params
        self.parent = parent

    
class State:
    # map that associate room with dynamic items to create on the fly
    items = {}
    room_items = {}
    items_room = {}
    @staticmethod
    def addItem (id : str, item : Item):
        State.items[id]= item
    
    @staticmethod
    def setDynamicItem(room : str, item : DynamicItem):
        if room not in State.room_items:
            State.room_items[room] = {}
        # if item is already somewhere, remove it from current location
        if item.id in State.items_room:
            current_room = State.items_room[item.id]
            del State.room_items[current_room][item.id]
        State.room_items[room][item.id] = item

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




