import example
from lib_py.script import Script
from lib_py.actions import Delay,SetState,Move,CallFunc, ChangeRoom
from lib_py.entity import Sprite
from lib_py.components import SmartCollider, Info, StateMachine, Controller2D, Dynamics2D, Bounce, GarbageCollect
from lib_py.platformer.components import Jump
import smb_py.vars as vars
import funcs as func

def _fire(a: example.Wrap1, state: str):
    if vars.state >= 2:
        a.setState(state, {})
        b = Sprite (model='fire',pos=[a.x + (-2 if a.flipx else 2),a.y+16,0])        
        b.flipx = a.flipx
        b.addComponent (Controller2D(
            maskUp = vars.flags.platform, 
            maskDown = vars.flags.platform | vars.flags.platform_passthrough, 
            maxClimbAngle = 80, 
            maxDescendAngle = 80))
        b.addComponent (GarbageCollect(10))
        b.addComponent (Dynamics2D(gravity= vars.gravity))        
        b.addComponent (SmartCollider(flag=vars.flags.player_attack, mask= vars.flags.foe|vars.flags.platform, tag=vars.tags.player_fire))   
        sm = StateMachine (initialState='jmp')
        sm.states.append (Bounce (id='jmp', speed=300, a =0, b=200))
        b.addComponent(sm)
        id = example.get('main').add(b)

def fire(a : example.Wrap1):
    _fire(a, 'attack1')

def firej(a : example.Wrap1):
    _fire(a, 'attack2')

        #c = Script()
        #c.addAction (act.MoveAccelerated (v0=[-300 if a.flipx else 300, 0], a=[0,vars.gravity], yStop = -100, id = id))
        #c.addAction (act.RemoveEntity (id=id))
        #example.play(c)


def enterPipe (a: example.Wrap1):
    if not vars.paused and vars.currentWarp != -1:
        a.setState('pipe', {})
        info = example.getById(vars.currentWarp).getInfo()
        s = Script()
        s.addAction (Move(speed=100,by=[0,-64], tag='player'))
        s.addAction (CallFunc (f = func.gotoWorld (info['world'], info['start'])))
        example.play(s)
        
def cippo():
    print ('ciappo')
    example.get('w1').setActive(False)
    s = Script()
    s.addAction (SetState(tag='player', state='pipe'))
    s.addAction (Move(tag='player', speed=50, by=[0,64]))
    s.addAction (SetState(tag='player', state='walk'))
    example.play(s)


def pickupCoin(p,k,x,y):
    example.remove(k.id)
    vars.coins += 1
    example.get('coin_label').setText ('{:02d}'.format(vars.coins))

def pipe_out(p : example.Wrap1,k,x,y):
    p.setState ('demo', {'left':0})
    addInfo = k.getInfo()['info']
    s = Script()
    from smb_py.funcs import gotoWorld
    s.addAction(Delay(sec=0.5))
    s.addAction (CallFunc (gotoWorld(addInfo['world'], addInfo['pos'])))
    example.play(s)

def dead(p:example.Wrap1, k,x,y):
    p.setModel(vars.stateInfo[0])
    vars.state = 0
    func.downgradePlayer()

def winSlide(p:example.Wrap1,k,x,y):
    example.remove(k.id)
    p.setState('slide',{})
    s = Script()
    p.vy = 0
    s.addAction (Move(speed=50, to=[p.x, 48], tag='player'))   
    s.addAction (SetState (tag='player', state='demo', args={'left': 0}))
    example.play(s) 

def gotoNext(p:example.Wrap1,k: example.Wrap1,x,y):
    #print (k.getInfo())
    addInfo = k.getInfo()['info']
    #print('world is ' + ['world'])
    example.remove(k.id)
    p.setActive(False)
    s = Script()
    from smb_py.funcs import gotoWorld
    s.addAction(Delay(sec=0.5))
    s.addAction (CallFunc (gotoWorld(addInfo['world'], addInfo['pos'])))
    example.play(s)
