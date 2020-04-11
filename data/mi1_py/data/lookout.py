from lib_py.scumm.scumm import State
from lib_py.scumm.scumm import Item
from lib_py.scumm.dialogue import Dialogue, NodeStatus
from lib_py.scumm.dialogue import Line, DialogueNode
from lib_py.script import Script
import lib_py.scumm.actions as sa
import lib_py.scumm.scripts as ssc
import lib_py.engine as engine
import mi1_py.variables as var
import example

st = engine.data['strings']
sl = st['dialogues']['lookout']

State.addItem (
    id = 'lookout.stairs', 
    item = Item(
        text = st['objects']['stairs'], 
        width = 30, 
        height = 10, 
        walkto = [250, 0], 
        dir = 's',
        actions = {
            'walkto': ssc.changeRoom(room = 'village1', pos = [20, 20, 0], dir='s')
        }))

State.addItem (
    id = 'lookout.lookout', 
    item = Item(
        text = st['objects']['lookout'],
        width = 20, 
        height = 47, 
        offset= [-10,0],
        walkto = [134, 36], 
        dir = 'w',
        actions = {
            'look': ssc.say(lines=[st['dialogues']['lookout'][50]]),
            'talkto': ssc.startDialogue('lookout')
        }))

d = Dialogue('lookout')

def f():
    print ('cane!')

def g(n):
    def f():
        s = Script()
        l = None
        if var.talked_to_lookout>00:
            l = [sl[5], sl[43], sl[53]]
            #dl = State.getDialogue('lookout')
            #dl.lines[6].active = False
            #dl.lines[7].active = False
        else:
            l = [sl[5], sl[6], sl[7], sl[8], sl[9]]
        var.talked_to_lookout +=1    
        s.addAction (sa.Say(lines = [sl[n]], tag='player'))
        s.addAction (sa.Turn(tag='lookout.lookout', dir='s'))
        s.addAction (sa.Say(tag='lookout.lookout', lines = l))
        return s
    return f

def dialogue_helper(s, *args):
    def f():
        script = Script()
        for b in args:
            lines = []
            for c in b[1:]:
                lines.append(s[c])
            script.addAction(sa.Say(lines=lines, tag=b[0]))
        return script
    return f

def lookoutTurn(n):
    def f():
        s = Script()
        s.addAction(sa.Say(tag="player", lines = [sl[n]]))
        s.addAction(sa.Turn(tag='lookout.lookout', dir='e'))
        s.addAction(sa.Say(tag="lookout.lookout", lines = [sl[15], sl[16]]))
        return s
    return f

def squinky():
    if d.nodes['imguy'].status == NodeStatus.CLOSED:
        return dialogue_helper(sl, ['player', 11], ['lookout.lookout', 27], ['player',28], ['lookout.lookout', 29])()        
    else:
        return dialogue_helper(sl, ['player', 11], ['lookout.lookout', 41])()        

def start(self):
    return
    #self.lines[8].active=True
    #self.lines[14].active=True

def end(self):
    s = Script()
    s.addAction(sa.Turn(tag='lookout.lookout', dir='w'))
    example.play(s)
    
import types
d.onStart = types.MethodType( start, d )
d.onEnd = types.MethodType( end, d )

d.addNode (DialogueNode ('init', lines = [
    Line (sl[1], g(1)),
    Line (sl[2], g(2)),
    Line (sl[3], g(3)),
    Line (sl[4], g(4))
], status = NodeStatus.ACTIVE, nextStatus= NodeStatus.ACTIVE, resume= True))

d.addNode (DialogueNode (
    'imguy', 
    lines = [ Line(sl[10], dialogue_helper(sl, ['player', 10, 17], ['lookout.lookout', 18, 19, 20, 21])) ],
    status = NodeStatus.ACTIVE,
    nextStatus = NodeStatus.CLOSED,
    resume=True,
    active = lambda: var.talked_to_lookout == 1 ))

d.addNode (DialogueNode (
    'squinky',
    lines = [ Line(sl[11], squinky, 2)],
    status = NodeStatus.ACTIVE,
    nextStatus= NodeStatus.CLOSED,
    resume=True,
    active = lambda: var.talked_to_lookout==1
))

d.addNode (DialogueNode (
    'THR', 
    lines = [ Line(sl[47], dialogue_helper(sl, ['player', 47], ['lookout.lookout', 49])) ],
    status = NodeStatus.ACTIVE,
    nextStatus = NodeStatus.ACTIVE,
    resume=True,
    active = lambda: var.talked_to_lookout > 1 ))

