import example
import lib_py.script as script
import lib_py.actions as actions
from lib_py.scumm.scumm import Config 
import lib_py.scumm.actions as sa
import lib_py.scumm.scumm as s
import lib_py.scumm.helper as helper

def start_dialogue():
    # first of all, set UI to inactive
    ui : example.Wrap1 = example.get('ui')
    ui.setActive(False)

# handle 1-verb actions
def handler1():
    item : s.Item = s.State.items[s.Config.item1]
    sc = script.Script(id = '_main')
    # if item has a walk-to attribute, walk to it
    if item.walkto:
        x = item.walkto[0]
        y = item.walkto[1]
        sc.addAction( sa.Walk(pos = [x, y], tag = 'player'))
    if item.dir:
        sc.addAction( sa.Turn(dir = item.dir, tag = 'player'))
    # check if we have a custom script for this action
    print ('ciao ' + s.Config.verb)
    if s.Config.verb in item.actions:
        a = item.actions[s.Config.verb]()
        if a:
            sc.addAction (actions.RunScript(s = a))
    else:
        v = s.Config.getVerb(s.Config.verb)
        if v.default_action:
            a = v.default_action()
            sc.addAction (actions.RunScript(s = a))
    sc.addAction (sa.ResetVerb())
    example.play(sc)
        # run default script
    



def walkto(x, y, obj=None):
    #ds = example.getDeviceSize()
    #print('device size is ' + str(ds))
    s = script.Script(id = '_main')
    s.addAction( sa.Walk(pos = [x, y], tag = 'player'))
    example.play(s)    
    print ('clicked on ' + str(x) + ', ' + str(y))




# this is called whenever you click on a item
def run_action(x,y,obj=None):
    # first, get the current verb
    verb = s.Config.getVerb(s.Config.verb)
    print ('action: ' + verb.text + ' ' + s.Config.item1)
    # next, call the handler for the current verb
    verb.handler()

