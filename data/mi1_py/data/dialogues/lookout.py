from lib_py.scumm.dialogue import Dialogue, NodeStatus, DialogueNode, Line
from lib_py.script import Script
from lib_py.scumm.scumm import State
import lib_py.engine as engine
import mi1_py.variables as var
import lib_py.scumm.actions as sa
import example

st = engine.data['strings']
sl = st['dialogues']['lookout']
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

State.addDialogue (d)
