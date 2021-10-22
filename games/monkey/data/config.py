ui_height = 56
font_size = 8
current_player = 'guybrush'

verbs = {
    'open': {'text': '$ui/open', 'items': 1},
    'close': {'text': '$ui/close', 'items': 1},
    'push': {'text': '$ui/push', 'items': 1},
    'pull': {'text': '$ui/pull', 'items': 1},
    'walkto': {'text': '$ui/walkto', 'items': 1},
    'pickup': {'text': '$ui/pickup', 'items': 1},
    'talkto': {'text': '$ui/talkto', 'items': 1},
    'give': {'text': '$ui/give', 'items': 2, 'prep': '$ui/to'},         # if verb takes 2 items, you need to provide a preposition!
    'use': {'text': '$ui/use', 'items': 2, 'prep': '$ui/with'},
    'lookat': {'text': '$ui/lookat', 'items': 1},
    'turnon': {'text': '$ui/turnon', 'items': 1},
    'turnoff': {'text': '$ui/turnoff', 'items': 1}
}

verb_sets = [
    { 'verbs': ['open', 'close', 'push', 'pull', 'walkto', 'pickup', 'talkto', 'give', 'use', 'lookat', 'turnon', 'turnoff'], 'default_verb': 'walkto'}
]


class Colors:
    current_action = [0, 170, 170, 255]
    verb_selected = [255, 255, 85, 255]
    verb_unselected = [0, 170, 0, 255]
    inv_unselected = [170, 0, 170, 255]
    inv_selected= [255, 85, 255, 255]


class Collision:
    class Flags:
        player = 0
        other = 1
    class Tags:
        player = 0
        trap = 1