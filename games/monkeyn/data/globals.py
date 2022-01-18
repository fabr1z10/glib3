# global section.. required
import mopy.util as utils

ui_height = 56
font_size = 8
current_verb = None
current_item_1 = ''
current_item_2 = ''
current_player = 'main.guybrush'
default_text_offset = (0, 60)
default_speed = 100
ui_font = 'fonts.ui'
default_font = 'fonts.monkey'

class Colors:
    current_action = utils.rgb(0, 170, 170)
    verb_selected = utils.rgb(255, 255, 85)
    verb_unselected = utils.rgb(0, 170, 0)
    inv_unselected = [170, 0, 170, 255]
    inv_selected = [255, 85, 255, 255]


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
    {'verbs': ['open', 'close', 'push', 'pull', 'walkto', 'pickup', 'talkto', 'give', 'use', 'lookat', 'turnon', 'turnoff'], 'default_verb': 'walkto'}
]

inventory =dict()