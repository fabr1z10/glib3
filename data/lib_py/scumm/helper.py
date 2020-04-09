import example
from lib_py.scumm.scumm import Config, State

def set_verb(verbId):
    def f(x, y, e : example.Wrap1):
        Config.verb = verbId
        Config.item1 = ''
        Config.item2 = ''
        update_current_action()
    return f

def update_current_action():
    a : example.Wrap1 = example.get('current_verb')
    verb = Config.getVerb(Config.verb)
    text = verb.text
    if Config.item1:
        item = State.items[Config.item1]
        text += ' ' + item.text
    a.setText (text)