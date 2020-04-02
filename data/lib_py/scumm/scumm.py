
# scumm requires a list of verb. Each verb 
import lib_py.scumm.entity as entity

class Verb:
    def __init__(self, id : str, text: str, items: int):
        self.text = text
        self.id = id
        self.items = items

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
    __verbs = {}
    verbSets = []
    @staticmethod
    def addVerb(v : Verb):
        Config.__verbs[v.id] = v
    @staticmethod
    def getVerb(id : str) -> Verb:
        return Config.__verbs[id]

class DynamicItem:
    def __init__(self, id : str, params : dict = {}, parent: str = 'main'):
        self.id = id
        self.params = params
        self.parent = parent

    
class State:
    # map that associate room with dynamic items to create on the fly
    room_items = {}
    items_room = {}
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




