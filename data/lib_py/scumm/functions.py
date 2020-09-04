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
    

def get_action_script(s: str, ds: str = None):            
    if hasattr(engine.scripts.actions, s):
        return getattr(engine.scripts.actions, s)
    else:
        if ds is not None:
            if hasattr(engine.scripts.actions, ds):
                return getattr(engine.scripts.actions, ds)
    return None

# handle 1-item actions
def handler1():
    item : s.Item = s.Data.items[s.Config.item1] # s.State.items[s.Config.item1]
    sc = script.Script(id = '_main')
    # if item has a walk-to attribute, walk to it
    # only if item is not owned
    if not s.State.has(s.Config.item1):
        walkto = engine.read (item, 'walkto', default_value=None)
        wdir = engine.read (item, 'wdir', default_value=None)
        if walkto is not None:
            sc.addAction( sa.Walk(pos = walkto, tag = 'player'))    
        if wdir is not None:
            sc.addAction( sa.Turn(dir = wdir, tag = 'player'))
    # check if we have a custom script for this action
    func = s.Config.verb+'_'+s.Config.item1
    if hasattr(engine.scripts.actions, func):
        a = getattr(engine.scripts.actions, func)()
        if a:
            sc.addAction (actions.RunScript(s=a))        
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
    sc.addAction (sa.ResetVerb())
    example.play(sc)
        # run default script
    

def handler2_sub(item: str):
    def f():
        sc = script.Script(id = '_main2')
        if s.State.has(item):
            handler2_do (sc)
        else:
            # fail
            func = s.Config.verb + '_'
            if hasattr(engine.scripts.actions, func):
                a = getattr(engine.scripts.actions, func)()
                sc.addAction (actions.RunScript(s=a))  
            example.play(sc)
                        

def handler2_do(sc : script.Script):
    item2 : s.Item = s.Data.items[s.Config.item2] # s.State.items[s.Config.item1]
    walkto = helper.gdd(item2, 'walkto', None)
    wdir = helper.gdd (item2, 'wdir', None)
    if walkto is not None:
        sc.addAction( sa.Walk(pos = walkto, tag = 'player'))    
    if wdir is not None:
        sc.addAction( sa.Turn(dir = wdir, tag = 'player'))
    asc = get_action_script (s.Config.verb + '_' + s.Config.item1 + '_' + s.Config.item2, s.Config.verb +'_')
    if asc:
        sc.addAction (actions.RunScript (s = asc))





# handle 2-item actions
def handler2():
    # the rule is. Walk to item 2, but you need to HAVE item 1.
    # so if you 
    print ('A')
    sc = script.Script(id = '_main')
    if s.Config.item2:
        print ('B')
        item1 : s.Item = s.Data.items[s.Config.item1] # s.State.items[s.Config.item1]
        if s.State.has(s.Config.item1):
            handler2_do(sc)
        else:
            # try to pick up item1
            print ('try to pick up ' + s.Config.item1)
            walkto = helper.gdd(item1, 'walkto', None)
            wdir = helper.gdd (item1, 'wdir', None)
            if walkto is not None:
                sc.addAction( sa.Walk(pos = walkto, tag = 'player'))    
            if wdir is not None:
                sc.addAction( sa.Turn(dir = wdir, tag = 'player'))
            # ok, now check if pickup action is available            
            func = 'pickup_'+s.Config.item1
            if hasattr(engine.scripts.actions, func):
                a = getattr(engine.scripts.actions, func)()
                sc.addAction (actions.RunScript(s=a))        
                # now go to item 2 ONLY IF item is in inventory
                sc.addAction (actions.CallFunc (f = handler2_sub))
            else:
                # no pick up action, then do nothing.
                func = s.Config.verb + '_'
                if hasattr(engine.scripts.actions, func):
                    a = getattr(engine.scripts.actions, func)()
                    sc.addAction (actions.RunScript(s=a))  
        example.play(sc)           
    else:
        s.Config.wait_for_second_item = True
        print ('QUI')
        from lib_py.scumm.entity import update_current_action
        update_current_action()
        # if I don't have an item2, then 


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