ui_height = 56
msg_height = 16
main_height = 128

font_size = 8

current_player = 'dave'
players = ['Dave', 'Michael', 'Pippo']
player_info = {
    'Dave': 'dave',
    'Michael': 'michael'
}
current_verb = None
current_item_1 = None
current_item_2 = None
wait_for_second_item = False

items = dict()
dialogues = dict()

items_in_room = dict()

inventory = dict()

class Collision:
    class Flags:
        player = 0
        other = 1
    class Tags:
        player = 0
        trap = 1

class Colors:
    current_action = [0, 170, 170, 255]
    verb_selected = [255, 255, 85, 255]
    verb_unselected = [0, 170, 0, 255]
    inv_unselected = [170, 0, 170, 255]
    inv_selected= [255, 85, 255, 255]

#inventory['meat'] = 1
#inventory['fish'] = 1

verbs = {
    'push': {'text': '$ui/push', 'items': 1},
    'pull': {'text': '$ui/pull', 'items': 1},
    'give': {'text': '$ui/give', 'items': 2, 'prep': '$ui/to'},         # if verb takes 2 items, you need to provide a preposition!
    'open': {'text': '$ui/open', 'items': 1},
    'close': {'text': '$ui/close', 'items': 1},
    'read': {'text': '$ui/read', 'items': 1},
    'walkto': {'text': '$ui/walkto', 'items': 1},
    'pickup': {'text': '$ui/pickup', 'items': 1},
    'whatis': {'text': '$ui/whatis', 'items': 1},
    'unlock': {'text': '$ui/unlock', 'items': 1},
    'newkid': {'text': '$ui/newkid', 'items': 1, 'callback': 'on_new_kid_pressed'},
    'use': {'text': '$ui/use', 'items': 2, 'prep': '$ui/with'},
    'turnon': {'text': '$ui/turnon', 'items': 1},
    'turnoff': {'text': '$ui/turnoff', 'items': 1},
    'fix': {'text': '$ui/fix', 'items': 2, 'prep': '$ui/with'},
}

verb_sets = [
    { 'verbs': ['push', 'pull', 'give', 'open', 'close', 'read', 'walkto', 'pickup', 'unlock', 'newkid', 'use', 'turnon', 'turnoff'], 'default_verb': 'walkto'}
]
