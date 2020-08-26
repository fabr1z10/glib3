import example
from lib_py.scumm.scumm import Config, State
from lib_py.engine import data
from lib_py.actions import RunScript
#from lib_py.scumm.entity import Item, CharItem

def addCustomScript (ns, f: str, s = None):
    if hasattr(ns, f):
        scr = getattr(ns, f)()
        if s is not None and scr:
            s.addAction (RunScript(s=scr))   
        return scr

def gdd(d: dict, key: str, defaultvalue):
    if key in d:
        return gd(d, key)
    return defaultvalue

def gv(val: str):
    if isinstance(val, str) and val[0] == '@':
        # lookup in variables
        cc = data['vars']
        print (cc)
        for b in val[1:].split('/'):
            print(b)
            cc = cc[b]
        return cc
    else:
        return val

def sv(id: str, val):
    if id[0] == '@':
        # lookup in variables
        cc = data['vars']
        xo = id[1:].split('/')
        print(xo)
        for b in xo[:-1]:
            cc = cc[b]
        print ('before ' + str(cc[xo[-1]]))
        cc[xo[-1]] = val
        print ('after' + str(cc[xo[-1]]))

def gd(d: dict, key: str):
    if key not in d:
        raise BaseException('key ' + key + ' not found!')
    val = d[key]
    return gv(val)

def gt(key: str):
    x = data['strings']
    if key[0] == '@':
        for b in key[1:].split('/'):
            if b.isnumeric():
                x = x[int(b)]
            else:
                x = x[b]
    return x


def set_verb(verbId):
    def f(x, y, e : example.Wrap1):
        Config.verb = verbId
        Config.item1 = ''
        Config.item2 = ''
        Config.wait_for_second_item = False
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

def refresh_inventory():
    p = example.get('inventory')
    if p.valid:
        inv = State.getCurrentInventory()
        p.clearText()
        for key, value in inv.items():
            p.appendText ((key, value))
