import example
import lib_py.script as script
import lib_py.actions as actions
from lib_py.scumm.scumm import Config 
import lib_py.scumm.actions as sa
import lib_py.scumm.scumm as s
import lib_py.scumm.helper as helper
import lib_py.engine as engine

def start_dialogue():
    # first of all, set UI to inactive
    ui : example.Wrap1 = example.get('ui')
    ui.setActive(False)

# handle 1-verb actions
def handler1():
    item : s.Item = s.Data.items[s.Config.item1] # s.State.items[s.Config.item1]
    sc = script.Script(id = '_main')
    # if item has a walk-to attribute, walk to it
    walkto = helper.gdd(item, 'walkto', None)
    wdir = helper.gdd (item, 'wdir', None)
    if walkto is not None:
        sc.addAction( sa.Walk(pos = walkto, tag = 'player'))    
    if wdir is not None:
        sc.addAction( sa.Turn(dir = wdir, tag = 'player'))
    # check if we have a custom script for this action
    func = s.Config.verb+'_'+s.Config.item1
    print ('checking ' + func)
    if hasattr(engine.scripts.actions, func):
        a = getattr(engine.scripts.actions, func)()
        if a:
            sc.addAction (actions.RunScript(s=a))        
        print ('dodo')
    else:
        # look for default action
        func = s.Config.verb + '_'
        if hasattr(engine.scripts.actions, func):
            a = getattr(engine.scripts.actions, func)()
            if a:
                sc.addAction (actions.RunScript(s=a))                    
        print ('not found')
    # print ('ciao ' + s.Config.verb)
    # if s.Config.verb in item.actions:
    #     a = item.actions[s.Config.verb]()
    #     if a:
    #         sc.addAction (actions.RunScript(s = a))
    # else:
    #     v = s.Config.getVerb(s.Config.verb)
    #     if v.default_action:
    #         a = v.default_action()
    #         sc.addAction (actions.RunScript(s = a))
    # sc.addAction (sa.ResetVerb())
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
    if s.Config.item1:
        # next, call the handler for the current verb
        verb.handler()

def dialogueHelper1(strings, characters, *args):
    def f():
        sc = script.Script()
        for b in args:
            pos= characters[b[0]][0]
            col = characters[b[0]][1]
            print ('position = ' + str(pos[0]))
            for c in b[1:]:
                sc.addAction (actions.Msg(text = strings[c], font='monkey', pos = (pos[0], pos[1], 5), color = col))
        return sc
    return f


def dialogueHelper2(s, *args):
    def f():
        sc = script.Script()
        for b in args:
            lines = []
            for c in b[1:]:
                lines.append(s[c])
            #print ('adding action ' + str(lines))
            sc.addAction(sa.Say(lines=lines, tag=b[0]))
        return sc
    return f


# a: animate forward - async
# ab: aimate backward - async
# A: animate forward - sync
# Ab: animate backward - async
# d: delay
# (...) lines to say

# dialogue with anim control
# supercool and quick way to create a dialogue
d3h = {
    'a': lambda tag, c : actions.Animate (anim = c, tag = tag, fwd = True, sync = False),
    'ab': lambda tag, c : actions.Animate (anim = c, tag = tag, fwd = False, sync = False),
    'A': lambda tag, c : actions.Animate (anim = c, tag = tag, fwd = True, sync = True),
    'Ab': lambda tag, c : actions.Animate (anim = c, tag = tag, fwd = False, sync = True),
    'd': lambda tag, c: actions.Delay (sec = float(c))
}

def d3(s, *args):
    def f():
        sc = script.Script()
        an = True
        for b in args:
            tag = b[0]
            print (tag)
            for c in b[1:]:
                if isinstance(c, tuple):
                    animate = True if c[0] == 'a' else False
                    l = [s[x] for x in list(c[1:])]
                    #print ('say ' + str(l))
                    sc.addAction (sa.Say (lines = l, tag = tag, animate = animate)) 
                elif isinstance(c, str):
                    # check if we have pending lines
                    i = c.find(':')
                    act = c[:i]
                    print ('adding ' + act)
                    sc.addAction (d3h[act](tag, c[i+1:]))
        print ('script has ' + str(len(sc.actions))  + ' acts.')
        return sc
    return f


def d4(s, *args):
    def f():
        sc = script.Script()
        for b in args:
            sc.addAction(b)
        return sc
    return f