d.addNode (DialogueNode (
    'exit', 
    lines = [ Line(sl[14], dialogue_helper(sl, ['player', 14], ['lookout.lookout', 42]), 100) ],
    status = NodeStatus.ACTIVE,
    nextStatus = NodeStatus.ACTIVE,
    resume=False))

d.addNode (DialogueNode (
    'whatswrong', 
    lines = [ Line(sl[22], dialogue_helper(sl, ['player', 22], ['lookout.lookout', 23,24,25,26]), 3) ],
    status = NodeStatus.ACTIVE,
    nextStatus = NodeStatus.CLOSED,
    resume=True))

d.addNode (DialogueNode (
    'whoru', 
    lines = [ Line(sl[13], dialogue_helper(sl, ['player', 13], ['lookout.lookout', 30, 31, 32]),4) ],
    status = NodeStatus.ACTIVE,
    nextStatus = NodeStatus.OPEN,
    resume = True,
    closeNodes=['imguy', 'squinky']))

d.addNode (DialogueNode (
    'whyexp', 
    lines = [ Line(sl[34], dialogue_helper(sl, ['player', 34], ['lookout.lookout', 35, 36, 37])) ],
    status = NodeStatus.ACTIVE,
    nextStatus = NodeStatus.CLOSED,
    resume = True))

d.addNode (DialogueNode (
    'bat', 
    lines = [ Line(sl[38], dialogue_helper(sl, ['player', 38], ['lookout.lookout', 39, 40])) ],
    status = NodeStatus.ACTIVE,
    nextStatus = NodeStatus.CLOSED,
    resume = True))

d.addNode (DialogueNode (
    'imoverhere', 
    lines = [ Line(sl[12], lookoutTurn(12), 3) ],
    status = NodeStatus.ACTIVE,
    nextStatus = NodeStatus.ACTIVE,
    resume = True))


d.addEdge('init', 'imguy')
d.addEdge('init', 'squinky')
d.addEdge('init', 'THR')
d.addEdge('init', 'imoverhere')
d.addEdge('init', 'whoru')
d.addEdge('whoru', 'whyexp')
d.addEdge('whoru', 'bat')
d.addEdge('init', 'exit')
d.addEdge('imguy', 'whatswrong')
# d.addLine (1, 0, DialogueLine(sl[1], g(1), 1))
# d.addLine (2, 0, DialogueLine(sl[2], g(2), 1))
# d.addLine (3, 0, DialogueLine(sl[3], g(3), 1))
# d.addLine (4, 0, DialogueLine(sl[4], g(4), 1))
# # I'm Guybrush
# d.addLine (6, 1, DialogueLine(sl[10], dialogue_helper(sl, ['player', 10, 17], ['lookout.lookout', 18, 19, 20, 21]), 1, deact=[6]))
# # THREEPWOOD
# #d.addLine (15, 1, DialogueLine(sl[47],))
# # what's wrong with GT?
# d.addLine (11, 1, DialogueLine(sl[22], dialogue_helper(sl, ['player', 22], ['lookout.lookout', 23, 24, 25, 26]), 1, deact = [11], active = False))
# d.addLine (7, 1, DialogueLine(sl[11], dialogue_helper(sl, ['player', 11], ['lookout.lookout', 41]), True, 1))
# d.addLine (8, 1, DialogueLine(sl[12], lookoutTurn(12), True, 1))
# # whoa re YOU
# d.addLine (9, 1, DialogueLine(sl[13], dialogue_helper(sl, ['player', 13], ['lookout.lookout', 30, 31, 32]), 1, act =[] True, 2))
# d.addLine (10, 1, DialogueLine(sl[14], dialogue_helper(sl, ['player', 14], ['lookout.lookout', 42]), False, -1))
# d.addLine (12, 2, DialogueLine(sl[34], dialogue_helper(sl, ['player', 34], ['lookout.lookout', 35, 36, 37]), True, 2))
# d.addLine (13, 2, DialogueLine(sl[38], dialogue_helper(sl, ['player', 38], ['lookout.lookout', 39, 40]), True, 2))
# d.addLine (14, 2, DialogueLine(sl[52], lookoutTurn(52), True, 2))
# d.addToGroup (10, 2)

State.addDialogue (d)
